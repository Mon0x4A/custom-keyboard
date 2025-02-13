#ifndef VAMK_KEYBOARD_STATE_H
#define VAMK_KEYBOARD_STATE_H

///Imports
#include "vamk_types.h"
#include "vamk_layer_info.h"

#include "stdbool.h"
#include "pico/stdlib.h"

///Type Declarations
///Function Definitions
uint8_t keyboard_state_get_current_layer_index(void);
uint8_t keyboard_state_clear_sticky_layer(void);
bool keyboard_state_get_is_layer_modifier_pressed(uint8_t layer_index);
void keyboard_state_set_is_layer_modifier_pressed(uint8_t layer_index, bool is_layer_modifier_pressed);

//TODO modifier helper?
bool keyboard_state_modifier_collection_contains_keycode(struct modifier_collection_t modifier_collection,
    uint8_t modifier_keycode);

bool keyboard_state_is_any_modifier_pressed(void);
struct modifier_collection_t keyboard_state_get_currently_pressed_modifiers(void);

void keyboard_state_set_repeat_state(struct hid_keycode_container_t repeat_code);
void keyboard_state_send_repeat_state(void);
#endif
