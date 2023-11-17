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
typedef const keycode_definition_array_ptr_t (*keycode_array_result_function_ptr_t)(
    uint8_t row, uint8_t col, uint8_t layer_index);

struct layer_index_value_container_t
{
    uint8_t layer_index_value;
    bool needs_ascii_translation;
    bool has_valid_contents;
};

///Static Functions
#if IS_VOK_SL_MODEL
static const keycode_definition_array_ptr_t get_vok_sl_base_value_at(
    uint8_t row, uint8_t col, uint8_t layer_index)
{
    keycode_definition_array_ptr_t base_layer_definitions_ptr = NULL;
    switch (layer_index)
    {
        case 0:
            base_layer_definitions_ptr = &L0_BASE_KEYCODES;
            break;
        case 1:
            base_layer_definitions_ptr = &L1_BASE_KEYCODES;
            break;
        case 2:
            base_layer_definitions_ptr = &L2_BASE_KEYCODES;
            break;
    }
    return base_layer_definitions_ptr;
}
static const keycode_definition_array_ptr_t get_vok_sl_tap_value_at(
    uint8_t row, uint8_t col, uint8_t layer_index)
{
    keycode_definition_array_ptr_t tap_layer_definitions_ptr = NULL;
    switch (layer_index)
    {
        case 0:
        case 2:
            tap_layer_definitions_ptr = &L0_TAP_KEYS;
            break;
        case 1:
            tap_layer_definitions_ptr = &L1_TAP_KEYS;
            break;
    }
    return tap_layer_definitions_ptr;
}
static const keycode_definition_array_ptr_t get_vok_sl_delay_value_at(
    uint8_t row, uint8_t col, uint8_t layer_index)
{
    keycode_definition_array_ptr_t delay_hold_layer_definitions_ptr = null;
    switch (layer_index)
    {
        case 0:
        case 1:
        case 2:
            delay_hold_layer_definitions_ptr = &L_HOLD_DELAY_KEYS;
            break;
    }
    return delay_hold_layer_definitions_ptr;
}
#endif

#if IS_QLP_MODEL
static const keycode_definition_array_ptr_t get_qlp_base_value_at(
    uint8_t row, uint8_t col, uint8_t layer_index)
{
    keycode_definition_array_ptr_t base_layer_definitions_ptr = NULL;
    switch (layer_index)
    {
        case 0:
            base_layer_definitions_ptr = &L0_BASE_KEYCODES;
            break;
        case 1:
            base_layer_definitions_ptr = &L1_BASE_KEYCODES;
            break;
        case 3:
        case 4:
            base_layer_definitions_ptr = &L0_CHILD_BASE_LAYER;
            break;
        case 5:
        case 6:
            base_layer_definitions_ptr = &L1_CHILD_BASE_LAYER;
            break;
        case 2:
            base_layer_definitions_ptr = &L2_BASE_KEYCODES;
            break;
    }
    return base_layer_definitions_ptr;
}
static const keycode_definition_array_ptr_t get_qlp_tap_value_at(
    uint8_t row, uint8_t col, uint8_t layer_index)
{
    keycode_definition_array_ptr_t tap_layer_definitions_ptr = NULL;
    switch (layer_index)
    {
        case 0:
        case 2:
            tap_layer_definitions_ptr = &L0_TAP_KEYCODES;
            break;
        case 1:
            tap_layer_definitions_ptr = &L1_TAP_KEYCODES;
            break;
        case 3:
            tap_layer_definitions_ptr = &L3_TAP_KEYCODES;
            break;
        case 4:
            tap_layer_definitions_ptr = &L4_TAP_KEYCODES;
            break;
        case 5:
            tap_layer_definitions_ptr = &L5_TAP_KEYCODES;
            break;
        case 6:
            tap_layer_definitions_ptr = &L6_TAP_KEYCODES;
            break;
    }
    return tap_layer_definitions_ptr;
}
static const keycode_definition_array_ptr_t get_qlp_delay_value_at(
    uint8_t row, uint8_t col, uint8_t layer_index)
{
    keycode_definition_array_ptr_t delay_hold_layer_definitions_ptr = NULL;
    switch (layer_index)
    {
        case 0:
            delay_hold_layer_definitions_ptr = &L0_HOLD_DELAY_KEYCODES;
            break;
        case 1:
        case 2:
        case 5:
        case 6:
            delay_hold_layer_definitions_ptr = &NULL_KEYCODE_ARRAY;
            break;
        case 3:
            delay_hold_layer_definitions_ptr = &L3_HOLD_DELAY_KEYCODES;
            break;
        case 4:
            delay_hold_layer_definitions_ptr = &L4_HOLD_DELAY_KEYCODES;
            break;
    }
    return delay_hold_layer_definitions_ptr;
}
#endif

static struct layer_index_value_container_t build_layer_index_value_from(
    uint8_t row,
    uint8_t col,
    key_event_source_identifier_t key_event_source,
    const keycode_definition_array_ptr_t keycode_definition_array_ptr)
{
    struct layer_index_value_container_t index_value_container = {0};
    if (keycode_definition_array_ptr == NULL)
    {
        index_value_container.has_valid_contents = false;
        return index_value_container;
    }

    uint8_t key_definition_array_row = row;
    uint8_t key_definition_array_col = col;

#if IS_SPLIT_KEYBOARD
    // Determine if a row/col offset is necessary to index the correctly
    // key definition.
    switch (key_event_source)
    {
        case CONTROLLER_IDENTIFIER:
            if (CONTROLLER_IS_RIGHT_SIDE)
                key_definition_array_col += COLUMN_COUNT;
            break;
        case PERIPHERAL_IDENTIFIER:
            if (CONTROLLER_IS_LEFT_SIDE)
                key_definition_array_col += COLUMN_COUNT;
            break;
    }
#endif

    index_value_container.layer_index_value =
        (*keycode_definition_array_ptr)[key_definition_array_row][key_definition_array_col].keycode;
    index_value_container.needs_ascii_translation =
        (*keycode_definition_array_ptr)[key_definition_array_row][key_definition_array_col].is_ascii;
    index_value_container.has_valid_contents = true;

    return index_value_container;
}

static struct layer_index_value_container_t get_base_value_at(
    uint8_t row, uint8_t col, uint8_t layer_index, key_event_source_identifier_t key_event_source,
    keycode_array_result_function_ptr_t base_value_layer_function_ptr)
{
    keycode_definition_array_ptr_t base_layer_definitions_ptr = (*base_value_layer_function_ptr)(row, col, layer_index);
    return build_layer_index_value_from(row, col, key_event_source, base_layer_definitions_ptr);
}

static struct layer_index_value_container_t get_tap_value_at(
    uint8_t row, uint8_t col, uint8_t layer_index, key_event_source_identifier_t key_event_source,
    keycode_array_result_function_ptr_t tap_value_layer_function_ptr)
{
    keycode_definition_array_ptr_t tap_layer_definitions_ptr = (*tap_value_layer_function_ptr)(row, col, layer_index);
    return build_layer_index_value_from(row, col, key_event_source, tap_layer_definitions_ptr);
}

static struct layer_index_value_container_t get_delay_hold_value_at(
    uint8_t row, uint8_t col, uint8_t layer_index, key_event_source_identifier_t key_event_source,
    keycode_array_result_function_ptr_t delay_value_layer_function_ptr)
{
    keycode_definition_array_ptr_t delay_hold_layer_definitions_ptr = (*delay_value_layer_function_ptr)(row, col, layer_index);
    return build_layer_index_value_from(row, col, key_event_source, delay_hold_layer_definitions_ptr);
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
    uint8_t row, uint8_t col, uint8_t layer_index, key_event_source_identifier_t key_event_source)
{
#if IS_VOK_SL_MODEL
    struct layer_index_value_container_t layer_value = get_base_value_at(row, col, layer_index, key_event_source,
        &get_vok_sl_base_value_at);
#elif IS_QLP_MODEL
    struct layer_index_value_container_t layer_value = get_base_value_at(row, col, layer_index, key_event_source,
        &get_qlp_base_value_at);
#endif
    return build_code_container(layer_value);
}

struct hid_keycode_container_t layer_info_get_tap_keycode_at(
    uint8_t row, uint8_t col, uint8_t layer_index, key_event_source_identifier_t key_event_source)
{
#if IS_VOK_SL_MODEL
    struct layer_index_value_container_t layer_value = get_tap_value_at(row, col, layer_index, key_event_source,
        &get_vok_sl_tap_value_at);
#elif IS_QLP_MODEL
    struct layer_index_value_container_t layer_value = get_tap_value_at(row, col, layer_index, key_event_source,
        &get_qlp_tap_value_at);
#endif
    return build_code_container(layer_value);
}

struct hid_keycode_container_t layer_info_get_hold_delay_keycode_at(
    uint8_t row, uint8_t col, uint8_t layer_index, key_event_source_identifier_t key_event_source)
{
#if IS_VOK_SL_MODEL
    struct layer_index_value_container_t layer_value = get_delay_hold_value_at(row, col, layer_index, key_event_source,
        &get_vok_sl_delay_value_at);
#elif IS_QLP_MODEL
    struct layer_index_value_container_t layer_value = get_delay_hold_value_at(row, col, layer_index, key_event_source,
        &get_qlp_delay_value_at);
#endif
    return build_code_container(layer_value);
}

