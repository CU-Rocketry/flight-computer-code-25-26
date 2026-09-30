#include "Arduino.h"

typedef struct{ 
    uint8_t pin;
} btn_t;

void btn_init(btn_t *btn){

    pinMode(btn->pin, INPUT_PULLUP);
}

void get_btn(btn_t *btn, int out) {

    out = digitalRead(btn->pin);

}