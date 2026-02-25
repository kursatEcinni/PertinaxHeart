#if 1
#ifndef LV_CONF_H
#define LV_CONF_H

#include <stdint.h>

#define LV_COLOR_DEPTH          16
#define LV_COLOR_16_SWAP        0

#define LV_HOR_RES_MAX          240
#define LV_VER_RES_MAX          240

#define LV_MEM_CUSTOM           0
#define LV_MEM_SIZE             (48U * 1024U)

#define LV_TICK_CUSTOM          1
#define LV_TICK_CUSTOM_INCLUDE  "Arduino.h"
#define LV_TICK_CUSTOM_SYS_TIME_EXPR (millis())

#define LV_USE_LOG              0
#define LV_USE_PERF_MONITOR     0

// Widgets
#define LV_USE_BTN              1
#define LV_USE_LABEL            1
#define LV_USE_ARC              1
#define LV_USE_BAR              1
#define LV_USE_SLIDER           1
#define LV_USE_IMG              1
#define LV_USE_ANIMIMG          1

// Animations
#define LV_USE_ANIMATION        1

// Theme
#define LV_USE_THEME_DEFAULT    1
#ifndef LV_THEME_DEFAULT_DARK
#define LV_THEME_DEFAULT_DARK   1
#endif

// Fonts
#define LV_FONT_MONTSERRAT_14   1
#define LV_FONT_MONTSERRAT_24  1  // Medium-Large
#define LV_FONT_MONTSERRAT_48  1  // Huge
#define LV_FONT_UNSCII_16      1  // Large Retro Pixel Font (Double the 8)
#define LV_FONT_UNSCII_8  1
#define LV_FONT_DEFAULT         &lv_font_montserrat_14

#endif
#endif