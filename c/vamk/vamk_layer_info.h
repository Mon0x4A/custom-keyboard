#ifndef VAMK_LAYER_INFO_H
#define VAMK_LAYER_INFO_H

///Imports
#include "pico/stdlib.h"
#include "vamk_keymap_config.h"
#include "vamk_types.h"

///Type Declarations
struct hid_keycode_container_t
{
    uint8_t hid_keycode;
    uint8_t modifier;
    bool has_valid_contents:1;
};

///Function Declarations
struct hid_keycode_container_t layer_info_get_base_keycode_at(
    uint8_t row, uint8_t col, uint8_t layer_index, key_event_source_identifier_t keyboard_side);

struct hid_keycode_container_t layer_info_get_tap_keycode_at(
    uint8_t row, uint8_t col, uint8_t layer_index, key_event_source_identifier_t keyboard_side);

struct hid_keycode_container_t layer_info_get_hold_delay_keycode_at(
    uint8_t row, uint8_t col, uint8_t layer_index, key_event_source_identifier_t keyboard_side);
#endif
