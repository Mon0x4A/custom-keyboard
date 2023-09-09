#ifndef VAMK_RELEASE_HANDLER_H
#define VAMK_RELEASE_HANDLER_H

///Imports
#include "pico/stdlib.h"

///Function Declarations
void release_handler_on_switch_release(uint16_t row, uint16_t col, key_event_source_identifier_t keyboard_side);

#endif
