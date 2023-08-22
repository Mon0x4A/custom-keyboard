
///Imports
#include <stdbool.h>
#include <malloc.h>
#include "pico/stdlib.h"
#include "time.h"
#include "hardware/timer.h"
#include "vamk_config.h"
#include "vamk_hold_delay_handler.h"
#include "vamk_keymap_config.h"
#include "vamk_layer_info.h"
#include "vamk_types.h"

///Static Constants

///Local Declarations
struct delay_callback_params_t
{
    uint16_t row;
    uint16_t col;
    keyboard_side_t keyboard_side;
    volatile bool *should_handle_ptr;
};

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

static int64_t delay_callback(alarm_id_t id, void *callback_params)
{
    struct delay_callback_params_t *callback_params_ptr = callback_params;
    if (*callback_params_ptr->should_handle_ptr)
    {
        printf(">>DELAY CALLBACK FIRED %d,%d\n", callback_params_ptr->row, callback_params_ptr->col);
        //TODO fetch our keycode and send that to the handling function.
        //printf("%d", keycode_container.hid_keycode);
    }

    // Handling has been completed.
    (*callback_params_ptr->should_handle_ptr) = false;
    free(callback_params_ptr);

    return 0;
}

///Extern Functions
void hold_delay_handler_on_switch_press(uint16_t row, uint16_t col, uint8_t layer_index, keyboard_side_t keyboard_side)
{
    struct delay_callback_params_t *callback_params_ptr = malloc(sizeof(callback_params_ptr));
    callback_params_ptr->row = row;
    callback_params_ptr->col = col;
    callback_params_ptr->keyboard_side = keyboard_side;
    callback_params_ptr->should_handle_ptr = get_callback_should_handle(row, col, keyboard_side);

    (*callback_params_ptr->should_handle_ptr) = true;

    // Start a timer with the intent to handle the action later.
    alarm_id_t timerId = add_alarm_in_ms(HOLD_DELAY_THRESHOLD_MS, delay_callback, (void*)callback_params_ptr, false);
}

void hold_delay_handler_on_switch_release(uint16_t row, uint16_t col, uint8_t layer_index, keyboard_side_t keyboard_side)
{
    // If the key has been released, we have either already handled
    // the event, or setting to false will prevent it from executing.
    volatile bool *should_handle_ptr = get_callback_should_handle(row, col, keyboard_side);
    (*should_handle_ptr) = false;
}
