/*
** SDMMC.c SD card interface
*/
#include <xc.h>
#include "SDMMC.h"

// I/O definitions
// NOTE: Do not use the pins given
// by the MassStorage.pdf file. To find the 
// correct pinout, use the SDCardBoard and
// IO Expansion Board Information Sheet PDF's
// to map the pins to the top-right slot on the
// expansion board.
#define SDWP _RF1 // Write Protect input
#define SDCD _RF0 // Card Detect input
#define SDCS _RB1 // Card Select output


// Macros from reference file go here
#define readSPI() writeSPI(0xFF)
#define clockSPI() writeSPI(0xFF)

#define disableSD() SDCS = 1; clockSPI()
#define enableSD() SDCS = 0

// SD card commands from reference file go here

#define RESET           0       //GO_IDLE(CMD0)
#define INIT            1       //SEND_OP_COND(CMD1)
#define READ_SINGLE     17
#define WRITE_SINGLE    24

#define DATA_START      0xFE
#define DATA_ACCEPT     0x05

#define I_TIMEOUT 10000
#define R_TIMEOUT 25000
#define W_TIMEOUT 250000

void initSD(void)
{
    disableSD();            // disable SD Card for initialization
    _TRISB1 = 0;            //set the card select an output pin
    
    SPI1BRG = 71;           //clock = Fpb/144 = 250kHz
    SPI1CON = 0x8120;       //ON, CKE = 1, CKP = 0, Sample middle
    
//    enableSD();
} // initSD

unsigned char writeSPI(unsigned char byte){

    SPI1BUF = byte;                 //TX data buffer fill
    while(!SPI1STATbits.SPIRBF){}   //wait for TX to complete
    return SPI1BUF;                 //return the received value
}// write a byte using SPI

int sendSDCmd(unsigned char c, unsigned a, unsigned crc)
{

    int i, r;
    // enable SD card
    enableSD();
    // send a 6-byte command packet over SPI
    writeSPI(c | 0x40);     //send command
    writeSPI(a >> 24);      //MSB of address
    writeSPI(a >> 16);
    writeSPI(a >> 8);
    writeSPI(a);            //LSB
    
    writeSPI(0x95);         //send CMD0 CRC
    // read 8 bytes over SPI
    // if any byte is not 0xFF, return that byte
    for( i=0; i<8; i++)
    {
        r = readSPI();
        if (r != 0xFF)
        {
            break;
        }//if its returning something not our checkpoint
    }
    return r;
} // sendSDCmd

int initMedia(void){
    // Note: initMedia will return different values corresponding to error conditions
    // returns 0: if successful
    // return E_COMMAND_ACK: if failed to acknowledge reset command
    // return E_INIT_TIMEOUT: if failed to initialize

    int i, r;

    // 1. with the card NOT selected
    SDCS = 1;
    // 2. send 80 clock cycles start up
    for(i=0; i < 10; i++)
    {
        clockSPI();
    }
    
    // 3. now select the card
    enableSD();
    
    // 4. send a single RESET command, then disable SD, and
    // be sure to check if the command acknowledge failed
    r = sendSDCmd(RESET, 0, 0x00);
    disableSD();
    
    if(r != 1)                  //must return idle
    {
        printf("Command rejected. The r I got back is, %i\n\r", r);
        return E_COMMAND_ACK;   //command rejected
    }
    
    // 5. send repeatedly INIT until Idle terminates, and
    // be sure to check if the initialization failed due to timeout
    
    for(i=0; i < I_TIMEOUT; i++)
    {
        r = sendSDCmd(INIT, 0, 0x00);
        disableSD();
        if(!r)
        {
            break;
        }
    }
    if(i == I_TIMEOUT)
    {
        printf("Initialization timeout\n\r");
        return E_INIT_TIMEOUT;      //init timed out
    }
    
    // 6. increase speed: disable SPI first, change settings and re-enable

    SPI1CON = 0;        //disable SPI2 while configuring
    SPI1BRG = 1;        //Fpb/(2*(0 + 1)) = 36/2 = 18MHz
    SPI1CON = 0x8120;   //re-enable the SPI2 module
    
    return 0;
} // init media

/*
To avoid confusion, in the following we will uniformly use only LBAs or block
addresses, and we will obtain an actual byte address by multiplying the LBA value by
512 just before passing the parameter to the READ_SINGLE command. 
 */


int readSECTOR( LBA a, char *p)
{
    // 'a' LBA of sector requested
    // 'p' pointer to sector buffer
    // returns TRUE if successful

    int r, i;

    // 1. send READ command, and check if command was accepted
    r = sendSDCmd(READ_SINGLE, (a <<9), 0x00);
    if(r == 0)      //check if cmd was accepted
    {
        // 2. wait for a DATA_START response for some time (use R_TIMEOUT)
        for(i=0; i < R_TIMEOUT; i++)
        {
            r = readSPI();
            if(r == DATA_START)
                break;
        }
        // 3. if it did not timeout, read 512 byte of data
        if( i != R_TIMEOUT)
        {
            i = 512;
            do{
                *p++ = readSPI();
            }while(--i > 0);
            
            // 4. ignore CRC (read 2 bytes but do nothing with them)
            readSPI();
            readSPI();
        }//data arrived
    }//command accepted
    
    // 5. remember to disable the card, return TRUE if DATA_START was previously received, or
    // false otherwise.
    disableSD();
    
    return r == DATA_START;
} // readSECTOR

int writeSECTOR(LBA a, char *p)
{

    // a LBA of sector requested
    // p pointer to sector buffer
    // returns TRUE if successful, FAIL if not

    unsigned r, i;
    int FAIL = 5; // arbitrary number
    
    // 0. check Write Protect
    if(getWP())
    {
        return FAIL;
    }
    
    // 1. send WRITE command

    r = sendSDCmd(WRITE_SINGLE, (a <<9), 0x00);
    if(r == 0)
    {
        
        // 2. send data
        writeSPI(DATA_START);
        
        for( i = 0; i < 512; i++)
        {
            writeSPI(*p++);
        }
        
        // 3. send dummy CRC
        clockSPI();
        clockSPI();
        
        // 4. check if data accepted
        r = readSPI();
        if((r&0xf) == DATA_ACCEPT)
        {
            // 5. wait for write completion
            for(i = 0; i < W_TIMEOUT; i++)
            {
                r = readSPI();
                if(r != 0)
                {
                    break;
                }
            }
        }//accepted
        else
        {
            r = FAIL;
        }//failed
    }//command was accepted

    // 6. remember to disable the card and return TRUE/FALSE
    disableSD();
    
    return r;
    
} // writeSECTOR

/*
    When a card is inserted in the connector, the Card Detect switch is closed and the SDCD
input pin is pulled low. The getCD() function will allow us to detect the card ? s presence
by returning TRUE when the card is inserted and ready for use.
    Similarly, when the Write Protection tab on the card is not in the ? lock ? position and the
card is inserted, the Write Protect switch will close and the corresponding SDWP input pin
will be pulled low. 
 */


// SD card connector presence detection switch (1 line of code)
int getCD(void)
{
    return !SDCD;
}

// card Write Protect tab detection switch (1 line of code)
int getWP(void)
{
    return SDWP;
}

// The function below is used in the other .c file
void initData(void){
    int idx, b = 0;
    for (idx = 0; idx < B_SIZE; idx++) {
        data[idx] = b;
        b ^= 1;
    }
}
