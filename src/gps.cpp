#include "gps.h"

SFE_UBLOX_GNSS myGNSS;

void GPS_init()
{

  Serial.println("SparkFun u-blox Example");

  //Assume that the U-Blox GNSS is running at 9600 baud (the default) or at 38400 baud.
  //Loop until we're in sync and then ensure it's at 38400 baud.
    Serial.println("SparkFun u-blox Example");

  //Assume that the U-Blox GNSS is running at 9600 baud (the default) or at 38400 baud.
  //Loop until we're in sync and then ensure it's at 38400 baud.
  do {
    
    Serial.println("GNSS: trying 38400 baud");
    Serial2.begin(38400, SERIAL_8N1, U1_RX, U1_TX);
    if (myGNSS.begin(Serial2) == true) break;

    delay(100);
    Serial.println("GNSS: trying 9600 baud");
    Serial2.begin(9600);
    if (myGNSS.begin(Serial2) == true) {
        Serial.println("GNSS: connected at 9600 baud, switching to 38400");
        myGNSS.setSerialRate(38400);
        delay(100);
    } else {
        //myGNSS.factoryReset();
        delay(2000); //Wait a bit before trying again to limit the Serial output
    }
  } while(1);
  Serial.println("GNSS serial connected");

  myGNSS.setUART1Output(COM_TYPE_UBX); //Set the UART port to output UBX only
  
}

void GPS_poll()
{
  // Request (poll) the position, velocity and time (PVT) information.
  // The module only responds when a new position is available. Default is once per second.
  // getPVT() returns true when new data is received.
  if (myGNSS.getPVT() == true)
  {
    int32_t latitude = myGNSS.getLatitude();
    Serial.print(F("Lat: "));
    Serial.print(latitude);

    int32_t longitude = myGNSS.getLongitude();
    Serial.print(F(" Long: "));
    Serial.print(longitude);
    Serial.print(F(" (degrees * 10^-7)"));

    int32_t altitude = myGNSS.getAltitudeMSL(); // Altitude above Mean Sea Level
    Serial.print(F(" Alt: "));
    Serial.print(altitude);
    Serial.print(F(" (mm)"));

    Serial.println();
  }
}

//TODO
//add GPS satellites recieved
//configure GPS data to a callback instead of poll
//create GPS packet

//USE
//use the callback nav sat 
//use the callback in the data loop 
//use callback nav_pvt (how to setup signal strength data)
//position-velocity-time-callback (how to setup callback for PVT data)
