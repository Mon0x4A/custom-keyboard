///Imports
#include "vamk_config.h"
#include "vamk_keymap_config.h"
#include "vamk_key_helper.h"
#include "vamk_layer_info.h"
#include "vamk_types.h"

#include "stdbool.h"
#include "tusb.h"

///Extern Functions
bool key_helper_is_system_modifier_keycode(uint8_t hid_keycode)
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
            return true;
        default:
            return false;
    }
}
bool key_helper_is_system_modifier_keycode_container(struct hid_keycode_container_t code_container)
{
    hard_assert(code_container.has_valid_contents);
    return key_helper_is_system_modifier_keycode(code_container.hid_keycode);
}

bool key_helper_is_layer_modifier_keycode(uint8_t keycode)
{
    switch (keycode)
    {
        case KC_LM0_L:
        case KC_LM1_L:
        case KC_LM2_L:
        case KC_LM3_L:
        case KC_LM4_L:
        case KC_LM5_L:
        case KC_LM6_L:
        case KC_LM7_L:
        case KC_LM8_L:
        case KC_LM9_L:
        case KC_LM0_R:
        case KC_LM1_R:
        case KC_LM2_R:
        case KC_LM3_R:
        case KC_LM4_R:
        case KC_LM5_R:
        case KC_LM6_R:
        case KC_LM7_R:
        case KC_LM8_R:
        case KC_LM9_R:
            return true;
        default:
            return false;
    }
}
bool key_helper_is_layer_modifier_keycode_container(struct hid_keycode_container_t code_container)
{
    hard_assert(code_container.has_valid_contents);
    return key_helper_is_layer_modifier_keycode(code_container.hid_keycode);
}

bool key_helper_is_modifier_keycode(uint8_t hid_keycode)
{
    return key_helper_is_system_modifier_keycode(hid_keycode)
        || key_helper_is_layer_modifier_keycode(hid_keycode);
}
bool key_helper_is_modifier_keycode_container(struct hid_keycode_container_t code_container)
{
    hard_assert(code_container.has_valid_contents);
    return key_helper_is_modifier_keycode(code_container.hid_keycode);
}

uint8_t key_helper_get_layer_index_from_layer_keycode(uint8_t keycode)
{
    switch (keycode)
    {
        case KC_LM0_L:
        case KC_LM0_R:
            return 0;
        case KC_LM1_L:
        case KC_LM1_R:
            return 1;
        case KC_LM2_L:
        case KC_LM2_R:
            return 2;
        case KC_LM3_L:
        case KC_LM3_R:
            return 3;
        case KC_LM4_L:
        case KC_LM4_R:
            return 4;
        case KC_LM5_L:
        case KC_LM5_R:
            return 5;
        case KC_LM6_L:
        case KC_LM6_R:
            return 6;
        case KC_LM7_L:
        case KC_LM7_R:
            return 7;
        case KC_LM8_L:
        case KC_LM8_R:
            return 8;
        case KC_LM9_L:
        case KC_LM9_R:
            return 9;
        default:
            return 0;
    }
}
