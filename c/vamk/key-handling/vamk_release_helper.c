
///Imports
#include "pico/stdlib.h"
#include "vamk_key_state.h"
#include "vamk_key_helper.h"
#include "vamk_keyboard_state.h"
#include "vamk_release_helper.h"

///Static Functions
static void keycode_release_internal(struct hid_keycode_container_t keycode_container)
{
    if (!keycode_container.has_valid_contents || keycode_container.hid_keycode == KC_NULL)
        return;

    bool need_remove_code_from_report = true;
    switch (keycode_container.hid_keycode)
    {
        case HID_KEY_ALT_LEFT:
        case HID_KEY_ALT_RIGHT:
            break;
        case HID_KEY_GUI_LEFT:
        case HID_KEY_GUI_RIGHT:
            break;
        case HID_KEY_CONTROL_LEFT:
        case HID_KEY_CONTROL_RIGHT:
            break;
        case HID_KEY_SHIFT_LEFT:
        case HID_KEY_SHIFT_RIGHT:
            break;
        case KC_NULL:
        //HID_KEY_NONE as well
            // Nothing to do if we hit a null code.
            need_remove_code_from_report = false;
            break;
        default:
            break;
    }

    if (key_helper_is_layer_modifier_keycode(keycode_container.hid_keycode))
    {
        keyboard_state_set_is_layer_keycode_pressed(keycode_container.hid_keycode, false);
        need_remove_code_from_report = false;
        printf("Leaving layer %d\n", key_helper_get_layer_index_from_layer_keycode(keycode_container.hid_keycode));
        if (ENABLE_SERIAL_LOGGING)
            printf("Layer value released: %u\n", keycode_container.hid_keycode);
    }

    if (ENABLE_KEYBOARD_COMMANDS && need_remove_code_from_report)
        key_state_release(keycode_container.hid_keycode);
    if (ENABLE_SERIAL_LOGGING && need_remove_code_from_report)
        printf("Keycode value released: %u\n", keycode_container.hid_keycode);
}

///Extern Functions
void release_helper_key_release(struct hid_keycode_container_t keycode_container)
{
    keycode_release_internal(keycode_container);
}
