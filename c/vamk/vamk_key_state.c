///Imports
#include <stdbool.h>
#include "pico/stdlib.h"
#include "vamk_config.h"
#include "vamk_key_state.h"
#include "vamk_types.h"

///Global Variables

///Static Variables
static uint8_t _current_layer = 0;

///Private Declarations

///Static (Private/Local) Functions

///Public Functions
static key_report_t key_state_build_report()
{
}

uint8_t key_state_get_current_layer()
{
}

void key_state_press(uint8_t keycode, bool shouldHoldDown)
{
}

void key_state_release(uint8_t keycode)
{
}
