#pragma once

#include <stdint.h>

namespace Drivers {

void encoder_init();
int  encoder_get_delta();
bool encoder_button_pressed();

} // namespace Drivers
