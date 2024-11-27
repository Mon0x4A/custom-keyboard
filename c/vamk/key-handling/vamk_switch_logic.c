
///Imports
#include "pico/stdlib.h"
#include "vamk_types.h"
#include "vamk_switch_logic.h"
#include "vamk_key_timer.h"
#include "vamk_keyboard_state.h"

///Local Declarations
///Static Constants
///Static Global Variables
///Static Functions

///Extern Functions
void switch_logic_press_handler(uint16_t row, uint16_t col, key_event_source_identifier_t key_event_source)
{
    uint8_t current_layer = keyboard_state_get_current_layer_index();
    struct key_event_location_t key_location =
    {
        .row = row,
        .column = col,
        .key_event_source = key_event_source,
    };
    key_timer_mark_key_down(key_location, current_layer);
}

void switch_logic_release_handler(uint16_t row, uint16_t col, key_event_source_identifier_t key_event_source)
{
    struct key_event_location_t key_location =
    {
        .row = row,
        .column = col,
        .key_event_source = key_event_source,
    };
    key_timer_mark_key_up(key_location);
}
