#pragma once

#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <lvgl.h>


#ifdef __cplusplus
extern "C" {
#endif
// forward declarations for screens used across modules
// optional widget screen used for testing
#ifdef ENABLE_WIDGET_TEST
extern lv_obj_t *screen_widgets;
#endif

// the dashboard/transition screen
extern lv_obj_t *screen_transition;

// the UNISCI 8‑pixel font is provided by LVGL when enabled in lv_conf.h
extern const lv_font_t lv_font_unscii_8;
#ifdef __cplusplus
} // extern "C"
#endif

// initialize the display & LVGL, create base screens
void ui_init();

void ui_set_encoder_value(int value); // Update the encoder value label on the dashboard

void create_widget_screen();

// must be called periodically from the main loop to service LVGL
void ui_update_current_screen();

// helper actions typically triggered by encoder/button events
void ui_switch_action();
void ui_click_action();


