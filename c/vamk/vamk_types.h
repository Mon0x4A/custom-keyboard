// Protect from multiple includes
#ifndef VAMK_TYPES_H
#define VAMK_TYPES_H

///Imports
#include "pico/stdlib.h"
#include "vamk_config.h"
#include "vamk_display_config.h"

///Enums
typedef enum key_event_source_identifier
{
    CONTROLLER_IDENTIFIER = 42,
    PERIPHERAL_IDENTIFIER = 69,
//TODO refactor this to have an "_e" suffix instead.
} key_event_source_identifier_t;

///Structures
struct key_event_location_t
{
    uint16_t row;
    uint16_t column;
    key_event_source_identifier_t key_event_source;
};

struct modifier_collection_t
{
    uint8_t modifiers[HID_REPORT_KEYCODE_ARRAY_LENGTH];
    uint8_t modifier_count:3;
};

struct key_event_report_t
{
    uint64_t elapsed_interval_ms;
    struct modifier_collection_t modifiers_at_key_down;
    uint8_t layer_index_at_key_down;
    bool is_valid:1;
};

///Function Pointers
//TODO these need to use key_event_location_t
typedef void (*switch_pressed_callback_t)(uint16_t row, uint16_t col, key_event_source_identifier_t key_event_source);
typedef void (*switch_released_callback_t)(uint16_t row, uint16_t col, key_event_source_identifier_t key_event_source);

//struct macro_key_instruction_unit_t
//{
//    struct hid_keycode_container_t keycode_container;
//    bool press_key:1;
//    bool release_key:1;
//};
//
//struct macro_sequence_t
//{
//    uint8_t macro_code;
//    char macro_display_name[DISPLAY_LINE_MAX_CHAR_COUNT];
//    uint8_t instruction_count;
//    //TODO this will probably need to be of a set size if we want
//    //to declare these as const in a header file. Reading from a xml
//    //file or something and building them at startup is an option
//    //and would allow then to be variable length. Or made into a
//    //singlely linked list and have this hold a pointer to the head.
//    struct macro_key_instruction_unit_t instruction_sequence[];
//};

#endif
