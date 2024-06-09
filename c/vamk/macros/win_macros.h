#ifndef WIN_MACROS_H
#define WIN_MACROS_H

///Imports
#include <stdbool.h>
#include "pico/stdlib.h"
#include "vamk_key_state.h"
#include "vamk_layer_info.h"
#include "tusb.h"

///Function Declarations
void macro_windows_ime_toggle(void)
{
    struct hid_keycode_container_t os_mod_container =
    {
        .hid_keycode = HID_KEY_GUI_RIGHT,
        .modifier = 0,
        .has_valid_contents = 1,
    };
    key_state_press(os_mod_container, true);

    struct hid_keycode_container_t space_container =
    {
        .hid_keycode = HID_KEY_SPACE,
        .modifier = 0,
        .has_valid_contents = 1,
    };
    key_state_press(space_container, true);
}

void macro_windows_alphabet_swap(void)
{
    struct hid_keycode_container_t alt_mod_container =
    {
        .hid_keycode = HID_KEY_ALT_RIGHT,
        .modifier = 0,
        .has_valid_contents = 1,
    };
    key_state_press(alt_mod_container, true);

    struct hid_keycode_container_t grave_container =
    {
        .hid_keycode = HID_KEY_GRAVE,
        .modifier = 0,
        .has_valid_contents = 1,
    };
    key_state_press(grave_container, true);
}

#endif
