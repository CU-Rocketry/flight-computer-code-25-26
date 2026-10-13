#include "Arduino.h"
#include "pyro.h"



void pyro_init(pyro_t *pyro){

pinMode(pyro->control_pin, OUTPUT);

//set the resolution to 12 bits (0-4095)
analogReadResolution(12);
analogSetPinAttenuation(pyro->sense_pin, ADC_11db);

}

void pyro_sense_ADC(pyro_t *pyro){ //adc to run in the loop

  // read the analog / millivolts value for pin 2:
  uint16_t analogValue = analogRead(pyro->sense_pin);
  uint16_t analogVolts = analogReadMilliVolts(pyro->sense_pin);

  // print out the values you read:
  Serial.printf("ADC analog value = %d\n", analogValue);
  Serial.printf("ADC millivolts value = %d\n", analogVolts);

  pyro->pyro_value_mv = analogVolts;

  int pyro_counter;
  if (pyro->pyro_value_mv > 1000){
    pyro_counter = pyro_counter + 1;
  } else if (pyro->pyro_value_mv){
    pyro_counter = pyro_counter;
  };

//PROBABLY WILL NEED TO EDIT THIS
// at refresh of 50Hz (0.02 seconds) counter needs to reach 100 to have been fired for 2 seconds

  if (pyro_counter > 100){
    pyro->pyro_fired = 1; //pyro has been fired 
  } else if (pyro_counter < 100){
    pyro->pyro_fired = 0; //pyro has not been fired 
  };

}

void pyro_boom(pyro_t *pyro){

  digitalWrite(pyro->control_pin, HIGH);

}