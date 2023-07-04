///Imports
#include <stddef.h>
#include <stdio.h>
#include "hardware/gpio.h"
#include "vamk_config.h"
#include "vamk_switch_state.h"
#include "vamk_types.h"

///Global Variables
static uint8_t _switch_matrix_curr[ROW_COUNT][COLUMN_COUNT] = {0};
static uint8_t _switch_matrix_prev[ROW_COUNT][COLUMN_COUNT] = {0};

//TODO these need to accept a side and this class will pass the CURRENT_KEYBOARD_SIDE
static switch_pressed_callback_t _pressed_callback = NULL;
static switch_released_callback_t _released_callback = NULL;

///Static (Private) Functions
static void read_matrix_state(void)
{
    for (uint16_t row = 0; row < ROW_COUNT; row++)
    {
        // Pull the row pins LOW. With the INPUT_PULLUP cols high and the diodes pointed
        // toward the rows, we will allow current to flow from Col->Row.
        uint8_t rowPin = ROWS[row];
        gpio_set_dir(rowPin, GPIO_OUT);
        gpio_pull_down(rowPin);

        for (uint16_t col = 0; col < COLUMN_COUNT; col++)
        {
            // Attempt connection to the row pin we just pulled down.
            // Should read zero if switch is pressed.
            uint8_t colPin = COLS[col];
            gpio_set_dir(colPin, GPIO_IN);
            gpio_pull_up(colPin);
            _switch_matrix_curr[row][col] = gpio_get(COLS[col]);
        }

        // Disable the row output.
        gpio_set_dir(rowPin, GPIO_IN);
        gpio_pull_up(rowPin);
    }
}

static void update_prev_matrix(void)
{
    for (uint16_t i = 0; i < ROW_COUNT; i++)
    {
        for (uint16_t j = 0; j < COLUMN_COUNT; j++)
        {
            _switch_matrix_prev[i][j] = _switch_matrix_curr[i][j];
        }
    }
}

static void fire_callback_events(void)
{
    for (uint16_t i = 0; i < ROW_COUNT; i++)
    {
        for (uint16_t j = 0; j < COLUMN_COUNT; j++)
        {
            uint8_t switchCurrPress = _switch_matrix_curr[i][j];
            uint8_t switchPrevPress = _switch_matrix_prev[i][j];
            if (switchCurrPress != switchPrevPress)
            {
                if (switchCurrPress == SWITCH_PRESSED_VALUE &&
                    switchPrevPress == SWITCH_NOT_PRESSED_VALUE)
                {
                    // We started pressing a key.
                    if (_pressed_callback != NULL)
                        _pressed_callback(i, j, CURRENT_KEYBOARD_SIDE);
                }
                else
                {
                    // We released a key.
                    if (_released_callback != NULL)
                        _released_callback(i, j, CURRENT_KEYBOARD_SIDE);
                }
            }
        }
    }
}

static void print_matrix_state(void)
{
    static uint32_t report_id = 0;
    for (uint16_t i = 0; i < ROW_COUNT; i++)
    {
        printf("%uN0%i:", report_id, i);
        for (uint16_t j = 0; j < COLUMN_COUNT; j++)
        {
            printf("%i", _switch_matrix_curr[i][j]);
        }
        printf("\n");
    }
    report_id++;
}

///Public Functions
void switch_state_init(void)
{
    // Init all the row and column gpio pins.
    for(uint16_t i = 0; i < ROW_COUNT; i++)
    {
        uint8_t rowPin = ROWS[i];
        gpio_init(rowPin);
    }

    for (uint16_t i = 0; i < COLUMN_COUNT; i++)
    {
        uint8_t colPin = COLS[i];
        gpio_init(colPin);
    }

    //Load the default switch state into each array.
    read_matrix_state();
    update_prev_matrix();
}

void switch_state_task(void)
{
    read_matrix_state();
    fire_callback_events();

    update_prev_matrix();

    if (SWITCH_TESTING_MODE)
    {
        //TODO this sleep suspends the USB device. REMOVE WHEN REPORTING IS NEEDED.
        //sleep_ms(500);

        print_matrix_state();
    }
}

void switch_state_set_pressed_callback(switch_pressed_callback_t pressed_callback)
{
    _pressed_callback = pressed_callback;
}

void switch_state_set_released_callback(switch_released_callback_t released_callback)
{
    _released_callback = released_callback;
}

