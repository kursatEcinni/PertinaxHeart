#include <Arduino.h>
#include "ui/ui_manager.h"
#include "tasks/sensor_task.h"

void setup() {
  Serial.begin(115200);
  UI::init();
  // Create FreeRTOS tasks
  xTaskCreate(sensor_task, "sensors", 4096, NULL, 1, NULL);
}

void loop() {
  UI::loop();
  delay(1);
}
