#include "sensor_task.h"
#include "../drivers/dht22.h"
#include "../drivers/distance.h"

#include <Arduino.h>

void sensor_task(void* pvParameters) {
  (void)pvParameters;
  for(;;) {
    float t, h;
    if (Drivers::dht_read(t, h)) {
      // publish or cache readings
    }
    float d = Drivers::distance_read_cm();
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}
