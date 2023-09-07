///Imports
#include <stdbool.h>
#include "pico/stdlib.h"
#include "vamk_keymap_config.h"
#include "vamk_config.h"
#include "vamk_layer_info.h"
#include "vamk_types.h"
#include "tusb.h"

///Static Global Variables
// TinyUSB provided lookup of ascii keycodes (literal chars) to the HID_* codes
// The [128][1] array is the char byte keys and the [128][0] array is a bool if shift
// should be applied to print it.
static const uint8_t _ASCII_CHAR_TO_HID_KEYCODE [128][2] = { HID_ASCII_TO_KEYCODE };

///Local Declarations
typedef const struct keycode_definition_t (*keycode_definition_array_ptr_t)[ROW_COUNT][COLUMN_COUNT];

struct layer_index_value_container_t
{
    uint8_t layer_index_value;
    bool needs_ascii_translation;
    bool has_valid_contents;
};

///Static Functions
static struct layer_index_value_container_t build_layer_index_value_from(
    uint8_t row,
    uint8_t col,
    const keycode_definition_array_ptr_t keycode_definition_array_ptr)
{
    struct layer_index_value_container_t index_value_container = {0};
    if (keycode_definition_array_ptr == NULL)
    {
        index_value_container.has_valid_contents = false;
        return index_value_container;
    }

    index_value_container.layer_index_value = (*keycode_definition_array_ptr)[row][col].keycode;
    index_value_container.needs_ascii_translation = (*keycode_definition_array_ptr)[row][col].is_ascii;
    index_value_container.has_valid_contents = true;

    return index_value_container;
}

static struct layer_index_value_container_t get_base_value_at(
    uint8_t row, uint8_t col, uint8_t layer_index, keyboard_side_t keyboard_side)
{
    keycode_definition_array_ptr_t base_layer_definitions_ptr = NULL;
    switch (layer_index)
    {
// These are defined as two separate if statements intentionally such that
// compilation errors will occur if both or neither are set to true.
#if IS_UNIFIED_KEYBOARD
        case 0:
            base_layer_definitions_ptr = &L0_BASE_KEYCODES;
            break;
        case 1:
            base_layer_definitions_ptr = &L1_BASE_KEYCODES;
            break;
        case 2:
            base_layer_definitions_ptr = &L2_BASE_KEYCODES;
            break;
#endif
#if IS_SPLIT_KEYBOARD
        case 0:
            if (keyboard_side == LEFT_SIDE)
                base_layer_definitions_ptr = &L0_BASE_KEYCODES;
            else if (keyboard_side == RIGHT_SIDE)
                base_layer_definitions_ptr = &R0_BASE_KEYCODES;
            break;
        case 1:
            if (keyboard_side == LEFT_SIDE)
                base_layer_definitions_ptr = &L1_BASE_KEYCODES;
            else if (keyboard_side == RIGHT_SIDE)
                base_layer_definitions_ptr = &R1_BASE_KEYCODES;
            break;
        case 2:
            if (keyboard_side == LEFT_SIDE)
                base_layer_definitions_ptr = &L2_BASE_KEYCODES;
            else if (keyboard_side == RIGHT_SIDE)
                base_layer_definitions_ptr = &R2_BASE_KEYCODES;
            break;
#endif
    }
    return build_layer_index_value_from(row, col, base_layer_definitions_ptr);
}

static struct layer_index_value_container_t get_tap_value_at(
    uint8_t row, uint8_t col, uint8_t layer_index, keyboard_side_t keyboard_side)
{
    keycode_definition_array_ptr_t tap_layer_definitions_ptr = NULL;
    switch (layer_index)
    {
#if IS_UNIFIED_KEYBOARD
        case 0:
        // TODO 2 will not be required here once tap registers layer on event start
        case 2:
            tap_layer_definitions_ptr = &L0_TAP_KEYS;
            break;
        case 1:
            tap_layer_definitions_ptr = &L1_TAP_KEYS;
            break;
#endif
#if IS_SPLIT_KEYBOARD
        case 0:
        // TODO 2 will not be required here once tap registers layer on event start
        case 2:
            if (keyboard_side == LEFT_SIDE)
                tap_layer_definitions_ptr = &L0_TAP_KEYS;
            else if (keyboard_side == RIGHT_SIDE)
                tap_layer_definitions_ptr = &R0_TAP_KEYS;
            break;
        case 1:
            if (keyboard_side == LEFT_SIDE)
                tap_layer_definitions_ptr = &L1_TAP_KEYS;
            else if (keyboard_side == RIGHT_SIDE)
                tap_layer_definitions_ptr = &R1_TAP_KEYS;
            break;
#endif
    }
    return build_layer_index_value_from(row, col, tap_layer_definitions_ptr);
}

static struct layer_index_value_container_t get_delay_hold_value_at(
    uint8_t row, uint8_t col, uint8_t layer_index, keyboard_side_t keyboard_side)
{
    keycode_definition_array_ptr_t delay_hold_layer_definitions_ptr = NULL;
    switch (layer_index)
    {
#if IS_UNIFIED_KEYBOARD
        case 0:
        case 1:
        case 2:
            delay_hold_layer_definitions_ptr = &L_HOLD_DELAY_KEYS;
            break;
#endif
#if IS_SPLIT_KEYBOARD
        case 0:
        case 1:
        case 2:
            if (keyboard_side == LEFT_SIDE)
                delay_hold_layer_definitions_ptr = &L_HOLD_DELAY_KEYS;
            else if (keyboard_side == RIGHT_SIDE)
                delay_hold_layer_definitions_ptr = &R_HOLD_DELAY_KEYS;
            break;
#endif
    }
    return build_layer_index_value_from(row, col, delay_hold_layer_definitions_ptr);
}

static struct hid_keycode_container_t build_code_container(struct layer_index_value_container_t layer_value)
{
    struct hid_keycode_container_t code_container = {0};

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

///Extern Functions
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

struct hid_keycode_container_t layer_info_get_hold_delay_keycode_at(
    uint8_t row, uint8_t col, uint8_t layer_index, keyboard_side_t keyboard_side)
{
    struct layer_index_value_container_t layer_value = get_delay_hold_value_at(row, col, layer_index, keyboard_side);
    return build_code_container(layer_value);
}

