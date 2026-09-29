#include "Arduino.h"

typedef struct {
	uint16_t freq;   // [Hz] or 0 for off
	uint16_t duration; // [ms]
} buzzer_beep_t;

typedef struct{

    uint32_t tim_freq;

	// music player
	const buzzer_beep_t* seq;
	uint16_t seq_len;
	uint16_t seq_idx;
	uint32_t beep_start; // [ms] since boot (hal get tick)
	uint8_t seq_playing;
    uint8_t pin;
    int tim_channel;

} buzzer_t;

void buzzer_init(buzzer_t* buzzer){
    //set pin modes

const int freq = 2000;         // 2000 kHz PWM frequency
const int resolution = 8;      // 8-bit resolution (0-255)

ledcSetup(buzzer->tim_channel, freq, resolution); // Configure channel properties
ledcAttachPin(buzzer->pin, buzzer->tim_channel);     // Route channel to GPIO pin via mux

}

void buzzer_set(buzzer_t* buzzer, uint8_t status) {
	uint32_t ccr;

	if (status == 0) {
		ccr = 0;
	}

	if (status == 1) {
		ccr = 1000; //half duty cycle 
	}

	// update duty cycles
	ledcWrite(buzzer->tim_channel, ccr);
}


void buzzer_play_tone(buzzer_t* buzzer, uint16_t freq) {
	if (freq == 0) { // silent
		ledcWrite(buzzer->tim_channel, 0); // don't play
	} else { // sound playing
		uint32_t arr = (buzzer->tim_freq / freq) - 1; // calculate period for given frequency

		ledcWrite(buzzer->tim_channel, arr / 2); // update the duty cycle so it stays at 50%
	}
}

void buzzer_play_sequence(buzzer_t* buzzer, const buzzer_beep_t* seq, uint16_t len) {
	buzzer->seq = seq;
	buzzer->seq_len = len;
	buzzer->seq_idx = 0;
	buzzer->seq_playing = 1;
	buzzer->beep_start = millis(); // record start time

	buzzer_play_tone(buzzer, seq[0].freq); // first beep in seq
}

void buzzer_update(buzzer_t* buzzer) {
	if (!buzzer->seq_playing) { // skip if not playing anything
		return;
	}

	uint32_t now = millis();
	uint16_t duration = buzzer->seq[buzzer->seq_idx].duration;

	if ((now - buzzer->beep_start) >= duration) { // if time since start is >= duration
		buzzer->seq_idx++; // move to next note

		if (buzzer->seq_idx >= buzzer->seq_len) { // if sequence done
			buzzer->seq_playing = 0; // stop playing
			buzzer_play_tone(buzzer, 0); // turn it off
		} else {
			// move on to next note
			buzzer_play_tone(buzzer, buzzer->seq[buzzer->seq_idx].freq);
			buzzer->beep_start = now;
		}
	}
}