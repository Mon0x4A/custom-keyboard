///Imports
#include <stdbool.h>
#include "pico/stdlib.h"
#include "vamk_config.h"
#include "vamk_keymap_config.h"
#include "vamk_key_helper.h"
#include "vamk_key_state.h"
#include "vamk_keyboard_state.h"
#include "vamk_layer_info.h"
#include "vamk_press_handler.h"
#include "vamk_press_helper.h"
#include "vamk_types.h"
#include "tusb.h"

///Static Global Variables
///Local Declarations

///Static Functions
static void keycode_press_internal(struct hid_keycode_container_t keycode_container,
    bool should_auto_release, bool should_release_on_next_report)
{
    // If we are receiving invalid codes, something has gone
    // programatically wrong.
    hard_assert(keycode_container.has_valid_contents);

    bool is_modifier_code = key_helper_is_modifier_keycode_container(keycode_container);

    // If we are handling a non-modifier press then any chord we were
    // pressing has now been completed.
    keyboard_state_set_has_chord_action_been_performed(
        keyboard_state_is_any_modifier_pressed()
        && !is_modifier_code
        && keycode_container.hid_keycode != KC_NULL);

    bool should_report_code = true;
    switch (keycode_container.hid_keycode)
    {
        case KC_LM0:
            should_report_code = false;
            keyboard_state_set_is_layer_modifier_pressed(0, true);
            printf("Entering layer 0\n");
            break;
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
        case KC_LM3:
            should_report_code = false;
            keyboard_state_set_is_layer_modifier_pressed(3, true);
            printf("Entering layer 3\n");
            break;
        case KC_LM4:
            should_report_code = false;
            keyboard_state_set_is_layer_modifier_pressed(4, true);
            printf("Entering layer 4\n");
            break;
        case KC_LM5:
            should_report_code = false;
            keyboard_state_set_is_layer_modifier_pressed(5, true);
            printf("Entering layer 5\n");
            break;
        case KC_LM6:
            should_report_code = false;
            keyboard_state_set_is_layer_modifier_pressed(6, true);
            printf("Entering layer 6\n");
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
        key_state_press(keycode_container, should_auto_release, should_release_on_next_report);

        if (!is_modifier_code)
            keyboard_state_set_repeat_state(keycode_container);
    }

    if (ENABLE_SERIAL_LOGGING && should_report_code)
    {
        printf("Keycode value pressed: %u\n", keycode_container.hid_keycode);
    }
}

///Extern Functions
void press_helper_key_press(struct hid_keycode_container_t keycode_container)
{
    keycode_press_internal(keycode_container, false, false);
}

void press_helper_momentary_press_with_modifiers(struct hid_keycode_container_t keycode_container,
    struct modifier_collection_t modifiers_collection)
{
    hard_assert(keycode_container.has_valid_contents);

    for (int i = 0; i < modifiers_collection.modifier_count; i++)
    {
        uint8_t modifier_code = modifiers_collection.modifiers[i];
        if (modifier_code == KC_NULL)
            continue;
        if (!key_helper_is_modifier_keycode(modifier_code))
            continue;

        struct hid_keycode_container_t modifier_code_container =
        {
            .hid_keycode = modifier_code,
            .modifier = 0,
            .has_valid_contents = true
        };
        press_helper_single_report_press(modifier_code_container);
    }

    press_helper_momentary_press(keycode_container);
}

void press_helper_momentary_press(struct hid_keycode_container_t keycode_container)
{
    keycode_press_internal(keycode_container, true, false);
}

void press_helper_single_report_press(struct hid_keycode_container_t keycode_container)
{
    keycode_press_internal(keycode_container, false, true);
}
