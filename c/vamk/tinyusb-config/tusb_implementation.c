
///Imports
#include "pico/stdlib.h"
#include "tusb.h"
#include "tusb_implementation.h"
#include "usb_descriptors.h"
#include "bsp/board.h" // Required to access on-board switch and LED.

///Local Declarations
typedef enum led_blink_pattern_ms
{
    NOT_MOUNTED = 250,
    MOUNTED = 1000,
    SUSPENDED = 2500,
} led_blink_pattern_e;

///Static Constants

///Static Global Variables
static led_blink_pattern_e _led_mode = NOT_MOUNTED;
///Static Functions

///Extern Functions
void led_blinking_task(void)
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
