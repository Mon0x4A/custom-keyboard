#ifndef VAMK_KEYMAP_CONSTANTS_H
#define VAMK_KEYMAP_CONSTANTS_H

///Imports
#include "pico/stdlib.h"

///Constants
#define KC_NULL 0x00 //Same as HID_KEY_NONE

#define KC_LM0_L 0xA6 //Layer keycodes. These are reserved codes
#define KC_LM1_L 0xA7 //in TinyUSB that we've repurposed to represent
#define KC_LM2_L 0xA8 //layers locally. They should not be sent into
#define KC_LM3_L 0xA9 //the TinyUSB API.
#define KC_LM4_L 0xAA //
#define KC_LM5_L 0xAB //The reserved codes are 0xA5-0xDF
#define KC_LM6_L 0xAC
#define KC_LM7_L 0xAD
#define KC_LM8_L 0xAE
#define KC_LM9_L 0xAF

#define KC_LM0_R 0xB6
#define KC_LM1_R 0xB7
#define KC_LM2_R 0xB8
#define KC_LM3_R 0xB9
#define KC_LM4_R 0xBA
#define KC_LM5_R 0xBB
#define KC_LM6_R 0xBC
#define KC_LM7_R 0xBD
#define KC_LM8_R 0xBE
#define KC_LM9_R 0xBF

#define KC_REPEAT 0xC0 //Also a repurposed reserved TinyUSB code.
#define KC_WIN_IME_TOGGLE 0xC1 //OS+Space: Windows IME toggle shortcut
#define KC_WIN_ALPHA_SWAP 0xC2 //Alt+Grave: Windows alphabet swap shortcut.

#define KC_KM_TOGGLE 0xD0 //Swap between output ports.

///Type Declarations
struct keycode_definition_t
{
    uint8_t keycode;
    bool is_ascii:1;
};

#endif
