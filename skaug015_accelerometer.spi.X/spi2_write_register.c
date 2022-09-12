/* ************************************************************************** */
/** spi2_write_register.c

  @Description
    Send data to SPI buffer.
 */
/* ************************************************************************** */

#include "accel_define.h"       // Some #define statements in this file might be used 
#include "io_setup.h"

void spi2_write_register(uint8_t address, uint8_t data)
{   
    uint16_t write_frame;
    uint16_t trash;
    
    write_frame = ((uint16_t)address << 8) | data;
            
    delay(1);
    
    ACCEL_CS = 0;
    // enable accelerometer chip select
    //0 -> because we have high idle and low active

    SPI2BUF = write_frame;
    // send "write_frame" to the SPI2 receive buffer                     
    
    while(SPI2STATbits.SPIRBF == 0){}
    // wait for the SPI2 receiver buffer full flag bit
    //make sure it has all of the information we were sending to it
    
    trash = SPI2BUF;
    // clear SPI2 buffer using the "trash" variable
    //removes elements from the buffer when it is saved to
    //another variable, hence we are "moving" the data from the
    //buffer into the trash
    
    ACCEL_CS = 1;
    // disable accelerometer chip select
    //1 -> because we have high idle and low active
}


/* *****************************************************************************
 End of File
 */
