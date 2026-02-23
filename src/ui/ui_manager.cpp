#include "ui_manager.h"
#include "../config/settings.h"

namespace UI {

void init() {
  lv_init();
  // Display + input init should go here (driver hookups)
}

void loop() {
  lv_timer_handler();
}

void show_app(const char* app_id) {
  // App switching stub
}

} // namespace UI
