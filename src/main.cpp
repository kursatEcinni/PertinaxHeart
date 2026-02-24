
#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <lvgl.h>
#include "ui/ui_manager.h"

void setup() {
    // delegate the low-level initialization to the UI module
    ui_init();
}

void loop() {
    // drive LVGL's timer
    ui_update_current_screen();
    delay(5);
} 
