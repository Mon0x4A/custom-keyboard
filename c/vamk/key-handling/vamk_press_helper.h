#ifndef VAMK_PRESS_HELPER_H
#define VAMK_PRESS_HELPER_H

///Imports
#include "pico/stdlib.h"
#include "vamk_keyboard_state.h"
#include "vamk_layer_info.h"
#include "vamk_types.h"

///Constants

///Function Definitions
void press_helper_key_press(struct hid_keycode_container_t keycode_container);
void press_helper_momentary_press_with_modifiers(struct hid_keycode_container_t keycode_container,
    struct modifier_collection_t modifiers_collection);
void press_helper_momentary_press(struct hid_keycode_container_t keycode_container);
void press_helper_minimal_press(struct hid_keycode_container_t keycode_container);

#endif
