///Imports
#include <stdbool.h>
#include "pico/stdlib.h"
#include "vamk_config.h"
#include "vamk_types.h"
#include "tusb.h"

///Global Variables
// TinyUSB provided lookup of ascii keycodes (literal chars) to the HID_* codes
// The [128][1] array is the char byte keys and the [128][0] array is a bool if shift
// should be applied to print it.
static const uint8_t _ASCII_CHAR_TO_HID_KEYCODE [128][2] =  { HID_ASCII_TO_KEYCODE };

///Private Structure Declarations
typedef struct layer_index_value_container
{
    uint8_t layer_index_value;
    bool needs_ascii_translation;
    bool has_valid_contents;
} layer_index_value_container_t;

///Static (Private) Functions
static layer_index_value_container_t get_layer_value_at(
    uint8_t row, uint8_t col, uint8_t layer_index, keyboard_side_t keyboard_side)
{
    layer_index_value_container_t index_value_container;

    const uint8_t (*layer_array_ptr)[ROW_COUNT][COLUMN_COUNT] = NULL;
    switch (layer_index)
    {
        case 0:
            if (keyboard_side == LEFT_SIDE)
                layer_array_ptr = &L0_BASE_KEYCODES;
            else
                layer_array_ptr = &R0_BASE_KEYCODES;
            break;
        case 1:
            if (keyboard_side == LEFT_SIDE)
                layer_array_ptr = &L1_BASE_KEYCODES;
            else
                layer_array_ptr = &R1_BASE_KEYCODES;
            break;
        case 2:
            if (keyboard_side == LEFT_SIDE)
                layer_array_ptr = &L2_BASE_KEYCODES;
            else
                layer_array_ptr = &R2_BASE_KEYCODES;
            break;
    }

    if (layer_array_ptr == NULL)
    {
        index_value_container.has_valid_contents = false;
        return index_value_container;
    }

    index_value_container.layer_index_value = (*layer_array_ptr)[row][col];
    //TODO get shift flag
    index_value_container.has_valid_contents = true;
}

///Public Functions
hid_keycode_container_t layer_info_get_keycode_at(
    uint8_t row, uint8_t col, uint8_t layer_index, keyboard_side_t keyboard_side)
{
    hid_keycode_container_t code_container;

    layer_index_value_container_t layer_value = get_layer_value_at(row, col, layer_index, keyboard_side);

    if (!layer_value.has_valid_contents)
    {
        code_container.has_valid_contents = false;
        return code_container;
    }
    else
    {
        code_container.has_valid_contents = true;
    }

    if (layer_value.needs_ascii_translation)
    {
        // Determine if we need to apply shift to correctly print this character.
        if (_ASCII_CHAR_TO_HID_KEYCODE[layer_value.layer_index_value][0])
            code_container.modifier = KEYBOARD_MODIFIER_LEFTSHIFT;

        // Translate the ascii char into the HID_* keycode we need.
        code_container.hid_keycode
            = _ASCII_CHAR_TO_HID_KEYCODE[layer_value.layer_index_value][1];
    }
    else
    {
        // We already have the keycode we need.
        code_container.modifier = 0;
        code_container.hid_keycode = layer_value.layer_index_value;
    }

    return code_container;
}
