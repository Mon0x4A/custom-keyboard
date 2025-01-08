
///Imports
#include <stdio.h>
#include "mcp23017_config.h"
#include "mcp23017_i2c_api.h"
#include "time.h"

///Static Constants
#define IO_EXPANDER_SLEEP_BUFFER_US 100 //NOTE: Datasheet says this is min 10us
#define I2C_INSTRUCTION_TIMEOUT_MS 5
#define SINGLE_REGISTER_WRITE_COMMAND_BYTE_LENGTH 2
#define DOUBLE_REGISTER_WRITE_COMMAND_BYTE_LENGTH 3

#define REGISTER_READ_REQUEST_BYTE_LENGTH 1
#define SINGLE_REGISTER_READ_RECEIPT_BYTE_LENGTH 1
#define DOUBLE_REGISTER_READ_RECEIPT_BYTE_LENGTH 2

#define REGISTER_B_MIN_PIN_NUMBER 1
#define REGISTER_B_MAX_PIN_NUMBER 8
#define REGISTER_A_MIN_PIN_NUMBER 21
#define REGISTER_A_MAX_PIN_NUMBER 28

///Static Functions
static absolute_time_t build_i2c_timeout(void)
{
    absolute_time_t time_base = get_absolute_time();
    absolute_time_t timeout_target = delayed_by_us(time_base, I2C_INSTRUCTION_TIMEOUT_MS*1000);
    return timeout_target;
}

///Extern Functions
bool mcp23017_does_pin_number_belong_to_register_a(uint8_t pin_number)
{
    return pin_number >= REGISTER_A_MIN_PIN_NUMBER && pin_number <= REGISTER_A_MAX_PIN_NUMBER;
}

bool mcp23017_does_pin_number_belong_to_register_b(uint8_t pin_number)
{
    return pin_number >= REGISTER_B_MIN_PIN_NUMBER && pin_number <= REGISTER_B_MAX_PIN_NUMBER;
}

int8_t mcp23017_get_register_a_bit_index_from_pin_number(uint8_t pin_number)
{
    return mcp23017_does_pin_number_belong_to_register_a(pin_number) ? pin_number-21 : -1;
}

int8_t mcp23017_get_register_b_bit_index_from_pin_number(uint8_t pin_number)
{
    return mcp23017_does_pin_number_belong_to_register_b(pin_number) ? pin_number-1 : -1;
}

int8_t mcp23017_write_single_register_value(uint8_t register_address, uint8_t register_contents, bool retry_on_failure)
{
    // Sleep briefly to avoid overwhelming the expander with too many commands.
    sleep_us(IO_EXPANDER_SLEEP_BUFFER_US);

    // To write a single register value byte, write the device address (handled by i2c api), then the
    // register you want to set, followed by the register value. For a total of 3 bytes.
    const uint8_t write_buffer[SINGLE_REGISTER_WRITE_COMMAND_BYTE_LENGTH] = { register_address, register_contents };
    const bool DO_NOT_SEND_STOP = false;
    int8_t i2c_result = i2c_write_blocking_until(MCP23017_I2C_BUS, MCP23017_I2C_ADDRESS,
        write_buffer, SINGLE_REGISTER_WRITE_COMMAND_BYTE_LENGTH, DO_NOT_SEND_STOP, build_i2c_timeout());

    if (!retry_on_failure)
        return i2c_result;

    switch (i2c_result)
    {
        case PICO_ERROR_TIMEOUT:
            // Retry until we receive a correct written_byte_count
            printf("[ER_TIMEOUT] Retrying...\n");
            mcp23017_write_single_register_value(register_address, register_contents, retry_on_failure);
            break;
        case PICO_ERROR_GENERIC:
            printf("[ER_GENERIC] Retrying...\n");
            mcp23017_write_single_register_value(register_address, register_contents, retry_on_failure);
            break;
        default:
            if (i2c_result != SINGLE_REGISTER_WRITE_COMMAND_BYTE_LENGTH)
            {
                printf("[ER_BYTE_MISMATCH] Retrying...\n");
                mcp23017_write_single_register_value(register_address, register_contents, retry_on_failure);
            }
            break;
    }

    return i2c_result;
}

int8_t mcp23017_write_double_register_value(uint8_t register_a_address,
    struct io_expander_register_value_pair_s register_values, bool retry_on_failure)
{
    // Sleep briefly to avoid overwhelming the expander with too many commands.
    sleep_us(IO_EXPANDER_SLEEP_BUFFER_US);

    // To write a double register value byte, write the device address (handled by i2c api), then the
    // 'A' register of the pair you want to set, followed by the register A value, the then register B
    // value. For a total of 4 bytes.
    const uint8_t write_buffer[DOUBLE_REGISTER_WRITE_COMMAND_BYTE_LENGTH] =
        { register_a_address, register_values.register_a_value, register_values.register_b_value };
    const bool DO_NOT_SEND_STOP = false;
    int8_t i2c_result = i2c_write_blocking_until(MCP23017_I2C_BUS, MCP23017_I2C_ADDRESS,
        write_buffer, DOUBLE_REGISTER_WRITE_COMMAND_BYTE_LENGTH, DO_NOT_SEND_STOP, build_i2c_timeout());

    if (!retry_on_failure)
        return i2c_result;

    switch (i2c_result)
    {
        case PICO_ERROR_TIMEOUT:
            // Retry until we receive a correct written_byte_count
            printf("[ER_TIMEOUT] Retrying...\n");
            mcp23017_write_double_register_value(register_a_address, register_values, retry_on_failure);
            break;
        case PICO_ERROR_GENERIC:
            printf("[ER_GENERIC] Retrying...\n");
            mcp23017_write_double_register_value(register_a_address, register_values, retry_on_failure);
            break;
        default:
            if (i2c_result != DOUBLE_REGISTER_WRITE_COMMAND_BYTE_LENGTH)
            {
                printf("[ER_BYTE_MISMATCH] Retrying...\n");
                mcp23017_write_double_register_value(register_a_address, register_values, retry_on_failure);
            }
            break;
    }
    return i2c_result;
}

struct io_expander_register_value_with_read_state_s mcp23017_read_single_register_value(uint8_t register_address)
{
    // To get a register value byte, write the device address (handled by the i2c api) and then the
    // register you want to start retrieving data from.
    const bool DO_NOT_SEND_STOP = false;
    int8_t written_byte_count = i2c_write_blocking(MCP23017_I2C_BUS, MCP23017_I2C_ADDRESS,
        &register_address, REGISTER_READ_REQUEST_BYTE_LENGTH, DO_NOT_SEND_STOP);

    // Request N number of registries to be returned since each is 1 byte.
    // Values will start from the register previously written.
    uint8_t read_buffer[SINGLE_REGISTER_READ_RECEIPT_BYTE_LENGTH] = {0};
    uint8_t read_count = i2c_read_blocking(MCP23017_I2C_BUS, MCP23017_I2C_ADDRESS,
        read_buffer, SINGLE_REGISTER_READ_RECEIPT_BYTE_LENGTH, DO_NOT_SEND_STOP);

    struct io_expander_register_value_with_read_state_s register_value_container =
    {
        .register_value = read_buffer[0],
        .read_success = !(read_count < SINGLE_REGISTER_READ_RECEIPT_BYTE_LENGTH),
    };

    return register_value_container;
}

struct io_expander_register_value_pair_with_read_state_s mcp23017_read_double_register_value(
    uint8_t register_a_address)
{
    // Sleep briefly to avoid overwhelming the expander with too many commands.
    sleep_us(IO_EXPANDER_SLEEP_BUFFER_US);

    // To get a register value byte, write the device address (handled by the i2c api) and then the
    // register you want to start retrieving data from.
    const bool DO_NOT_SEND_STOP = false;
    int8_t written_byte_count = i2c_write_blocking(MCP23017_I2C_BUS, MCP23017_I2C_ADDRESS,
        &register_a_address, REGISTER_READ_REQUEST_BYTE_LENGTH, DO_NOT_SEND_STOP);

    // Request N number of registries to be returned since each is 1 byte.
    // Values will start from the register previously written.
    // Reading two bytes will get us the A and B register values.
    uint8_t read_buffer[DOUBLE_REGISTER_READ_RECEIPT_BYTE_LENGTH] = {0};
    uint8_t read_count = i2c_read_blocking(MCP23017_I2C_BUS, MCP23017_I2C_ADDRESS,
        read_buffer, DOUBLE_REGISTER_READ_RECEIPT_BYTE_LENGTH, DO_NOT_SEND_STOP);

    struct io_expander_register_value_pair_with_read_state_s register_value_pair_container =
    {
        .register_a_value = read_buffer[0],
        .register_b_value = read_buffer[1],
        .read_success = !(read_count < DOUBLE_REGISTER_READ_RECEIPT_BYTE_LENGTH)
    };
    return register_value_pair_container;
}
