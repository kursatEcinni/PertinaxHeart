#include "ui_manager.h"
#include "lv_conf.h"
#include "../config/settings.h"

#define TFT_SCLK  12
#define TFT_MOSI  11
#define TFT_DC     9
#define TFT_RST   10
#define TFT_CS    -1

#define SCREEN_W  240
#define SCREEN_H  240

Arduino_DataBus *bus = new Arduino_ESP32SPI(
  TFT_DC, TFT_CS, TFT_SCLK, TFT_MOSI, GFX_NOT_DEFINED, HSPI
);
Arduino_GFX *gfx = new Arduino_ST7789(
  bus, TFT_RST, 0, true, SCREEN_W, SCREEN_H
);

// forward LVGL variables that are shared by several functions
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[SCREEN_W * 20];

// placeholder screens that will be constructed during initialization
lv_obj_t *screen_bounce = nullptr;
lv_obj_t *screen_widgets = nullptr;
lv_obj_t *screen_transition = nullptr;

static int current_screen = 0;

// ── LVGL Flush ───────────────────────────────────────────
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = area->x2 - area->x1 + 1;
  uint32_t h = area->y2 - area->y1 + 1;
  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
  lv_disp_flush_ready(disp);
}

// ── Forward declarations ──────────────────────────────────
static void create_widget_screen();
static void create_transition_screen();
static void switch_screen(int index);

// ════════════════════════════════════════════════════════
// DISPLAY TEST FUNCTION — Widgets (Arc + Slider + Bar)
// ════════════════════════════════════════════════════════
static lv_obj_t *arc_widget;
static lv_obj_t *bar_widget;
static lv_anim_t anim_arc, anim_bar;

void create_widget_screen() {
  screen_widgets = lv_obj_create(NULL);
  lv_obj_set_style_bg_color(screen_widgets, lv_color_hex(0x0d1a0d), 0);

  // Title
  lv_obj_t *title = lv_label_create(screen_widgets);
  lv_label_set_text(title, "Widget Animations");
  lv_obj_set_style_text_color(title, lv_color_hex(0x2ed573), 0);
  lv_obj_set_style_text_font(title, &lv_font_montserrat_14, 0);
  lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 8);

  // Arc
  arc_widget = lv_arc_create(screen_widgets);
  lv_obj_set_size(arc_widget, 110, 110);
  lv_arc_set_rotation(arc_widget, 135);
  lv_arc_set_bg_angles(arc_widget, 0, 270);
  lv_arc_set_value(arc_widget, 0);
  lv_obj_set_style_arc_color(arc_widget, lv_color_hex(0x2ed573), LV_PART_INDICATOR);
  lv_obj_set_style_arc_width(arc_widget, 10, LV_PART_INDICATOR);
  lv_obj_set_style_arc_width(arc_widget, 10, LV_PART_MAIN);
  lv_obj_align(arc_widget, LV_ALIGN_CENTER, 0, -20);
  lv_obj_remove_style(arc_widget, NULL, LV_PART_KNOB);

  // Arc label
  lv_obj_t *arc_label = lv_label_create(arc_widget);
  lv_label_set_text(arc_label, "0%");
  lv_obj_set_style_text_color(arc_label, lv_color_hex(0xffffff), 0);
  lv_obj_center(arc_label);

  // Animate arc
  lv_anim_init(&anim_arc);
  lv_anim_set_var(&anim_arc, arc_widget);
  lv_anim_set_exec_cb(&anim_arc, (lv_anim_exec_xcb_t)lv_arc_set_value);
  lv_anim_set_values(&anim_arc, 0, 100);
  lv_anim_set_time(&anim_arc, 2000);
  lv_anim_set_playback_time(&anim_arc, 2000);
  lv_anim_set_repeat_count(&anim_arc, LV_ANIM_REPEAT_INFINITE);
  lv_anim_set_path_cb(&anim_arc, lv_anim_path_ease_in_out);
  lv_anim_start(&anim_arc);

  // Bar
  bar_widget = lv_bar_create(screen_widgets);
  lv_obj_set_size(bar_widget, 180, 14);
  lv_bar_set_range(bar_widget, 0, 100);
  lv_bar_set_value(bar_widget, 0, LV_ANIM_OFF);
  lv_obj_set_style_bg_color(bar_widget, lv_color_hex(0x2ed573), LV_PART_INDICATOR);
  lv_obj_align(bar_widget, LV_ALIGN_BOTTOM_MID, 0, -50);

  // Animate bar
  lv_anim_init(&anim_bar);
  lv_anim_set_var(&anim_bar, bar_widget);
  lv_anim_set_exec_cb(&anim_bar, (lv_anim_exec_xcb_t)lv_bar_set_value);
  lv_anim_set_values(&anim_bar, 0, 100);
  lv_anim_set_time(&anim_bar, 1500);
  lv_anim_set_playback_time(&anim_bar, 1500);
  lv_anim_set_repeat_count(&anim_bar, LV_ANIM_REPEAT_INFINITE);
  lv_anim_set_path_cb(&anim_bar, lv_anim_path_ease_in_out);
  lv_anim_start(&anim_bar);

  // Next button
  lv_obj_t *btn = lv_btn_create(screen_widgets);
  lv_obj_set_size(btn, 100, 35);
  lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, -8);
  lv_obj_set_style_bg_color(btn, lv_color_hex(0x2ed573), 0);
  lv_obj_add_event_cb(btn, [](lv_event_t *e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) switch_screen(2);
  }, LV_EVENT_CLICKED, NULL);
  lv_obj_t *lbl = lv_label_create(btn);
  lv_label_set_text(lbl, "Next >");
  lv_obj_center(lbl);
}

void switch_screen(int index) {
  current_screen = index;
  lv_obj_t *target = nullptr;
  if (index == 0) target = screen_bounce;
  else if (index == 1) target = screen_widgets;
  else if (index == 2) target = screen_transition;

  if (target) {
    lv_scr_load_anim(target, LV_SCR_LOAD_ANIM_MOVE_LEFT, 400, 0, false);
  }
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

  // create all of the screens we know about so they exist when switching
  screen_bounce      = lv_obj_create(NULL);
  lv_obj_set_style_bg_color(screen_bounce, lv_color_hex(0x000000), 0);

  create_widget_screen();
  create_transition_screen();

  // start on the bounce screen for now
  lv_scr_load(screen_bounce);
}

void ui_update_current_screen() {
  // LVGL requires periodic calls to its timer handler
  lv_timer_handler();
}

void ui_switch_action() {
  // simple cycling behaviour for now
  int next = (current_screen + 1) % 3;
  switch_screen(next);
}

void ui_click_action() {
  // could be used by encoder/button callbacks later
  ui_switch_action();
}

// ── placeholder transition screen ─────────────────────────
static void create_transition_screen() {
  screen_transition = lv_obj_create(NULL);
  lv_obj_set_style_bg_color(screen_transition, lv_color_hex(0x001a1a), 0);
  lv_obj_t *lbl = lv_label_create(screen_transition);
  lv_label_set_text(lbl, "Transition");
  lv_obj_center(lbl);
}

