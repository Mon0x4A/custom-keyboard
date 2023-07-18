///Imports
#include <stddef.h>
#include <stdio.h>
#include "hardware/i2c.h"
#include "vamk_config.h"
#include "vamk_peripheral_switch_state.h"
#include "vamk_types.h"

///Static Global Variables
static uint8_t _peripheral_switch_matrix_curr[ROW_COUNT][COLUMN_COUNT] = {0};
static uint8_t _peripheral_switch_matrix_prev[ROW_COUNT][COLUMN_COUNT] = {0};

//TODO these need to accept a side and this class will pass the CURRENT_KEYBOARD_SIDE
static switch_pressed_callback_t _pressed_callback = NULL;
static switch_released_callback_t _released_callback = NULL;

///Static Functions
static void read_matrix_state(void)
{
    // Request the peripheral I2C device for matrix state.
    uint8_t read_buffer[I2C_TRANSMISSION_SIZE];
    uint8_t read_count = i2c_read_blocking(
        I2C_CONTROLLER_PORT, PERIPHERAL_KEYBOARD_ADDRESS, read_buffer, I2C_TRANSMISSION_SIZE, true);

    // Do not attempt to process a malformed message.
    if (read_count != I2C_TRANSMISSION_SIZE)
        return;

    // Break out the sequential buffer contents.
    for (int i = 0; i < I2C_TRANSMISSION_SIZE; i++)
        _peripheral_switch_matrix_curr[i/COLUMN_COUNT][i%COLUMN_COUNT] = read_buffer[i];
}

static void update_prev_matrix(void)
{
    //todo helper
    for (uint16_t i = 0; i < ROW_COUNT; i++)
    {
        for (uint16_t j = 0; j < COLUMN_COUNT; j++)
        {
            _peripheral_switch_matrix_prev[i][j] = _peripheral_switch_matrix_curr[i][j];
        }
    }
}

static void fire_callback_events(void)
{
    //todo helper
    for (uint16_t i = 0; i < ROW_COUNT; i++)
    {
        for (uint16_t j = 0; j < COLUMN_COUNT; j++)
        {
            uint8_t switch_curr_press = _peripheral_switch_matrix_curr[i][j];
            uint8_t switch_prev_press = _peripheral_switch_matrix_prev[i][j];
            if (switch_curr_press != switch_prev_press)
            {
                if (switch_curr_press == SWITCH_PRESSED_VALUE &&
                    switch_prev_press == SWITCH_NOT_PRESSED_VALUE)
                {
                    // We started pressing a key.
                    if (_pressed_callback != NULL)
                        _pressed_callback(i, j, OPPOSITE_KEYBOARD_SIDE);
                }
                else
                {
                    // We released a key.
                    if (_released_callback != NULL)
                        _released_callback(i, j, OPPOSITE_KEYBOARD_SIDE);
                }
            }
        }
    }
}

static void print_matrix_state(void)
{
    //todo helper
    static uint32_t report_id = 0;
    for (uint16_t i = 0; i < ROW_COUNT; i++)
    {
        printf("%uP0%i:", report_id, i);
        for (uint16_t j = 0; j < COLUMN_COUNT; j++)
        {
            printf("%i", _peripheral_switch_matrix_curr[i][j]);
        }
        printf("\n");
    }
    report_id++;
}

///Extern Functions
void peripheral_switch_state_init(void)
{
    //Set up this device as I2C controller.
    gpio_init(I2C_CONTROLLER_SDA_PIN);
    gpio_set_function(I2C_CONTROLLER_SDA_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_CONTROLLER_SDA_PIN);

    gpio_init(I2C_CONTROLLER_SCL_PIN);
    gpio_set_function(I2C_CONTROLLER_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_CONTROLLER_SCL_PIN);

    i2c_init(I2C_CONTROLLER_PORT, I2C_CLOCK_SPEED);

    //Load the default switch state into each array.
    read_matrix_state();
    update_prev_matrix();
}

void peripheral_switch_state_task(void)
{
    read_matrix_state();
    //static bool just_pressed = false;
    ////sleep_ms(100);
    //if (!just_pressed)
    //{
    //    _peripheral_switch_matrix_curr[0][5] = 1;
    //    just_pressed = true;
    //}
    //else
    //{
    //    _peripheral_switch_matrix_curr[0][5] = 0;
    //    just_pressed = false;
    //}

    fire_callback_events();

    update_prev_matrix();

    if (SWITCH_TESTING_MODE)
    {
        //TODO this sleep suspends the USB device. REMOVE WHEN REPORTING IS NEEDED.
        //sleep_ms(500);
        print_matrix_state();
    }
}

void peripheral_switch_state_set_pressed_callback(switch_pressed_callback_t pressed_callback)
{
    _pressed_callback = pressed_callback;
}

void peripheral_switch_state_set_released_callback(switch_released_callback_t released_callback)
{
    _released_callback = released_callback;
}

