///Imports
#include "vamk_config.h"
#include "vamk_keymap_config.h"
#include "vamk_key_helper.h"
#include "vamk_layer_info.h"
#include "vamk_types.h"

#include "stdbool.h"
#include "tusb.h"

///Static Global Variables
///Static Functions
///Extern Functions
bool key_helper_is_modifier_keycode(uint8_t hid_keycode)
{
    switch (hid_keycode)
    {
        case HID_KEY_CONTROL_LEFT:
        case HID_KEY_CONTROL_RIGHT:
        case HID_KEY_SHIFT_LEFT:
        case HID_KEY_SHIFT_RIGHT:
        case HID_KEY_ALT_LEFT:
        case HID_KEY_ALT_RIGHT:
        case HID_KEY_GUI_LEFT:
        case HID_KEY_GUI_RIGHT:
        case KC_LM0:
        case KC_LM1:
        case KC_LM2:
        case KC_LM3:
        case KC_LM4:
        case KC_LM5:
        case KC_LM6:
        case KC_LM7:
        case KC_LM8:
        case KC_LM9:
            return true;
        default:
            return false;
    }
}

bool key_helper_is_modifier_keycode_container(struct hid_keycode_container_t code_container)
{
    hard_assert(code_container.has_valid_contents);
    return key_helper_is_modifier_keycode(code_container.hid_keycode);
}
