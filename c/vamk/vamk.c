// Pico SDK imports
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "hardware/timer.h"

// TinyUSB imports
#include "tusb.h"
#include "usb_descriptors.h"

// Required to access on-board switch and LED.
#include "bsp/board.h"

// Project Imports
#include "vamk_config.h"
#include "vamk_constants.h"

// GPIO defines
// Example uses GPIO 2
#define GPIO 2

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9

// Enums
typedef enum led_blink_pattern_ms
{
    NOT_MOUNTED = 250,
    MOUNTED = 1000,
    SUSPENDED = 2500,
} led_pattern_t;

// Global Variables
static led_pattern_t led_mode = NOT_MOUNTED;

// Function Declarations
static void led_blinking_task(void);
static void hid_task(void);

////TODO this timer code could be very useful for key events
//int64_t alarm_callback(alarm_id_t id, void *user_data) {
//    // Put your timeout handler code in here
//    return 0;
//}

// ENTRY POINT
int main(void)
{
    // Required pico utils initialization call.
    stdio_init_all();
    // Required board utils initialization call.
    board_init();
    // TinyUSB required initialization call.
    tusb_init();

    //// GPIO initialisation.
    //// We will make this GPIO an input, and pull it up by default
    //gpio_init(GPIO);
    //gpio_set_dir(GPIO, GPIO_IN);
    //gpio_pull_up(GPIO);

    //// I2C Initialisation. Using it at 400Khz.
    //i2c_init(I2C_PORT, 400*1000);

    //gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    //gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    //gpio_pull_up(I2C_SDA);
    //gpio_pull_up(I2C_SCL);

    //// Timer example code - This example fires off the callback after 2000ms
    //add_alarm_in_ms(2000, alarm_callback, NULL, false);

    // Main run loop
    while (1)
    {
        // TinyUSB device task required to be called every iteration.
        tud_task();

        // Update LED state.
        led_blinking_task();
        // Update keyboard state.
        hid_task();
    }

    return 0;
}

// Static (Private/Local) Functions
static void send_hid_report(uint8_t report_id, uint32_t btn)
{
    (void) report_id;

    if (!tud_hid_ready())
        // Abort if our HID driver is not ready.
        return;

    // Avoid sending multiple consecutive reports.
    static bool has_reported_keys = false;

    if (btn && !has_reported_keys)
    {
        uint8_t keycode[6] = { 0 };
        keycode[0] = HID_KEY_A;
        printf("Attempting to press \'a\'\n");
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
        has_reported_keys = true;
    }
    else if (!btn && has_reported_keys)
    {
        // Send empty key report if we previously had a key pressed.
        printf("Attempting to release \'a\'\n");
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
        has_reported_keys = false;
    }
}

static void hid_task(void)
{
    // Init poll interval (ms)
    const uint32_t interval_ms = 10;
    static uint32_t start_ms = 0;

    if (board_millis() - start_ms < interval_ms)
        return;
    start_ms += interval_ms;

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
    if (!led_mode)
        return;

    // Blink every interval ms
    if (board_millis() - start_ms < led_mode)
        return;

    start_ms += led_mode;

    board_led_write(led_state);
    // Toggle LED state
    led_state = 1 - led_state;
}


// BEGIN TinyUSB Device Callbacks -----------------------------------------+
// Invoked when device is mounted
void tud_mount_cb(void)
{
    led_mode = MOUNTED;
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
    led_mode = NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
    (void) remote_wakeup_en;
    led_mode = SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
    led_mode = MOUNTED;
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
