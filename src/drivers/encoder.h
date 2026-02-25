#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

void encoder_init();
void encoder_update(); // Call this in your main loop
int encoder_get_diff(); // Returns the direction (-1, 0, 1)

bool encoder_button_pressed();

#endif // ENCODER_H