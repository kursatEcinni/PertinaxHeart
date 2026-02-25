#include "ui_manager.h"
#include "../config/lv_conf.h"
#include "../config/settings.h"

// 1. Declare the font correctly for the linker
extern "C" {
    LV_FONT_DECLARE(lv_font_unscii_16);
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

lv_obj_t *encoder_label = nullptr;

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
    lv_obj_set_style_bg_color(screen_dashboard, lv_color_hex(0x000000), 0);

    // --- TITLE LABEL ---
    lv_obj_t *title = lv_label_create(screen_dashboard);
    lv_label_set_text(title, "17:45:23");
    lv_obj_set_style_text_font(title, &lv_font_unscii_16, 0);
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFF00), 0); // Yellow
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10); // Top center with 10px offset

    // --- SENSOR DATA LABEL ---
    lv_obj_t *sensor_val = lv_label_create(screen_dashboard);
    lv_label_set_text(sensor_val, "TEMP: 22.5C");
    lv_obj_set_style_text_font(sensor_val, &lv_font_unscii_16, 0); // Bigger font
    lv_obj_set_style_text_color(sensor_val, lv_color_hex(0x00FF00), 0); // Green
    lv_obj_align(sensor_val, LV_ALIGN_CENTER, 0, 0); // Dead center

    // --- FOOTER LABEL ---
    lv_obj_t *footer = lv_label_create(screen_dashboard);
    lv_label_set_text(footer, "PRESS BTN TO MENU");
    lv_obj_set_style_text_font(footer, &lv_font_unscii_8, 0);
    lv_obj_set_style_text_color(footer, lv_color_hex(0xFFFFFF), 0); // White
    lv_obj_align(footer, LV_ALIGN_BOTTOM_MID, 0, -10); // Bottom center, 10px up

    encoder_label = lv_label_create(screen_dashboard);
    lv_label_set_text(encoder_label, "VAL: 0");
    lv_obj_set_style_text_font(encoder_label, &lv_font_unscii_8, 0);
    lv_obj_set_style_text_color(encoder_label, lv_color_hex(0x00D4FF), 0); // Cyan
    lv_obj_align(encoder_label, LV_ALIGN_CENTER, 0, 40); // 40px below center
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

void ui_set_encoder_value(int value) {
    if (encoder_label != nullptr) {
        lv_label_set_text_fmt(encoder_label, "VAL: %d", value);
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