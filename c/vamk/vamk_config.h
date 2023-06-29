// Protect from multiple includes
#ifndef VAMK_CONFIG_H
#define VAMK_CONFIG_H

//Imports
#include "pico/stdlib.h"
#include "tusb.h"

//Serial Config
#define SERIAL_BAUD_RATE 9600

//I2C Config
#define I2C_CLOCK_SPEED 100*1000 //100Khz

#define PRIMARY_KEYBOARD_ADDRESS 0x2A
#define SECONDARY_KEYBOARD_ADDRESS 0x45

//TODO make these addresses condition on which side is primary?
#define OLED_PRIMARY_SCREEN_ADDRESS 0x3C
#define OLED_SECONDARY_SCREEN_ADDRESS 0x3D

#define OLED_SCREEN_WIDTH 128
#define OLED_SCREEN_HEIGHT 64

//Keyboard Constants
#define SWITCH_PRESSED_VALUE 0
#define SWITCH_NOT_PRESSED_VALUE 1

#define HID_REPORT_KEYCODE_ARRAY_LENGTH 6

#define KC_NULL 0x00 //Same as HID_KEY_NONE

#define KC_LM0 0xA5 //Layer keycodes. These are reserved codes
#define KC_LM1 0xA6 //in TinyUSB that we've repurposed to represent
#define KC_LM2 0xA7 //layers locally. They should not be sent into
#define KC_LM3 0xA8 //the TinyUSB API.
#define KC_LM4 0xA9 //
#define KC_LM5 0xAA //The reserved codes are 0xA5-0xDF
#define KC_LM6 0xAA
#define KC_LM7 0xAB
#define KC_LM8 0xAC
#define KC_LM9 0xAD

#define KC_REPEAT 0xC0 //Also a repurposed reserved TinyUSB code.

#define SWITCH_POLLING_INTERVAL_MS 1000

//Keyboard Config
#define SWITCH_TESTING_MODE 1
#define ENABLE_SERIAL_LOGGING 0
#define ENABLE_KEYBOARD_COMMANDS 0

#define IS_PRIMARY_KEYBOARD_SIDE 1
#define IS_LEFT_SIDE 1

#define COLUMN_COUNT 7
#define ROW_COUNT 3

static const uint8_t ROW_0_PIN = IS_PRIMARY_KEYBOARD_SIDE ? 20 : 18;
static const uint8_t ROW_1_PIN = IS_PRIMARY_KEYBOARD_SIDE ? 19 : 19;
static const uint8_t ROW_2_PIN = IS_PRIMARY_KEYBOARD_SIDE ? 18 : 20;

static const uint8_t COL_0_PIN = IS_PRIMARY_KEYBOARD_SIDE ? 12 : 12;
static const uint8_t COL_1_PIN = IS_PRIMARY_KEYBOARD_SIDE ? 8  : 6;
static const uint8_t COL_2_PIN = IS_PRIMARY_KEYBOARD_SIDE ? 11 : 11;
static const uint8_t COL_3_PIN = IS_PRIMARY_KEYBOARD_SIDE ? 9  : 7;
static const uint8_t COL_4_PIN = IS_PRIMARY_KEYBOARD_SIDE ? 10 : 10;
static const uint8_t COL_5_PIN = IS_PRIMARY_KEYBOARD_SIDE ? 7  : 8;
static const uint8_t COL_6_PIN = IS_PRIMARY_KEYBOARD_SIDE ? 6  : 9;

static const uint8_t ROWS[ROW_COUNT] = { ROW_0_PIN, ROW_1_PIN, ROW_2_PIN };
static const uint8_t COLS[COLUMN_COUNT] = { COL_0_PIN, COL_1_PIN, COL_2_PIN, COL_3_PIN, COL_4_PIN, COL_5_PIN, COL_6_PIN };

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

//static const uint8_t L_TAP_KEYS[ROW_COUNT][COLUMN_COUNT] =
//{
//    { HID_KEY_ESC,  KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, HID_KEY_TAB },
//    { KC_NULL,      KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, HID_KEY_SPACE },
//    { KC_NULL,      KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL },
//};

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

//static const unsigned uint8_t R_TAP_KEYS[ROW_COUNT][COLUMN_COUNT] =
//{
//    { KC_REPEAT,         KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, HID_KEY_RETURN },
//    { HID_KEY_BACKSPACE, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL },
//    { KC_NULL,           KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL },
//};
#endif
