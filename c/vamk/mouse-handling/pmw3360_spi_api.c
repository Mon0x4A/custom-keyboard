
///Imports
#include <stdio.h>
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include "pmw3360_config.h"
#include "pmw3360_spi_api.h"

///Local Declarations
///Static Constants
#define STARTUP_SLEEP_US 50

#define INSTRUCTION_SLEEP_US 10
#define READ_REQUEST_LENGTH 1
#define WRITE_REQUEST_LENGTH 2

#define SERIAL_OUT_DATA_DURING_READ 0

///Static Global Variables
///Static Functions

///Extern Functions
struct pmw3360_register_read_result_s pmw3360_read_register(uint8_t register_address)
{
    //TODO bring chip select low? Or is that done for us by the api?
    sleep_us(INSTRUCTION_SLEEP_US);

    // Write the register we want to read from.
    uint8_t bytes_written = spi_write_blocking(
        PMW3360_SPI_INSTANCE, &register_address, READ_REQUEST_LENGTH);

    if (bytes_written != READ_REQUEST_LENGTH)
        printf("[WARNING] Unsuccessful read request of register: %x\n", register_address);

    sleep_us(INSTRUCTION_SLEEP_US);

    // Then read one byte.
    uint8_t read_buffer[READ_REQUEST_LENGTH] = {0};
    uint8_t bytes_read = spi_read_blocking(
        PMW3360_SPI_INSTANCE, SERIAL_OUT_DATA_DURING_READ, read_buffer, READ_REQUEST_LENGTH);

    bool successful_read = bytes_read != READ_REQUEST_LENGTH;
    if (!successful_read)
        printf("[WARNING] Unsuccessful read response of register: %x\n", register_address);

    struct pmw3360_register_read_result_s read_result =
    {
        .register_value = read_buffer[0],
        .read_success = successful_read,
    };

    return read_result;
}

bool pmw3360_write_register(uint8_t register_address, uint8_t register_value)
{
    sleep_us(INSTRUCTION_SLEEP_US);

    uint8_t write_buffer[WRITE_REQUEST_LENGTH] = { register_address, register_value };

    // Write the register we want to assign a value to followed by
    // by the value we want to assign.
    uint8_t bytes_written = spi_write_blocking(
        PMW3360_SPI_INSTANCE, write_buffer, WRITE_REQUEST_LENGTH);

    bool successful_write = bytes_written != WRITE_REQUEST_LENGTH;
    if (!successful_write)
        printf("[WARNING] Unsuccessful write request of register: %x\n", register_address);

    return successful_write;
}

void pmw3360_init(void)
{
    spi_init(PMW3360_SPI_INSTANCE, TARGET_BAUDRATE_HZ);

    gpio_set_function(PMW3360_SPI_CLOCK_GPIO, GPIO_FUNC_SPI);
    gpio_set_function(PMW3360_SPI_TX_GPIO, GPIO_FUNC_SPI);
    gpio_set_function(PMW3360_SPI_RX_GPIO, GPIO_FUNC_SPI);

    //TODO does this actually need to happen?
    gpio_set_function(PMW3360_SPI_CS0_GPIO, GPIO_FUNC_SPI);
    //TODO set up multiple chip select pins?

    // Brief break before we start sending commands to let everything
    // initialize.
    sleep_us(STARTUP_SLEEP_US);

    // Read from the motion and delta registers in sequence during
    // startup as per the datasheet instructions. Return is irrelevant.
    pmw3360_read_register(MOTION_REGISTER_ADDRESS);
    pmw3360_read_register(DELTA_XL_REGISTER_ADDRESS);
    pmw3360_read_register(DELTA_XH_REGISTER_ADDRESS);
    pmw3360_read_register(DELTA_YL_REGISTER_ADDRESS);
    pmw3360_read_register(DELTA_YH_REGISTER_ADDRESS);
}

struct pmw3360_mouse_sensor_delta_s pmw3360_get_current_delta(void)
{
    struct pmw3360_register_read_result_s dxh_result =
        pmw3360_read_register(DELTA_XH_REGISTER_ADDRESS);
    struct pmw3360_register_read_result_s dxl_result =
        pmw3360_read_register(DELTA_XL_REGISTER_ADDRESS);

    struct pmw3360_register_read_result_s dyh_result =
        pmw3360_read_register(DELTA_YH_REGISTER_ADDRESS);
    struct pmw3360_register_read_result_s dyl_result =
        pmw3360_read_register(DELTA_YL_REGISTER_ADDRESS);

    uint8_t x_delta_arr[sizeof(int16_t)] =
        { dxl_result.register_value, dxh_result.register_value };
    uint8_t y_delta_arr[sizeof(int16_t)] =
        { dyl_result.register_value, dyh_result.register_value };

    struct pmw3360_mouse_sensor_delta_s sensor_delta =
    {
        .x_delta = (int16_t)*x_delta_arr,
        .y_delta = (int16_t)*y_delta_arr,
        .has_valid_delta = dxl_result.read_success && dxh_result.read_success
            && dyl_result.read_success && dyh_result.read_success,
    };

    return sensor_delta;
}
