///Imports
#include <stdbool.h>
#include "pico/stdlib.h"
#include "vamk_config.h"
#include "vamk_key_state.h"
#include "vamk_layer_info.h"
#include "vamk_press_handler.h"
#include "vamk_tap_handler.h"
#include "vamk_types.h"

///Global Variables

///Function Declarations

///Static (Private) Functions
//#include "hardware/timer.h"
////TODO this timer code could be very useful for key events
//// Timer example code - This example fires off the callback after 2000ms
//add_alarm_in_ms(2000, alarm_callback, NULL, false);
//// And the callback:
//int64_t alarm_callback(alarm_id_t id, void *user_data) {
//    // Put your timeout handler code in here
//    return 0;
//}

///Public Functions
void press_handler_on_switch_press(uint16_t row, uint16_t col, keyboard_side_t keyboard_side)
{
    uint8_t current_layer = key_state_get_current_layer_index();

    tap_handler_on_switch_press(row, col, current_layer, keyboard_side);

    struct hid_keycode_container_t code_container =
        layer_info_get_base_keycode_at(row, col, current_layer, keyboard_side);

    // If we are receiving invalid codes, something has gone
    // programatically wrong with the layers.
    hard_assert(code_container.has_valid_contents);

    //TODO single tap action handling
    //TODO double tap action handling
    //TODO else notify chord action performed

    //TODO record repeat state

    bool should_report_code = true;
    switch (code_container.hid_keycode)
    {
        case KC_LM1:
            should_report_code = false;
            key_state_set_current_layer_index(1);
            printf("Entering layer 1\n");
            break;
        case KC_LM2:
            should_report_code = false;
            key_state_set_current_layer_index(2);
            printf("Entering layer 2\n");
            break;
        case KC_NULL:
        //HID_KEY_NONE as well
            // Nothing to do if we hit a null code.
            should_report_code = false;
            break;
        //case KEY_LEFT_ALT:
        //case KEY_RIGHT_ALT:
        //    break;
        //case KEY_LEFT_GUI:
        //case KEY_RIGHT_GUI:
        //    break;
        //case KEY_LEFT_CTRL:
        //case KEY_RIGHT_CTRL:
        //    break;
        //case KEY_LEFT_SHIFT:
        //case KEY_RIGHT_SHIFT:
        //    break;
        //default:
        //    break;
    }

    if (ENABLE_KEYBOARD_COMMANDS && should_report_code)
    {
        key_state_press(code_container, false);
    }

    if (ENABLE_SERIAL_LOGGING && should_report_code)
    {
        printf("Keycode value pressed: %u\n", code_container.hid_keycode);
    }
}

