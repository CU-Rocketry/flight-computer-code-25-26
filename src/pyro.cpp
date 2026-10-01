#include "Arduino.h"
#include "pyro.h"

//SO there is a batt sense line, but only pyro 2 sense is on continous
//will have to not use continous mode and just use analog read for pyro lines

//poll analog -> if more than 100 for more than 2 full seconds, assume fired

// Define how many conversion per pin will happen and reading the data will be and average of all conversions
#define CONVERSIONS_PER_PIN 5

// Declare array of ADC pins that will be used for ADC Continuous mode - ONLY ADC1 pins are supported
// Number of selected pins can be from 1 to ALL ADC1 pins.

uint8_t adc_pins[] = {SENSE_2};  //pyro lines


// Calculate how many pins are declared in the array - needed as input for the setup function of ADC Continuous
uint8_t adc_pins_count = sizeof(adc_pins) / sizeof(uint8_t);

// Flag which will be set in ISR when conversion is done
volatile bool adc_coversion_done = false;

// Result structure for ADC Continuous reading
adc_continuous_data_t *result = NULL;

// ISR Function that will be triggered when ADC conversion is done
void ARDUINO_ISR_ATTR adcComplete() {
  adc_coversion_done = true;
}

void analog_init(void) {


  // Optional for ESP32: Set the resolution to 9-12 bits (default is 12 bits)
  analogContinuousSetWidth(12);

  // Optional: Set different attenaution (default is ADC_11db)
  analogContinuousSetAtten(ADC_11db);

  // Setup ADC Continuous with following input:
  // array of pins, count of the pins, how many conversions per pin in one cycle will happen, sampling frequency, callback function
  analogContinuous(adc_pins, adc_pins_count, CONVERSIONS_PER_PIN, 20000, &adcComplete); //this starts the ADC on the given pins (sense pins above)

  // Start ADC Continuous conversions
  analogContinuousStart();

  
}

void pyro_init(pyro_t *pyro){

pinMode(pyro->control_pin, OUTPUT);

}

void pyro_sense_ADC(adc_continuous_data_t *result){ //adc to run in the loop
  // Check if conversion is done and try to read data
  if (adc_coversion_done == true) {
    // Set ISR flag back to false
    adc_coversion_done = false;
    // Read data from ADC
    if (analogContinuousRead(&result, 0)) {

      // Optional: Stop ADC Continuous conversions to have more time to process (print) the data
      analogContinuousStop();

      for (int i = 0; i < adc_pins_count; i++) {
        Serial.printf("\nADC PIN %u data:", result[i].pin);
        Serial.printf("\n   Avg raw value = %d", result[i].avg_read_raw);
        Serial.printf("\n   Avg millivolts value = %d", result[i].avg_read_mvolts);
      }

      // Delay for better readability of ADC data
      delay(1000);

      // Optional: If ADC was stopped, start ADC conversions and wait for callback function to set adc_coversion_done flag to true
      analogContinuousStart();
    } else {
      Serial.println("Error occurred during reading data. Set Core Debug Level to error or lower for more information.");
    }
  }
}

void pyro_boom(pyro_t *pyro){

    digitalWrite(pyro->control_pin, HIGH);

}