// Pico SDK imports
#include <stdio.h>
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

// Function Declarations

// ENTRY POINT
int main(void)
{
    stdio_init_all();
    tusb_init();

    // Set up our UART
    //uart_init(UART_ID, BAUD_RATE);
    //// Set the TX and RX pins by using the function select on the GPIO
    //// Set datasheet for more information on function select
    //gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    //gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    //// GPIO initialisation.
    //// We will make this GPIO an input, and pull it up by default
    //gpio_init(GPIO);
    //gpio_set_dir(GPIO, GPIO_IN);
    //gpio_pull_up(GPIO);

    //// Example of using the HW divider. The pico_divider library provides a more user friendly set of APIs
    //// over the divider (and support for 64 bit divides), and of course by default regular C language integer
    //// divisions are redirected thru that library, meaning you can just use C level `/` and `%` operators and
    //// gain the benefits of the fast hardware divider.
    //int32_t dividend = 123456;
    //int32_t divisor = -321;
    //// This is the recommended signed fast divider for general use.
    //divmod_result_t result = hw_divider_divmod_s32(dividend, divisor);
    //printf("%d/%d = %d remainder %d\n", dividend, divisor, to_quotient_s32(result), to_remainder_s32(result));
    //// This is the recommended unsigned fast divider for general use.
    //int32_t udividend = 123456;
    //int32_t udivisor = 321;
    //divmod_result_t uresult = hw_divider_divmod_u32(udividend, udivisor);
    //printf("%d/%d = %d remainder %d\n", udividend, udivisor, to_quotient_u32(uresult), to_remainder_u32(uresult));

    //// I2C Initialisation. Using it at 400Khz.
    //i2c_init(I2C_PORT, 400*1000);

    //gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    //gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    //gpio_pull_up(I2C_SDA);
    //gpio_pull_up(I2C_SCL);

    //// Timer example code - This example fires off the callback after 2000ms
    //add_alarm_in_ms(2000, alarm_callback, NULL, false);

    // Main run loop
    while(true)
    {
        sleep_ms(1000);
        printf("Hello, world!\n");
    }

    return 0;
}

// REQUIRED FOR TinyUSB ------------------------------------------------------//
// These function 'implementions' seem to be required for TinyUSB to compile.
// At this point I am not entirely sure why, but the stubs seem to satisfy.

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
   // Suppress complier warnings about unused parameters.
   (void) instance;
   (void) report_id;
   (void) report_type;
   (void) buffer;
   (void) reqlen;

  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
   // Suppress complier warnings about unused parameters.
   (void) instance;
   (void) report_id;
   (void) report_type;
   (void) buffer;
   (void) bufsize;
}
// END REQUIRED TinyUSB FUNCTIONS ---------------------------------------------//

