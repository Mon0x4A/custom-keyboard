#ifndef VAMK_KEY_LOGIC_H
#define VAMK_KEY_LOGIC_H
///Imports
#include "pico/stdlib.h"
#include "vamk_types.h"

///Type Declarations
///Constants

///Function Declarations
void key_logic_down_handler(struct key_event_location_t key_location, struct key_event_report_t key_event_report);
void key_logic_up_handler(struct key_event_location_t key_location, struct key_event_report_t key_event_report);
void key_logic_delay_handler(struct key_event_location_t key_location, struct key_event_report_t key_event_report);

#endif
