//Imports
#include <stdbool.h>

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

//Keyboard Config
const bool SWITCH_TESTING_MODE = false;
const bool ENABLE_SERIAL_LOGGING = false;
const bool ENABLE_KEYBOARD_COMMANDS = false;

const bool IS_PRIMARY_KEYBOARD_SIDE = true;

const int COLUMN_COUNT = 7;
const int ROW_COUNT = 3;
