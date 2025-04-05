///Imports
#include <stdio.h>
#include <stddef.h>
#include "hardware/i2c.h"
#include "mcp23017_i2c_api.h"
#include "vamk_keymap_config.h"
#include "vamk_config.h"
#include "vamk_peripheral_switch_state.h"
#include "vamk_types.h"

//Constants
#define RETRY_ON_FAILURE 1

///Static Global Variables
static uint8_t _peripheral_switch_matrix_curr[ROW_COUNT][COLUMN_COUNT] = {0};
static uint8_t _peripheral_switch_matrix_prev[ROW_COUNT][COLUMN_COUNT] = {0};

static switch_pressed_callback_t _pressed_callback = NULL;
static switch_released_callback_t _released_callback = NULL;

///Static Functions
static struct io_expander_register_value_pair_s build_default_io_expander_iodir_state(void)
{
    struct io_expander_register_value_pair_s iodir_register_value_pair = {0};
    //Set all selected columns to input pins (1). Leave everything else as output (0).
    for(uint16_t i = 0; i < COLUMN_COUNT; i++)
    {
        uint8_t col_pin_number = IO_EXPA_COLS[i];
        if (mcp23017_does_pin_number_belong_to_register_a(col_pin_number))
        {
            uint8_t bit_index = mcp23017_get_register_a_bit_index_from_pin_number(col_pin_number);
            iodir_register_value_pair.register_a_value |= 1 << bit_index;
        }
        else if (mcp23017_does_pin_number_belong_to_register_b(col_pin_number))
        {
            uint8_t bit_index = mcp23017_get_register_b_bit_index_from_pin_number(col_pin_number);
            iodir_register_value_pair.register_b_value |= 1 << bit_index;
        }
    }

    //Set all selected rows to input pins (1). Leave everything else as output (0).
    for(uint16_t i = 0; i < ROW_COUNT; i++)
    {
        uint8_t row_pin_number = IO_EXPA_ROWS[i];
        if (mcp23017_does_pin_number_belong_to_register_a(row_pin_number))
        {
            uint8_t bit_index = mcp23017_get_register_a_bit_index_from_pin_number(row_pin_number);
            iodir_register_value_pair.register_a_value |= 1 << bit_index;
        }
        else if (mcp23017_does_pin_number_belong_to_register_b(row_pin_number))
        {
            uint8_t bit_index = mcp23017_get_register_b_bit_index_from_pin_number(row_pin_number);
            iodir_register_value_pair.register_b_value |= 1 << bit_index;
        }
    }

    return iodir_register_value_pair;
}

static void set_default_io_expander_state()
{
    struct io_expander_register_value_pair_s iodir_register_value_pair = build_default_io_expander_iodir_state();
    // We can use the same values here to set all the columns to pullup.
    struct io_expander_register_value_pair_s gppu_register_value_pair = iodir_register_value_pair;

    mcp23017_write_double_register_value(IODIR_A_REGISTER_ADDRESS, iodir_register_value_pair, RETRY_ON_FAILURE);
    mcp23017_write_double_register_value(GPPU_A_REGISTER_ADDRESS, gppu_register_value_pair, RETRY_ON_FAILURE);
}

// TODO It could be worth experimenting with setting the IODIR of the rows one by one.
static void read_matrix_state(void)
{
    for (uint16_t row = 0; row < ROW_COUNT; row++)
    {
        uint8_t row_pin_number = IO_EXPA_ROWS[row];

        struct io_expander_register_value_pair_s initial_iodir_values =
            build_default_io_expander_iodir_state();

        struct io_expander_register_value_pair_s row_output_no_pullup_values =
        {
            .register_a_value = initial_iodir_values.register_a_value,
            .register_b_value = initial_iodir_values.register_b_value
        };

        if (mcp23017_does_pin_number_belong_to_register_a(row_pin_number))
        {
            uint8_t bit_index = mcp23017_get_register_a_bit_index_from_pin_number(row_pin_number);
            row_output_no_pullup_values.register_a_value ^= 1 << bit_index;
        }
        else if (mcp23017_does_pin_number_belong_to_register_b(row_pin_number))
        {
            uint8_t bit_index = mcp23017_get_register_b_bit_index_from_pin_number(row_pin_number);
            row_output_no_pullup_values.register_b_value ^= 1 << bit_index;
        }

        mcp23017_write_double_register_value(IODIR_A_REGISTER_ADDRESS, row_output_no_pullup_values, RETRY_ON_FAILURE);
        mcp23017_write_double_register_value(GPPU_A_REGISTER_ADDRESS, row_output_no_pullup_values, RETRY_ON_FAILURE);

        struct io_expander_register_value_pair_with_read_state_s gpio_values = mcp23017_read_double_register_value(
            GPIO_A_REGISTER_ADDRESS);

        //Only update from a valid read operation.
        if (gpio_values.read_success)
        {
            for (uint16_t col = 0; col < COLUMN_COUNT; col++)
            {
                uint8_t col_pin_number = IO_EXPA_COLS[col];
                if (mcp23017_does_pin_number_belong_to_register_a(col_pin_number))
                {
                    uint8_t bit_index = mcp23017_get_register_a_bit_index_from_pin_number(col_pin_number);
                    _peripheral_switch_matrix_curr[row][col] = (gpio_values.register_a_value >> bit_index) & 1;
                }
                else if (mcp23017_does_pin_number_belong_to_register_b(col_pin_number))
                {
                    uint8_t bit_index = mcp23017_get_register_b_bit_index_from_pin_number(col_pin_number);
                    _peripheral_switch_matrix_curr[row][col] = (gpio_values.register_b_value >> bit_index) & 1;
                }
            }
        }

        set_default_io_expander_state();
    }
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
                        _pressed_callback(i, j, PERIPHERAL_IDENTIFIER);
                }
                else
                {
                    // We released a key.
                    if (_released_callback != NULL)
                        _released_callback(i, j, PERIPHERAL_IDENTIFIER);
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
    //TODO need to implement a way to skip one of the gpio inits
    //if the display and expander are on the same bus

    //Set up this device as the I2C controller for the
    //I/O expander bus.
    i2c_init(I2C_IO_EXPANDER_BUS, I2C_CLOCK_SPEED);

    gpio_init(I2C_IO_EXPANDER_SDA_PIN);
    gpio_set_function(I2C_IO_EXPANDER_SDA_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_IO_EXPANDER_SDA_PIN);

    gpio_init(I2C_IO_EXPANDER_SCL_PIN);
    gpio_set_function(I2C_IO_EXPANDER_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_IO_EXPANDER_SCL_PIN);

    set_default_io_expander_state();

    //Load the default switch state into each array.
    read_matrix_state();
    update_prev_matrix();
}

void peripheral_switch_state_task_update(void)
{
    read_matrix_state();
}

void peripheral_switch_state_task_process(void)
{
    fire_callback_events();
}

void peripheral_switch_state_task_finalize(void)
{
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

