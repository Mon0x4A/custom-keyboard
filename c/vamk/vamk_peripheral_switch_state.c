///Imports
#include <stddef.h>
#include <stdio.h>
#include "hardware/i2c.h"
#include "vamk_keymap_config.h"
#include "vamk_config.h"
#include "vamk_peripheral_switch_state.h"
#include "vamk_types.h"

///Static Global Constants
const uint8_t GPIO_A_REGISTER_ADDRESS = 0x12;
const uint8_t GPIO_B_REGISTER_ADDRESS = 0x13;
const uint8_t IODIR_A_REGISTER_ADDRESS = 0x00;
const uint8_t IODIR_B_REGISTER_ADDRESS = 0x01;
const uint8_t GPPU_A_REGISTER_ADDRESS = 0x0C;
const uint8_t GPPU_B_REGISTER_ADDRESS = 0x0D;

///Static Global Variables
static uint8_t _peripheral_switch_matrix_curr[ROW_COUNT][COLUMN_COUNT] = {0};
static uint8_t _peripheral_switch_matrix_prev[ROW_COUNT][COLUMN_COUNT] = {0};

//TODO these need to accept a side and this class will pass the CURRENT_KEYBOARD_SIDE
static switch_pressed_callback_t _pressed_callback = NULL;
static switch_released_callback_t _released_callback = NULL;

///Static Functions
static void read_matrix_state(void)
{
    // To get a register value byte, write the device address and then the
    // register you want to start retrieving data from.
    const uint8_t REGISTER_WRITE_REQUEST_LENGTH = 1;
    const bool DO_NOT_SEND_STOP = false;
    int8_t written_byte_count = i2c_write_blocking(
        I2C_IO_EXPANDER_BUS, IO_EXPANDER_ADDRESS, &GPIO_A_REGISTER_ADDRESS,
        REGISTER_WRITE_REQUEST_LENGTH, DO_NOT_SEND_STOP);

    // Request N number of registries to be returned since each is 1 byte.
    // Values will start from the register previously written.
    const uint8_t REGISTER_READ_BYTE_REQUEST_COUNT = 2;
    uint8_t read_buffer[REGISTER_READ_BYTE_REQUEST_COUNT];
    uint8_t read_count = i2c_read_blocking(
        I2C_IO_EXPANDER_BUS, IO_EXPANDER_ADDRESS, read_buffer, REGISTER_READ_BYTE_REQUEST_COUNT, DO_NOT_SEND_STOP);

    //TODO assert that read_count == 2?

    //TODO we need to map each register value to an index value

    // Break out the sequential buffer contents.
    //for (int i = 0; i < I2C_TRANSMISSION_SIZE; i++)
    //    _peripheral_switch_matrix_curr[i/COLUMN_COUNT][i%COLUMN_COUNT] = read_buffer[i];
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
    //Set up this device as the I2C controller for the
    //I/O expander bus.
    i2c_init(I2C_IO_EXPANDER_BUS, I2C_CLOCK_SPEED);

    gpio_init(I2C_IO_EXPANDER_SDA_PIN);
    gpio_set_function(I2C_IO_EXPANDER_SDA_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_IO_EXPANDER_SDA_PIN);

    gpio_init(I2C_IO_EXPANDER_SCL_PIN);
    gpio_set_function(I2C_IO_EXPANDER_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_IO_EXPANDER_SCL_PIN);

    //TODO init the expander I/0 pins and pullup resistors

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

