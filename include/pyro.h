#include "Arduino.h"

//There is no batt sense on this module
//Only need to configure two pyro channels

typedef struct{
    uint8_t control_pin;
    uint8_t channel; //ADC1 Channel
    uint8_t sense_pin; 


} pyro_t;

void pyro_init(pyro_t *pyro){

    adcAttachPin(pyro->control_pin);

}

void batt_sense_get(batt_sense_t *batt_sense, float *out_v, float *out_i){
    uint16_t v_sense_raw = 


}


#include <Arduino.h>

//need to setup as continous to use DMA buffer

typedef struct {
    uint8_t pin;           /*!<ADC pin */
    uint8_t channel;       /*!<ADC channel */
    int avg_read_raw;      /*!<ADC average raw data */
    int avg_read_mvolts;   /*!<ADC average voltage in mV */
} adc_continuous_result_t;



//define functions
void analogContinuousSetWidth(uint8_t bits);
void analogContinuousSetAtten(adc_attenuation_t attenuation);
bool analogContinuousDeinit();
bool analogContinuousStop();
bool analogContinuousStart();
bool analogContinuousRead(adc_continuous_result_t ** buffer, uint32_t timeout_ms);
bool analogContinuous(const uint8_t pins[], size_t pins_count, uint32_t conversions_per_pin, uint32_t sampling_freq_hz, void (*userFunc)(void));


// Define how many conversion per pin will happen and reading the data will be and average of all conversions
#define CONVERSIONS_PER_PIN 5

// Declare array of ADC pins that will be used for ADC Continuous mode - ONLY ADC1 pins are supported
// Number of selected pins can be from 1 to ALL ADC1 pins.
#ifdef CONFIG_IDF_TARGET_ESP32
uint8_t adc_pins[] = {36, 39, 34, 35};  //some of ADC1 pins for ESP32
#else
uint8_t adc_pins[] = {1, 2, 3, 4};  //ADC1 common pins for ESP32S2/S3 + ESP32C3/C6 + ESP32H2
#endif

// Calculate how many pins are declared in the array - needed as input for the setup function of ADC Continuous
uint8_t adc_pins_count = sizeof(adc_pins) / sizeof(uint8_t);

// Flag which will be set in ISR when conversion is done
volatile bool adc_coversion_done = false;

// Result structure for ADC Continuous reading
adc_continuous_result_t *result = NULL;

// ISR Function that will be triggered when ADC conversion is done
void ARDUINO_ISR_ATTR adcComplete() {
  adc_coversion_done = true;
}

void setup() {
  // Initialize serial communication at 115200 bits per second:
  Serial.begin(115200);

  // Optional for ESP32: Set the resolution to 9-12 bits (default is 12 bits)
  analogContinuousSetWidth(12);

  // Optional: Set different attenaution (default is ADC_11db)
  analogContinuousSetAtten(ADC_11db);

  // Setup ADC Continuous with following input:
  // array of pins, count of the pins, how many conversions per pin in one cycle will happen, sampling frequency, callback function
  analogContinuous(adc_pins, adc_pins_count, CONVERSIONS_PER_PIN, 20000, &adcComplete);

  // Start ADC Continuous conversions
  analogContinuousStart();
}

void pyro_sense_get(pyro *batt_sense,  float *out_v, float *out_i){
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
