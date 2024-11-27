#ifndef VAMK_CONFIG_H
#define VAMK_CONFIG_H

//Imports
#include "pico/stdlib.h"

///General Keyboard Constants
//===========================
#define SWITCH_PRESSED_VALUE 0
#define SWITCH_NOT_PRESSED_VALUE 1

#define HID_REPORT_KEYCODE_ARRAY_LENGTH 6

#define SWITCH_POLLING_INTERVAL_MS 25

#define SWITCH_TESTING_MODE 0
#define ENABLE_SERIAL_LOGGING 1
#define ENABLE_KEYBOARD_COMMANDS 1

#define ENABLE_LED_DEVICE_STATUS_INDICATOR 1

#define IS_SPLIT_KEYBOARD 1
#define IS_UNIFIED_KEYBOARD 0

#if IS_SPLIT_KEYBOARD && IS_UNIFIED_KEYBOARD || !(IS_SPLIT_KEYBOARD || IS_UNIFIED_KEYBOARD)
#error "Must define either split OR unified configuration"
#endif

#define CONTROLLER_IS_LEFT_SIDE 1
#define CONTROLLER_IS_RIGHT_SIDE 0
#if (CONTROLLER_IS_LEFT_SIDE && CONTROLLER_IS_RIGHT_SIDE) || !(CONTROLLER_IS_LEFT_SIDE || CONTROLLER_IS_RIGHT_SIDE)
#error "Controller must be on one (and only one) side in a split configuration"
#endif

#define IS_VOK_SL_MODEL 0
#define IS_QLP_MODEL 1
#define IS_SEOK_MODEL 0

#if IS_VOK_SL_MODEL && (IS_QLP_MODEL || IS_SEOK_MODEL)
#error "VOK_SL_MODEL has been declared. No other models are allowed."
#endif

#if IS_QLP_MODEL && (IS_VOK_SL_MODEL || IS_SEOK_MODEL)
#error "QLP_MODEL has been declared. No other models are allowed."
#endif

#if IS_SEOK_MODEL && (IS_QLP_MODEL || IS_VOK_SL_MODEL)
#error "SEOK_MODEL has been declared. No other models are allowed."
#endif

#if !(IS_VOK_SL_MODEL || IS_QLP_MODEL || IS_SEOK_MODEL)
#error "Must define singluar, valid keyboard model"
#endif

#define IS_QLP_REV0 0

/// Key Behavior Config
//=====================
#define TAP_ACTION_TIMEOUT_MS 200 //ms
#define TAP_ACTION_TIMEIN_MS 25 //ms

#define HOLD_DELAY_THRESHOLD_MS TAP_ACTION_TIMEOUT_MS+2

///I2C Config
//===========
#define I2C_CLOCK_SPEED 400*1000 //Khz

#define I2C_IO_EXPANDER_BUS i2c0
#define I2C_IO_EXPANDER_SDA_PIN 20
#define I2C_IO_EXPANDER_SCL_PIN 21

#define IS_I2C_DISPLAY_ENABLED 0
#define I2C_DISPLAY_BUS i2c0
#define I2C_DISPLAY_SDA_PIN 20
#define I2C_DISPLAY_SCL_PIN 21

#define IO_EXPANDER_ADDRESS 0x20
#define IO_EXPANDER_REGISTER_COUNT 22

//TODO make these addresses conditional on which side is primary?
#define OLED_PRIMARY_SCREEN_ADDRESS 0x3C
#define OLED_SECONDARY_SCREEN_ADDRESS 0x3D

// SPI Config
#define IS_SPI_MOUSE_ENABLED 0
#define SPI_MOUSE_BUS spi0
#define SPI_MOUSE_CLK_PIN 2
#define SPI_MOUSE_TX_PIN 3
#define SPI_MOUSE_RX_PIN 4
#define SPI_MOUSE_CS0_PIN 5
#define SPI_MOUSE_CS1_PIN 5

#endif
