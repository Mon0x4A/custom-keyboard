
///Imports
#include <stdbool.h>
#include <malloc.h>
#include "pico/stdlib.h"
#include "time.h"
#include "hardware/timer.h"
#include "vamk_config.h"
#include "vamk_hold_delay_handler.h"
#include "vamk_keyboard_state.h"
#include "vamk_keymap_config.h"
#include "vamk_layer_info.h"
#include "vamk_press_helper.h"
#include "vamk_types.h"

///Static Constants

///Local Declarations
struct callback_event_t
{
    alarm_id_t event_id;
    bool should_handle:1;
};

struct delay_callback_params_t
{
    struct hid_keycode_container_t keycode_container;
    struct modifier_collection_t modifiers_at_key_down;
    volatile struct callback_event_t *current_event_ptr;
};

///Static Global Variables
//TODO replace with queue
static volatile struct callback_event_t _c_delay_callback_should_handle[ROW_COUNT][COLUMN_COUNT] = {0};
static volatile struct callback_event_t _p_delay_callback_should_handle[ROW_COUNT][COLUMN_COUNT] = {0};

///Static Functions
static volatile struct callback_event_t* get_current_callback_event(uint16_t row, uint16_t col, key_event_source_identifier_t key_event_source)
{
    switch (key_event_source)
    {
        case CONTROLLER_IDENTIFIER:
            return &_c_delay_callback_should_handle[row][col];
        case PERIPHERAL_IDENTIFIER:
            return &_p_delay_callback_should_handle[row][col];
        default:
            hard_assert(false);
            break;
    }
}

static int64_t delay_callback(alarm_id_t id, void *callback_params)
{
    struct delay_callback_params_t *callback_params_ptr = callback_params;
    // We only handle this event if the most recent event shares the same id
    // and has not been handled already.
    volatile struct callback_event_t *current_event_ptr = callback_params_ptr->current_event_ptr;
    if (((current_event_ptr->event_id) == id) && (current_event_ptr->should_handle))
    {
        press_helper_momentary_press(callback_params_ptr->keycode_container);
    }

    // Handling has been completed.
    free(callback_params_ptr);

    return 0;
}

///Extern Functions
void hold_delay_handler_on_switch_press(uint16_t row, uint16_t col, uint8_t layer_index, key_event_source_identifier_t key_event_source)
{
    struct delay_callback_params_t *callback_params_ptr = malloc(sizeof(struct delay_callback_params_t));
    hard_assert(callback_params_ptr != NULL);

    callback_params_ptr->keycode_container = layer_info_get_hold_delay_keycode_at(row, col, layer_index, key_event_source);
    callback_params_ptr->modifiers_at_key_down = keyboard_state_get_currently_pressed_modifiers();

    volatile struct callback_event_t *event_ptr = get_current_callback_event(row, col, key_event_source);
    callback_params_ptr->current_event_ptr = event_ptr;

    // Start a timer with the intent to handle the action later.
    alarm_id_t event_id = add_alarm_in_ms(HOLD_DELAY_THRESHOLD_MS, delay_callback, (void*)callback_params_ptr, false);

    callback_params_ptr->current_event_ptr->event_id = event_id;
    callback_params_ptr->current_event_ptr->should_handle = true;
}

void hold_delay_handler_on_switch_release(uint16_t row, uint16_t col, uint8_t layer_index, key_event_source_identifier_t key_event_source)
{
    // If the key has been released, we have either already handled
    // the event, or setting to false will prevent it from executing.
    volatile struct callback_event_t *current_event_ptr = get_current_callback_event(row, col, key_event_source);
    current_event_ptr->should_handle = false;
}
