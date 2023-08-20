
///Imports
#include <stdbool.h>
#include "pico/stdlib.h"
#include "time.h"
#include "hardware/timer.h"
#include "vamk_config.h"
#include "vamk_hold_delay_handler.h"
#include "vamk_keymap_config.h"
#include "vamk_layer_info.h"
#include "vamk_types.h"

///Static Constant Variables

///Static Global Variables
static volatile bool _l_delay_callback_should_handle[ROW_COUNT][COLUMN_COUNT] = {0};
static volatile bool _r_delay_callback_should_handle[ROW_COUNT][COLUMN_COUNT] = {0};

///Static Functions
static volatile bool* get_callback_should_handle(uint16_t row, uint16_t col, keyboard_side_t keyboard_side)
{
    switch (keyboard_side)
    {
        case LEFT_SIDE:
            return &_l_delay_callback_should_handle[row][col];
        case RIGHT_SIDE:
            return &_r_delay_callback_should_handle[row][col];
        default:
            hard_assert(false);
            break;
    }
}

static int64_t delay_callback(alarm_id_t id, void *should_handle)
{
    volatile bool *should_handle_ptr = should_handle;
    if (*should_handle_ptr)
    {
        //TODO here
        printf(">>DELAY CALLBACK FIRED\n");
        //printf("%d", keycode_container.hid_keycode);
    }

    // Handling has been completed.
    (*should_handle_ptr) = false;
    return 0;
}

///Extern Functions
void hold_delay_handler_on_switch_press(uint16_t row, uint16_t col, uint8_t layer_index, keyboard_side_t keyboard_side)
{
    // Start a timer with the intent to handle the action later.
    volatile bool *should_handle_ptr = get_callback_should_handle(row, col, keyboard_side);
    (*should_handle_ptr) = true;
    alarm_id_t timerId = add_alarm_in_ms(HOLD_DELAY_THRESHOLD_MS, delay_callback, (void*)should_handle_ptr, false);
}

void hold_delay_handler_on_switch_release(uint16_t row, uint16_t col, uint8_t layer_index, keyboard_side_t keyboard_side)
{
    // If the key has been released, we have either already handled
    // the event, or setting to false will prevent it from executing.
    volatile bool *should_handle_ptr = get_callback_should_handle(row, col, keyboard_side);
    (*should_handle_ptr) = false;
}

//#include "hardware/timer.h"
////TODO this timer code could be very useful for key events
///static inline alarm_id_t add_alarm_in_ms(uint32_t ms, alarm_callback_t callback, void *user_data, bool fire_if_past)
//// Timer example code - This example fires off the callback after 2000ms
//add_alarm_in_ms(2000, alarm_callback, NULL, false);
//// And the callback:
//int64_t alarm_callback(alarm_id_t id, void *user_data) {
//    // Put your timeout handler code in here
//    return 0;
//}
