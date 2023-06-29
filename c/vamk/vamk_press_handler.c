///Imports
#include <stdbool.h>
#include "pico/stdlib.h"
#include "vamk_config.h"
#include "vamk_key_state.h"
#include "vamk_layer_info.h"
#include "vamk_press_handler.h"

//TODO here

///Global Variables

///Function Declarations

///Static (Private) Functions

///Public Functions
void press_handler_on_switch_press(uint16_t row, uint16_t col)
{
    uint8_t current_layer = key_state_get_current_layer_index();
    struct hid_keycode_container_t code_container =
        layer_info_get_keycode_at(row, col, current_layer, LEFT_SIDE);

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
            printf("Entering layer 1");
            break;
        case KC_LM2:
            should_report_code = false;
            key_state_set_current_layer_index(2);
            printf("Entering layer 2");
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
}

