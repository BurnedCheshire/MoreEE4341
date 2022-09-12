/* ************************************************************************** */
/** skaug015_main.c

  @Description
    Main file for the accelerometer demo n schtuff
 
 */
/* ************************************************************************** */

#include "io_setup.h"
#include "skaug015_accelerometer_spi.h"
#include <stdio.h>
#include "accel_define.h"
#include "uart1_setup.h"

void setup();
void demoButtons();
void test_accel();
void accel_print_data(char);
void accel_move_cursor();

int main(void)
{
    setup();
    delay(100);                  // 100 ms delay as precaution

    while(1)
    {
        //test_accel();
        //delay(50);
        demoButtons();
    }

    return 0;
}

void demoButtons(void)
{
    // Include code for debouncing every time a button is pressed
    // BUTTONs are pulled-up, so poll for low state
        
    if (!BUTTON1)
    {
        delay(20);
            //20ms delay for debounce, it then double checks
        if(!BUTTON1)
        {
            printf("X axis:");
            accel_print_data('x');
            button_on(1);
        }
    }
    else
    {
        button_off(1);
    }
    
    if (!BUTTON2)
    {
        delay(20);
        if(!BUTTON2)
        {
            printf("Y axis:");
            accel_print_data('y');
            button_on(2);
        }
    }
    else
    {
        button_off(2);
    }
    
    if (!BUTTON3)
    {
        delay(20);
        if(!BUTTON3)
        {
            puts("\033[3B");
            //accel_move_cursor();
            button_on(3);
        }
    }
    else
    {
        button_off(3);
    } 
}

void setup(void)
{   
    io_setup();
    uart1_setup();
    spi2_setup();
    accel_setup();
    // include any other setup functions here
}

void test_accel(void)
{   
    putchar(' ');
    
    
    int16_t test = spi2_read_register(0x0F);  // read WHO_AM_I register
    
    if (test == 0x0033)
    {
        printf("Pass");
    }
    else
    {
        printf("Fail");
    }
}

void accel_print_data(char axis)
{
    float data;
    
    if (axis == 'x')
    {
        data = accel_read_x();
    }
    else if (axis == 'y')
    {
        data = accel_read_y();
    }
    else if (axis == 'z')
    {
        data = accel_read_z();
    }
    
    char buffer[50]; 
    sprintf(buffer, "%f", data); 
    printf("%s \r\n", buffer);
}

void accel_move_cursor(void)
{
    if (accel_read_x() > 0.4)
    {
        putchar(' ');
    }
    else if (accel_read_x() < -0.4)
    {
        putchar(0x8);
    }
    
}



/* *****************************************************************************
 End of File
 */
