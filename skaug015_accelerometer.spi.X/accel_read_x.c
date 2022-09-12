/* ************************************************************************** */
/** accel_read_x.c

  @Description
    Read X-axis data from the LIS3DH accelerometer.
 */
/* ************************************************************************** */

#include "accel_define.h"           // Some #define statements in this file might be used 
#include "skaug015_accelerometer_spi.h"

float accel_read_x(void)
{
   int16_t X_H; 
   int16_t X_L; 
   int16_t X;
   
   X_H = spi2_read_register(OUT_X_H);
   X_L = spi2_read_register(OUT_X_L);
   
   X_H = X_H & 0b0000000011111111;
   X_H = X_H << 8;
   X = X_H | X_L;
   
   // Combine data from both registers
   //Bitwise babyeee

   float value = X * 0.000061;            // Convert to units of g
   return value;
}


/* *****************************************************************************
 End of File
 */
