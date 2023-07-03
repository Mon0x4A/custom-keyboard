///Imports
#include <stdio.h>
#include <string.h>
#include "pico/i2c_slave.h"
#include "pico/stdlib.h"
#include "bsp/board.h"
#include "hardware/i2c.h"
#include "vamk_i2c_switch_state_transmitter.h"
#include "vamk_config.h"
#include "vamk_types.h"

///Static Global Variables
static uint8_t _transmission_switch_matrix[ROW_COUNT][COLUMN_COUNT] = {0};

///Static Functions

///Extern Functions
void i2c_switch_state_transmitter_init(void)
{
    gpio_init(I2C_PERIPHERAL_SDA_PIN);
    gpio_set_function(I2C_PERIPHERAL_SDA_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_PERIPHERAL_SDA_PIN);

    gpio_init(I2C_PERIPHERAL_SCL_PIN);
    gpio_set_function(I2C_PERIPHERAL_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_PERIPHERAL_SCL_PIN);

    i2c_init(I2C_PERIPHERAL_PORT, I2C_CLOCK_SPEED);

    i2c_slave_init(I2C_PERIPHERAL_PORT, PERIPHERAL_KEYBOARD_ADDRESS, &i2c_switch_state_request_handler);
}

void i2c_switch_state_request_handler(i2c_inst_t *i2c, i2c_slave_event_t event)
{
    static uint8_t tx_byte_index = 0;
    static bool send_one = false;
    switch (event)
    {
        case I2C_SLAVE_RECEIVE:
            break;
        case I2C_SLAVE_REQUEST:
            i2c_write_byte_raw(i2c, send_one ? 1 : _transmission_switch_matrix[tx_byte_index/COLUMN_COUNT][tx_byte_index%COLUMN_COUNT]);
            tx_byte_index++;
            send_one = !send_one;
            //TODO led blink for transmit?
            // Once we reach the full matrix set, restart from 0;
            if (tx_byte_index >= I2C_TRANSMISSION_SIZE)
            {
                tx_byte_index = 0;
                send_one = false;
            }
            break;
        case I2C_SLAVE_FINISH:
            break;
        default:
            break;
    }
}

void i2c_switch_state_on_switch_pressed(uint16_t row, uint16_t col, keyboard_side_t keyboard_side)
{
    (void) keyboard_side;
    _transmission_switch_matrix[row][col] = 1;
}

void i2c_switch_state_on_switch_released(uint16_t row, uint16_t col, keyboard_side_t keyboard_side)
{
    (void) keyboard_side;
    _transmission_switch_matrix[row][col] = 0;
}

