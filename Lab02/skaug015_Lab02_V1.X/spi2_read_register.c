/* ************************************************************************** */
/** spir2_read_register.c

  @Description
    Read data from SPI2 buffer.
 */
/* ************************************************************************** */

#include "accel_define.h"       // Some #define statements in this file might be used
#include "io_setup.h"
#include "uart1_setup.h"

int16_t spi2_read_register(uint8_t address)
{
    uint16_t read_frame;
    uint16_t value;
    
    read_frame = (((uint16_t)address|0x80) << 8) | 0x00;

    delay(1);

    ACCEL_CS = 0;
    // enable accelerometer chip select
    // 0 -> Active low, idle high
    
    SPI2BUF = read_frame;
    //sends the "read_frame" data to the SPI2 buffer
    while(SPI2STATbits.SPIRBF == 0){}
    //waits for the SPI2BUF to fill
    
    //SPI2STATbits.SPIROV = 0;
    //Clears the overflow bit
    
    value = SPI2BUF;
    //reads the value in from the SPI2BUF
   
    ACCEL_CS = 1;
    // disable accelerometer chip select
    // 1-> active low, idle high
    
    return value;
}


/* *****************************************************************************
 End of File
 */
