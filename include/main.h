// Pin Definitions //

//TODO: Update to match schematic

//GPS 
#define GPS_TP 21
#define GPS_EXTINT 3
#define GPS_RESET   14

//GPS Serial
#define U1_TX  17
#define U1_RX  18

// Additional Peripherals
#define BUZZER 1

#define BUTT_0 2

#define STATUS_B  5
#define STATUS_G  6
#define STATUS_R  7

//SPI 2
#define IMU_CS 9
#define IMU_INT   37

#define FLASH_CS  10

#define MISO_2  11
#define SPI_CLK_2  12
#define MOSI_2 13

//SPI 3 
#define MOSI_3  38
#define MISO_3 39
#define SPI_CLK_3 41

//Telemetry
#define TELE_CS 40
#define TELE_INT  35
#define TELE_RST  42
 

//PYRO
#define SENSE_1 2 //GPIO2 ADC1_CH1
#define SENSE_2  4 //GPIO4 ADC1_CH3

#define PYRO_1 16
#define PYRO_2 15

//i2c baro
#define BARO_INT 36

#define I2C_SDA 47
#define I2C_SCL 48