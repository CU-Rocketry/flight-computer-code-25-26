#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "main.h"
#include "sensors.h"
#include "gps.h"
#include "buzzer.h"
#include "rgb.h"
#include "btn.h"
#include "pyro.h"
#include "lora.h"
#include "batt_sense.h"

//HOLY INCLUDES GODDAMN

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

//setup pyros
pyro_t pyro1 { 

  .control_pin = PYRO_1,
  .sense_pin = SENSE_1,
  .pyro_value_mv = 0,
  .pyro_fired = 0,

};

pyro_t pyro2 { 

  .control_pin = PYRO_2,
  .sense_pin = SENSE_2,
  .pyro_value_mv = 0,
  .pyro_fired = 0,

};

//setup battery sense
adc_continuous_data_t batt_sense_result{
    .pin = BATT_SENSE,           /*!<ADC pin */
    .channel = 1,      /*!<ADC channel */
    .avg_read_raw = 0,     /*!<ADC average raw data */
    .avg_read_mvolts = 0,   /*!<ADC average voltage in mV */
};

// btn_t btn0 {

//   .pin = BUTT_0,

// };

rgb_led rgb { 

  .channel_r = STATUS_R,
	.channel_g = STATUS_G,
	.channel_b = STATUS_B,

	.tim_channel_r = 1,
	.tim_channel_g = 2,
	.tim_channel_b = 3,

};

void setup(){

  delay(500);
  //initilie all peripherals 
  Serial.begin(112500);
  Serial.println("Serial online");
  
  //imu_init();
  //baro_init();

  Serial.println("sensors initilized");

  GPS_init();
  lora_init();

  Serial.println("GPS initilized");
 
  analog_init();
  Serial.println("Analog initilized");

  //buzzer_init(&buzzer);
  
  rgb_init(&rgb);
  rgb_set_color(&rgb, 0x800080); //set led to purple 

  Serial.println("peripherals initilized");

  //initialize pyro channels
  pyro_init(&pyro1);
  pyro_init(&pyro2);

  Serial.println("Pyros initialized");

  analog_init();

}


void loop(){

  delay(500); //sets the refresh rate 

  // GPS_poll();
  // imu_callback();
  // baro_callback();
  
  buzzer_play_tone(&buzzer, 2000);
  buzzer_update(&buzzer);

  batt_sense_ADC(&batt_sense_result); //read out results of battery sense line
  

}