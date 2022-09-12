/* ************************************************************************** */
/** x500_accelerometer_spi.h

  @Description
    Need this file to access functions from library.
 
 */
/* ************************************************************************** */

#ifndef _SKAUG015_ACCELEROMETER_SPI_H    /* Guard against multiple inclusion */
#define _SKAUG015_ACCELEROMETER_SPI_H 

//#include <xc.h>

void spi2_setup(void);
void spi2_write_register(uint8_t address, uint8_t data);
int16_t spi2_read_register(uint8_t address);
void accel_setup(void);               
float accel_read_x(void);
float accel_read_y(void);   
float accel_read_z(void);
//void delay(int ms);

#endif /* _SKAUG015_ACCELEROMETER_SPI_H  */

/* *****************************************************************************
 End of File
 */
