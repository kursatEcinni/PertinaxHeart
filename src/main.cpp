#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <lvgl.h>
#include "ui/ui_manager.h"
#include "drivers/encoder.h"

int total_count = 0;

void setup() {
    // delegate the low-level initialization to the UI module
    ui_init();
    encoder_init();


    ui_switch_action(); // bounce -> widgets
}

void loop() {
    int diff = encoder_get_diff(); 
    
    if (diff != 0) {
        total_count += diff;         
        ui_set_encoder_value(total_count); 
    }

    ui_update_current_screen();
    delay(5);
} 
