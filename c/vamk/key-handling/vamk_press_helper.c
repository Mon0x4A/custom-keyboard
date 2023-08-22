///Imports
#include <stdbool.h>
#include "pico/stdlib.h"
#include "vamk_config.h"
#include "vamk_keymap_config.h"
#include "vamk_key_helper.h"
#include "vamk_key_state.h"
#include "vamk_keyboard_state.h"
#include "vamk_press_handler.h"
#include "vamk_press_helper.h"
#include "vamk_types.h"
#include "tusb.h"
///Static Global Variables
///Local Declarations
///Static Functions
///Extern Functions
void press_helper_keycode_press(struct hid_keycode_container_t keycode_container, bool should_auto_release)
{
    // If we are receiving invalid codes, something has gone
    // programatically wrong.
    hard_assert(keycode_container.has_valid_contents);

    bool is_modifier_code = key_helper_is_modifier_keycode_container(keycode_container);

    // If we are handling a non-modifier press then any chord we were
    // pressing has now been completed.
    keyboard_state_set_has_chord_action_been_performed(!is_modifier_code);

    bool should_report_code = true;
    switch (keycode_container.hid_keycode)
    {
        case KC_LM1:
            should_report_code = false;
            keyboard_state_set_is_layer_modifier_pressed(1, true);
            printf("Entering layer 1\n");
            break;
        case KC_LM2:
            should_report_code = false;
            keyboard_state_set_is_layer_modifier_pressed(2, true);
            printf("Entering layer 2\n");
            break;
        //TODO handle the other layers, maybe with a helper method to convert to index?
        case KC_REPEAT:
            should_report_code = false;
            keyboard_state_send_repeat_state();
            break;
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
            should_report_code = false;
            break;
        default:
            break;
    }

    if (ENABLE_KEYBOARD_COMMANDS && should_report_code)
    {
        key_state_press(keycode_container, should_auto_release);

        if (!is_modifier_code)
            keyboard_state_set_repeat_state(keycode_container);
    }

    if (ENABLE_SERIAL_LOGGING && should_report_code)
    {
        printf("Keycode value pressed: %u\n", keycode_container.hid_keycode);
    }
}
