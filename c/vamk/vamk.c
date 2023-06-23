// Pico SDK imports
//#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "hardware/divider.h"
#include "hardware/i2c.h"
#include "hardware/timer.h"

// TinyUSB imports
#include "tusb.h"
#include "usb_descriptors.h"

// Project Imports
#include "vamk_config.h"
#include "vamk_constants.h"

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 9600

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5

// GPIO defines
// Example uses GPIO 2
#define GPIO 2


// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9

//int64_t alarm_callback(alarm_id_t id, void *user_data) {
//    // Put your timeout handler code in here
//    return 0;
//}


//// ENTRY POINT
//int main(void)
//{
//    stdio_init_all();
//    tusb_init();
//
//
//    // Set up our UART
//    //uart_init(UART_ID, BAUD_RATE);
//    //// Set the TX and RX pins by using the function select on the GPIO
//    //// Set datasheet for more information on function select
//    //gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
//    //gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
//
//    //// GPIO initialisation.
//    //// We will make this GPIO an input, and pull it up by default
//    //gpio_init(GPIO);
//    //gpio_set_dir(GPIO, GPIO_IN);
//    //gpio_pull_up(GPIO);
//
//    //// Example of using the HW divider. The pico_divider library provides a more user friendly set of APIs
//    //// over the divider (and support for 64 bit divides), and of course by default regular C language integer
//    //// divisions are redirected thru that library, meaning you can just use C level `/` and `%` operators and
//    //// gain the benefits of the fast hardware divider.
//    //int32_t dividend = 123456;
//    //int32_t divisor = -321;
//    //// This is the recommended signed fast divider for general use.
//    //divmod_result_t result = hw_divider_divmod_s32(dividend, divisor);
//    //printf("%d/%d = %d remainder %d\n", dividend, divisor, to_quotient_s32(result), to_remainder_s32(result));
//    //// This is the recommended unsigned fast divider for general use.
//    //int32_t udividend = 123456;
//    //int32_t udivisor = 321;
//    //divmod_result_t uresult = hw_divider_divmod_u32(udividend, udivisor);
//    //printf("%d/%d = %d remainder %d\n", udividend, udivisor, to_quotient_u32(uresult), to_remainder_u32(uresult));
//
//    //// I2C Initialisation. Using it at 400Khz.
//    //i2c_init(I2C_PORT, 400*1000);
//
//    //gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
//    //gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
//    //gpio_pull_up(I2C_SDA);
//    //gpio_pull_up(I2C_SCL);
//
//    //// Timer example code - This example fires off the callback after 2000ms
//    //add_alarm_in_ms(2000, alarm_callback, NULL, false);
//
//    // Main run loop
//    bool has_keyboard_key = false;
//    unsigned int counter = 0;
//    while(true)
//    {
//        sleep_ms(1000);
//        tud_task();
//        //cdc_task();
//        char counterStr[12];
//        sprintf(counterStr, "%u", counter);
//        printf(counterStr);
//        printf(": Hello, world! This is the latest version!\n");
//        counter++;
//
//        if (tud_suspended())
//        {
//            tud_remote_wakeup();
//        }
//
//        if (!tud_hid_ready())
//        {
//            printf("tud_hid_ready is not ready!\n");
//            continue;
//        }
//
//        if (!has_keyboard_key)
//        {
//            uint8_t keycode[6] = { 0 };
//            keycode[0] = HID_KEY_A;
//            printf("Attempting to press \'a\'\n");
//            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
//            has_keyboard_key = true;
//        }
//        else if (tud_hid_ready())
//        {
//            printf("Attempting to release \'a\'\n");
//            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
//            has_keyboard_key = false;
//        }
//    }
//
//    return 0;
//}

#include <string.h>

// Required to access on-board switch and LED.
#include "bsp/board.h"

// Blink Pattern (ms)
enum  {
  BLINK_NOT_MOUNTED = 250,
  BLINK_MOUNTED = 1000,
  BLINK_SUSPENDED = 2500,
};

// Global Variables
static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;

// Function Declarations
static void led_blinking_task(void);
static void hid_task(void);

// ENTRY POINT
int main(void)
{
    // Required pico utils initialization call.
    stdio_init_all();

    // Required board utils initialization call.
    board_init();

    // TinyUSB required initialization call.
    tusb_init();

    // Main run loop
    while (1)
    {
        // TinyUSB device task required to be called every iteration.
        tud_task();

        led_blinking_task();
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
    static bool has_keyboard_key = false;

    if (btn && !has_keyboard_key)
    {
        uint8_t keycode[6] = { 0 };
        keycode[0] = HID_KEY_A;
        printf("Attempting to press \'a\'\n");
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
        has_keyboard_key = true;
    }
    else if (!btn && has_keyboard_key)
    {
        // Send empty key report if we previously had a key pressed.
        printf("Attempting to release \'a\'\n");
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
        has_keyboard_key = false;
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
    if (!blink_interval_ms)
        return;

    // Blink every interval ms
    if (board_millis() - start_ms < blink_interval_ms)
        return;

    start_ms += blink_interval_ms;

    board_led_write(led_state);
    // Toggle LED state
    led_state = 1 - led_state;
}


// BEGIN TinyUSB Device Callbacks -----------------------------------------+
// Invoked when device is mounted
void tud_mount_cb(void)
{
    blink_interval_ms = BLINK_MOUNTED;
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
    blink_interval_ms = BLINK_NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
    (void) remote_wakeup_en;
    blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
    blink_interval_ms = BLINK_MOUNTED;
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
