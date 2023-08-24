///Imports
#include "stdbool.h"
#include "pico/stdlib.h"
#include "vamk_config.h"
#include "vamk_keymap_config.h"
#include "vamk_key_helper.h"
#include "vamk_key_state.h"
#include "vamk_keyboard_state.h"
#include "vamk_types.h"

///Static Constants
static const uint8_t DEFAULT_LAYER_INDEX = 0;

///Static Global Variables
static bool _has_chord_action_been_performed = false;
static bool _is_waiting_for_chord_action = false;
static uint8_t _last_pressed_layer_index = 0;

static int8_t _quant_layer_mod_pressed[MAX_LAYER_COUNT] = {0};

static struct hid_keycode_container_t _repeat_code = {0};
static uint8_t _repeat_modifiers[HID_REPORT_KEYCODE_ARRAY_LENGTH] = {0};

///Static Functions
static int imax(int a, int b)
{
    return a > b ? a : b;
}

static void clear_repeat_modifers(void)
{
    for (int i = 0; i < HID_REPORT_KEYCODE_ARRAY_LENGTH; i++)
        _repeat_modifiers[i] = 0;
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
void keyboard_state_set_is_layer_modifier_pressed(uint8_t layer_index, bool is_layer_modifier_pressed)
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

bool keyboard_state_is_any_modifier_pressed(void)
{
    struct key_report_t current_report = key_state_preview_hid_report();
    for (int i = 0; i < HID_REPORT_KEYCODE_ARRAY_LENGTH; i++)
    {
        if (key_helper_is_modifier_keycode(current_report.keycodes[i]))
            return true;
    }
    return false;
}

void keyboard_state_set_repeat_state(struct hid_keycode_container_t hid_repeat_code)
{
    hard_assert(hid_repeat_code.has_valid_contents);
    _repeat_code = hid_repeat_code;

    // Grab the curret hid report state and search for modifiers.
    struct key_report_t report_preview = key_state_preview_hid_report();

    clear_repeat_modifers();
    uint8_t current_repeat_arr_index = 0;
    for (uint8_t i = 0; i < HID_REPORT_KEYCODE_ARRAY_LENGTH; i++)
    {
        uint8_t curr_report_hid_keycode = report_preview.keycodes[i];
        if (key_helper_is_modifier_keycode(curr_report_hid_keycode))
        {
            // Record any modifiers we find.
            _repeat_modifiers[current_repeat_arr_index] = curr_report_hid_keycode;
            current_repeat_arr_index++;
        }
    }
}
void keyboard_state_send_repeat_state(void)
{
    if (!_repeat_code.has_valid_contents)
        return;

    for (int i = 0; i < HID_REPORT_KEYCODE_ARRAY_LENGTH; i++)
    {
        if(_repeat_modifiers[i] == 0)
            continue;

        // Send each valid modifier we recorded.
        struct hid_keycode_container_t modifier_code =
        {
            .hid_keycode = _repeat_modifiers[i],
            .modifier = 0,
            .has_valid_contents = true
        };
        key_state_press(modifier_code, true);
    }

    // Send our original repeat code. This has to be done last
    // so the new codes in the report are processed in order.
    key_state_press(_repeat_code, true);
}

