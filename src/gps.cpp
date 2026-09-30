#include "gps.h"

SFE_UBLOX_GNSS_SERIAL myGNSS;

void GPS_init()
{

  Serial.println("SparkFun u-blox Example");

  Serial2.begin(38400, U1_RX, U1_TX); // u-blox F9 and M10 modules default to 38400 baud. Change this if required

  //myGNSS.enableDebugging(); // Uncomment this line to enable helpful debug messages on Serial

  myGNSS.connectedToUART2(); // This tells the library we are connecting to UART2 so it uses the correct configuration keys

  while (myGNSS.begin(mySerial) == false) //Connect to the u-blox module using mySerial (defined above)
  {
    Serial.println(F("u-blox GNSS not detected"));
    
    Serial.println(F("Attempting to enable the UBX protocol for output"));
    
    myGNSS.setUART2Output(COM_TYPE_UBX); // Enable UBX output. Disable NMEA output
    
    Serial.println(F("Retrying..."));
    delay (1000);
  }

  //myGNSS.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT); //Optional: save (only) the communications port settings to flash and BBR
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
