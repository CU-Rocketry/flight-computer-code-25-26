#include "gps.h"

SFE_UBLOX_GNSS myGNSS;

void GPS_init(gps_t *GPS)
{
  //Assume that the U-Blox GNSS is running at 9600 baud (the default) or at 38400 baud.
  //Loop until we're in sync and then ensure it's at 38400 baud.
  do {
    
    Serial.println("GNSS: trying 9600 baud");
    
    //use serial 2 for all GPS work
    Serial2.begin(9600, SERIAL_8N1, GPS->GPS_TX, GPS->GPS_RX); 
    if (myGNSS.begin(Serial2) == true) break;

  } while(1);
  Serial.println("GNSS serial connected");

  myGNSS.setUART1Output(COM_TYPE_UBX); //Set the UART port to output UBX only
  
}

void GPS_poll()
{
    // old printing code, save for use with Ground Station
    // long latitude = myGNSS.getLatitude();
    // Serial.print(F("Lat: "));
    // Serial.print(latitude);

    // long longitude = myGNSS.getLongitude();
    // Serial.print(F(" Long: "));
    // Serial.print(longitude);
    // Serial.print(F(" (degrees * 10^-7)"));

    // long altitude = myGNSS.getAltitude();
    // Serial.print(F(" Alt: "));
    // Serial.print(altitude);
    // Serial.print(F(" (mm)"));

    // byte SIV = myGNSS.getSIV();
    // Serial.print(F(" SIV: "));
    // Serial.print(SIV);

    // Serial.println();

  long latitude = myGNSS.getLatitude();
  long longitude = myGNSS.getLongitude();
  long altitude = myGNSS.getAltitude();
  byte satellites = myGNSS.getSIV();

}

//use callback nav_pvt (how to setup signal strength data)

