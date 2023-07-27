#ifndef SSD1306_I2C_API_H
#define SSD1306_I2C_API_H

///Imports
#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#include "ssd1306_config.h"
#include "vamk_config.h"


///Type Definitions
struct render_area_t
{
    uint8_t start_col;
    uint8_t end_col;
    uint8_t start_page;
    uint8_t end_page;

    int buffer_length;
};

///Function Definitions
void ssd1306_init(void);
struct render_area_t ssd1306_build_default_full_render_area_for_display(void);
void ssd1306_render(uint8_t *buf, struct render_area_t *area);
void ssd1306_clear_display(void);
void ssd1306_buffer_set_pixel(uint8_t *buf, int x, int y, bool on);
void ssd1306_buffer_draw_line(uint8_t *buf, int x0, int y0, int x1, int y1, bool on);

#endif
