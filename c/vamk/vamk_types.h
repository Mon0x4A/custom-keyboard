// Protect from multiple includes
#ifndef VAMK_TYPES_H
#define VAMK_TYPES_H

///Imports
#include "pico/stdlib.h"

///Enums
typedef enum led_blink_pattern_ms
{
    NOT_MOUNTED = 250,
    MOUNTED = 1000,
    SUSPENDED = 2500,
} led_blink_pattern_t;

///Function Pointers
typedef void (*switch_pressed_callback_t)(uint16_t row, uint16_t col);
typedef void (*switch_released_callback_t)(uint16_t row, uint16_t col);

///Structures

#endif
