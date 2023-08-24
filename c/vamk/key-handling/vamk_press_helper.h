#ifndef VAMK_PRESS_HELPER_H
#define VAMK_PRESS_HELPER_H

///Imports
#include "pico/stdlib.h"
#include "vamk_types.h"

///Constants

///Function Definitions
void press_helper_keycode_press(struct hid_keycode_container_t keycode_container,
    bool should_auto_release, bool should_release_on_next_report);

#endif
