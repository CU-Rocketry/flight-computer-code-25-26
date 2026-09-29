#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "main.h"
#include "sensors.h"
#include "gps.h"
#include "buzzer.h"
#include "rgb.h"

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

rgb_led rgb { 

  .channel_r = STATUS_R,
	.channel_g = STATUS_G,
	.channel_b = STATUS_B,

	.tim_channel_r = 1,
	.tim_channel_g = 2,
	.tim_channel_b = 3,

};

void setup(){

  imu_init();
  baro_init();
  GPS_init();
  buzzer_init(&buzzer);

 
}


void loop(){


  imu_callback();
  baro_callback();
  GPS_poll();

  buzzer_update(&buzzer);
  
}