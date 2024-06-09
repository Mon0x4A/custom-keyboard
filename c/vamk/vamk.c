//Imports
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Pico SDK imports
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"

//// TinyUSB imports
#include "tusb.h"
#include "tusb_implementation.h"
#include "usb_descriptors.h"
#include "bsp/board.h" // Required to access board timer.

// Project Imports
#include "ssd1306_config.h"
#include "ssd1306_buffer_helper.h"
#include "ssd1306_i2c_api.h"
#include "vamk_keymap_config.h"
#include "vamk_config.h"
#include "vamk_display_state.h"
#include "vamk_key_state.h"
#include "vamk_peripheral_switch_state.h"
#include "vamk_press_handler.h"
#include "vamk_release_handler.h"
#include "vamk_switch_state.h"
#include "vamk_types.h"

///Static Variables

///Static Functions
static void send_hid_report(uint8_t report_id)
{
    // Right now we are always assuming we are processing
    // a keyboard report.
    (void) report_id;

    if (!tud_hid_ready())
        // Abort if our HID driver is not ready.
        return;

    // Avoid sending multiple consecutive reports.
    static struct key_report_t keyboard_report_prev =
    {
        .keycodes = 0,
        .modifier = 0
    };

    // Build our new report
    struct key_report_t keyboard_report_curr = key_state_build_hid_report();

    // Compare current and previously sent report. If we're sending
    // the same codes, there's no need to report.
    bool keycodes_differ = false;
    for (int i = 0; i < HID_REPORT_KEYCODE_ARRAY_LENGTH; i++)
    {
        if (keyboard_report_curr.keycodes[i] != keyboard_report_prev.keycodes[i])
        {
            keycodes_differ = true;
            break;
        }
    }

    if (!keycodes_differ)
        return;

    // If the reports differ, send the new one.
    tud_hid_keyboard_report(
        REPORT_ID_KEYBOARD, keyboard_report_curr.modifier, keyboard_report_curr.keycodes);

    // Update the prev report
    keyboard_report_prev = keyboard_report_curr;
}

static void hid_task(void)
{
    static uint32_t start_ms = 0;
    if (board_millis() - start_ms < SWITCH_POLLING_INTERVAL_MS)
        return;
    start_ms += SWITCH_POLLING_INTERVAL_MS;

    send_hid_report(REPORT_ID_KEYBOARD);
}


///Extern Functions
int main(void)
{
    // Required pico utils initialization call.
    stdio_init_all();
    // Required board utils initialization call.
    board_init();
    // TinyUSB required initialization call.
    tusb_init();
    // Physical switch logic initialization call.
    switch_state_init();

#if IS_I2C_DISPLAY_ENABLED
    i2c_init(I2C_DISPLAY_BUS, I2C_CLOCK_SPEED);
    gpio_init(I2C_DISPLAY_SDA_PIN);
    gpio_init(I2C_DISPLAY_SCL_PIN);
    gpio_set_function(I2C_DISPLAY_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_DISPLAY_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_DISPLAY_SDA_PIN);
    gpio_pull_up(I2C_DISPLAY_SCL_PIN);

    ssd1306_init();
    display_reset_sleep_timeout();
#endif

    // Init local/native switch handling
    switch_state_set_pressed_callback(press_handler_on_switch_press);
    switch_state_set_released_callback(release_handler_on_switch_release);

#if IS_SPLIT_KEYBOARD
    // Join I2C bus as controller
    peripheral_switch_state_init();

    // Init peripheral switch state handling.
    peripheral_switch_state_set_pressed_callback(press_handler_on_switch_press);
    peripheral_switch_state_set_released_callback(release_handler_on_switch_release);
#endif

        // Primary side run loop
        while (1)
        {
            // TinyUSB device task required to be called every iteration.
            tud_task();

#if ENABLE_LED_DEVICE_STATUS_INDICATOR
            // Update LED state.
            led_blinking_task();
#endif

            // Update local, phyiscal switch state.
            switch_state_task();

#if IS_SPLIT_KEYBOARD
            // Update non-native (peripheral), phyiscal switch state.
            peripheral_switch_state_task();
#endif
            // Update reported keyboard state.
            hid_task();

#if IS_I2C_DISPLAY_ENABLED
            // Update the display state.
            display_task();
#endif
        }

    return 0;
}
