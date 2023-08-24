#ifndef VAMK_KEYMAP_CONFIG_H
#define VAMK_KEYMAP_CONFIG_H

///Imports
#include "pico/stdlib.h"
#include "vamk_types.h"
#include "tusb.h"

///Constants
#define KC_NULL 0x00 //Same as HID_KEY_NONE

#define KC_LM0 0xA5 //Layer keycodes. These are reserved codes
#define KC_LM1 0xA6 //in TinyUSB that we've repurposed to represent
#define KC_LM2 0xA7 //layers locally. They should not be sent into
#define KC_LM3 0xA8 //the TinyUSB API.
#define KC_LM4 0xA9 //
#define KC_LM5 0xAA //The reserved codes are 0xA5-0xDF
#define KC_LM6 0xAB
#define KC_LM7 0xAC
#define KC_LM8 0xAD
#define KC_LM9 0xAE

#define KC_REPEAT 0xC0 //Also a repurposed reserved TinyUSB code.

#define LAYER_COUNT 3
#define MAX_LAYER_COUNT 10

#if IS_SPLIT_KEYBOARD
    /// Split Keyboard Config
    //=======================
    #define IS_PRIMARY_KEYBOARD_SIDE 1
    static const keyboard_side_t CURRENT_KEYBOARD_SIDE = RIGHT_SIDE;
    static const keyboard_side_t OPPOSITE_KEYBOARD_SIDE = CURRENT_KEYBOARD_SIDE == LEFT_SIDE ? RIGHT_SIDE : LEFT_SIDE;

    #define COLUMN_COUNT 7
    #define ROW_COUNT 3

    static const uint8_t ROW_0_PIN = CURRENT_KEYBOARD_SIDE == LEFT_SIDE ? 20 : 18;
    static const uint8_t ROW_1_PIN = CURRENT_KEYBOARD_SIDE == LEFT_SIDE ? 19 : 19;
    static const uint8_t ROW_2_PIN = CURRENT_KEYBOARD_SIDE == LEFT_SIDE ? 18 : 20;

    static const uint8_t COL_0_PIN = CURRENT_KEYBOARD_SIDE == LEFT_SIDE ? 12 : 12;
    static const uint8_t COL_1_PIN = CURRENT_KEYBOARD_SIDE == LEFT_SIDE ? 8  : 6;
    static const uint8_t COL_2_PIN = CURRENT_KEYBOARD_SIDE == LEFT_SIDE ? 11 : 11;
    static const uint8_t COL_3_PIN = CURRENT_KEYBOARD_SIDE == LEFT_SIDE ? 9  : 7;
    static const uint8_t COL_4_PIN = CURRENT_KEYBOARD_SIDE == LEFT_SIDE ? 10 : 10;
    static const uint8_t COL_5_PIN = CURRENT_KEYBOARD_SIDE == LEFT_SIDE ? 7  : 8;
    static const uint8_t COL_6_PIN = CURRENT_KEYBOARD_SIDE == LEFT_SIDE ? 6  : 9;

    static const uint8_t ROWS[ROW_COUNT] = { ROW_0_PIN, ROW_1_PIN, ROW_2_PIN };
    static const uint8_t COLS[COLUMN_COUNT] = { COL_0_PIN, COL_1_PIN, COL_2_PIN, COL_3_PIN, COL_4_PIN, COL_5_PIN, COL_6_PIN };

    /// Split Keymaps
    ///==============
    static const uint8_t L0_BASE_KEYCODES[ROW_COUNT][COLUMN_COUNT] =
    {
        { HID_KEY_CONTROL_LEFT, 'q', 'w', 'e', 'r', 't', KC_LM1 },
        { KC_NULL,              'a', 's', 'd', 'f', 'g', KC_LM2 },
        { KC_NULL,              'z', 'x', 'c', 'v', 'b', HID_KEY_SHIFT_LEFT },
    };
    static const bool L0_IS_ASCII[ROW_COUNT][COLUMN_COUNT] =
    {
        { 0, 1, 1, 1, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0 },
    };

    static const uint8_t L1_BASE_KEYCODES[ROW_COUNT][COLUMN_COUNT] =
    {
        { HID_KEY_ALT_LEFT, HID_KEY_F1, HID_KEY_F4, HID_KEY_F7, HID_KEY_F10, KC_NULL, KC_LM1 },
        { KC_NULL,          HID_KEY_F2, HID_KEY_F5, HID_KEY_F8, HID_KEY_F11, KC_NULL, KC_LM2 },
        { KC_NULL,          HID_KEY_F3, HID_KEY_F6, HID_KEY_F9, HID_KEY_F12, KC_NULL, HID_KEY_SHIFT_LEFT },
    };
    static const bool L1_IS_ASCII[ROW_COUNT][COLUMN_COUNT] =
    {
        { 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0 },
    };

    static const uint8_t L2_BASE_KEYCODES[ROW_COUNT][COLUMN_COUNT] =
    {
        { HID_KEY_GUI_LEFT, '`', '0', '1', '2', '3', KC_LM1 },
        { KC_NULL,          '@', '$', '4', '5', '6', KC_LM2 },
        { KC_NULL,          '<', '>', '7', '8', '9', HID_KEY_SHIFT_RIGHT },
    };
    static const bool L2_IS_ASCII[ROW_COUNT][COLUMN_COUNT] =
    {
        { 0, 1, 1, 1, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0 },
    };

    static const uint8_t L_TAP_KEYS[ROW_COUNT][COLUMN_COUNT] =
    {
        { HID_KEY_ESCAPE,  KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, HID_KEY_TAB },
        { KC_NULL,         KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, HID_KEY_SPACE },
        { KC_NULL,         KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL },
    };
    static const bool L_TAP_IS_ASCII[ROW_COUNT][COLUMN_COUNT] = {0};

    static const uint8_t L_HOLD_DELAY_KEYS[ROW_COUNT][COLUMN_COUNT] = {0};
    static const bool L_HOLD_DELAY_IS_ASCII[ROW_COUNT][COLUMN_COUNT] = {0};

    static const uint8_t R0_BASE_KEYCODES[ROW_COUNT][COLUMN_COUNT] =
    {
        { KC_LM1,              'y', 'u', 'i', 'o', 'p', HID_KEY_CONTROL_RIGHT },
        { KC_LM2,              'h', 'j', 'k', 'l', ';', KC_NULL },
        { HID_KEY_SHIFT_RIGHT, 'n', 'm', ',', '.', '/', KC_NULL },
    };
    static const bool R0_IS_ASCII[ROW_COUNT][COLUMN_COUNT] =
    {
        { 0, 1, 1, 1, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0 },
    };

    static const uint8_t R1_BASE_KEYCODES[ROW_COUNT][COLUMN_COUNT] =
    {
        { KC_LM1,              HID_KEY_HOME,         HID_KEY_PAGE_DOWN,  HID_KEY_PAGE_UP,  HID_KEY_END,         HID_KEY_DELETE, HID_KEY_ALT_RIGHT },
        { KC_LM2,              HID_KEY_ARROW_LEFT,   HID_KEY_ARROW_DOWN, HID_KEY_ARROW_UP, HID_KEY_ARROW_RIGHT, KC_NULL,        KC_NULL },
        { HID_KEY_SHIFT_RIGHT, HID_KEY_PRINT_SCREEN, KC_NULL,            KC_NULL,          KC_NULL,             KC_NULL,        KC_NULL },
    };
    static const bool R1_IS_ASCII[ROW_COUNT][COLUMN_COUNT] =
    {
        { 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0 },
    };

    static const uint8_t R2_BASE_KEYCODES[ROW_COUNT][COLUMN_COUNT] =
    {
        { KC_LM1,              '&', '*', '(', ')', '=',  HID_KEY_GUI_RIGHT },
        { KC_LM2,              '-', '_', '{', '}', '\'', KC_NULL },
        { HID_KEY_SHIFT_RIGHT, '+', '!', '[', ']', '\\', KC_NULL },
    };
    static const bool R2_IS_ASCII[ROW_COUNT][COLUMN_COUNT] =
    {
        { 0, 1, 1, 1, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0 },
    };

    static const uint8_t R_TAP_KEYS[ROW_COUNT][COLUMN_COUNT] =
    {
        { KC_REPEAT,         KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, HID_KEY_ENTER },
        { HID_KEY_BACKSPACE, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL },
        { KC_NULL,           KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL },
    };
    static const bool R_TAP_IS_ASCII[ROW_COUNT][COLUMN_COUNT] = {0};

    static const uint8_t R_HOLD_DELAY_KEYS[ROW_COUNT][COLUMN_COUNT] = {0};
    static const bool R_HOLD_DELAY_IS_ASCII[ROW_COUNT][COLUMN_COUNT] = {0};
#endif

#if !IS_SPLIT_KEYBOARD
    ///Unified/Unibody Keyboard Config
    //================================
    #define IS_PRIMARY_KEYBOARD_SIDE 1
    static const keyboard_side_t CURRENT_KEYBOARD_SIDE = LEFT_SIDE;
    static const keyboard_side_t OPPOSITE_KEYBOARD_SIDE = RIGHT_SIDE;

    #define COLUMN_COUNT 14
    #define ROW_COUNT 3

    static const uint8_t ROW_0_PIN = 20;
    static const uint8_t ROW_1_PIN = 19;
    static const uint8_t ROW_2_PIN = 18;

    static const uint8_t COL_0_PIN = 6;
    static const uint8_t COL_1_PIN = 8;
    static const uint8_t COL_2_PIN = 11;
    static const uint8_t COL_3_PIN = 9;
    static const uint8_t COL_4_PIN = 10;
    static const uint8_t COL_5_PIN = 7;
    static const uint8_t COL_6_PIN = 12;
    static const uint8_t COL_7_PIN = 16;
    static const uint8_t COL_8_PIN = 27;
    static const uint8_t COL_9_PIN = 21;
    static const uint8_t COL_10_PIN = 22;
    static const uint8_t COL_11_PIN = 17;
    static const uint8_t COL_12_PIN = 26;
    static const uint8_t COL_13_PIN = 28;

    static const uint8_t ROWS[ROW_COUNT] = { ROW_0_PIN, ROW_1_PIN, ROW_2_PIN };
    static const uint8_t COLS[COLUMN_COUNT] =
    {
        COL_0_PIN, COL_1_PIN, COL_2_PIN, COL_3_PIN, COL_4_PIN, COL_5_PIN, COL_6_PIN,
        COL_7_PIN, COL_8_PIN, COL_9_PIN, COL_10_PIN, COL_11_PIN, COL_12_PIN, COL_13_PIN
    };

    /// Unified Keymaps
    ///================
    static const uint8_t L0_BASE_KEYCODES[ROW_COUNT][COLUMN_COUNT] =
    {
        { HID_KEY_CONTROL_LEFT, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_LM1,              KC_LM1,              KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, HID_KEY_CONTROL_RIGHT },
        { KC_NULL,              KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_LM2,              KC_LM2,              KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL },
        { KC_NULL,              KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, HID_KEY_SHIFT_RIGHT, HID_KEY_SHIFT_RIGHT, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL },
    };

    static const bool L0_IS_ASCII[ROW_COUNT][COLUMN_COUNT] =
    {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };

    static const uint8_t L1_BASE_KEYCODES[ROW_COUNT][COLUMN_COUNT] =
    {
        { HID_KEY_ALT_LEFT, HID_KEY_F1, HID_KEY_F4, HID_KEY_F7, HID_KEY_F10, KC_NULL, KC_LM1,              KC_LM1,              HID_KEY_HOME,         HID_KEY_PAGE_DOWN,  HID_KEY_PAGE_UP,  HID_KEY_END,         HID_KEY_DELETE, HID_KEY_ALT_RIGHT },
        { KC_NULL,          HID_KEY_F2, HID_KEY_F5, HID_KEY_F8, HID_KEY_F11, KC_NULL, KC_LM2,              KC_LM2,              HID_KEY_ARROW_LEFT,   HID_KEY_ARROW_DOWN, HID_KEY_ARROW_UP, HID_KEY_ARROW_RIGHT, KC_NULL,        KC_NULL },
        { KC_NULL,          HID_KEY_F3, HID_KEY_F6, HID_KEY_F9, HID_KEY_F12, KC_NULL, HID_KEY_SHIFT_RIGHT, HID_KEY_SHIFT_RIGHT, HID_KEY_PRINT_SCREEN, KC_NULL,            KC_NULL,          KC_NULL,             KC_NULL,        KC_NULL },
    };
    static const bool L1_IS_ASCII[ROW_COUNT][COLUMN_COUNT] =
    {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };

    static const uint8_t L2_BASE_KEYCODES[ROW_COUNT][COLUMN_COUNT] =
    {
        { HID_KEY_GUI_LEFT, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_LM1,              KC_LM1,              KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, HID_KEY_GUI_RIGHT },
        { KC_NULL,          KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_LM2,              KC_LM2,              KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL },
        { KC_NULL,          KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, HID_KEY_SHIFT_RIGHT, HID_KEY_SHIFT_RIGHT, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL },
    };
    static const bool L2_IS_ASCII[ROW_COUNT][COLUMN_COUNT] =
    {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };

    static const uint8_t L0_TAP_KEYS[ROW_COUNT][COLUMN_COUNT] =
    {
        { HID_KEY_ESCAPE, 'q', 'w', 'e', 'r', 't', HID_KEY_TAB,   KC_REPEAT,         'y', 'u', 'i', 'o', 'p', HID_KEY_ENTER },
        { KC_NULL,        'a', 's', 'd', 'f', 'g', HID_KEY_SPACE, HID_KEY_BACKSPACE, 'h', 'j', 'k', 'l', ';', KC_NULL },
        { KC_NULL,        'z', 'x', 'c', 'v', 'b', KC_NULL,       KC_NULL,           'n', 'm', ',', '.', '/', KC_NULL },
    };
    static const bool L0_TAP_IS_ASCII[ROW_COUNT][COLUMN_COUNT] =
    {
        { 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0 },
    };

    static const uint8_t L1_TAP_KEYS[ROW_COUNT][COLUMN_COUNT] =
    {
        { HID_KEY_ESCAPE, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, HID_KEY_TAB,   KC_REPEAT,         KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, HID_KEY_ENTER },
        { KC_NULL,        KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, HID_KEY_SPACE, HID_KEY_BACKSPACE, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL },
        { KC_NULL,        KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL,       KC_NULL,           KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL },
    };
    static const bool L1_TAP_IS_ASCII[ROW_COUNT][COLUMN_COUNT] =
    {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };

    static const uint8_t L_HOLD_DELAY_KEYS[ROW_COUNT][COLUMN_COUNT] =
    {
        { KC_NULL, '`', '0', '1', '2', '3', KC_NULL, KC_NULL, '&', '*', '(', ')', '=',  KC_NULL },
        { KC_NULL, '@', '$', '4', '5', '6', KC_NULL, KC_NULL, '-', '_', '{', '}', '\'', KC_NULL },
        { KC_NULL, '<', '>', '7', '8', '9', KC_NULL, KC_NULL, '+', '!', '[', ']', '\\', KC_NULL },
    };
    static const bool L_HOLD_DELAY_IS_ASCII[ROW_COUNT][COLUMN_COUNT] =
    {
        { 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0 },
    };

    static const uint8_t R0_BASE_KEYCODES[ROW_COUNT][COLUMN_COUNT] = {0};
    static const bool R0_IS_ASCII[ROW_COUNT][COLUMN_COUNT] = {0};
    static const uint8_t R1_BASE_KEYCODES[ROW_COUNT][COLUMN_COUNT] = {0};
    static const bool R1_IS_ASCII[ROW_COUNT][COLUMN_COUNT] = {0};
    static const uint8_t R2_BASE_KEYCODES[ROW_COUNT][COLUMN_COUNT] = {0};
    static const bool R2_IS_ASCII[ROW_COUNT][COLUMN_COUNT] = {0};
    static const uint8_t R_TAP_KEYS[ROW_COUNT][COLUMN_COUNT] = {0};
    static const bool R_TAP_IS_ASCII[ROW_COUNT][COLUMN_COUNT] = {0};
    static const uint8_t R_HOLD_DELAY_KEYS[ROW_COUNT][COLUMN_COUNT] = {0};
    static const bool R_HOLD_DELAY_IS_ASCII[ROW_COUNT][COLUMN_COUNT] = {0};
#endif

///Function Definitions

#endif
