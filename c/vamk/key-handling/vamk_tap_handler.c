///Imports
#include <stdbool.h>
#include "pico/stdlib.h"
#include "time.h"
#include "hardware/timer.h"
#include "vamk_config.h"
#include "vamk_keymap_config.h"
#include "vamk_key_state.h"
#include "vamk_keyboard_state.h"
#include "vamk_layer_info.h"
#include "vamk_press_helper.h"
#include "vamk_tap_handler.h"
#include "vamk_types.h"

///Local Declarations
struct tap_event_params_t
{
    absolute_time_t key_down_time;
    struct modifier_collection_t modifiers_at_key_down;
    uint8_t layer_index_at_key_down;
};

///Static Global Variables
//TODO replace with hashmap
static struct tap_event_params_t _key_down_params_controller[ROW_COUNT][COLUMN_COUNT] = {0};
static struct tap_event_params_t _key_down_params_peripheral[ROW_COUNT][COLUMN_COUNT] = {0};

///Static Functions
static struct tap_event_params_t* get_key_down_params_pointer(int16_t row, int16_t col, key_event_source_identifier_t key_event_source)
{
    switch (key_event_source)
    {
        case CONTROLLER_IDENTIFIER:
            return &_key_down_params_controller[row][col];
        case PERIPHERAL_IDENTIFIER:
            return &_key_down_params_peripheral[row][col];
        default:
            return NULL;
    }
}

static void mark_key_down(int16_t row, int16_t col, uint8_t layer_index, key_event_source_identifier_t key_event_source)
{
    struct tap_event_params_t *key_down_params_ptr = get_key_down_params_pointer(row, col, key_event_source);

    if (key_down_params_ptr == NULL)
        return;

    key_down_params_ptr->key_down_time = get_absolute_time();

    struct modifier_collection_t current_modifiers = keyboard_state_get_currently_pressed_modifiers();
    key_down_params_ptr->modifiers_at_key_down.modifier_count = current_modifiers.modifier_count;
    memcpy(&(key_down_params_ptr->modifiers_at_key_down.modifiers), &(current_modifiers.modifiers), HID_REPORT_KEYCODE_ARRAY_LENGTH);

    key_down_params_ptr->layer_index_at_key_down = layer_index;
}

///Extern Functions
void tap_handler_on_switch_press(uint16_t row, uint16_t col, uint8_t layer_index, key_event_source_identifier_t key_event_source)
{
    struct hid_keycode_container_t code_container =
        layer_info_get_tap_keycode_at(row, col, layer_index, key_event_source);

    if (!code_container.has_valid_contents || code_container.hid_keycode == KC_NULL)
        // We do not need to handle this event.
        return;

    mark_key_down(row, col, layer_index, key_event_source);
}

bool tap_handler_on_switch_release(uint16_t row, uint16_t col, uint8_t layer_index, key_event_source_identifier_t key_event_source)
{
    struct tap_event_params_t *key_down_params_ptr = get_key_down_params_pointer(row, col, key_event_source);
    if (key_down_params_ptr == NULL)
        return false;

    struct hid_keycode_container_t code_container =
        layer_info_get_tap_keycode_at(row, col, key_down_params_ptr->layer_index_at_key_down, key_event_source);

    if (!code_container.has_valid_contents || code_container.hid_keycode == KC_NULL)
        // We do not need to handle this event.
        return false;

    // Calc the interval and convert to milliseconds
    uint64_t elapsed_interval_ms = (absolute_time_diff_us(key_down_params_ptr->key_down_time, get_absolute_time()))/1000;
    if (elapsed_interval_ms <= TAP_ACTION_TIMEOUT_MS
        && elapsed_interval_ms > TAP_ACTION_TIMEIN_MS)
    {
        press_helper_momentary_press_with_modifiers(code_container, key_down_params_ptr->modifiers_at_key_down);
        return true;
    }

    return false;
}
