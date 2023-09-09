// Protect from multiple includes
#ifndef VAMK_TYPES_H
#define VAMK_TYPES_H

///Imports
#include "pico/stdlib.h"
#include "vamk_display_config.h"

///Enums
typedef enum led_blink_pattern_ms
{
    NOT_MOUNTED = 250,
    MOUNTED = 1000,
    SUSPENDED = 2500,
} led_blink_pattern_t;

typedef enum key_event_source_identifier
{
    CONTROLLER_IDENTIFIER = 42,
    PERIPHERAL_IDENTIFIER = 69,
} key_event_source_identifier_t;

///Function Pointers
typedef void (*switch_pressed_callback_t)(uint16_t row, uint16_t col, key_event_source_identifier_t key_event_source);
typedef void (*switch_released_callback_t)(uint16_t row, uint16_t col, key_event_source_identifier_t key_event_source);

///Structures
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
