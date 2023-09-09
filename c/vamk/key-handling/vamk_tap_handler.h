#ifndef VAMK_TAP_HANDLER_H
#define VAMK_TAP_HANDLER_H

///Imports
#include <stdbool.h>
#include "pico/stdlib.h"
#include "vamk_types.h"

///Function Declarations
void tap_handler_on_switch_press(uint16_t row, uint16_t col, uint8_t layer_index, key_event_source_identifier_t keyboard_side);
bool tap_handler_on_switch_release(uint16_t row, uint16_t col, uint8_t layer_index, key_event_source_identifier_t keyboard_side);

#endif
