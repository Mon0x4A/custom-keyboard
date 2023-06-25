///Imports
#include <stddef.h>
#include "vamk_config.h"
#include "vamk_types.h"

///Global Variables
static int _switchMatrixCurr[ROW_COUNT][COLUMN_COUNT] = {0};
static int _switchMatrixPrev[ROW_COUNT][COLUMN_COUNT] = {0};

static switch_pressed_callback_t _press_callback = NULL;
static switch_released_callback_t _released_callback = NULL;

///Function Declarations
///Static (Private) Functions
static void read_matrix_state(void)
{
}

static void update_prev_matrix(void)
{
}

///Public Functions
void switch_state_task(void)
{
}

void switch_state_set_pressed_callback(switch_pressed_callback_t pressed_callback)
{
    _press_callback = pressed_callback;
}

void switch_state_set_released_callback(switch_released_callback_t released_callback)
{
    _released_callback = released_callback;
}

