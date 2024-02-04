#ifndef VAMK_KEY_HELPER_H
#define VAMK_KEY_HELPER_H

///Imports
#include "vamk_config.h"
#include "vamk_layer_info.h"
#include "stdbool.h"
#include "tusb.h"

///Function Definitions
bool key_helper_is_system_modifier_keycode(uint8_t hid_keycode);
bool key_helper_is_system_modifier_keycode_container(struct hid_keycode_container_t code_container);

bool key_helper_is_layer_modifier_keycode(uint8_t keycode);
bool key_helper_is_layer_modifier_keycode_container(struct hid_keycode_container_t code_container);

bool key_helper_is_modifier_keycode(uint8_t hid_keycode);
bool key_helper_is_modifier_keycode_container(struct hid_keycode_container_t code_container);

uint8_t key_helper_get_layer_index_from_layer_keycode(uint8_t keycode);

#endif
