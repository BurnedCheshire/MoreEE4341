/*
** RWTest.c
**
*/
// configuration bit settings, Fcy=72 MHz, Fpb=36 MHz

#pragma config POSCMOD=XT, FNOSC=PRIPLL
#pragma config FPLLIDIV=DIV_2, FPLLMUL=MUL_18, FPLLODIV=DIV_1
#pragma config FPBDIV=DIV_2, FWDTEN=OFF, CP=OFF, BWP=OFF

#include "SDMMC.h"
#include <stdio.h>
#include <string.h>
#include <xc.h>
#include "uart1_setup.h"

#define START_ADDRESS 10000 // start block address
#define N_BLOCKS 10 // number of blocks 

#define LED3 _RD2  // visual feedback about SD usage status - fail
#define LED2 _RD1  // visual feedback about SD usage status - pass

void system_reg_unlock(void);
void system_reg_lock(void);
void delay(int);

void system_reg_unlock(void)
{
    SYSKEY = 0x12345678;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
}

void system_reg_lock(void)
{
    SYSKEY = 0x00000000; 
}

void delay(int ms)
{
    int i, j;
	for( i = 0; i < ms; i++)
    {
        for(j = 0; j < 9996; j++)
        {
            asm("NOP");
        }
    }
}

int main(void){

    system_reg_unlock();            // unlock PPS
    CFGCONbits.IOLOCK = 0;
    
    U1RXRbits.U1RXR = 0b0010;
        //UART receive bits peripheral
    RPF5Rbits.RPF5R = 0b0011;
        //sets the pin to peripheral UART tx
    
    SDI1Rbits.SDI1R = 0b1010;  // map RC4 to SDI1
   
    RPD9Rbits.RPD9R = 0b0111; // map SS1 to RD9
    RPD0Rbits.RPD0R = 0b1000; // map SDO1 to RD0
    
    CFGCONbits.IOLOCK = 1;
    system_reg_lock();            // lock PPS
        
    uart1_setup();
    
    // set RD1 and RD2 as outputs:

    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD1 = 0;
    
    TRISFbits.TRISF5 = 1;
    
    LED3 = 0;
    LED2 = 0;

    LBA addr;
    int i, j, r;
    
    initData();     // 1. initialize data
    initSD();       // 2. initialize SD/MMC module

    printf("\n\nWe got to checkpoint A\n\r");
    
    // 3. fill the buffer with pattern
    for(i=0; i < B_SIZE; i++)
    {
        data[i] = i;
    }
    
    // 4. wait for the card to be inserted
    
    while(!getCD()){};
//    delay(100);
    int x;
    
    x = initMedia();
    if(x) //init card
    {
        printf("Error on CD, %i\n\r", x);
        goto End;
    }//if error code returned
    
    // 5. fill 16 groups of N_BLOCK sectors with data

//    LED2 = 1;       //visual confirmation that SD card currently in use

    addr = START_ADDRESS;

    for(i = 0; i < 16; i++)
    {
        for(j=0; j < N_BLOCKS; j++)
        {
            if(!writeSECTOR(addr+j*i, data))
            {
                printf("Writing failed. \n\r");
                goto End;
            }//writing failed
        }// j inc
    }// i inc
    
    // 6. verify the contents of each sector written

   addr = START_ADDRESS;
	
   for(i = 0; i < 16; i++)
    {
        for(j=0; j < N_BLOCKS; j++)
        {
            if(!readSECTOR(addr+(j*i), data))	//reading one block at a time
            {
                printf("Reading1 Sect failed. \n\r");
                goto End;
            }//reading failed

            if(memcmp(data, buffer, B_SIZE))	//verifying each block
    		{
        		printf("Verify contents failed \n\r");
        		goto End;
    		}//data mismatch
  
        }// j inc
    }// i inc
    
    // 7. indicate successful execution
    printf("Successful execution \n\r");
    LED3 = 1;
    LED2 = 0;
    
    // main loop
    while(1){};

    // If this is reached --> failure   
    End:
        LED2 = 1;
        LED3 = 0;
        printf("BAD END\n\r");
        // main loop
        while(1){};
    
    return 0;
}