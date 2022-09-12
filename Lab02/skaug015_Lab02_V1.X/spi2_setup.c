/* ************************************************************************** */
/** spi2_setup.c

  @Description
    Setup SPI2 peripheral.
 */
/* ************************************************************************** */

#include "accel_define.h"           // Some #define statements in this file might be used 

void spi2_setup(void)
{
    TRISGbits.TRISG6 = 0;	    // set serial clock as an output
    TRISGbits.TRISG9 = 0;	    // set Accelerometer Chip Select as an output
    
    ACCEL_CS = 1;
    // disable chip select "ACCEL_CS"
    
    SPI2CON = 0;    
    SPI2CON2 = 0;
    // clear SPI2CON registers
    
    SPI2BUF = 0;
    // clear SPI2BUF register

    SPI2BRG = 511;
    //BR of 39,060Hz
    
    SPI2STATbits.SPIROV = 0;
    // clear overflow flag in SPI2STAT register
    
    SPI2CONbits.FRMEN = 0;
    // framed support off    
    
    SPI2CONbits.MODE16 = 1;
    // 16 bit communication
    SPI2CONbits.MODE32 = 0;
    //turns off 32bit just to be sure
    
    SPI2CONbits.CKE = 0;
    //Serial output data changes on transition from active to idle clk state
    //Our idle is set to high
    
                      // Look at the pictures on pages 4-5 in LAB2 manual 
                          // Very important to know how to figure these out
    SPI2CONbits.CKP = 1;
    //sets it so that the idle state for the clk is high, and active is low
    
    SPI2CONbits.MSTEN = 1;
    // master mode
    
    SPI2CONbits.SMP = 1;
    // sample data at the end of clock time
    
    SPI2CONbits.ON = 1;
    // enable SPI2 (ON)

}


/* *****************************************************************************
 End of File
 */
