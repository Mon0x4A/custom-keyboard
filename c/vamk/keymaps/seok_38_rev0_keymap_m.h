#ifndef SEOK_38_REV0_KEYMAP_M
#define SEOK_38_REV0_KEYMAP_M

///Imports
#include "pico/stdlib.h"
#include "vamk_types.h"
#include "vamk_keymap_constants.h"
#include "tusb.h"

///Constants
#define KEY_DEFINITION_COL_COUNT 10
#define KEY_DEFINITION_ROW_COUNT 4

#define COLUMN_COUNT KEY_DEFINITION_COL_COUNT
#define ROW_COUNT KEY_DEFINITION_ROW_COUNT

static const uint8_t ROW_0_PIN = 12;
static const uint8_t ROW_1_PIN = 13;
static const uint8_t ROW_2_PIN = 14;
static const uint8_t ROW_3_PIN = 15;

static const uint8_t COL_0_PIN = 5;
static const uint8_t COL_1_PIN = 6;
static const uint8_t COL_2_PIN = 7;
static const uint8_t COL_3_PIN = 8;
static const uint8_t COL_4_PIN = 9;
static const uint8_t COL_5_PIN = 19;
static const uint8_t COL_6_PIN = 20;
static const uint8_t COL_7_PIN = 21;
static const uint8_t COL_8_PIN = 22;
static const uint8_t COL_9_PIN = 26;

static const uint8_t ROWS[ROW_COUNT] = { ROW_0_PIN, ROW_1_PIN, ROW_2_PIN, ROW_3_PIN };
static const uint8_t COLS[COLUMN_COUNT] =
{
    COL_0_PIN, COL_1_PIN, COL_2_PIN, COL_3_PIN, COL_4_PIN,
    COL_5_PIN, COL_6_PIN, COL_7_PIN, COL_8_PIN, COL_9_PIN
};

/// Keymaps
///================
static const struct keycode_definition_t L0_BASE_KEYCODES[KEY_DEFINITION_ROW_COUNT][KEY_DEFINITION_COL_COUNT] =
{
    { {KC_NULL,0},              {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0},             {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0},             {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}               },
    { {KC_NULL,0},              {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0},             {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0},             {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}               },
    { {KC_NULL,0},              {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0},             {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0},             {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}               },
    { {HID_KEY_CONTROL_LEFT,0}, {KC_NULL,0}, {KC_LM2,0},  {HID_KEY_SHIFT_RIGHT,0}, {KC_LM1,0},  {KC_LM1,0},  {HID_KEY_SHIFT_RIGHT,0}, {KC_LM2,0},  {KC_NULL,0}, {HID_KEY_CONTROL_RIGHT,0} },
};

static const struct keycode_definition_t L1_BASE_KEYCODES[KEY_DEFINITION_ROW_COUNT][KEY_DEFINITION_COL_COUNT] =
{
    { {HID_KEY_F1,0},       {HID_KEY_F4,0}, {HID_KEY_F7,0}, {HID_KEY_F10,0},         {KC_NULL,0}, {HID_KEY_HOME,0},         {HID_KEY_PAGE_DOWN,0},   {HID_KEY_PAGE_UP,0},  {HID_KEY_END,0},         {HID_KEY_DELETE,0},   },
    { {HID_KEY_F2,0},       {HID_KEY_F5,0}, {HID_KEY_F8,0}, {HID_KEY_F11,0},         {KC_NULL,0}, {HID_KEY_ARROW_LEFT,0},   {HID_KEY_ARROW_DOWN,0},  {HID_KEY_ARROW_UP,0}, {HID_KEY_ARROW_RIGHT,0}, {HID_KEY_TAB,0},      },
    { {HID_KEY_F3,0},       {HID_KEY_F6,0}, {HID_KEY_F9,0}, {HID_KEY_F12,0},         {KC_NULL,0}, {HID_KEY_PRINT_SCREEN,0}, {KC_NULL,0},             {KC_NULL,0},          {KC_NULL,0},             {KC_NULL,0},          },
    { {HID_KEY_ALT_LEFT,0}, {KC_NULL,0},    {KC_LM2,0},     {HID_KEY_SHIFT_RIGHT,0}, {KC_LM1,0},  {KC_LM1,0},               {HID_KEY_SHIFT_RIGHT,0}, {KC_LM2,0},           {KC_NULL,0},             {HID_KEY_ALT_RIGHT,0} },
};

static const struct keycode_definition_t L2_BASE_KEYCODES[KEY_DEFINITION_ROW_COUNT][KEY_DEFINITION_COL_COUNT] =
{
    { {KC_NULL,0},          {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0},             {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0},             {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}           },
    { {KC_NULL,0},          {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0},             {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0},             {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}           },
    { {KC_NULL,0},          {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0},             {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0},             {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}           },
    { {HID_KEY_GUI_LEFT,0}, {KC_NULL,0}, {KC_LM2,0},  {HID_KEY_SHIFT_RIGHT,0}, {KC_LM1,0},  {KC_LM1,0},  {HID_KEY_SHIFT_RIGHT,0}, {KC_LM2,0},  {KC_NULL,0}, {HID_KEY_GUI_RIGHT,0} },
};

static const struct keycode_definition_t L0_TAP_KEYS[KEY_DEFINITION_ROW_COUNT][KEY_DEFINITION_COL_COUNT] =
{
    { {'q',1},            {'w',1},     {'e',1},           {'r',1},     {'t',1},         {'y',1},       {'u',1},     {'i',1},               {'o',1},     {'p',1}           },
    { {'a',1},            {'s',1},     {'d',1},           {'f',1},     {'g',1},         {'h',1},       {'j',1},     {'k',1},               {'l',1},     {';',1}           },
    { {'z',1},            {'x',1},     {'c',1},           {'v',1},     {'b',1},         {'n',1},       {'m',1},     {',',1},               {'.',1},     {'/',1}           },
    { {HID_KEY_ESCAPE,0}, {KC_NULL,0}, {HID_KEY_SPACE,0}, {KC_NULL,0}, {HID_KEY_TAB,0}, {KC_REPEAT,0}, {KC_NULL,0}, {HID_KEY_BACKSPACE,0}, {KC_NULL,0}, {HID_KEY_ENTER,0} },
    //TODO replace tab with IME key
};

static const struct keycode_definition_t L1_TAP_KEYS[KEY_DEFINITION_ROW_COUNT][KEY_DEFINITION_COL_COUNT] =
{
    { {KC_NULL,0},        {KC_NULL,0}, {KC_NULL,0},       {KC_NULL,0}, {KC_NULL,0},     {KC_NULL,0},   {KC_NULL,0}, {KC_NULL,0},           {KC_NULL,0}, {KC_NULL,0}       },
    { {KC_NULL,0},        {KC_NULL,0}, {KC_NULL,0},       {KC_NULL,0}, {KC_NULL,0},     {KC_NULL,0},   {KC_NULL,0}, {KC_NULL,0},           {KC_NULL,0}, {KC_NULL,0}       },
    { {KC_NULL,0},        {KC_NULL,0}, {KC_NULL,0},       {KC_NULL,0}, {KC_NULL,0},     {KC_NULL,0},   {KC_NULL,0}, {KC_NULL,0},           {KC_NULL,0}, {KC_NULL,0}       },
    { {HID_KEY_ESCAPE,0}, {KC_NULL,0}, {HID_KEY_SPACE,0}, {KC_NULL,0}, {HID_KEY_TAB,0}, {KC_REPEAT,0}, {KC_NULL,0}, {HID_KEY_BACKSPACE,0}, {KC_NULL,0}, {HID_KEY_ENTER,0} },
    //TODO replace tab with IME key
};

static const struct keycode_definition_t L_HOLD_DELAY_KEYS[KEY_DEFINITION_ROW_COUNT][KEY_DEFINITION_COL_COUNT] =
{
    { {'`',1},     {'0',1},     {'1',1},     {'2',1},     {'3',1},     {'&',1},     {'*',1},     {'(',1},     {')',1},     {'=',1}     },
    { {'@',1},     {'$',1},     {'4',1},     {'5',1},     {'6',1},     {'-',1},     {'_',1},     {'{',1},     {'}',1},     {'\'',1}    },
    { {'<',1},     {'>',1},     {'7',1},     {'8',1},     {'9',1},     {'+',1},     {'!',1},     {'[',1},     {']',1},     {'\\',1}    },
    { {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0}, {KC_NULL,0} },
};
#endif
