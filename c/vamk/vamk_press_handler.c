///Imports
#include <stdbool.h>
#include "pico/stdlib.h"
#include "vamk_config.h"
#include "vamk_key_helper.h"
#include "vamk_key_state.h"
#include "vamk_keyboard_state.h"
#include "vamk_layer_info.h"
#include "vamk_press_handler.h"
#include "vamk_tap_handler.h"
#include "vamk_types.h"
#include "tusb.h"

///Static Global Variables
static bool _has_chord_action_been_performed = false;

///Static Functions
//#include "hardware/timer.h"
////TODO this timer code could be very useful for key events
//// Timer example code - This example fires off the callback after 2000ms
//add_alarm_in_ms(2000, alarm_callback, NULL, false);
//// And the callback:
//int64_t alarm_callback(alarm_id_t id, void *user_data) {
//    // Put your timeout handler code in here
//    return 0;
//}

///Extern Functions
void press_handler_on_switch_press(uint16_t row, uint16_t col, keyboard_side_t keyboard_side)
{
    uint8_t current_layer = keyboard_state_get_current_layer_index();

    tap_handler_on_switch_press(row, col, current_layer, keyboard_side);

    struct hid_keycode_container_t code_container =
        layer_info_get_base_keycode_at(row, col, current_layer, keyboard_side);

    // If we are receiving invalid codes, something has gone
    // programatically wrong with the layers.
    hard_assert(code_container.has_valid_contents);

    bool is_modifier_code = key_helper_is_modifier_keycode_container(code_container);

    // If we are handling a non-modifier press then any chord we were
    // pressing has now been completed.
    keyboard_state_set_has_chord_action_been_performed(!is_modifier_code);

    //TODO double tap action handling

    bool should_report_code = true;
    switch (code_container.hid_keycode)
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
        key_state_press(code_container, false);

        if (!is_modifier_code)
            keyboard_state_set_repeat_state(code_container);
    }

    if (ENABLE_SERIAL_LOGGING && should_report_code)
    {
        printf("Keycode value pressed: %u\n", code_container.hid_keycode);
    }
}

