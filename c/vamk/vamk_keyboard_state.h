#ifndef VAMK_KEYBOARD_STATE_H
#define VAMK_KEYBOARD_STATE_H
///Imports
#include "stdbool.h"
#include "pico/stdlib.h"
///Function Definitions
uint8_t keyboard_state_get_current_layer_index(void);
void keyboard_state_set_current_layer_index(uint8_t current_layer_index);

bool keyboard_state_get_has_chord_action_been_performed(void);
void keyboard_state_set_has_chord_action_been_performed(bool has_chord_action_been_performed);
#endif
