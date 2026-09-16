#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "main.h"
#include "sensors.h"



void setup(){

  imu_init();
  baro_init();

 
}


void loop(){


  imu_callback();
  baro_callback();
  
}