
#ifndef VAMK_KEY_HELPER_H
#define VAMK_KEY_HELPER_H
///Imports
#include "vamk_config.h"
#include "vamk_types.h"
#include "stdbool.h"
#include "tusb.h"
///Function Definitions
bool key_helper_is_modifier_keycode(struct hid_keycode_container_t code_container);
#endif
