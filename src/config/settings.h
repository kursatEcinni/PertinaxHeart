#pragma once

//---------------------------------------------------------------
// DISPLAY
//---------------------------------------------------------------
#define TFT_SCLK  12
#define TFT_MOSI  11
#define TFT_DC     9
#define TFT_RST   10
#define TFT_CS    -1

#define SCREEN_W  240
#define SCREEN_H  240

#define PIN_ENCODER_A  2
#define PIN_ENCODER_B  1
//#define PIN_ENCODER_BTN ??

#define PIN_DHT22      25
#define PIN_TOF_XSHUT  26

// App constants
#define LVGL_TASK_PERIOD_MS 10
#define SENSOR_TASK_PERIOD_MS 2000

// Uncomment to compile the optional widget test screen
//#define ENABLE_WIDGET_TEST 1
