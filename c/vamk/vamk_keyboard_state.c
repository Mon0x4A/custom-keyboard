
///Imports
#include "math.h"
#include "stdbool.h"
#include "pico/stdlib.h"
#include "vamk_config.h"
#include "vamk_keyboard_state.h"

///Static Global Variables
static bool _has_chord_action_been_performed = false;
static uint8_t _last_pressed_layer_index = 0;

static int8_t _quant_layer_mod_pressed[MAX_LAYER_COUNT] = {0};

///Local Definitions

///Static Functions
static int max(int a, int b)
{
    return a > b ? a : b;
}

///Extern Get Functions
uint8_t keyboard_state_get_current_layer_index(void)
{
    if (_last_pressed_layer_index != 0)
        return _last_pressed_layer_index;

    for(uint8_t i = MAX_LAYER_COUNT-1; i > 0; i--)
    {
        if (keyboard_state_get_is_layer_modifier_pressed(i))
            return i;
    }
    return 0;
}

bool keyboard_state_get_has_chord_action_been_performed(void)
{
    return _has_chord_action_been_performed;
}

bool keyboard_state_get_is_layer_modifier_pressed(uint8_t layer_index)
{
    return _quant_layer_mod_pressed[layer_index] > 0;
}

///Extern Set Functions
void keyboard_state_set_has_chord_action_been_performed(bool has_chord_action_been_performed)
{
    _has_chord_action_been_performed = has_chord_action_been_performed;
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
        _quant_layer_mod_pressed[layer_index] = max(_quant_layer_mod_pressed[layer_index]-1, 0);
        _last_pressed_layer_index = 0;
    }
}

///Extern Functions
