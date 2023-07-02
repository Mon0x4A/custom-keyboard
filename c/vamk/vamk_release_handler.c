///Imports
#include "pico/stdlib.h"
#include "vamk_config.h"
#include "vamk_key_state.h"
#include "vamk_layer_info.h"
#include "vamk_release_handler.h"
#include "vamk_types.h"

///Global Variables

///Function Declarations

///Static (Private) Functions

///Public Functions
void release_handler_on_switch_release(uint16_t row, uint16_t col, keyboard_side_t keyboard_side)
{
    uint8_t current_layer = key_state_get_current_layer_index();
    struct hid_keycode_container_t code_container =
        layer_info_get_keycode_at(row, col, current_layer, keyboard_side);

    //TODO record repeat state

    bool need_remove_code_from_report = true;
    switch (code_container.hid_keycode)
    {
        case KC_LM1:
            need_remove_code_from_report = false;
            key_state_set_current_layer_index(0);
            printf("Entering layer 0\n");
            break;
        case KC_LM2:
            need_remove_code_from_report = false;
            key_state_set_current_layer_index(0);
            printf("Entering layer 0\n");
            break;
        case KC_NULL:
        //HID_KEY_NONE as well
            // Nothing to do if we hit a null code.
            need_remove_code_from_report = false;
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

    for (int i = 0; i < LAYER_COUNT; i++)
    {
        // Make sure all keycodes at this location across all layers
        // have been removed from the report.
        struct hid_keycode_container_t code_container =
            //TODO side logic
            layer_info_get_keycode_at(row, col, i, LEFT_SIDE);

        if (ENABLE_KEYBOARD_COMMANDS && need_remove_code_from_report)
            key_state_release(code_container.hid_keycode);
        if (ENABLE_SERIAL_LOGGING && need_remove_code_from_report)
            printf("Keycode value released: %u\n", code_container.hid_keycode);
    }
}
