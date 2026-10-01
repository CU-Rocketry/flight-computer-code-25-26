#include "Arduino.h"


//Setup LEDs

typedef struct {
	uint32_t channel_r;
	uint32_t channel_g;
	uint32_t channel_b;

	uint32_t tim_channel_r;
	uint32_t tim_channel_g;
	uint32_t tim_channel_b;
} rgb_led; //create RGB led

void rgb_set_color(rgb_led* led, uint32_t color){

	// color should be in lower 24 bits (color input is a hex code)
	uint8_t r = (color >> 16) & 0xFF;
	uint8_t g = (color >> 8) & 0xFF;
	uint8_t b = color >> 0 & 0xFF;

    uint32_t ccr_r = 255 - r; //sets the intensity of each color on 255 scale
	uint32_t ccr_g = 255 - g;
	uint32_t ccr_b = 255 - b;

	// prevent 1 tick of on time
	if (ccr_r == 255) ccr_r = 256;
	if (ccr_g == 255) ccr_g = 256;
	if (ccr_b == 255) ccr_b = 256;

	// update duty cycles
	ledcWrite(led->channel_r, ccr_r);
	ledcWrite(led->channel_g, ccr_g);
	ledcWrite(led->channel_b, ccr_b);

}

void rgb_init(rgb_led* led){
    //set pin modes

const int freq = 5000;         // 5 kHz PWM frequency
const int resolution = 8;      // 8-bit resolution (0-255)

ledcAttach(led->channel_r, freq, resolution);
ledcAttach(led->channel_g, freq, resolution);
ledcAttach(led->channel_b, freq, resolution);

rgb_set_color(led, 0x000000); //turn off

Serial.println("LED Init");

}
