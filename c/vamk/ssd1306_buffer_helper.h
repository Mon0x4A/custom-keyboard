#ifndef SSD1306_BUFFER_HELPER_H
#define SSD1306_BUFFER_HELPER_H
///Imports
#include <stdlib.h>
#include "pico/stdlib.h"
#include "ssd1306_config.h"

///Constants
///Function Definitions
void ssd1306_buffer_set_pixel(uint8_t *buf, int x, int y, bool on);
void ssd1306_buffer_draw_line(uint8_t *buf, int x0, int y0, int x1, int y1, bool on);
#endif
