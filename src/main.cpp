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

pyro_t pyro1 { 

  .control_pin = PYRO_1,
  .sense_pin = SENSE_1,

};

// adc_continuous_data_t pyro1_result {
//     .pin = SENSE_1,           /*!<ADC pin */
//     .channel = 0,      /*!<ADC channel */
//     .avg_read_raw = 0,     /*!<ADC average raw data */
//     .avg_read_mvolts = 0,   /*!<ADC average voltage in mV */
// };

adc_continuous_data_t pyro2_result{
    .pin = SENSE_2,           /*!<ADC pin */
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

  delay(1000);
  //initilie all peripherals 
  Serial.begin(112500);
  Serial.println("Serial online");
  
  //imu_init();
  //baro_init();

  Serial.println("sensors initilized");

  GPS_init();

  Serial.println("GPS initilized");
 
  analog_init();
  Serial.println("Analog initilized");

  //buzzer_init(&buzzer);
  

  rgb_init(&rgb);
  rgb_set_color(&rgb, 0x800080); //set led to purple 

  //btn_init(&btn0);

  pinMode(BUTT_0, INPUT);

  //setup pyro channel
  pinMode(PYRO_1, OUTPUT);
  

    //set the resolution to 12 bits (0-4095)
  analogReadResolution(12);
  analogRead(SENSE_1);
  analogSetPinAttenuation(SENSE_1, ADC_11db);

  digitalWrite(BUTT_0, LOW);

  Serial.println("peripherals initilized");

  pinMode(BUZZER, OUTPUT);
  
 
}


void loop(){

  delay(500);

  // GPS_poll();
  // imu_callback();
  // baro_callback();
  
  buzzer_play_tone(&buzzer, 2000);
  buzzer_update(&buzzer);

  tone(BUZZER, 4000, 100);
  Serial.println("tone played");
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);

  


  // pyro_sense_ADC(&pyro1_result);
  //pyro_sense_ADC(&pyro2_result);


  // get_btn(&btn0, btn_value);

  int out = digitalRead(BUTT_0);
   
  if (out == HIGH){

    digitalWrite(PYRO_1, LOW);

  } else if (out == LOW){
  
    digitalWrite(PYRO_1, HIGH);
    Serial.println("button pressed");

  }

   // read the analog / millivolts value for pin 2:
  int analogValue = analogRead(SENSE_1);
  uint16_t analogVolts = analogReadMilliVolts(SENSE_1);

  // print out the values you read:
  Serial.printf("ADC analog value = %d\n", analogValue);
  Serial.printf("ADC volts value = %d\n", analogVolts/1000);







  
}