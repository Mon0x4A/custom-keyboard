// Protect from multiple includes
#ifndef VAMK_KEY_STATE_H
#define VAMK_KEY_STATE_H

///Imports
#include <stdbool.h>
#include "pico/stdlib.h"
#include "vamk_types.h"

///Function Declarations
struct key_report_t key_state_build_hid_report(void);
void key_state_press(struct hid_keycode_container_t keycode_container, bool release_on_next_report);
void key_state_release(uint8_t hid_keycode);

#endif
