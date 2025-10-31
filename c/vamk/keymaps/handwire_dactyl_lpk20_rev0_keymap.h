
#ifndef HANDWIRE_DACTYL_LPK20_REV0_KEYMAP
#define HANDWIRE_DACTYL_LPK20_REV0_KEYMAP

///Imports
#include "pico/stdlib.h"
#include "vamk_types.h"
#include "vamk_keymap_constants.h"
#include "tusb.h"

///Constants
#define KEY_DEFINITION_COL_COUNT 10
#define KEY_DEFINITION_ROW_COUNT 2

#define COLUMN_COUNT KEY_DEFINITION_COL_COUNT
#define ROW_COUNT KEY_DEFINITION_ROW_COUNT

///Split MSKP_LPK_20_REV0 Config
//================================
//NOTE: These are the GPIO numbers.
static const uint8_t ROW_0_PIN = 6;
static const uint8_t ROW_1_PIN = 7;

static const uint8_t COL_0_PIN = 10;
static const uint8_t COL_1_PIN = 11;
static const uint8_t COL_2_PIN = 13;
static const uint8_t COL_3_PIN = 12;
static const uint8_t COL_4_PIN = 14;
static const uint8_t COL_5_PIN = 20;
static const uint8_t COL_6_PIN = 26;
static const uint8_t COL_7_PIN = 28;
static const uint8_t COL_8_PIN = 21;
static const uint8_t COL_9_PIN = 22;

static const uint8_t ROWS[ROW_COUNT] = { ROW_0_PIN, ROW_1_PIN };
static const uint8_t COLS[COLUMN_COUNT] =
{
    COL_0_PIN, COL_1_PIN, COL_2_PIN, COL_3_PIN, COL_4_PIN,
    COL_5_PIN, COL_6_PIN, COL_7_PIN, COL_8_PIN, COL_9_PIN,
};

//Delay Timers (ms)
static const uint16_t DELAY_TIMER_OVERRIDES[KEY_DEFINITION_ROW_COUNT][KEY_DEFINITION_COL_COUNT] =
{
    { 175, 125, 0, 0, 0, 0, 0, 0, 125, 175 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};


    /// Keymaps
    ///================
    static const struct keycode_definition_t NULL_KEYCODE_ARRAY[KEY_DEFINITION_ROW_COUNT][KEY_DEFINITION_COL_COUNT] =
    {
        { {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0} },
        { {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0} },
    };

    static const struct keycode_definition_t L0_BASE_KEYCODES[KEY_DEFINITION_ROW_COUNT][KEY_DEFINITION_COL_COUNT] =
    {
        { {KC_NULL,0}, {KC_NULL,0}, {KC_LM3_L,0},  {KC_LM4_L,0},  {HID_KEY_CONTROL_LEFT,0}, {HID_KEY_CONTROL_RIGHT,0}, {KC_LM4_R,0},  {KC_LM3_R,0},  {KC_NULL,0}, {KC_NULL,0} },
        { {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0} },
    };

    static const struct keycode_definition_t L0_TAP_KEYCODES[KEY_DEFINITION_ROW_COUNT][KEY_DEFINITION_COL_COUNT] =
    {
        { {HID_KEY_SPACE,0}, {KC_REPEAT,0},   {KC_NULL,0}, {KC_NULL,0}, {HID_KEY_ESCAPE,0}, {HID_KEY_ENTER,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_REPEAT,0}, {HID_KEY_BACKSPACE,0} },
        { {'a',1},           {'r',1},         {'s',1},     {'t',1},     {'g',1},            {'m',1},           {'n',1},     {'e',1},     {'i',1},       {'o',1},              },
    };

    static const struct keycode_definition_t L3_TAP_KEYCODES[KEY_DEFINITION_ROW_COUNT][KEY_DEFINITION_COL_COUNT] =
    {
        { {HID_KEY_SPACE,0}, {KC_REPEAT,0},   {KC_NULL,0}, {KC_NULL,0}, {HID_KEY_ESCAPE,0}, {HID_KEY_ENTER,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_REPEAT,0}, {HID_KEY_BACKSPACE,0} },
        { {'z',1},           {'x',1},         {'c',1},     {'d',1},     {'v',1},            {'k',1},           {'h',1},     {',',1},     {'.',1},       {'/',1},              },
    };

    static const struct keycode_definition_t L4_TAP_KEYCODES[KEY_DEFINITION_ROW_COUNT][KEY_DEFINITION_COL_COUNT] =
    {
        { {HID_KEY_SPACE,0}, {KC_REPEAT,0},   {KC_NULL,0}, {KC_NULL,0}, {HID_KEY_ESCAPE,0}, {HID_KEY_ENTER,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_REPEAT,0}, {HID_KEY_BACKSPACE,0} },
        { {'q',1},           {'w',1},         {'f',1},     {'p',1},     {'b',1},            {'j',1},           {'l',1},     {'u',1},     {'y',1},       {';',1},              },
    };

    static const struct keycode_definition_t L0_HOLD_DELAY_KEYCODES[KEY_DEFINITION_ROW_COUNT][KEY_DEFINITION_COL_COUNT] =
    {
        { {KC_LM1_L,0}, {HID_KEY_SHIFT_RIGHT,0},   {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {HID_KEY_SHIFT_RIGHT,0}, {KC_LM1_R,0} },
        { {'@',1},      {'$',1},                   {'4',1},     {'5',1},     {'6',1},     {'-',1},     {'_',1},     {'{',1},     {'}',1},                 {'\'',1},   },
    };

    static const struct keycode_definition_t L3_HOLD_DELAY_KEYCODES[KEY_DEFINITION_ROW_COUNT][KEY_DEFINITION_COL_COUNT] =
    {
        { {KC_LM1_L,0}, {HID_KEY_SHIFT_RIGHT,0},   {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {HID_KEY_SHIFT_RIGHT,0}, {KC_LM1_R,0} },
        { {'<',1},      {'>',1},                   {'7',1},     {'8',1},     {'9',1},     {'+',1},     {'!',1},     {'[',1},     {']',1},       {'\\',1},              },
    };

    static const struct keycode_definition_t L4_HOLD_DELAY_KEYCODES[KEY_DEFINITION_ROW_COUNT][KEY_DEFINITION_COL_COUNT] =
    {
        { {KC_LM1_L,0}, {HID_KEY_SHIFT_RIGHT,0},   {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {HID_KEY_SHIFT_RIGHT,0}, {KC_LM1_R,0} },
        { {'`',1},      {'0',1},                   {'1',1},     {'2',1},     {'3',1},     {'&',1},     {'*',1},     {'(',1},     {')',1},       {'=',1},              },
    };

    static const struct keycode_definition_t L1_BASE_KEYCODES[KEY_DEFINITION_ROW_COUNT][KEY_DEFINITION_COL_COUNT] =
    {
        { {KC_NULL,0}, {KC_NULL,0}, {KC_LM5_L,0},  {KC_LM6_L,0},  {KC_NULL,0}, {KC_NULL,0}, {KC_LM6_R,0},  {KC_LM5_R,0},  {KC_NULL,0}, {KC_NULL,0} },
        { {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0} },
    };

    static const struct keycode_definition_t L1_TAP_KEYCODES[KEY_DEFINITION_ROW_COUNT][KEY_DEFINITION_COL_COUNT] =
    {
        { {HID_KEY_SPACE,0}, {KC_REPEAT,0},   {KC_NULL,0},    {KC_NULL,0},     {HID_KEY_ESCAPE,0}, {HID_KEY_ENTER,0},      {KC_NULL,0},            {KC_NULL,0},          {KC_REPEAT,0},           {HID_KEY_BACKSPACE,0} },
        { {HID_KEY_F2,0},    {HID_KEY_F5,0},  {HID_KEY_F8,0}, {HID_KEY_F11,0}, {KC_NULL,0},        {HID_KEY_ARROW_LEFT,0}, {HID_KEY_ARROW_DOWN,0}, {HID_KEY_ARROW_UP,0}, {HID_KEY_ARROW_RIGHT,0}, {HID_KEY_TAB,0}    },
    };

    static const struct keycode_definition_t L5_TAP_KEYCODES[KEY_DEFINITION_ROW_COUNT][KEY_DEFINITION_COL_COUNT] =
    {
        { {HID_KEY_SPACE,0}, {KC_REPEAT,0},   {KC_NULL,0},    {KC_NULL,0},     {HID_KEY_ESCAPE,0}, {HID_KEY_ENTER,0},        {KC_NULL,0}, {KC_NULL,0}, {KC_REPEAT,0}, {HID_KEY_BACKSPACE,0} },
        { {HID_KEY_F3,0},    {HID_KEY_F6,0},  {HID_KEY_F9,0}, {HID_KEY_F12,0}, {KC_NULL,0},        {HID_KEY_PRINT_SCREEN,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0},   {KC_NULL,0}           },
    };

    static const struct keycode_definition_t L6_TAP_KEYCODES[KEY_DEFINITION_ROW_COUNT][KEY_DEFINITION_COL_COUNT] =
    {
        { {HID_KEY_SPACE,0}, {KC_REPEAT,0},   {KC_NULL,0},    {KC_NULL,0},     {HID_KEY_ESCAPE,0}, {HID_KEY_ENTER,0}, {KC_NULL,0},           {KC_NULL,0},         {KC_REPEAT,0},   {HID_KEY_BACKSPACE,0} },
        { {HID_KEY_F1,0},    {HID_KEY_F4,0},  {HID_KEY_F7,0}, {HID_KEY_F10,0}, {KC_NULL,0},        {HID_KEY_HOME,0},  {HID_KEY_PAGE_DOWN,0}, {HID_KEY_PAGE_UP,0}, {HID_KEY_END,0}, {HID_KEY_DELETE,0}    },
    };

    static const struct keycode_definition_t L1_HOLD_DELAY_KEYCODES[KEY_DEFINITION_ROW_COUNT][KEY_DEFINITION_COL_COUNT] =
    {
        { {KC_NULL,0},          {HID_KEY_SHIFT_RIGHT,0},  {KC_NULL,0},          {KC_NULL,0}, {KC_NULL,0},      {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0},           {HID_KEY_SHIFT_RIGHT,0},   {KC_NULL,0}           },
        { {HID_KEY_GUI_LEFT,0}, {HID_KEY_CONTROL_LEFT,0}, {HID_KEY_ALT_LEFT,0}, {KC_NULL,0}, {KC_KM_TOGGLE,0}, {KC_NULL,0}, {KC_NULL,0}, {HID_KEY_ALT_RIGHT,0}, {HID_KEY_CONTROL_RIGHT,0}, {HID_KEY_GUI_RIGHT,0} },
    };
#endif
