
///Imports
#include "pico/stdlib.h"
#include "vamk_types.h"
#include "vamk_layer_info.h"
#include "vamk_release_helper.h"
#include "vamk_press_helper.h"
#include "vamk_key_helper.h"
#include "vamk_key_logic.h"

///Local Declarations
///Static Constants
///Static Global Variables
///Static Functions

///Extern Functions
void key_logic_down_handler(struct key_event_location_t key_location, struct key_event_report_t key_event_report)
{
    struct hid_keycode_container_t code_container =
        layer_info_get_base_keycode_at(key_location.row, key_location.column, key_event_report.layer_index_at_key_down, key_location.key_event_source);

    if (code_container.has_valid_contents && code_container.hid_keycode != KC_NULL)
        press_helper_key_press(code_container);
}

void key_logic_up_handler(struct key_event_location_t key_location, struct key_event_report_t key_event_report)
{
    hard_assert(key_event_report.is_valid);

    if (key_event_report.elapsed_interval_ms <= TAP_ACTION_TIMEOUT_MS
        && key_event_report.elapsed_interval_ms > TAP_ACTION_TIMEIN_MS)
    {
        struct hid_keycode_container_t code_container =
            layer_info_get_tap_keycode_at(key_location.row, key_location.column, key_event_report.layer_index_at_key_down, key_location.key_event_source);

        if (code_container.has_valid_contents && code_container.hid_keycode != KC_NULL)
            press_helper_momentary_press_with_modifiers(code_container, key_event_report.modifiers_at_key_down);
    }

    //TODO makes sure we have a valid layer count value here
    for (int i = 0; i < LAYER_COUNT; i++)
    {
        // Make sure all keycodes at this location across all layers
        // have been removed from the report.
        struct hid_keycode_container_t code_container =
            layer_info_get_base_keycode_at(key_location.row, key_location.column, key_event_report.layer_index_at_key_down, key_location.key_event_source);
        release_helper_key_release(code_container);

        code_container =
            layer_info_get_hold_delay_keycode_at(key_location.row, key_location.column, key_event_report.layer_index_at_key_down, key_location.key_event_source);
        release_helper_key_release(code_container);
    }
}

void key_logic_delay_handler(struct key_event_location_t key_location, struct key_event_report_t key_event_report)
{
    //TODO press helper (momentary) + layer/mod hold until release
    struct hid_keycode_container_t code_container =
        layer_info_get_hold_delay_keycode_at(key_location.row, key_location.column, key_event_report.layer_index_at_key_down, key_location.key_event_source);

    if (!code_container.has_valid_contents || code_container.hid_keycode == KC_NULL)
        return;

    if (key_helper_is_modifier_keycode_container(code_container))
        press_helper_key_press(code_container);
    else
        press_helper_momentary_press_with_modifiers(code_container, key_event_report.modifiers_at_key_down);
}
