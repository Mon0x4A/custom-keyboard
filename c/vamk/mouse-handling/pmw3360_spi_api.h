#ifndef PWM3360_SPI_API_H
#define PWM3360_SPI_API_H

///Imports
#include "pico/stdlib.h"

///Type Declarations
struct pmw3360_register_read_result_s
{
    uint8_t register_value;
    bool read_success;
};

struct pmw3360_mouse_sensor_delta_s
{
    int16_t x_delta;
    int16_t y_delta;
    bool has_valid_delta;
};

///Constants
#define MOTION_REGISTER_ADDRESS       0x02 // Bool: has motion occured since last report.
#define DELTA_XL_REGISTER_ADDRESS     0x03 // Lower 8 bits of X delta.
#define DELTA_XH_REGISTER_ADDRESS     0x04 // Higher 8 bits of X delta.
#define DELTA_YL_REGISTER_ADDRESS     0x05 // Lower 8 bits of Y delta.
#define DELTA_YH_REGISTER_ADDRESS     0x06 // Higher 8 bits of Y delta.

///Function Declarations
struct pmw3360_register_read_result_s pmw3360_read_register(uint8_t register_address);
bool pmw3360_write_register(uint8_t register_address, uint8_t register_value);

void pmw3360_init(void);

struct pmw3360_mouse_sensor_delta_s pmw3360_get_current_delta(void);

#endif
