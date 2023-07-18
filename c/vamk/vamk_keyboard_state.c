///Imports
#include "stdbool.h"
#include "pico/stdlib.h"
#include "vamk_config.h"
#include "vamk_keyboard_state.h"

///Static Constants
static const uint8_t DEFAULT_LAYER_INDEX = 0;

///Static Global Variables
static bool _has_chord_action_been_performed = false;
static uint8_t _last_pressed_layer_index = 0;

static int8_t _quant_layer_mod_pressed[MAX_LAYER_COUNT] = {0};

///Static Functions
static int imax(int a, int b)
{
    return a > b ? a : b;
}

///Extern Functions
uint8_t keyboard_state_get_current_layer_index(void)
{
    // Just return the last layer pressed if available.
    if (_last_pressed_layer_index != 0)
        return _last_pressed_layer_index;

    // Otherwise start counting backwards by index.
    // TODO both these could easily be represented as a
    // layer queue in the future.
    for (uint8_t i = MAX_LAYER_COUNT-1; i > 0; i--)
    {
        if (keyboard_state_get_is_layer_modifier_pressed(i))
            return i;
    }

    // If nothing is pressed, return the default layer.
    return DEFAULT_LAYER_INDEX;
}

bool keyboard_state_get_is_layer_modifier_pressed(uint8_t layer_index)
{
    return _quant_layer_mod_pressed[layer_index] > 0;
}

bool keyboard_state_set_is_layer_modifier_pressed(uint8_t layer_index, bool is_layer_modifier_pressed)
{
    if (is_layer_modifier_pressed)
    {
        _quant_layer_mod_pressed[layer_index]++;
        _last_pressed_layer_index = layer_index;
    }
    else
    {
        _quant_layer_mod_pressed[layer_index] = imax(_quant_layer_mod_pressed[layer_index]-1, 0);
        _last_pressed_layer_index = 0;
    }
}

bool keyboard_state_get_has_chord_action_been_performed(void)
{
    return _has_chord_action_been_performed;
}

void keyboard_state_set_has_chord_action_been_performed(bool has_chord_action_been_performed)
{
    _has_chord_action_been_performed = has_chord_action_been_performed;
}

