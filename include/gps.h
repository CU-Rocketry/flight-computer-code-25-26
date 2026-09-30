#include "Arduino.h"
#include "main.h"
#include <SparkFun_u-blox_GNSS_v3.h>


extern SFE_UBLOX_GNSS_SERIAL myGNSS;

#define mySerial Serial2 // Use Serial1 to connect to the GNSS module. Change this if required

void GPS_init(void);
void GPS_poll(void);