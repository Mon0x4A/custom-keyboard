//Imports
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Pico SDK imports
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"

// TinyUSB imports
#include "tusb.h"
#include "usb_descriptors.h"

// Required to access on-board switch and LED.
#include "bsp/board.h"

// Project Imports
#include "vamk_config.h"
#include "vamk_i2c_switch_state_transmitter.h"
#include "vamk_key_state.h"
#include "vamk_peripheral_switch_state.h"
#include "vamk_press_handler.h"
#include "vamk_release_handler.h"
#include "vamk_switch_state.h"
#include "vamk_types.h"

///Static Variables
static led_blink_pattern_t _led_mode = NOT_MOUNTED;

///Function Declarations
static void led_blinking_task(void);
static void hid_task(void);

///ENTRY POINT
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

    if (IS_PRIMARY_KEYBOARD_SIDE)
    {
        // TODO TEMP TEST Set up I2C as peripheral
        //i2c_switch_state_transmitter_init();

        // Init local/native switch handling
        switch_state_set_pressed_callback(press_handler_on_switch_press);
        switch_state_set_released_callback(release_handler_on_switch_release);

#if IS_SPLIT_KEYBOARD
        // Join I2C bus as controller
        peripheral_switch_state_init();

        // Init peripheral switch state handling.
        peripheral_switch_state_set_released_callback(release_handler_on_switch_release);
        peripheral_switch_state_set_pressed_callback(press_handler_on_switch_press);
#endif

        // Primary side run loop
        while (1)
        {
            // TinyUSB device task required to be called every iteration.
            tud_task();

            // Update LED state.
            led_blinking_task();

            // Update local, phyiscal switch state.
            switch_state_task();

#if IS_SPLIT_KEYBOARD
            // Update non-native (peripheral), phyiscal switch state.
            peripheral_switch_state_task();
#endif

            // Update reported keyboard state.
            hid_task();
        }
    }
    else
    {
        // Set up I2C as peripheral
        i2c_switch_state_transmitter_init();

        switch_state_set_pressed_callback(i2c_switch_state_on_switch_pressed);
        switch_state_set_released_callback(i2c_switch_state_on_switch_released);

        // Peripheral side run loop
        bool led_is_on = false;
        while (1)
        {
            // Keep our local switch state up to date.
            switch_state_task();

            sleep_ms(10);
            board_led_write(1);
        }
    }

    return 0;
}

///Static Functions
static void send_hid_report(uint8_t report_id, uint32_t btn)
{
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
    // Init poll interval (ms)
    const uint32_t interval_ms = 10;
    static uint32_t start_ms = 0;

    if (board_millis() - start_ms < interval_ms)
        return;
    start_ms += interval_ms;

    //TODO remove this code that references 'btn'
    uint32_t const btn = board_button_read();

    // Remote wakeup
    if (tud_suspended() && btn)
    {
        // Wake up host if we are in suspend mode
        // and REMOTE_WAKEUP feature is enabled by host
        tud_remote_wakeup();
    }
    else
    {
        send_hid_report(REPORT_ID_KEYBOARD, btn);
    }
}

static void led_blinking_task(void)
{
    static uint32_t start_ms = 0;
    static bool led_state = false;

    // LED blink is disabled if set to zero.
    if (!_led_mode)
        return;

    // Blink every interval ms
    if (board_millis() - start_ms < _led_mode)
        return;

    start_ms += _led_mode;

    board_led_write(led_state);
    // Toggle LED state
    led_state = 1 - led_state;
}

///Extern Functions

//TODO refactor this into its own file.
// BEGIN TinyUSB Device Callbacks -----------------------------------------+
// Invoked when device is mounted
void tud_mount_cb(void)
{
    _led_mode = MOUNTED;
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
    _led_mode = NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
    (void) remote_wakeup_en;
    _led_mode = SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
    _led_mode = MOUNTED;
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: Implementation required by TinyUSB, even if unused.
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint16_t len)
{
    // Not Implemented
    (void) instance;
    (void) len;
    (void) report;
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
// Note: Implementation required by TinyUSB, even if unused.
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
    // Not Implemented
    (void) instance;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) reqlen;

    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
// Note: Implementation required by TinyUSB, even if unused.
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
    // Not Implemented
    (void) instance;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) bufsize;
}
// END TinyUSB Device Callbacks -----------------------------------------+
