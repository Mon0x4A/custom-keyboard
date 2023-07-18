#ifndef VAMK_PERIPHERAL_SWITCH_STATE_H
#define VAMK_PERIPHERAL_SWITCH_STATE_H

///Imports
#include "vamk_types.h"

///Function Declarations
void peripheral_switch_state_init(void);
void peripheral_switch_state_task(void);
void peripheral_switch_state_set_pressed_callback(switch_pressed_callback_t pressed_callback);
void peripheral_switch_state_set_released_callback(switch_released_callback_t released_callback);

#endif
