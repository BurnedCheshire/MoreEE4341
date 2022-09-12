/* ************************************************************************** */
/** accel_read_z.c

  @Description
    Read the Z-axis data from the LIS3DH accelerometer.
 */
/* ************************************************************************** */

#include "accel_define.h"       // Some #define statements in this file might be used 
#include "skaug015_accelerometer_spi.h"


float accel_read_z(void)
{
   int16_t Z_H; 
   int16_t Z_L; 
   int16_t Z;
   
   Z_H = spi2_read_register(OUT_Z_H);
   Z_L = spi2_read_register(OUT_Z_L);
   
   Z_H = Z_H & 0b0000000011111111;
   Z_H = Z_H << 8;
   Z = Z_H | Z_L;
   
   // Combine data from both registers
   
   float value = Z * 0.000061;            // Convert to units of g
   return value;
}


/* *****************************************************************************
 End of File
 */
