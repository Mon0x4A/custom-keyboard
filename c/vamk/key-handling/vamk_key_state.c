///Imports
#include <stdbool.h>
#include "pico/stdlib.h"
#include "vamk_config.h"
#include "vamk_key_state.h"
#include "vamk_key_helper.h"
#include "vamk_layer_info.h"
#include "vamk_types.h"

///Static Constants
static const uint8_t STANDARD_MINIMAL_REPORT_QUANTITY = 3;
static const uint8_t SYSTEM_MODIFIER_MINIMAL_REPORT_QUANTITY = 2;

///Static Global Variables
//TODO these properties should be made volatile if timer/alarm release
//code gets added.
static uint8_t _current_hid_report_codes[HID_REPORT_KEYCODE_ARRAY_LENGTH] = {0};
static uint8_t _current_report_code_quantity = 0;
static uint8_t _code_report_lifetime_countdown[HID_REPORT_KEYCODE_ARRAY_LENGTH] = {0};
static uint8_t _current_modifier = 0;

static uint8_t _current_layer = 0;

///Static Functions
static bool contains_hid_report_code(uint8_t hid_keycode)
{
    for (int i = 0; i < HID_REPORT_KEYCODE_ARRAY_LENGTH; i++)
        if (_current_hid_report_codes[i] == hid_keycode)
            return true;
    return false;
}

static void insert_hid_report_code(struct hid_keycode_container_t keycode_container,
    bool should_press_for_minimal_time_and_auto_release)
{
    // If this did not initialize correctly, something has gone wrong.
    hard_assert(keycode_container.has_valid_contents);

    // Check to make sure it's not already in the report.
    if (contains_hid_report_code(keycode_container.hid_keycode))
        return;

    // Insert the code into the report at the first available index.
    for (int i = 0; i < HID_REPORT_KEYCODE_ARRAY_LENGTH; i++)
    {
        if (_current_hid_report_codes[i] == 0)
        {
            _current_hid_report_codes[i] = keycode_container.hid_keycode;
            _code_report_lifetime_countdown[i] = 0;

            if (should_press_for_minimal_time_and_auto_release)
            {
                bool is_system_modifier_code = key_helper_is_system_modifier_keycode_container(keycode_container);
                _code_report_lifetime_countdown[i] = is_system_modifier_code
                    ? SYSTEM_MODIFIER_MINIMAL_REPORT_QUANTITY
                    : STANDARD_MINIMAL_REPORT_QUANTITY;
            }

            _current_modifier = keycode_container.modifier;
            break;
        }
    }
}

static void remove_hid_report_code(uint8_t hid_keycode)
{
    for (int i = 0; i < HID_REPORT_KEYCODE_ARRAY_LENGTH; i++)
    {
        if (_current_hid_report_codes[i] == hid_keycode)
        {
            _current_hid_report_codes[i] = 0;
            _code_report_lifetime_countdown[i] = 0;
            _current_modifier = 0;
        }
    }
}

///Global Functions
struct key_report_t key_state_preview_hid_report(void)
{
    struct key_report_t key_report_to_send = {0};

    for (int i = 0; i < HID_REPORT_KEYCODE_ARRAY_LENGTH; i++)
        key_report_to_send.keycodes[i] = _current_hid_report_codes[i];

    key_report_to_send.modifier = _current_modifier;

    return key_report_to_send;
}

struct key_report_t key_state_build_hid_report(void)
{
    struct key_report_t key_report_to_send = key_state_preview_hid_report();

    // Now that we've built the report, handle any countdowns.
    for (int i = 0; i < HID_REPORT_KEYCODE_ARRAY_LENGTH; i++)
    {
        if (_code_report_lifetime_countdown[i] > 1)
            _code_report_lifetime_countdown[i]--;

        if (_code_report_lifetime_countdown[i] == 1)
        {
            // We've reached the end of our countdown.
            _current_hid_report_codes[i] = 0;
            _code_report_lifetime_countdown[i] = 0;
            _current_modifier = 0;
        }
    }

    return key_report_to_send;
}

void key_state_press(struct hid_keycode_container_t keycode_container,
    bool should_press_for_minimal_time_and_auto_release)
{
    insert_hid_report_code(keycode_container, should_press_for_minimal_time_and_auto_release);
}

void key_state_release(uint8_t hid_keycode)
{
    remove_hid_report_code(hid_keycode);
}
