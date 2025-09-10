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
#include "vamk_config.h"
#include "vamk_types.h"
#include "vamk_key_logic.h"
#include "vamk_switch_logic.h"
#include "vamk_key_timer.h"
#include "vamk_keymap_config.h"
#include "vamk_switch_state.h"
#include "vamk_display_state.h"
#include "vamk_key_state.h"
#if IS_SPLIT_KEYBOARD
    #include "vamk_peripheral_switch_state.h"
#endif

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

#if KM_SWITCH_ENABLED
    gpio_init(KM_SWITCH_SELECT_PIN);
    gpio_init(KM_SWITCH_SUSPEND_PIN);
    gpio_pull_up(KM_SWITCH_SELECT_PIN);
    gpio_pull_down(KM_SWITCH_SUSPEND_PIN);
#endif

    //gpio_init(22);
    //gpio_init(19);
    //gpio_init(18);

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
    switch_state_set_pressed_callback(switch_logic_press_handler);
    switch_state_set_released_callback(switch_logic_release_handler);

#if IS_SPLIT_KEYBOARD
    // Join I2C bus as controller
    peripheral_switch_state_init();

    // Init peripheral switch state handling.
    peripheral_switch_state_set_pressed_callback(switch_logic_press_handler);
    peripheral_switch_state_set_released_callback(switch_logic_release_handler);
#endif

    // Init logic handlers for key gestures
    key_timer_set_key_down_callback(key_logic_down_handler);
    key_timer_set_key_up_callback(key_logic_up_handler);
    key_timer_set_key_delay_callback(key_logic_delay_handler);

        // Primary side run loop
        while (1)
        {
            // TinyUSB device task required to be called every iteration.
            tud_task();

#if ENABLE_LED_DEVICE_STATUS_INDICATOR
            // Update LED state.
            led_blinking_task();
#endif

//            // Update local, phyiscal switch state.
//            switch_state_task();
//
//#if IS_SPLIT_KEYBOARD
//            // Update non-native (peripheral), phyiscal switch state.
//            peripheral_switch_state_task();
//#endif

            // TODO we want to have an alternate eval path for the
            // macro reporting here.

            // Update matrices
            switch_state_task_update();
#if IS_SPLIT_KEYBOARD
            peripheral_switch_state_task_update();
#endif

            // Handle all keystates
            switch_state_task_process();
#if IS_SPLIT_KEYBOARD
            peripheral_switch_state_task_process();
#endif

            // Clean up and reset.
            switch_state_task_finalize();
#if IS_SPLIT_KEYBOARD
            peripheral_switch_state_task_finalize();
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
