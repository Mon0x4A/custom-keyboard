///Imports
#include <stdlib.h>
//#include <ctype.h>

#include "pico/stdlib.h"
//#include "pico/binary_info.h"
#include "hardware/i2c.h"

#include "ssd1306_i2c_api.h"
#include "ssd1306_buffer_helper.h"

///Static Global Variables

///Local Definitions

///Static Functions
static void send_command(uint8_t command)
{
    // I2C write process expects a control byte followed by data
    // this "data" can be a command or data to follow up a command
    // Co = 1, D/C = 0 => the driver expects a command
    uint8_t transmission_buffer[2] = { 0x80, command };
    //TODO submit appropriate two wire reference in place of 'i2c_default'
    //TODO actually we should make this a parameter of i2c_inst_t*.
    //i2c_write_blocking(i2c_default, (SSD1306_I2C_ADDR & SSD1306_WRITE_MODE), transmission_buffer, 2, false);
    i2c_write_blocking(i2c0, (SSD1306_I2C_ADDR & SSD1306_WRITE_MODE), transmission_buffer, 2, false);
}

static void send_command_list(uint8_t *command_buffer, int buffer_command_count)
{
    for (int i = 0; i < buffer_command_count; i++)
        send_command(command_buffer[i]);
}

static void send_buffer(uint8_t buffer[], int buffer_length)
{
    // in horizontal addressing mode, the column address pointer auto-increments
    // and then wraps around to the next page, so we can send the entire frame
    // buffer in one gooooooo!

    // copy our frame buffer into a new buffer because we need to add the control byte
    // to the beginning

    uint8_t *temp_buf = malloc(buffer_length + 1);

    temp_buf[0] = 0x40;
    memcpy(temp_buf+1, buffer, buffer_length);

    i2c_write_blocking(i2c_default, (SSD1306_I2C_ADDR & SSD1306_WRITE_MODE), temp_buf, buffer_length + 1, false);

    free(temp_buf);
}

static void calc_render_area_buffer_length(struct render_area_t *area)
{
    // calculate how long the flattened buffer will be for a render area
    area->buffer_length = (area->end_col - area->start_col + 1) * (area->end_page - area->start_page + 1);
}

///Extern Functions
//TODO this currently assumes there will be I2C pins set up before being run.
void ssd1306_init(void)
{
    uint8_t command_arr[] =
    {
        SSD1306_SET_DISP,               // set display off
        /* memory mapping */
        SSD1306_SET_MEM_MODE,           // set memory address mode 0 = horizontal, 1 = vertical, 2 = page
        0x00,                           // horizontal addressing mode
        /* resolution and layout */
        SSD1306_SET_DISP_START_LINE,    // set display start line to 0
        SSD1306_SET_SEG_REMAP | 0x01,   // set segment re-map, column address 127 is mapped to SEG0
        SSD1306_SET_MUX_RATIO,          // set multiplex ratio
        SSD1306_HEIGHT - 1,             // Display height - 1
        SSD1306_SET_COM_OUT_DIR | 0x08, // set COM (common) output scan direction. Scan from bottom up, COM[N-1] to COM0
        SSD1306_SET_DISP_OFFSET,        // set display offset
        0x00,                           // no offset
        SSD1306_SET_COM_PIN_CFG,        // set COM (common) pins hardware configuration. Board specific magic number. 
                                        // 0x02 Works for 128x32, 0x12 Possibly works for 128x64. Other options 0x22, 0x32
#if ((SSD1306_WIDTH == 128) && (SSD1306_HEIGHT == 32))
        0x02,
#elif ((SSD1306_WIDTH == 128) && (SSD1306_HEIGHT == 64))
        0x12,
#else
        0x02,
#endif
        /* timing and driving scheme */
        SSD1306_SET_DISP_CLK_DIV,       // set display clock divide ratio
        0x80,                           // div ratio of 1, standard freq
        SSD1306_SET_PRECHARGE,          // set pre-charge period
        0xF1,                           // Vcc internally generated on our board
        SSD1306_SET_VCOM_DESEL,         // set VCOMH deselect level
        0x30,                           // 0.83xVcc
        /* display */
        SSD1306_SET_CONTRAST,           // set contrast control
        0xFF,
        SSD1306_SET_ENTIRE_ON,          // set entire display on to follow RAM content
        SSD1306_SET_NORM_DISP,           // set normal (not inverted) display
        SSD1306_SET_CHARGE_PUMP,        // set charge pump
        0x14,                           // Vcc internally generated on our board
        SSD1306_SET_SCROLL | 0x00,      // deactivate horizontal scrolling if set. This is necessary as memory writes will corrupt if scrolling was enabled
        SSD1306_SET_DISP | 0x01, // turn display on
    };

    send_command_list(command_arr, count_of(command_arr));
}

struct render_area_t ssd1306_build_default_full_render_area_for_display(void)
{
    struct render_area_t frame_area =
    {
        start_col: 0,
        end_col : SSD1306_WIDTH - 1,
        start_page : 0,
        end_page : SSD1306_NUM_PAGES - 1
    };

    // Set the buffer length for this frame size.
    calc_render_area_buffer_length(&frame_area);
    return frame_area;
}

void ssd1306_render(uint8_t *buf, struct render_area_t *area)
{
    // Recalculate the buffer length just to make sure
    // we have the correct length based on area.
    calc_render_area_buffer_length(area);

    // update a portion of the display with a render area
    uint8_t cmds[] =
    {
        SSD1306_SET_COL_ADDR,
        area->start_col,
        area->end_col,
        SSD1306_SET_PAGE_ADDR,
        area->start_page,
        area->end_page
    };

    send_command_list(cmds, count_of(cmds));
    send_buffer(buf, area->buffer_length);
}

void ssd1306_clear_display(void)
{
    uint8_t clear_buffer[SSD1306_BUF_LEN];
    // Zero the entire display
    memset(clear_buffer, 0, SSD1306_BUF_LEN);
    struct render_area_t full_area = ssd1306_build_default_full_render_area_for_display();
    ssd1306_render(clear_buffer, &full_area);
}
