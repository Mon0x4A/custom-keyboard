///Imports
#include <stdbool.h>
#include "pico/stdlib.h"
#include "vamk_config.h"
#include "vamk_layer_info.h"
#include "vamk_types.h"
#include "tusb.h"

///Static Variables
// TinyUSB provided lookup of ascii keycodes (literal chars) to the HID_* codes
// The [128][1] array is the char byte keys and the [128][0] array is a bool if shift
// should be applied to print it.
static const uint8_t _ASCII_CHAR_TO_HID_KEYCODE [128][2] = { HID_ASCII_TO_KEYCODE };

///Private Declarations
struct layer_index_value_container_t
{
    uint8_t layer_index_value;
    bool needs_ascii_translation;
    bool has_valid_contents;
};

///Static (Private) Functions
static struct layer_index_value_container_t get_base_value_at(
    uint8_t row, uint8_t col, uint8_t layer_index, keyboard_side_t keyboard_side)
{
    struct layer_index_value_container_t index_value_container;

    const uint8_t (*layer_array_ptr)[ROW_COUNT][COLUMN_COUNT] = NULL;
    const bool (*is_ascii_array_ptr)[ROW_COUNT][COLUMN_COUNT] = NULL;
    switch (layer_index)
    {
        case 0:
            if (keyboard_side == LEFT_SIDE)
            {
                layer_array_ptr = &L0_BASE_KEYCODES;
                is_ascii_array_ptr = &L0_IS_ASCII;
            }
            else if (keyboard_side == RIGHT_SIDE)
            {
                layer_array_ptr = &R0_BASE_KEYCODES;
                is_ascii_array_ptr = &R0_IS_ASCII;
            }
            break;
        case 1:
            if (keyboard_side == LEFT_SIDE)
            {
                layer_array_ptr = &L1_BASE_KEYCODES;
                is_ascii_array_ptr = &L1_IS_ASCII;
            }
            else if (keyboard_side == RIGHT_SIDE)
            {
                layer_array_ptr = &R1_BASE_KEYCODES;
                is_ascii_array_ptr = &R1_IS_ASCII;
            }
            break;
        case 2:
            if (keyboard_side == LEFT_SIDE)
            {
                layer_array_ptr = &L2_BASE_KEYCODES;
                is_ascii_array_ptr = &L2_IS_ASCII;
            }
            else if (keyboard_side == RIGHT_SIDE)
            {
                layer_array_ptr = &R2_BASE_KEYCODES;
                is_ascii_array_ptr = &R2_IS_ASCII;
            }
            break;
    }

    if (layer_array_ptr == NULL || is_ascii_array_ptr == NULL)
    {
        index_value_container.has_valid_contents = false;
        return index_value_container;
    }

    index_value_container.layer_index_value = (*layer_array_ptr)[row][col];
    index_value_container.needs_ascii_translation = (*is_ascii_array_ptr)[row][col];
    index_value_container.has_valid_contents = true;

    return index_value_container;
}

struct layer_index_value_container_t get_tap_value_at(
    uint8_t row, uint8_t col, uint8_t layer_index, keyboard_side_t keyboard_side)
{
    struct layer_index_value_container_t index_value_container;

    const uint8_t (*tap_layer_array_ptr)[ROW_COUNT][COLUMN_COUNT] = NULL;
    const bool (*is_ascii_array_ptr)[ROW_COUNT][COLUMN_COUNT] = NULL;
    switch (layer_index)
    {
        case 0:
        case 1:
        case 2:
            if (keyboard_side == LEFT_SIDE)
            {
                tap_layer_array_ptr = &L_TAP_KEYS;
                is_ascii_array_ptr = &L_TAP_IS_ASCII;
            }
            else if (keyboard_side == RIGHT_SIDE)
            {
                tap_layer_array_ptr = &R_TAP_KEYS;
                is_ascii_array_ptr = &R_TAP_IS_ASCII;
            }
            break;
    }

    if (tap_layer_array_ptr == NULL || is_ascii_array_ptr == NULL)
    {
        index_value_container.has_valid_contents = false;
        return index_value_container;
    }

    index_value_container.layer_index_value = (*tap_layer_array_ptr)[row][col];
    index_value_container.needs_ascii_translation = (*is_ascii_array_ptr)[row][col];
    index_value_container.has_valid_contents = true;

    return index_value_container;
}

static struct hid_keycode_container_t build_code_container(struct layer_index_value_container_t layer_value)
{
    struct hid_keycode_container_t code_container;

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
        else
            code_container.modifier = 0;

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


///Public Functions
struct hid_keycode_container_t layer_info_get_base_keycode_at(
    uint8_t row, uint8_t col, uint8_t layer_index, keyboard_side_t keyboard_side)
{
    struct layer_index_value_container_t layer_value = get_base_value_at(row, col, layer_index, keyboard_side);
    return build_code_container(layer_value);
}

struct hid_keycode_container_t layer_info_get_tap_keycode_at(
    uint8_t row, uint8_t col, uint8_t layer_index, keyboard_side_t keyboard_side)
{
    struct layer_index_value_container_t layer_value = get_tap_value_at(row, col, layer_index, keyboard_side);
    return build_code_container(layer_value);
}
