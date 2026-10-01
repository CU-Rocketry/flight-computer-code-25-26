#include "Arduino.h"
#include "main.h"
#include "SparkFun_u-blox_GNSS_Arduino_Library.h"
#include "HardwareSerial.h"


extern SFE_UBLOX_GNSS myGNSS;

void GPS_init(void);
void GPS_poll(void);