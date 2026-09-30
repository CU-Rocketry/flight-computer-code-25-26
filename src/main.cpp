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

  //initilie all peripherals 
  
  imu_init();
  baro_init();

  GPS_init();

  buzzer_init(&buzzer);

  rgb_init(&rgb);
  rgb_set_color(&rgb, 0x800080); //set led to purple 

  btn_init(&btn0);
  
  
 
}


void loop(){


  imu_callback();
  baro_callback();
  GPS_poll();

  buzzer_update(&buzzer);

  boolean btn_value = 0;
  get_btn(&btn0, btn_value);

  if ( btn_value == 1) {

  rgb_set_color(&rgb, 0x008000);
  buzzer_play_tone(&buzzer, 2000);

  } else if (btn_value == 0){

    buzzer_play_tone(&buzzer, 0);
    rgb_set_color(&rgb, 0xFF0000);

  }
  

  
  
}