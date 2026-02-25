#include "encoder.h"
#include "../config/settings.h"

volatile int _encoder_steps = 0;

// Optimized ISR for ESP32
void IRAM_ATTR read_encoder_isr() {
    static uint8_t old_AB = 3;
    static const int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
    old_AB <<= 2;
    if (digitalRead(PIN_ENCODER_A)) old_AB |= 0x02;
    if (digitalRead(PIN_ENCODER_B)) old_AB |= 0x01;
    _encoder_steps += enc_states[(old_AB & 0x0f)];
}

void encoder_init() {
    pinMode(PIN_ENCODER_A, INPUT_PULLUP);
    pinMode(PIN_ENCODER_B, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_A), read_encoder_isr, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_B), read_encoder_isr, CHANGE);
}

int encoder_get_diff() {
    // Since your hardware moves 1 value per 2 clicks, 
    // we set the threshold to 2 steps per detent.
    const int steps_per_click = 2; 

    if (abs(_encoder_steps) >= steps_per_click) {
        int clicks = _encoder_steps / steps_per_click;
        _encoder_steps -= (clicks * steps_per_click); 
        return clicks;
    }
    return 0;
}