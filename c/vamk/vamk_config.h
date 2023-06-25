// Protect from multiple includes
#ifndef VAMK_CONFIG_H
#define VAMK_CONFIG_H

//Imports
#include "pico/stdlib.h"

//Serial Config
#define SERIAL_BAUD_RATE 9600

//I2C Config
#define I2C_CLOCK_SPEED 100*1000 //100Khz

#define PRIMARY_KEYBOARD_ADDRESS 0x2A
#define SECONDARY_KEYBOARD_ADDRESS 0x45

#define OLED_PRIMARY_SCREEN_ADDRESS 0x3C
#define OLED_SECONDARY_SCREEN_ADDRESS 0x3D

#define OLED_SCREEN_WIDTH 128
#define OLED_SCREEN_HEIGHT 64

//Keyboard Constants
#define SWITCH_PRESSED_VALUE 0
#define SWITCH_NOT_PRESSED_VALUE 1

#define KC_NULL 0x00
#define KC_LM1 0x01 //(STX) //Repurposing obsolete ascii codes for our custom codes
#define KC_LM2 0x02 //(ETX)
#define KC_REPEAT 0x07 //(BEL)
#define KEY_PRINT_SCREEN 0xCE //TODO Unclear if this will work with TinyUSB...

#define SWITCH_POLLING_INTERVAL_MS 1000

//Keyboard Config
#define SWITCH_TESTING_MODE 1
#define ENABLE_SERIAL_LOGGING 0
#define ENABLE_KEYBOARD_COMMANDS 0

#define IS_PRIMARY_KEYBOARD_SIDE 1

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

#endif
