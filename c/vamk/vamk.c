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
#include "ssd1306_config.h"
#include "ssd1306_buffer_helper.h"
#include "ssd1306_i2c_api.h"
#include "vamk_keymap_config.h"
#include "vamk_config.h"
#include "vamk_display_state.h"
#include "vamk_i2c_switch_state_transmitter.h"
#include "vamk_key_state.h"
#include "vamk_peripheral_switch_state.h"
#include "vamk_press_handler.h"
#include "vamk_release_handler.h"
#include "vamk_switch_state.h"
#include "vamk_types.h"

///Static Variables
static led_blink_pattern_t _led_mode = NOT_MOUNTED;
static uint32_t _display_main_loop_iteration_timeout = 0;

///Static Functions
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
    static uint32_t start_ms = 0;
    if (board_millis() - start_ms < SWITCH_POLLING_INTERVAL_MS)
        return;
    start_ms += SWITCH_POLLING_INTERVAL_MS;

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

    i2c_init(i2c1, I2C_CLOCK_SPEED);
    gpio_set_function(I2C_CONTROLLER_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_CONTROLLER_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_CONTROLLER_SDA_PIN);
    gpio_pull_up(I2C_CONTROLLER_SCL_PIN);

    i2c_init(I2C_IO_EXPANDER_BUS, I2C_CLOCK_SPEED);
    gpio_set_function(I2C_IO_EXPANDER_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_IO_EXPANDER_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_IO_EXPANDER_SDA_PIN);
    gpio_pull_up(I2C_IO_EXPANDER_SCL_PIN);

    //NOTE: Despite being a byte large, we assume the I2C address is only 7bits.
    //uint8_t bit_shifted_expander_address = IO_EXPANDER_ADDRESS << 1;
    uint8_t expander_address_with_write_flag = IO_EXPANDER_ADDRESS;
    uint8_t expander_address_with_read_flag = IO_EXPANDER_ADDRESS & 0x01;

    const uint8_t gpio_a_register_address = 0x12;
    const uint8_t gpio_b_register_address = 0x13;
    const uint8_t iodir_a_register_address = 0x00;
    const uint8_t iodir_b_register_address = 0x01;
    const uint8_t gppu_a_register_address = 0x0C;
    const uint8_t gppu_b_register_address = 0x0D;

#define REGISTER_VALUE_REQUEST_LENGTH 2
    const uint8_t register_value_request[REGISTER_VALUE_REQUEST_LENGTH] =
    {
        expander_address_with_write_flag,
        gpio_a_register_address
    };

    // To get a register value byte, write the device address and then the
    // register you want to start retrieving data from.
    int8_t written_byte_count = i2c_write_blocking(
        I2C_IO_EXPANDER_BUS, expander_address_with_write_flag, &iodir_a_register_address, 1, false);

    // Then invoke a read with the number of register bytes you want. 22 will get you all registers.
    uint8_t read_buffer[IO_EXPANDER_REGISTER_COUNT];
    uint8_t read_byte_count = i2c_read_blocking(I2C_IO_EXPANDER_BUS, IO_EXPANDER_ADDRESS, read_buffer, IO_EXPANDER_REGISTER_COUNT, false);
    printf("%d\n", read_byte_count);

    // Attempt to turn on all pullup resistor for GPIO_A_2
    const uint8_t gppu_a_on_request[2] =
    {
        gppu_a_register_address,
        0x02
    };
    written_byte_count = i2c_write_blocking(
        I2C_IO_EXPANDER_BUS, IO_EXPANDER_ADDRESS, gppu_a_on_request, 2, false);

    // To get a register value byte, write the device address and then the
    // register you want to start retrieving data from.
    written_byte_count = i2c_write_blocking(
        I2C_IO_EXPANDER_BUS, expander_address_with_write_flag, &iodir_a_register_address, 1, false);

    // Then invoke a read with the number of register bytes you want. 21 will get you all registers.
    read_byte_count = i2c_read_blocking(I2C_IO_EXPANDER_BUS, IO_EXPANDER_ADDRESS, read_buffer, IO_EXPANDER_REGISTER_COUNT, false);
    printf("%d\n", read_byte_count);

    if (IS_PRIMARY_KEYBOARD_SIDE)
    {
        // TODO TEMP TEST Set up I2C as peripheral
        //i2c_switch_state_transmitter_init();

        ssd1306_init();
        display_reset_sleep_timeout();

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

            // Update the display state.
            display_task();
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
