#include "ui_manager.h"
#include "../config/lv_conf.h"
#include "../config/settings.h"

// 1. Declare the font correctly for the linker
extern "C" {
    LV_FONT_DECLARE(lv_font_montserrat_14);
    LV_FONT_DECLARE(lv_font_montserrat_16);
    LV_FONT_DECLARE(lv_font_montserrat_20);
    LV_FONT_DECLARE(lv_font_montserrat_24);
    LV_FONT_DECLARE(lv_font_montserrat_32);
    LV_FONT_DECLARE(lv_font_montserrat_36);
    LV_FONT_DECLARE(lv_font_montserrat_48);
}

Arduino_DataBus *bus = new Arduino_ESP32SPI(
  TFT_DC, TFT_CS, TFT_SCLK, TFT_MOSI, GFX_NOT_DEFINED, HSPI
);

Arduino_GFX *gfx = new Arduino_ST7789(
  bus, TFT_RST, 0, true, SCREEN_W, SCREEN_H
);

// Global variables for LVGL
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[SCREEN_W * 20];

// Screen objects
lv_obj_t *screen_bounce = nullptr;
lv_obj_t *screen_dashboard = nullptr;

// UI element references for updates
lv_obj_t *encoder_label = nullptr;
lv_obj_t *label_time = nullptr;
lv_obj_t *label_date = nullptr;
lv_obj_t *label_temp_value = nullptr;
lv_obj_t *label_humid_value = nullptr;
lv_obj_t *slider_main = nullptr;

static int current_screen = 0;

// ── LVGL Flush ───────────────────────────────────────────
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = area->x2 - area->x1 + 1;
  uint32_t h = area->y2 - area->y1 + 1;
  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
  lv_disp_flush_ready(disp);
}

// ── Screen Creation Functions ─────────────────────────────
void main_dashboard() {
    screen_dashboard = lv_obj_create(NULL);

    // --- BACKGROUND IMAGE ---
    // LV_IMAGE_DECLARE(image_Layer_2_dsc);  // Declare in header if image exists
    // lv_obj_t * image_Layer_2 = lv_image_create(screen_dashboard);
    // lv_image_set_src(image_Layer_2, &image_Layer_2_dsc);
    // lv_obj_set_pos(image_Layer_2, 0, 0);
    // lv_obj_set_size(image_Layer_2, 0, 0);

    // --- SLIDER ---
    slider_main = lv_slider_create(screen_dashboard);
    lv_slider_set_value(slider_main, 50, LV_ANIM_OFF);
    lv_obj_set_pos(slider_main, 25, 222);
    lv_obj_set_size(slider_main, 191, 11);
    lv_obj_set_style_bg_color(slider_main, lv_color_hex(0x455a64), LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(slider_main, lv_color_hex(0x455a64), LV_PART_KNOB);
    lv_obj_set_style_bg_color(slider_main, lv_color_hex(0x455a64), LV_PART_MAIN);

    // --- TIME LABEL (Top Center) ---
    label_time = lv_label_create(screen_dashboard);
    lv_obj_set_style_text_color(label_time, lv_color_hex(0x455a64), LV_PART_MAIN);
    lv_obj_set_style_text_font(label_time, &lv_font_montserrat_48, LV_PART_MAIN);
    lv_obj_set_pos(label_time, 65, 25);
    lv_label_set_text(label_time, "00:00");

    // --- TEMPERATURE LABEL ---
    lv_obj_t * label_temp = lv_label_create(screen_dashboard);
    lv_obj_set_style_text_color(label_temp, lv_color_hex(0x455a64), LV_PART_MAIN);
    lv_obj_set_style_text_font(label_temp, &lv_font_montserrat_20, LV_PART_MAIN);
    lv_obj_set_pos(label_temp, 45, 75);
    lv_label_set_text(label_temp, "TEMP : ");

    // --- HUMIDITY LABEL ---
    lv_obj_t * label_humid = lv_label_create(screen_dashboard);
    lv_obj_set_style_text_color(label_humid, lv_color_hex(0x455a64), LV_PART_MAIN);
    lv_obj_set_style_text_font(label_humid, &lv_font_montserrat_20, LV_PART_MAIN);
    lv_obj_set_pos(label_humid, 45, 102);
    lv_label_set_text(label_humid, "HUMID : ");

    // --- TEMPERATURE VALUE ---
    label_temp_value = lv_label_create(screen_dashboard);
    lv_obj_set_style_text_color(label_temp_value, lv_color_hex(0x008080), LV_PART_MAIN);
    lv_obj_set_style_text_font(label_temp_value, &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_set_pos(label_temp_value, 132, 75);
    lv_label_set_text(label_temp_value, "22.6 °C");

    // --- HUMIDITY VALUE ---
    label_humid_value = lv_label_create(screen_dashboard);
    lv_obj_set_style_text_color(label_humid_value, lv_color_hex(0x008080), LV_PART_MAIN);
    lv_obj_set_style_text_font(label_humid_value, &lv_font_montserrat_24, LV_PART_MAIN);
    lv_obj_set_pos(label_humid_value, 151, 102);
    lv_label_set_text(label_humid_value, "%37");

    // --- DATE LABEL ---
    label_date = lv_label_create(screen_dashboard);
    lv_obj_set_style_text_color(label_date, lv_color_hex(0x455a64), LV_PART_MAIN);
    lv_obj_set_style_text_font(label_date, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_set_pos(label_date, 156, 5);
    lv_label_set_text(label_date, "00/00/0000");

    // --- WEATHER PANEL ---
    lv_obj_t * panel_weather = lv_obj_create(screen_dashboard);
    lv_obj_set_pos(panel_weather, 73, 128);
    lv_obj_set_size(panel_weather, 93, 81);
    lv_obj_set_style_bg_color(panel_weather, lv_color_hex(0x455a64), LV_PART_MAIN);

    //WIFI INDICATOR
    lv_obj_t * label_wifi = lv_label_create(panel_weather);
    lv_obj_set_style_text_color(label_wifi, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_style_text_font(label_wifi, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_set_pos(label_wifi, 5, 5);
    lv_label_set_text(label_wifi, "WiFi: OK");

    // --- WEATHER ICON IMAGE ---
    // LV_IMAGE_DECLARE(image_weather_cloud_sunny_dsc);  // Declare in header if image exists
    // lv_obj_t * image_weather_cloud_sunny = lv_image_create(screen_dashboard);
    // lv_image_set_src(image_weather_cloud_sunny, &image_weather_cloud_sunny_dsc);
    // lv_obj_set_pos(image_weather_cloud_sunny, 86, 137);
    // lv_obj_set_size(image_weather_cloud_sunny, 68, 64);

    // --- MENU LABEL ---
    encoder_label = lv_label_create(screen_dashboard);
    lv_obj_set_style_text_color(encoder_label, lv_color_hex(0x455a64), LV_PART_MAIN);
    lv_obj_set_style_text_font(encoder_label, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_set_pos(encoder_label, 8, 5);
    lv_label_set_text(encoder_label, "Menu");
}

void switch_screen(int index) {
  // for selectinon logic, not actual screen management
}

// ── PUBLIC API ───────────────────────────────────────────

void ui_init() {
  Serial.begin(115200);
  delay(500);

  gfx->begin();

  lv_init();
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, SCREEN_W * 20);

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res  = SCREEN_W;
  disp_drv.ver_res  = SCREEN_H;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  // Initialize all screens
  main_dashboard();

  // Load the retro dashboard immediately
  lv_scr_load(screen_dashboard);
}

void show_wifi_popup(bool success) {
    // Create the message box on the active screen
    lv_obj_t * mbox = lv_msgbox_create(lv_scr_act(), 
        success ? "WiFi Status" : "Error", 
        success ? "System Online\nWiFi Connected!" : "Connection Failed!", 
        NULL, false); 

    lv_obj_center(mbox);
    
    // Aesthetic Styling (Fits a 'love-frame' theme)
    lv_obj_set_style_bg_color(mbox, lv_palette_main(LV_PALETTE_PINK), 0);
    lv_obj_set_style_text_color(mbox, lv_color_white(), 0);

    // Self-destruct timer so it disappears without a button
    lv_timer_create([](lv_timer_t * t) {
        lv_obj_t * obj = (lv_obj_t *)t->user_data;
        if(lv_obj_is_valid(obj)) lv_msgbox_close(obj);
    }, 4000, mbox);
}

void ui_set_encoder_value(int value) {
    if (slider_main != nullptr) {
        lv_slider_set_value(slider_main, value, LV_ANIM_OFF);
    }
}

void ui_set_temperature(float temp) {
    if (label_temp_value != nullptr) {
        lv_label_set_text_fmt(label_temp_value, "%.1f °C", temp);
    }
}

void ui_set_humidity(int humidity) {
    if (label_humid_value != nullptr) {
        lv_label_set_text_fmt(label_humid_value, "%%%d", humidity);
    }
}

void ui_set_time(const char *time_str) {
    if (label_time != nullptr) {
        lv_label_set_text(label_time, time_str);
    }
}

void ui_set_date(const char *date_str) {
    // Note: You'll need to make 'label_date' a global or static variable 
    // at the top of ui_manager.cpp if it isn't already, so this function can see it.
    if (label_date != nullptr) {
        lv_label_set_text(label_date, date_str);
    }
}

void ui_update_current_screen() {
  lv_timer_handler();
}

void ui_switch_action() {
  int next = (current_screen + 1) % 2;
  switch_screen(next);
}

void ui_click_action() {
  ui_switch_action();
}