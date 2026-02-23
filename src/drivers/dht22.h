#pragma once

#include <stdint.h>

namespace Drivers {

bool dht_init(int pin);
bool dht_read(float &temperature, float &humidity);

} // namespace Drivers
