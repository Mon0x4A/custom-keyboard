
///Imports
#include "stdbool.h"
#include "pico/stdlib.h"
#include "vamk_keyboard_state.h"

///Static Global Variables
static bool _has_chord_action_been_performed = false;
static uint8_t _current_layer_index = 0;

///Local Definitions

///Static Functions

///Extern Functions
uint8_t keyboard_state_get_current_layer_index(void)
{
    return _current_layer_index;
}

void keyboard_state_set_current_layer_index(uint8_t current_layer_index)
{
    _current_layer_index = current_layer_index;
}

bool keyboard_state_get_has_chord_action_been_performed(void)
{
    return _has_chord_action_been_performed;
}

void keyboard_state_set_has_chord_action_been_performed(bool has_chord_action_been_performed)
{
    _has_chord_action_been_performed = has_chord_action_been_performed;
}
