///Imports
#include <stdbool.h>
#include "pico/stdlib.h"
#include "vamk_config.h"
#include "vamk_key_state.h"
#include "vamk_layer_info.h"
#include "vamk_types.h"

///Global Variables

///Static Variables
static uint8_t _current_hid_report_codes[6] = {0};
static bool _code_has_single_report_lifetime[6] = {0};
static uint8_t _current_modifier = 0;

static uint8_t _current_layer = 0;

///Private Declarations

///Static (Private/Local) Functions
static void insert_report_code(struct hid_keycode_container_t hid_keycode, bool release_on_next_report)
{
    //if (hid_keycode == NULL)
    //    return;

    //TODO here
}

static void remove_report_code(uint8_t hid_keycode)
{
}

///Public Functions
struct key_report_t key_state_build_hid_report()
{
}

uint8_t key_state_get_current_layer()
{
    return _current_layer;
}

void key_state_press(struct hid_keycode_container_t hid_keycode, bool release_on_next_report)
{
}

void key_state_release(uint8_t hid_keycode)
{
}
