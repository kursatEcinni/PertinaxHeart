#pragma once

// Pin/platform configuration — tune for your wiring
#define PIN_ST7789_DC  16
#define PIN_ST7789_RST 17
#define PIN_ST7789_CS  5

#define PIN_ENCODER_A  32
#define PIN_ENCODER_B  33
#define PIN_ENCODER_BTN 34

#define PIN_DHT22      25
#define PIN_TOF_XSHUT  26

// App constants
#define LVGL_TASK_PERIOD_MS 10
#define SENSOR_TASK_PERIOD_MS 2000
