// Protect from multiple includes
#ifndef VAMK_I2C_SWITCH_STATE_TRANSMITTER_H
#define VAMK_I2C_SWITCH_STATE_TRANSMITTER_H

///Imports
#include "pico/stdlib.h"
#include "pico/i2c_slave.h"
#include "hardware/i2c.h"

///Function Declarations
void i2c_switch_state_transmitter_init(void);
void i2c_switch_state_request_handler(i2c_inst_t *i2c, i2c_slave_event_t event);
void i2c_switch_state_on_switch_pressed(uint16_t row, uint16_t col);
void i2c_switch_state_on_switch_released(uint16_t row, uint16_t col);

#endif
