#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "main.h"
#include "sensors.h"
#include "gps.h"
#include "buzzer.h"
#include "rgb.h"
#include "btn.h"

buzzer_t buzzer {

  .tim_freq = 4000,

	// music player
	.seq = 0,
	.seq_len = 0,
	.seq_idx = 0,
	.beep_start = 0, // [ms] since boot (hal get tick)
	.seq_playing = 0,
  .pin = BUZZER,
  .tim_channel = 0,

};

btn_t btn0 {

  .pin = BUTT_0,

};

rgb_led rgb { 

  .channel_r = STATUS_R,
	.channel_g = STATUS_G,
	.channel_b = STATUS_B,

	.tim_channel_r = 1,
	.tim_channel_g = 2,
	.tim_channel_b = 3,

};

void setup(){

  delay(1000);
  //initilie all peripherals 
  Serial.begin(112500);
  Serial.println("Serial online");
  
  //imu_init();
  //baro_init();

  Serial.println("sensors initilized");

  GPS_init();

  Serial.println("GPS initilized");
  delay(10000);
  Serial.println("passed delay");

  buzzer_init(&buzzer);

  rgb_init(&rgb);
  rgb_set_color(&rgb, 0x800080); //set led to purple 

  btn_init(&btn0);

  Serial.println("peripherals initilized");
  
  
 
}


void loop(){


  Serial.println("Loop");
  delay(1000);

  GPS_poll();
  // imu_callback();
  // baro_callback();
  

  buzzer_update(&buzzer);

  int btn_value;
  get_btn(&btn0, btn_value);

  rgb_set_color(&rgb, 0x008000); 

  if ( btn_value == LOW) {

  rgb_set_color(&rgb, 0x008000);
  buzzer_play_tone(&buzzer, 2000);
  Serial.println("Button pressed");

  } else if (btn_value == HIGH){

    buzzer_play_tone(&buzzer, 0);
    rgb_set_color(&rgb, 0xFF0000);
    Serial.println("Button not pressed");

  }
  
  buzzer_play_tone(&buzzer, 2000);
  
  
}