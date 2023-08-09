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
#include "vamk_tap_handler.h"
#include "vamk_types.h"

///Static Global Variables
static absolute_time_t _since_key_down_left[ROW_COUNT][COLUMN_COUNT] = {0};
static absolute_time_t _since_key_down_right[ROW_COUNT][COLUMN_COUNT] = {0};

///Static Methods
//static int64_t tap_timeout_alarm_callback(alarm_id_t id, void *user_data)
//{
//    (void) id;
//
//    if (user_data != NULL)
//    {
//        bool *should_fire_index = (bool*)user_data;
//        (*should_fire_index) = 0;
//    }
//}

static absolute_time_t* get_key_down_time_pointer(int16_t row, int16_t col, keyboard_side_t keyboard_side)
{
    switch (keyboard_side)
    {
        case LEFT_SIDE:
            return &_since_key_down_left[row][col];
        case RIGHT_SIDE:
            return &_since_key_down_right[row][col];
        default:
            return NULL;
    }
}

static void mark_key_down_time(int16_t row, int16_t col, keyboard_side_t keyboard_side)
{
    absolute_time_t *key_down_ptr = get_key_down_time_pointer(row, col, keyboard_side);
    if (key_down_ptr != NULL)
        (*key_down_ptr) = get_absolute_time();
}

///Extern Functions
void tap_handler_on_switch_press(uint16_t row, uint16_t col, uint8_t layer_index, keyboard_side_t keyboard_side)
{
    struct hid_keycode_container_t code_container =
        layer_info_get_tap_keycode_at(row, col, layer_index, keyboard_side);

    if (!code_container.has_valid_contents || code_container.hid_keycode == KC_NULL)
        // We do not need to handle this event.
        return;

    mark_key_down_time(row, col, keyboard_side);
}

bool tap_handler_on_switch_release(uint16_t row, uint16_t col, uint8_t layer_index, keyboard_side_t keyboard_side)
{
    struct hid_keycode_container_t code_container =
        layer_info_get_tap_keycode_at(row, col, layer_index, keyboard_side);

    if (!code_container.has_valid_contents || code_container.hid_keycode == KC_NULL)
        // We do not need to handle this event.
        return false;

    absolute_time_t *key_down_at = get_key_down_time_pointer(row, col, keyboard_side);
    if (key_down_at == NULL)
        return false;

    // Calc the interval and convert to milliseconds
    uint64_t elapsed_interval_ms = (absolute_time_diff_us((*key_down_at), get_absolute_time()))/1000;
    if (elapsed_interval_ms <= TAP_ACTION_TIMEOUT_MS
        && elapsed_interval_ms > TAP_ACTION_TIMEIN_MS)
    {
        // We met our interval requirement and now need to handle the code.
        switch (code_container.hid_keycode)
        {
            //TODO need to handle the non-reporting keycodes here too.
            case KC_REPEAT:
                keyboard_state_send_repeat_state();
                break;
            default:
                key_state_press(code_container, true);
                keyboard_state_set_repeat_state(code_container);
                break;
        }
        return true;
    }

    return false;
}
