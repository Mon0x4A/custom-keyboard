///Imports
#include <stddef.h>
#include <stdio.h>
#include "hardware/i2c.h"
#include "time.h"
#include "vamk_keymap_config.h"
#include "vamk_config.h"
#include "vamk_peripheral_switch_state.h"
#include "vamk_types.h"

///Static Global Constants
#define IO_EXPANDER_SLEEP_BUFFER_US 500
#define I2C_INSTRUCTION_TIMEOUT_MS 5
#define SINGLE_REGISTER_WRITE_COMMAND_BYTE_LENGTH 2
#define DOUBLE_REGISTER_WRITE_COMMAND_BYTE_LENGTH 3

#define REGISTER_READ_REQUEST_BYTE_LENGTH 1
#define SINGLE_REGISTER_READ_RECEIPT_BYTE_LENGTH 1
#define DOUBLE_REGISTER_READ_RECEIPT_BYTE_LENGTH 2

static const uint8_t REGISTER_B_MIN_PIN_NUMBER = 1;
static const uint8_t REGISTER_B_MAX_PIN_NUMBER = 8;

static const uint8_t REGISTER_A_MIN_PIN_NUMBER = 21;
static const uint8_t REGISTER_A_MAX_PIN_NUMBER = 28;

static const uint8_t GPIO_A_REGISTER_ADDRESS = 0x12;
static const uint8_t GPIO_B_REGISTER_ADDRESS = 0x13;
static const uint8_t IODIR_A_REGISTER_ADDRESS = 0x00;
static const uint8_t IODIR_B_REGISTER_ADDRESS = 0x01;
static const uint8_t GPPU_A_REGISTER_ADDRESS = 0x0C;
static const uint8_t GPPU_B_REGISTER_ADDRESS = 0x0D;

///Static Type Declarations
//struct io_expander_regsiter_value_with_read_state_t
//{
//    uint8_t register_value;
//    bool read_success;
//};

struct io_expander_register_value_pair_with_read_state_t
{
    uint8_t register_a_value;
    uint8_t register_b_value;
    bool read_success;
};

struct io_expander_register_value_pair_t
{
    uint8_t register_a_value;
    uint8_t register_b_value;
};

///Static Global Variables
static uint8_t _peripheral_switch_matrix_curr[ROW_COUNT][COLUMN_COUNT] = {0};
static uint8_t _peripheral_switch_matrix_prev[ROW_COUNT][COLUMN_COUNT] = {0};

static switch_pressed_callback_t _pressed_callback = NULL;
static switch_released_callback_t _released_callback = NULL;

///Static Functions
static bool does_pin_number_belong_to_register_a(uint8_t pin_number)
{
    return pin_number >= REGISTER_A_MIN_PIN_NUMBER && pin_number <= REGISTER_A_MAX_PIN_NUMBER;
}

static bool does_pin_number_belong_to_register_b(uint8_t pin_number)
{
    return pin_number >= REGISTER_B_MIN_PIN_NUMBER && pin_number <= REGISTER_B_MAX_PIN_NUMBER;
}

static uint8_t get_register_a_bit_index_from_pin_number(uint8_t pin_number)
{
    return does_pin_number_belong_to_register_a(pin_number) ? pin_number-21 : -1;
}

static uint8_t get_register_b_bit_index_from_pin_number(uint8_t pin_number)
{
    return does_pin_number_belong_to_register_b(pin_number) ? pin_number-1 : -1;
}

static absolute_time_t build_i2c_timeout(void)
{
    absolute_time_t time_base = get_absolute_time();
    absolute_time_t timeout_target = delayed_by_us(time_base, I2C_INSTRUCTION_TIMEOUT_MS*1000);
    return timeout_target;
}

//static void mcp23017_write_single_register_value(uint8_t register_address, uint8_t register_contents)
//{
//    // To write a single register value byte, write the device address (handled by i2c api), then the
//    // register you want to set, followed by the register value. For a total of 3 bytes.
//    const uint8_t write_buffer[SINGLE_REGISTER_WRITE_COMMAND_BYTE_LENGTH] = { register_address, register_contents };
//    const bool DO_NOT_SEND_STOP = false;
//    int8_t written_byte_count = i2c_write_blocking(I2C_IO_EXPANDER_BUS, IO_EXPANDER_ADDRESS,
//        write_buffer, SINGLE_REGISTER_WRITE_COMMAND_BYTE_LENGTH, DO_NOT_SEND_STOP);
//}

static void mcp23017_write_double_register_value(uint8_t register_a_address,
    struct io_expander_register_value_pair_t register_values)
{
    // Sleep briefly to avoid overwhelming the expander with too many write commands.
    sleep_us(IO_EXPANDER_SLEEP_BUFFER_US);

    // To write a double register value byte, write the device address (handled by i2c api), then the
    // 'A' register of the pair you want to set, followed by the register A value, the then register B
    // value. For a total of 4 bytes.
    const uint8_t write_buffer[DOUBLE_REGISTER_WRITE_COMMAND_BYTE_LENGTH] =
        { register_a_address, register_values.register_a_value, register_values.register_b_value };
    const bool DO_NOT_SEND_STOP = false;
    int8_t i2c_result = i2c_write_blocking_until(I2C_IO_EXPANDER_BUS, IO_EXPANDER_ADDRESS,
        write_buffer, DOUBLE_REGISTER_WRITE_COMMAND_BYTE_LENGTH, DO_NOT_SEND_STOP, build_i2c_timeout());

    if (i2c_result == PICO_ERROR_TIMEOUT)
    {
        // Retry until we receive a correct written_byte_count
        printf("[ER_TIMEOUT] Retrying...\n");
        mcp23017_write_double_register_value(register_a_address, register_values);
    }
    else if (i2c_result == PICO_ERROR_GENERIC)
    {
        printf("[ER_GENERIC] Retrying...\n");
        mcp23017_write_double_register_value(register_a_address, register_values);
    }
    else if (i2c_result != DOUBLE_REGISTER_WRITE_COMMAND_BYTE_LENGTH)
    {
        printf("[ER_BYTE_MISMATCH] Retrying...\n");
        mcp23017_write_double_register_value(register_a_address, register_values);
    }
}

//static uint8_t mcp23017_read_single_register_value(uint8_t register_address)
//{
//    // To get a register value byte, write the device address (handled by the i2c api) and then the
//    // register you want to start retrieving data from.
//    const bool DO_NOT_SEND_STOP = false;
//    int8_t written_byte_count = i2c_write_blocking(I2C_IO_EXPANDER_BUS, IO_EXPANDER_ADDRESS,
//        &register_address, REGISTER_READ_REQUEST_BYTE_LENGTH, DO_NOT_SEND_STOP);
//
//    // Request N number of registries to be returned since each is 1 byte.
//    // Values will start from the register previously written.
//    uint8_t read_buffer[SINGLE_REGISTER_READ_RECEIPT_BYTE_LENGTH] = {0};
//    uint8_t read_count = i2c_read_blocking(I2C_IO_EXPANDER_BUS, IO_EXPANDER_ADDRESS,
//        read_buffer, SINGLE_REGISTER_READ_RECEIPT_BYTE_LENGTH, DO_NOT_SEND_STOP);
//
//    //TODO warning if read_count is not expected value.
//
//    return read_buffer[0];
//}

static struct io_expander_register_value_pair_with_read_state_t mcp23017_read_double_register_value(
    uint8_t register_a_address)
{
    // To get a register value byte, write the device address (handled by the i2c api) and then the
    // register you want to start retrieving data from.
    const bool DO_NOT_SEND_STOP = false;
    int8_t written_byte_count = i2c_write_blocking(I2C_IO_EXPANDER_BUS, IO_EXPANDER_ADDRESS,
        &register_a_address, REGISTER_READ_REQUEST_BYTE_LENGTH, DO_NOT_SEND_STOP);

    // Request N number of registries to be returned since each is 1 byte.
    // Values will start from the register previously written.
    // Reading two bytes will get us the A and B register values.
    uint8_t read_buffer[DOUBLE_REGISTER_READ_RECEIPT_BYTE_LENGTH] = {0};
    uint8_t read_count = i2c_read_blocking(I2C_IO_EXPANDER_BUS, IO_EXPANDER_ADDRESS,
        read_buffer, DOUBLE_REGISTER_READ_RECEIPT_BYTE_LENGTH, DO_NOT_SEND_STOP);

    struct io_expander_register_value_pair_with_read_state_t register_value_pair =
    {
        .register_a_value = read_buffer[0],
        .register_b_value = read_buffer[1],
        .read_success = !(read_count < DOUBLE_REGISTER_READ_RECEIPT_BYTE_LENGTH)
    };
    return register_value_pair;
}

static void set_default_io_expander_state()
{
    struct io_expander_register_value_pair_t iodir_register_value_pair = {0};
    //Set all selected columns to input pins (1). Leave everything else as output (0).
    for(uint16_t i = 0; i < COLUMN_COUNT; i++)
    {
        uint8_t colPinNumber = IO_EXPA_COLS[i];
        if (does_pin_number_belong_to_register_a(colPinNumber))
        {
            uint8_t bit_index = get_register_a_bit_index_from_pin_number(colPinNumber);
            iodir_register_value_pair.register_a_value |= 1 << bit_index;
        }
        else if (does_pin_number_belong_to_register_b)
        {
            uint8_t bit_index = get_register_b_bit_index_from_pin_number(colPinNumber);
            iodir_register_value_pair.register_b_value |= 1 << bit_index;
        }
    }

    //Set all selected rows to input pins (1). Leave everything else as output (0).
    for(uint16_t i = 0; i < ROW_COUNT; i++)
    {
        uint8_t rowPinNumber = IO_EXPA_ROWS[i];
        if (does_pin_number_belong_to_register_a(rowPinNumber))
        {
            uint8_t bit_index = get_register_a_bit_index_from_pin_number(rowPinNumber);
            iodir_register_value_pair.register_a_value |= 1 << bit_index;
        }
        else if (does_pin_number_belong_to_register_b)
        {
            uint8_t bit_index = get_register_b_bit_index_from_pin_number(rowPinNumber);
            iodir_register_value_pair.register_b_value |= 1 << bit_index;
        }
    }

    // We can use the same values here to set all the columns to pullup.
    struct io_expander_register_value_pair_t gppu_register_value_pair = iodir_register_value_pair;

    mcp23017_write_double_register_value(IODIR_A_REGISTER_ADDRESS, iodir_register_value_pair);
    mcp23017_write_double_register_value(GPPU_A_REGISTER_ADDRESS, gppu_register_value_pair);
}

static void read_matrix_state(void)
{
    for (uint16_t row = 0; row < ROW_COUNT; row++)
    {
        uint8_t rowPinNumber = IO_EXPA_ROWS[row];

        struct io_expander_register_value_pair_with_read_state_t initial_iodir_values =
            mcp23017_read_double_register_value(IODIR_A_REGISTER_ADDRESS);

        struct io_expander_register_value_pair_t row_output_no_pullup_values =
        {
            .register_a_value = initial_iodir_values.register_a_value,
            .register_b_value = initial_iodir_values.register_b_value
        };

        if (does_pin_number_belong_to_register_a(rowPinNumber))
        {
            uint8_t bit_index = get_register_a_bit_index_from_pin_number(rowPinNumber);
            row_output_no_pullup_values.register_a_value ^= 1 << bit_index;
        }
        else if (does_pin_number_belong_to_register_b)
        {
            uint8_t bit_index = get_register_b_bit_index_from_pin_number(rowPinNumber);
            row_output_no_pullup_values.register_b_value ^= 1 << bit_index;
        }

        mcp23017_write_double_register_value(IODIR_A_REGISTER_ADDRESS, row_output_no_pullup_values);
        mcp23017_write_double_register_value(GPPU_A_REGISTER_ADDRESS, row_output_no_pullup_values);

        struct io_expander_register_value_pair_with_read_state_t gpio_values = mcp23017_read_double_register_value(
            GPIO_A_REGISTER_ADDRESS);

        //Only update from a valid read operation.
        if (gpio_values.read_success)
        {
            for (uint16_t col = 0; col < COLUMN_COUNT; col++)
            {
                uint8_t colPinNumber = IO_EXPA_COLS[col];
                if (does_pin_number_belong_to_register_a(colPinNumber))
                {
                    uint8_t bit_index = get_register_a_bit_index_from_pin_number(colPinNumber);
                    _peripheral_switch_matrix_curr[row][col] = (gpio_values.register_a_value >> bit_index) & 1;
                }
                else if (does_pin_number_belong_to_register_b)
                {
                    uint8_t bit_index = get_register_b_bit_index_from_pin_number(colPinNumber);
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

//void peripheral_switch_state_task(void)
//{
//    read_matrix_state();
//
//    fire_callback_events();
//
//    update_prev_matrix();
//
//    if (SWITCH_TESTING_MODE)
//    {
//        //TODO this sleep suspends the USB device. REMOVE WHEN REPORTING IS NEEDED.
//        //sleep_ms(500);
//        print_matrix_state();
//    }
//}

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

