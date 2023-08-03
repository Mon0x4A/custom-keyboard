///Imports
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include <ctype.h>

#include "ssd1306_buffer_helper.h"
#include "ssd1306_config.h"

///Static Global Variables
///Local Definitions
///Static Functions
static inline int get_font_index(uint8_t ch) {
    if (ch >= 'A' && ch <='Z') {
        return  ch - 'A' + 1;
    }
    else if (ch >= '0' && ch <='9') {
        return  ch - '0' + 27;
    }
    else return  0; // Not got that char so space.
}

///Extern Functions
void ssd1306_buffer_write_char(uint8_t *buf, int16_t x, int16_t y, uint8_t ch)
{
    if (x > SSD1306_WIDTH - 8 || y > SSD1306_HEIGHT - 8)
        return;

    // For the moment, only write on Y row boundaries (every 8 vertical pixels)
    y = y/8;

    ch = toupper(ch);
    int idx = get_font_index(ch);
    int fb_idx = y * 128 + x;

    for (int i=0;i<8;i++) {
        buf[fb_idx++] = DEFAULT_FONT[idx * 8 + i];
    }
}

void ssd1306_buffer_write_string(uint8_t *buf, int16_t x, int16_t y, char *str) {
    // Cull out any string off the screen
    if (x > SSD1306_WIDTH - 8 || y > SSD1306_HEIGHT - 8)
        return;

    while (*str) {
        ssd1306_buffer_write_char(buf, x, y, *str++);
        x+=8;
    }
}

void ssd1306_buffer_set_pixel(uint8_t *buf, int x, int y, bool on)
{
    assert(x >= 0 && x < SSD1306_WIDTH && y >= 0 && y < SSD1306_HEIGHT);

    // The calculation to determine the correct bit to set depends on which address
    // mode we are in. This code assumes horizontal

    // The video ram on the SSD1306 is split up in to 8 rows, one bit per pixel.
    // Each row is 128 long by 8 pixels high, each byte vertically arranged, so byte 0 is x=0, y=0->7,
    // byte 1 is x = 1, y=0->7 etc

    const int BYTES_PER_ROW = SSD1306_WIDTH ; // x pixels, 1bpp, but each row is 8 pixel high, so (x / 8) * 8

    //TODO make row height a constant
    int byte_idx = (y / 8) * BYTES_PER_ROW + x;
    uint8_t byte = buf[byte_idx];

    if (on)
        byte |=  1 << (y % 8);
    else
        byte &= ~(1 << (y % 8));

    buf[byte_idx] = byte;
}

void ssd1306_buffer_draw_line(uint8_t *buf, int x0, int y0, int x1, int y1, bool on)
{
    int dx =  abs(x1-x0);
    int sx = x0<x1 ? 1 : -1;
    int dy = -abs(y1-y0);
    int sy = y0<y1 ? 1 : -1;
    int err = dx+dy;
    int e2;

    while (true)
    {
        ssd1306_buffer_set_pixel(buf, x0, y0, on);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2*err;

        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}
