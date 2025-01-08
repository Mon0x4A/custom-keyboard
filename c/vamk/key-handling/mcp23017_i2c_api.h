
#ifndef MCP23017_I2C_API_H
#define MCP23017_I2C_API_H

///Imports
#include "pico/stdlib.h"
#include "hardware/i2c.h"

///Type Declarations
struct io_expander_register_value_with_read_state_s
{
    uint8_t register_value;
    bool read_success;
};

struct io_expander_register_value_pair_with_read_state_s
{
    uint8_t register_a_value;
    uint8_t register_b_value;
    bool read_success;
};

struct io_expander_register_value_pair_s
{
    uint8_t register_a_value;
    uint8_t register_b_value;
};

///Constants
#define GPIO_A_REGISTER_ADDRESS 0x12
#define GPIO_B_REGISTER_ADDRESS 0x13
#define IODIR_A_REGISTER_ADDRESS 0x00
#define IODIR_B_REGISTER_ADDRESS 0x01
#define GPPU_A_REGISTER_ADDRESS 0x0C
#define GPPU_B_REGISTER_ADDRESS 0x0D
//TODO put in the other register addresses

///Function Declarations
void mcp23017_init(void);

bool mcp23017_does_pin_number_belong_to_register_a(uint8_t pin_number);
bool mcp23017_does_pin_number_belong_to_register_b(uint8_t pin_number);
int8_t mcp23017_get_register_a_bit_index_from_pin_number(uint8_t pin_number);
int8_t mcp23017_get_register_b_bit_index_from_pin_number(uint8_t pin_number);

int8_t mcp23017_write_single_register_value(uint8_t register_address, uint8_t register_contents, bool retry_on_failure);
int8_t mcp23017_write_double_register_value(uint8_t register_a_address,
    struct io_expander_register_value_pair_s register_values, bool retry_on_failure);
struct io_expander_register_value_with_read_state_s mcp23017_read_single_register_value(uint8_t register_address);
struct io_expander_register_value_pair_with_read_state_s mcp23017_read_double_register_value(uint8_t register_a_address);

#endif
