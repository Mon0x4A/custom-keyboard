///Imports
#include <stdbool.h>
#include "pico/stdlib.h"
#include "vamk_config.h"
#include "vamk_hold_delay_handler.h"
#include "vamk_keymap_config.h"
#include "vamk_key_helper.h"
#include "vamk_key_state.h"
#include "vamk_keyboard_state.h"
#include "vamk_layer_info.h"
#include "vamk_press_handler.h"
#include "vamk_press_helper.h"
#include "vamk_tap_handler.h"
#include "vamk_types.h"
#include "tusb.h"

///Static Global Variables

///Extern Functions
void press_handler_on_switch_press(uint16_t row, uint16_t col, keyboard_side_t keyboard_side)
{
    uint8_t current_layer = keyboard_state_get_current_layer_index();

    tap_handler_on_switch_press(row, col, current_layer, keyboard_side);
    hold_delay_handler_on_switch_press(row, col, current_layer, keyboard_side);
    //TODO sticky key action handling
    //TODO double tap action handling

    struct hid_keycode_container_t code_container =
        layer_info_get_base_keycode_at(row, col, current_layer, keyboard_side);

    press_helper_key_press(code_container);
}
