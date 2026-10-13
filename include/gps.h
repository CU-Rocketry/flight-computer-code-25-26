#include "Arduino.h"
#include "main.h"
#include "SparkFun_u-blox_GNSS_Arduino_Library.h"
#include "HardwareSerial.h"


extern SFE_UBLOX_GNSS myGNSS;

typedef struct {

    uint8_t GPS_RX;
    uint8_t GPS_TX;
    long latitude;
    long longitude;
    long altitude;
    byte satellites;

} gps_t;

void GPS_init(void);
void GPS_poll(void);