#include "Arduino.h"
#include "main.h"

//There is no batt sense on this module
//Only need to configure two pyro channels

typedef struct{
    uint8_t control_pin;
    uint8_t sense_pin; 
} pyro_t;

//define functions

// //given analog functions:
// void analogContinuousSetWidth(uint8_t bits);
// void analogContinuousSetAtten(adc_attenuation_t attenuation);
// bool analogContinuousDeinit(void);
// bool analogContinuousStop(void);
// bool analogContinuousStart(void);
// bool analogContinuousRead(adc_continuous_result_t ** buffer, uint32_t timeout_ms);
// bool analogContinuous(const uint8_t pins[], size_t pins_count, uint32_t conversions_per_pin, uint32_t sampling_freq_hz, void (*userFunc)(void));

//custom functions (mine):
void pyro_sense_ADC(adc_continuous_data_t *result);
void pyro_init(pyro_t *pyro);
void analog_init(void);
void pyro_boom(void);






