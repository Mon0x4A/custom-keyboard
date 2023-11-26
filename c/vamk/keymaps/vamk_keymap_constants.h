#ifndef VAMK_KEYMAP_CONSTANTS_H
#define VAMK_KEYMAP_CONSTANTS_H

///Imports
#include "pico/stdlib.h"

///Constants
#define KC_NULL 0x00 //Same as HID_KEY_NONE

#define KC_LM0 0xA6 //Layer keycodes. These are reserved codes
#define KC_LM1 0xA7 //in TinyUSB that we've repurposed to represent
#define KC_LM2 0xA8 //layers locally. They should not be sent into
#define KC_LM3 0xA9 //the TinyUSB API.
#define KC_LM4 0xAA //
#define KC_LM5 0xAB //The reserved codes are 0xA5-0xDF
#define KC_LM6 0xAC
#define KC_LM7 0xAD
#define KC_LM8 0xAE
#define KC_LM9 0xAF

#define KC_REPEAT 0xC0 //Also a repurposed reserved TinyUSB code.

///Type Declarations
struct keycode_definition_t
{
    uint8_t keycode;
    bool is_ascii:1;
};

#endif
