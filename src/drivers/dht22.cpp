#include "dht22.h"

namespace Drivers {

bool dht_init(int pin) {
  // TODO: init DHT library
  (void)pin;
  return true;
}

bool dht_read(float &temperature, float &humidity) {
  // TODO: read sensor
  temperature = 0.0f;
  humidity = 0.0f;
  return false;
}

} // namespace Drivers
