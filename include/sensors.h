//sensor function definitions

#include <Arduino.h>
#include "lsm6dsv80x_reg.h"
#include <Wire.h>
#include <SPI.h>
#include "main.h"



// Setup SPI 
SPIClass *SPI_2 = NULL;
SPIClass *SPI_3 = NULL;
const int dataOrder = MSBFIRST;
const int speedMaximum = 1000000;

uint8_t tx_buffer[1000]; //buffer variable
void platform_delay(uint32_t ms);

//setup baro 
int LPS22HH_I2C_SDA = I2C_SDA;
int LPS22HH_I2C_SCL = I2C_SCL;

void baro_i2c_callback(void);
void mag_spi_callback(void);
void imu_spi_callback(void);

void baro_init(void);
void mag_init(void);
void imu_init(void);
void sensors_init(void);

// IMU platform functions
int32_t platform_write_imu(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len);
int32_t platform_read_imu(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);

