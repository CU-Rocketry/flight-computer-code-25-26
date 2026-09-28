#include "Arduino.h"


//Setup LEDs

typedef struct {
	uint32_t channel_r;
	uint32_t channel_g;
	uint32_t channel_b;
} rgb_led; //create RGB led

void rgb_set_color(reg_led* led, uint32_t color){

	// color should be in lower 24 bits
	uint8_t r = (color >> 16) & 0xFF;
	uint8_t g = (color >> 8) & 0xFF;
	uint8_t b = color >> 0 & 0xFF;



}

void rgb_init(reg_led* led){
    pinMode(led->channel_r, OUTPUT);
    pinMode(led->channel_b, OUTPUT);
    pinMode(led->channel_g, OUTPUT);
}


//Setup Buzzer