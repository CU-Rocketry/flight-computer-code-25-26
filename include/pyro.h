#include "Arduino.h"
#include "main.h"

//There is no batt sense on this module
//Only need to configure two pyro channels

typedef struct{
    uint8_t control_pin;
    uint8_t sense_pin; 
    uint16_t pyro_value_mv; //reading from sense line
    uint8_t pyro_fired; //1 or 0 to tell if pyro is fired
} pyro_t;

//custom functions (mine):
void pyro_sense_ADC(adc_continuous_data_t *result);
void pyro_init(pyro_t *pyro);
void pyro_boom(void);






