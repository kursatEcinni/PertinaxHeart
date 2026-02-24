#pragma once

#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <lvgl.h>


// initialize the display & LVGL, create base screens
void ui_init();

// must be called periodically from the main loop to service LVGL
void ui_update_current_screen();

// helper actions typically triggered by encoder/button events
void ui_switch_action();
void ui_click_action();
