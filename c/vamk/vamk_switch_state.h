// Protect from multiple includes
#ifndef VAMK_SWITCH_STATE_H
#define VAMK_SWITCH_STATE_H

///Imports

///Function Declarations
void switch_state_init(void);
void switch_state_task(void);
void switch_state_set_pressed_callback(switch_pressed_callback_t pressed_callback);
void switch_state_set_released_callback(switch_released_callback_t released_callback);

#endif
