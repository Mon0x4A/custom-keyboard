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

typedef enum keyboard_side
{
    LEFT_SIDE = 42,
    RIGHT_SIDE = 69,
} keyboard_side_t;

///Function Pointers
typedef void (*switch_pressed_callback_t)(uint16_t row, uint16_t col);
typedef void (*switch_released_callback_t)(uint16_t row, uint16_t col);

///Structures
typedef struct key_report
{
    uint8_t keycodes[6];
    uint8_t modfiers;
} key_report_t;

typedef struct hid_keycode_container
{
    uint8_t hid_keycode;
    uint8_t modifier;
    bool has_valid_contents;
} hid_keycode_container_t;

#endif
