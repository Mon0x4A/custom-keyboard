#ifndef VAMK_KEYBOARD_STATE_H
#define VAMK_KEYBOARD_STATE_H

///Imports
#include "vamk_types.h"
#include "stdbool.h"
#include "pico/stdlib.h"

///Function Definitions
uint8_t keyboard_state_get_current_layer_index(void);
bool keyboard_state_get_is_layer_modifier_pressed(uint8_t layer_index);
bool keyboard_state_set_is_layer_modifier_pressed(uint8_t layer_index, bool is_layer_modifier_pressed);

bool keyboard_state_get_has_chord_action_been_performed(void);
void keyboard_state_set_has_chord_action_been_performed(bool has_chord_action_been_performed);

#endif
