#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <lvgl.h>
#include "ui/ui_manager.h"
#include "drivers/encoder.h"
#include "services/network_portal.h"

int total_count = 0;
unsigned long lastClockUpdate = 0;

void setup() {
    // delegate the low-level initialization to the UI module
    ui_init();
    encoder_init();
    wifi_init();

    ui_set_time(get_clock_string().c_str());
    ui_set_date(get_date_string().c_str());

    ui_switch_action(); // bounce -> widgets
}

void loop() {
    lv_timer_handler(); // Vital for LVGL animations and popups
    ui_update_current_screen(); // Refresh the current screen's dynamic content
    
    // Update exactly every 60 seconds (60,000 ms)
   if (millis() - lastClockUpdate >= 60000) {
        lastClockUpdate = millis();
        ui_set_time(get_clock_string().c_str());
        ui_set_date(get_date_string().c_str());
        
        // Every hour, refresh the date just in case it passed midnight
        static int hourCounter = 0;
        hourCounter++;
        if(hourCounter >= 60) {
            ui_set_date(get_date_string().c_str());
            hourCounter = 0;
        }
    }
    delay(5);
}
