
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
static bool should_add_container(struct hid_keycode_container_t value_target)
{
    return value_target.has_valid_contents && value_target.hid_keycode != KC_NULL;
}

static bool container_arr_contains(struct hid_keycode_container_t* container_arr, size_t len,
    struct hid_keycode_container_t value_target)
{
    for (int i = 0; i < len; i++)
        if (((container_arr+i)->hid_keycode == value_target.hid_keycode)
            && ((container_arr+i)->modifier == value_target.modifier)
            && ((container_arr+i)->has_valid_contents == value_target.has_valid_contents))
            return true;
    return false;
}

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

    struct hid_keycode_container_t containers_to_release[MAX_LAYER_COUNT*3];
    uint8_t container_count = 0;

    for (int i = 0; i < LAYER_COUNT; i++)
    {
        // Make sure all keycodes at this location across all layers
        // have been removed from the report.
        struct hid_keycode_container_t code_container =
            layer_info_get_base_keycode_at(
                key_location.row, key_location.column, i, key_location.key_event_source);
        if (should_add_container(code_container) && !container_arr_contains(containers_to_release, container_count, code_container))
            containers_to_release[container_count++] = code_container;

        code_container =
            layer_info_get_hold_delay_keycode_at(key_location.row, key_location.column, i, key_location.key_event_source);
        if (should_add_container(code_container) && !container_arr_contains(containers_to_release, container_count, code_container))
            containers_to_release[container_count++] = code_container;

        code_container =
            layer_info_get_tap_keycode_at(key_location.row, key_location.column, i, key_location.key_event_source);
        if (should_add_container(code_container) && !container_arr_contains(containers_to_release, container_count, code_container))
            containers_to_release[container_count++] = code_container;
    }

    for (int i = 0; i < container_count; i++)
        release_helper_key_release(containers_to_release[i]);

    if (key_event_report.elapsed_interval_ms <= TAP_ACTION_TIMEOUT_MS
        && key_event_report.elapsed_interval_ms > TAP_ACTION_TIMEIN_MS)
    {
        struct hid_keycode_container_t code_container =
            layer_info_get_tap_keycode_at(key_location.row, key_location.column, key_event_report.layer_index_at_key_down, key_location.key_event_source);

        if (code_container.has_valid_contents && code_container.hid_keycode != KC_NULL)
            press_helper_momentary_press_with_modifiers(code_container, key_event_report.modifiers_at_key_down);
    }
}

void key_logic_delay_handler(struct key_event_location_t key_location, struct key_event_report_t key_event_report)
{
    struct hid_keycode_container_t code_container =
        layer_info_get_hold_delay_keycode_at(
            key_location.row, key_location.column, key_event_report.layer_index_at_key_down, key_location.key_event_source);

    if (!code_container.has_valid_contents || code_container.hid_keycode == KC_NULL)
        return;

    if (key_helper_is_modifier_keycode_container(code_container))
        press_helper_key_press(code_container);
    else
        press_helper_momentary_press_with_modifiers(code_container, key_event_report.modifiers_at_key_down);
}
