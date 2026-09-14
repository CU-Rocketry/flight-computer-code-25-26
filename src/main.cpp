#include <Arduino.h>
#include "lsm6dsv80x_reg.h"
#include "driver_w25qxx.h"
#include <Wire.h>
#include <SPI.h>
#include "lps22hh_reg.h"
#include <LPS22HHSensor.h>
#include "main.h"

#define esp32dev

w25qxx_handle_t flash; // creating stm class

int button_input;
int sense_1;



int CS;


// Flash platform functions
int32_t platform_write_flash(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len);
int32_t platform_read_flash(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);


void setup() {



      // Baro Setup
    
    

  // Initlialize baro 
  Wire.begin();
  
}



  

//     uint64_t read2;
//     //Checking Flash WhoAmI
//   SPI_2->beginTransaction(SPISettings(speedMaximum, MSBFIRST, SPI_MODE0));
//     digitalWrite(FLASH_CS, LOW);
//     SPI_2->transfer(144 | 0x24 ); // Flash_reg = 90h = 144
//     read2 = SPI_2->transfer(0x00);
//     SPI_2->endTransaction();

//     digitalWrite(FLASH_CS, HIGH);

//     Serial.println(read2);

//     if (read2 != 115) {
//       Serial.println("Flash not found.");
//     };

//     // Flash driver example code

//     uint8_t res;
// uint8_t manufacturer;
// uint8_t device_id;
// uint8_t data[8];

// res = w25qxx_get_manufacturer_device_id(&flash, &manufacturer, &device_id);
// if (res != 0)
// {
//  Serial.println("Flash not found :(");
// };



void loop() {
  // put your main code here, to run repeatedly:


  Serial.print("Loop:");

  //constants

  // Baro test

  // print an empty line


  // gyroscope
  // lsm6dsv80x_data_ready_t drdy;


 
  //Pyro test code

  // button_input = !digitalRead(2);
  // sense_1 = analogRead(13);
  // if (button_input){
  //   digitalWrite(5, LOW);
  //   digitalWrite(16, HIGH);
  // } else {
  //   digitalWrite(5, HIGH);
  //   digitalWrite(16, LOW);
  // }

  // Serial.println(sense_1);
  
}

//Function definitions


// int32_t platform_read_flash(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
// {
//   int i;

//   uint8_t dataRead;
//   // uint8_t *data[len];
//   for (int i = 0; i < len; i++)
//   {

    
    
//     SPI_2->beginTransaction(SPISettings(speedMaximum, MSBFIRST, SPI_MODE3));

//     digitalWrite(FLASH_CS, LOW);

//     SPI_2->transfer(reg | 0x80);
//     dataRead = SPI_2->transfer(0x00);
//     SPI_2->endTransaction();

//     digitalWrite(FLASH_CS, HIGH);

//     bufp[i] = dataRead;

//     reg = reg + 1;

//     }
  
//   return 0;
// }


// int32_t platform_write_flash(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len)
// {

//   uint8_t dataWrite;

//   SPI_2->beginTransaction(SPISettings(speedMaximum, MSBFIRST, SPI_MODE3));
//   digitalWrite(FLASH_CS, LOW);
//   SPI_2->transfer(reg | 0);
//   SPI_2->transfer(*bufp);
//   SPI_2->endTransaction();
//   digitalWrite(FLASH_CS, HIGH);

//   return 0;
// }