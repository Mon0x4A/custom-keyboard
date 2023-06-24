// Protect from multiple includes
#ifndef VAMK_TYPES_H
#define VAMK_TYPES_H

///Imports

///Enums
typedef enum led_blink_pattern_ms
{
    NOT_MOUNTED = 250,
    MOUNTED = 1000,
    SUSPENDED = 2500,
} led_blink_pattern_t;

///Function Pointers
typedef void (*switch_pressed_callback_t)(int row, int col);
typedef void (*switch_released_callback_t)(int row, int col);

///Structures

#endif
