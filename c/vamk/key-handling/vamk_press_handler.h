#ifndef VAMK_PRESS_HANDLER_H
#define VAMK_PRESS_HANDLER_H

///Imports
#include "pico/stdlib.h"
#include "vamk_types.h"

///Function Declarations
void press_handler_on_switch_press(uint16_t row, uint16_t col, keyboard_side_t keyboard_side);

#endif
