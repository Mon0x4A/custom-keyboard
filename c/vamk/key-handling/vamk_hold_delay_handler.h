#ifndef VAMK_HOLD_DELAY_HANDLER_H
#define VAMK_HOLD_DELAY_HANDLER_H
///Imports
#include "pico/stdlib.h"
#include "vamk_types.h"
///Constants
///Function Definitions
void hold_delay_handler_on_switch_release(uint16_t row, uint16_t col, uint8_t layer_index, keyboard_side_t keyboard_side);
void hold_delay_handler_on_switch_press(uint16_t row, uint16_t col, uint8_t layer_index, keyboard_side_t keyboard_side);
#endif
