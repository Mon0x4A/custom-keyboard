
///Imports
#include <stdlib.h>
#include "pico/stdlib.h"
#include "time.h"
#include "vamk_config.h"
#include "vamk_keyboard_state.h"
#include "vamk_keymap_config.h"
#include "vamk_key_timer.h"

///Local Declarations
struct key_down_event_t
{
    absolute_time_t key_down_time;
    struct modifier_collection_t modifiers_at_key_down;
    uint8_t layer_index_at_key_down;
    alarm_id_t current_delay_event_timer_id;
    volatile bool is_key_down:1;
    volatile bool is_valid:1;
};

///Static Constants
///Static Global Variables
static struct key_down_event_t _key_down_event_controller[ROW_COUNT][COLUMN_COUNT] = {0};
static struct key_down_event_t _key_down_event_peripheral[ROW_COUNT][COLUMN_COUNT] = {0};

static key_timer_key_down_event_callback_params_t _key_down_callback = NULL;
static key_timer_key_up_event_callback_params_t _key_up_callback = NULL;
static key_timer_key_delay_event_callback_params_t _key_delay_callback = NULL;

///Static Functions
static struct key_down_event_t* get_key_down_event_pointer(struct key_event_location_t key_location)
{
    switch (key_location.key_event_source)
    {
        case CONTROLLER_IDENTIFIER:
            return &_key_down_event_controller[key_location.row][key_location.column];
        case PERIPHERAL_IDENTIFIER:
            return &_key_down_event_peripheral[key_location.row][key_location.column];
        default:
            return NULL;
    }
}

static struct key_event_report_t build_event_report(struct key_event_location_t key_location)
{
    struct key_down_event_t *key_down_event_ptr = get_key_down_event_pointer(key_location);

    if (key_down_event_ptr == NULL)
        hard_assert(false); //TODO out of bounds console message.

    struct key_event_report_t event_report = {0};

    // Calc the interval, convert to milliseconds.
    uint64_t elapsed_interval_ms = (absolute_time_diff_us(key_down_event_ptr->key_down_time, get_absolute_time()))/1000;
    event_report.elapsed_interval_ms = elapsed_interval_ms;
    event_report.modifiers_at_key_down = key_down_event_ptr->modifiers_at_key_down;
    event_report.layer_index_at_key_down = key_down_event_ptr->layer_index_at_key_down;
    event_report.is_valid = true;

    return event_report;
}

static void try_invoke_key_down_callback(struct key_event_location_t key_location)
{
    if (_key_down_callback == NULL)
        return;
    struct key_event_report_t key_event_report = build_event_report(key_location);
    _key_down_callback(key_location, key_event_report);
}

static void try_invoke_key_up_callback(struct key_event_location_t key_location)
{
    if (_key_up_callback == NULL)
        return;
    struct key_event_report_t key_event_report = build_event_report(key_location);
    _key_up_callback(key_location, key_event_report);
}

static void try_invoke_key_delay_callback(struct key_event_location_t key_location)
{
    if (_key_delay_callback == NULL)
        return;
    struct key_event_report_t key_event_report = build_event_report(key_location);
    _key_delay_callback(key_location, key_event_report);
}

static int64_t key_delay_callback(alarm_id_t alarm_id, void *callback_params_key_location_ptr)
{
    struct key_event_location_t *key_event_location_ptr = callback_params_key_location_ptr;
    struct key_down_event_t *key_down_event_ptr = get_key_down_event_pointer(*key_event_location_ptr);

    if ((key_down_event_ptr->current_delay_event_timer_id) == alarm_id
        && key_down_event_ptr->is_valid
        && key_down_event_ptr->is_key_down)
    {
        try_invoke_key_delay_callback(*key_event_location_ptr);
    }

    // Handling has been completed.
    free(callback_params_key_location_ptr);

    return 0;
}

///Extern Functions
void key_timer_mark_key_down(struct key_event_location_t key_location, uint8_t layer_index)
{
    struct key_down_event_t *key_down_event_ptr = get_key_down_event_pointer(key_location);

    if (key_down_event_ptr == NULL)
        hard_assert(false); //TODO out of bounds console message.

    key_down_event_ptr->key_down_time = get_absolute_time();
    key_down_event_ptr->modifiers_at_key_down = keyboard_state_get_currently_pressed_modifiers();
    key_down_event_ptr->layer_index_at_key_down = layer_index;

    struct key_event_location_t *alarm_callback_key_location_ptr = malloc(sizeof(struct key_event_location_t));
    hard_assert(alarm_callback_key_location_ptr != NULL);

    *alarm_callback_key_location_ptr = key_location;

    // Start a timer with the intent to handle the action later.

    uint16_t col_index = key_location.key_event_source == PERIPHERAL_IDENTIFIER
        ? key_location.column + COLUMN_COUNT : key_location.column;
    uint16_t timer_override = DELAY_TIMER_OVERRIDES[key_location.row][col_index];
    uint16_t timer_duration = timer_override == 0 ? HOLD_DELAY_THRESHOLD_MS : timer_override;
    alarm_id_t event_id = add_alarm_in_ms(timer_duration, key_delay_callback, (void*)alarm_callback_key_location_ptr, false);

    key_down_event_ptr->current_delay_event_timer_id = event_id;
    key_down_event_ptr->is_key_down = true;
    key_down_event_ptr->is_valid = true;

    try_invoke_key_down_callback(key_location);
}

void key_timer_mark_key_up(struct key_event_location_t key_location)
{
    struct key_down_event_t *key_down_event_ptr = get_key_down_event_pointer(key_location);

    if (key_down_event_ptr == NULL)
        hard_assert(false); //TODO out of bounds console message.

    if (!(key_down_event_ptr->is_valid))
        // Nothing to do here.
        return;

    try_invoke_key_up_callback(key_location);

    // Clear out the event such that it does not get rehandled without being reinitialized.
    memset(key_down_event_ptr, 0, sizeof(struct key_down_event_t));
}

void key_timer_set_key_down_callback(key_timer_key_down_event_callback_params_t key_down_callback_ptr)
{
    _key_down_callback = key_down_callback_ptr;
}

void key_timer_set_key_up_callback(key_timer_key_up_event_callback_params_t key_up_callback_ptr)
{
    _key_up_callback = key_up_callback_ptr;
}

void key_timer_set_key_delay_callback(key_timer_key_delay_event_callback_params_t key_delay_callback_ptr)
{
    _key_delay_callback = key_delay_callback_ptr;
}

bool key_timer_is_key_down(struct key_event_location_t key_location)
{
    switch (key_location.key_event_source)
    {
        case CONTROLLER_IDENTIFIER:
            return _key_down_event_controller[key_location.row][key_location.column].is_key_down;
        case PERIPHERAL_IDENTIFIER:
            return _key_down_event_peripheral[key_location.row][key_location.column].is_key_down;
        default:
            hard_assert(false);
    }
}
