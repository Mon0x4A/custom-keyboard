///Imports
#include "pico/stdlib.h"
#include "time.h"
#include "hardware/timer.h"

#include "vamk_config.h"
#include "vamk_display_config.h"
#include "vamk_display_state.h"
#include "ssd1306_buffer_helper.h"
#include "ssd1306_i2c_api.h"

///Static Global Variables
static absolute_time_t _last_display_command = {0};
static bool _is_display_on = false;

///Static Functions
static void display_show_firmware_information(void)
{
    struct render_area_t area = ssd1306_build_default_full_render_area_for_display();
    uint8_t buffer[SSD1306_BUF_LEN] = {0};
    //15 character max per line with this font
    char *text[] = {
        "seok-38 mk i",
        " ",
        "vamk firmware",
        "alpha v0.1",
        "rpi pico",
        " ",
        "Hamlund MFG",
        "2024",
    };

    int y = 0;
    const int x_left_padding = 5;
    for (int i = 0 ; i < count_of(text); i++)
    {
        ssd1306_buffer_write_string(buffer, x_left_padding, y, text[i]);
        y += DEFAULT_FONT_ROW_HEIGHT_PX;
    }

    //ssd1306_buffer_set_pixel(buffer, 5, 5, true);
    //ssd1306_buffer_set_pixel(buffer, 10, 10, true);
    ssd1306_clear_display();
    ssd1306_render(buffer, &area);
}

static void wake_display(void)
{

    display_show_firmware_information();
    _is_display_on = true;
}

///Extern Functions
void display_task()
{
#if IS_I2C_DISPLAY_ENABLED
    if (_is_display_on)
    {
        uint64_t elapsed_interval_ms = (absolute_time_diff_us(_last_display_command, get_absolute_time()))/1000;
        if (elapsed_interval_ms >= DISPLAY_SLEEP_TIMEOUT_MS)
        {
            ssd1306_clear_display();
            _is_display_on = false;
        }
    }
#endif
}

void display_reset_sleep_timeout(void)
{
#if IS_I2C_DISPLAY_ENABLED
    if (!_is_display_on)
        wake_display();

    _last_display_command = get_absolute_time();
#endif
}

