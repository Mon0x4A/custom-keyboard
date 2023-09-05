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
    struct modifier_collection_t modifiers_at_key_down[HID_REPORT_KEYCODE_ARRAY_LENGTH];
};

///Static Global Variables
static struct tap_event_params_t _key_down_params_left[ROW_COUNT][COLUMN_COUNT] = {0};
static struct tap_event_params_t _key_down_params_right[ROW_COUNT][COLUMN_COUNT] = {0};

///Static Functions
static struct tap_event_params_t* get_key_down_params_pointer(int16_t row, int16_t col, keyboard_side_t keyboard_side)
{
    switch (keyboard_side)
    {
        case LEFT_SIDE:
            return &_key_down_params_left[row][col];
        case RIGHT_SIDE:
            return &_key_down_params_right[row][col];
        default:
            return NULL;
    }
}

static void mark_key_down(int16_t row, int16_t col, keyboard_side_t keyboard_side)
{
    struct tap_event_params_t *key_down_params_ptr = get_key_down_params_pointer(row, col, keyboard_side);

    if (key_down_params_ptr == NULL)
        return;

    key_down_params_ptr->key_down_time = get_absolute_time();
    struct modifier_collection_t current_modifiers = keyboard_state_get_currently_pressed_modifiers();
    (*key_down_params_ptr->modifiers_at_key_down).modifier_count = current_modifiers.modifier_count;
    memcpy(&(*key_down_params_ptr->modifiers_at_key_down).modifiers, &current_modifiers.modifiers, HID_REPORT_KEYCODE_ARRAY_LENGTH);
}

///Extern Functions
void tap_handler_on_switch_press(uint16_t row, uint16_t col, uint8_t layer_index, keyboard_side_t keyboard_side)
{
    struct hid_keycode_container_t code_container =
        layer_info_get_tap_keycode_at(row, col, layer_index, keyboard_side);

    if (!code_container.has_valid_contents || code_container.hid_keycode == KC_NULL)
        // We do not need to handle this event.
        return;

    mark_key_down(row, col, keyboard_side);
}

bool tap_handler_on_switch_release(uint16_t row, uint16_t col, uint8_t layer_index, keyboard_side_t keyboard_side)
{
    struct tap_event_params_t *key_down_params_ptr = get_key_down_params_pointer(row, col, keyboard_side);
    if (key_down_params_ptr == NULL)
        return false;

    struct hid_keycode_container_t code_container =
        layer_info_get_tap_keycode_at(row, col, layer_index, keyboard_side);

    if (!code_container.has_valid_contents || code_container.hid_keycode == KC_NULL)
        // We do not need to handle this event.
        return false;

    // Calc the interval and convert to milliseconds
    uint64_t elapsed_interval_ms = (absolute_time_diff_us(key_down_params_ptr->key_down_time, get_absolute_time()))/1000;
    if (elapsed_interval_ms <= TAP_ACTION_TIMEOUT_MS
        && elapsed_interval_ms > TAP_ACTION_TIMEIN_MS)
    {
        press_helper_momentary_press_with_modifiers(code_container, (*key_down_params_ptr->modifiers_at_key_down));
        return true;
    }

    return false;
}
