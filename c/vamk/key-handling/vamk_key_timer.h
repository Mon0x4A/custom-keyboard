#ifndef VAMK_KEY_TIMER_H
#define VAMK_KEY_TIMER_H

///Imports
#include "pico/stdlib.h"
#include "vamk_types.h"

///Type Declarations
typedef void (*key_timer_key_down_event_callback_params_t)(struct key_event_location_t key_location, struct key_event_report_t key_event_report);
typedef void (*key_timer_key_up_event_callback_params_t)(struct key_event_location_t key_location, struct key_event_report_t key_event_report);
typedef void (*key_timer_key_delay_event_callback_params_t)(struct key_event_location_t key_location, struct key_event_report_t key_event_report);

///Constants

///Function Declarations
void key_timer_mark_key_down(struct key_event_location_t key_location, uint8_t layer_index);
void key_timer_mark_key_up(struct key_event_location_t key_location);

void key_timer_set_key_down_callback(key_timer_key_down_event_callback_params_t key_down_callback_ptr);
void key_timer_set_key_up_callback(key_timer_key_up_event_callback_params_t key_up_callback_ptr);
void key_timer_set_key_delay_callback(key_timer_key_delay_event_callback_params_t key_delay_callback_ptr);

bool key_timer_is_key_down(struct key_event_location_t key_location);

#endif
