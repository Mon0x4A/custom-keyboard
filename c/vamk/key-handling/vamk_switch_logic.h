#ifndef VAMK_SWITCH_LOGIC_H
#define VAMK_SWITCH_LOGIC_H

///Imports
#include "pico/stdlib.h"
#include "vamk_types.h"

///Type Declarations
///Constants

///Function Declarations
void switch_logic_press_handler(uint16_t row, uint16_t col, key_event_source_identifier_t key_event_source);
void switch_logic_release_handler(uint16_t row, uint16_t col, key_event_source_identifier_t key_event_source);

#endif
