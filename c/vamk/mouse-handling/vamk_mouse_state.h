#ifndef VAMK_MOUSE_STATE_H
#define VAMK_MOUSE_STATE_H

///Imports
#include "pico/stdlib.h"
#include "pmw3360_spi_api.h"

///Type Declarations
typedef enum mouse_sensor_side
{
    LEFT = 1,
    RIGHT = 2,
} mouse_sensor_side_e;

///Constants
///Function Declarations
void mouse_init(void);
void mouse_task(void);

//TODO mouse report construction

#endif
