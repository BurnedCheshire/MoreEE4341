/* ************************************************************************** */
/** uart1_setup.c

  @Description
    Sets up UART1 with a baud rate of 9600.
 
 */
/* ************************************************************************** */

#include <xc.h>
#include "uart1_setup.h"

void uart1_setup(void)
{   
    U1MODEbits.ON = 0;
    //off when changing settings for safety
    
    U1MODEbits.BRGH = 0;    //BR high mode off, standard speed mode
    
    U1MODEbits.UEN = 00;    //UxTX & UxRX pins are enabled and used; rest
                       //controlled by corresponding bits in the PORTx register
    
    U1MODEbits.PDSEL = 00;
    //8 bit, no parity
        
    U1BRG = 259;
    //Calculated BR = 9615, goal: 9600, leaves a 0.16% error
    
    U1STAbits.URXEN = 1;
    U1STAbits.UTXEN = 1;
    //Enable both transmit and receiver

    U1MODEbits.ON = 1;
    //Enable UART (ON bit)
    __XC_UART = 1;              // Code is configured to use UART1 for printf()
}

/* *****************************************************************************
 End of File
 */