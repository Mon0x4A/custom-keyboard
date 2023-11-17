///Imports
#include "pico/stdlib.h"
#include "vamk_config.h"
#include "vamk_hold_delay_handler.h"
#include "vamk_keymap_config.h"
#include "vamk_key_helper.h"
#include "vamk_key_state.h"
#include "vamk_keyboard_state.h"
#include "vamk_keyboard_state.h"
#include "vamk_layer_info.h"
#include "vamk_release_handler.h"
#include "vamk_tap_handler.h"
#include "vamk_types.h"
#include "tusb.h"

///Static Global Variables

///Static Functions

///Extern Functions
void release_handler_on_switch_release(uint16_t row, uint16_t col, key_event_source_identifier_t keyboard_side)
{
    uint8_t current_layer = keyboard_state_get_current_layer_index();

    struct hid_keycode_container_t code_container =
        layer_info_get_base_keycode_at(row, col, current_layer, keyboard_side);

    if (!keyboard_state_get_has_chord_action_been_performed())
        tap_handler_on_switch_release(row, col, current_layer, keyboard_side);

    bool is_modifier_code = key_helper_is_modifier_keycode_container(code_container);
    if (!is_modifier_code)
    {
        keyboard_state_set_has_chord_action_been_performed(false);
    }

    hold_delay_handler_on_switch_release(row, col, current_layer, keyboard_side);

    //TODO need to create a release helper just like the press one.
    bool need_remove_code_from_report = true;
    switch (code_container.hid_keycode)
    {
        case KC_LM0:
            need_remove_code_from_report = false;
            keyboard_state_set_is_layer_modifier_pressed(0, false);
            printf("Leaving layer 0\n");
            break;
        case KC_LM1:
            need_remove_code_from_report = false;
            keyboard_state_set_is_layer_modifier_pressed(1, false);
            printf("Leaving layer 1\n");
            break;
        case KC_LM2:
            need_remove_code_from_report = false;
            keyboard_state_set_is_layer_modifier_pressed(2, false);
            printf("Leaving layer 2\n");
            break;
        case KC_LM3:
            need_remove_code_from_report = false;
            keyboard_state_set_is_layer_modifier_pressed(3, false);
            printf("Leaving layer 3\n");
            break;
        case KC_LM4:
            need_remove_code_from_report = false;
            keyboard_state_set_is_layer_modifier_pressed(4, false);
            printf("Leaving layer 4\n");
            break;
        case KC_LM5:
            need_remove_code_from_report = false;
            keyboard_state_set_is_layer_modifier_pressed(5, false);
            printf("Leaving layer 5\n");
            break;
        case KC_LM6:
            need_remove_code_from_report = false;
            keyboard_state_set_is_layer_modifier_pressed(6, false);
            printf("Leaving layer 6\n");
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
            need_remove_code_from_report = false;
            break;
        default:
            break;
    }

    for (int i = 0; i < LAYER_COUNT; i++)
    {
        // Make sure all keycodes at this location across all layers
        // have been removed from the report.
        struct hid_keycode_container_t code_container =
            layer_info_get_base_keycode_at(row, col, i, keyboard_side);

        if (key_helper_is_layer_keycode(code_container.hid_keycode))
        {
            keyboard_state_set_is_layer_modifier_pressed(
                key_helper_get_layer_index_from_layer_keycode(code_container.hid_keycode),
                false);
            if (ENABLE_SERIAL_LOGGING)
                printf("Layer value released: %u\n", code_container.hid_keycode);
        }

        if (ENABLE_KEYBOARD_COMMANDS && need_remove_code_from_report)
            key_state_release(code_container.hid_keycode);
        if (ENABLE_SERIAL_LOGGING && need_remove_code_from_report)
            printf("Keycode value released: %u\n", code_container.hid_keycode);
    }
}
