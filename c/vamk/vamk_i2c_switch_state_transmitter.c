///Imports
#include <stdio.h>
#include "pico/i2c_slave.h"
#include "pico/stdlib.h"
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
    gpio_init(I2C_SDA_PIN);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);

    gpio_init(I2C_SCL_PIN);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SCL_PIN);

    i2c_init(I2C_PORT, I2C_CLOCK_SPEED);

    i2c_slave_init(I2C_PORT, PERIPHERAL_KEYBOARD_ADDRESS, &i2c_switch_state_request_handler);
}

void i2c_switch_state_request_handler(i2c_inst_t *i2c, i2c_slave_event_t event)
{
    switch (event) {
    case I2C_SLAVE_RECEIVE:
        printf("Controller is sending data we are not handling!");
        break;
    case I2C_SLAVE_REQUEST:
        printf("Controller is requesting data.");
        for (int i = 0; i < ROW_COUNT; i++)
            for (int j = 0; j < COLUMN_COUNT; j++)
                i2c_write_byte_raw(i2c, _transmission_switch_matrix[i][j]);
        break;
    case I2C_SLAVE_FINISH:
        printf("Controller has sent stop signal!");
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

