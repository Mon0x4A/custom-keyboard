#ifndef VAMK_KEY_HELPER_H
#define VAMK_KEY_HELPER_H

///Imports
#include "vamk_config.h"
#include "vamk_layer_info.h"
#include "stdbool.h"
#include "tusb.h"

///Function Definitions
bool key_helper_is_modifier_keycode(uint8_t hid_keycode);
bool key_helper_is_modifier_keycode_container(struct hid_keycode_container_t code_container);

#endif
