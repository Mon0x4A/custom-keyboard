//Imports
#include "Keyboard.h"

//Constants
const bool SWITCH_TESTING_MODE = false;
const bool IS_LEFT_KEYBOARD_SIDE = false;

const int TESTING_SERIAL_BAUD_RATE = 115200;
const int LOOP_DELAY_TIME = 20;

const unsigned long TAP_ACTION_TIMEOUT = 200;
const unsigned long MODIFIER_APPLY_DELAY = 50;

const int COLUMN_COUNT = 6;
const int ROW_COUNT = 4;

const int LAYER_COUNT = 3;

const byte ROW_0_PIN = IS_LEFT_KEYBOARD_SIDE ? 8 : 9;
const byte ROW_1_PIN = IS_LEFT_KEYBOARD_SIDE ? 7 : 8;
const byte ROW_2_PIN = IS_LEFT_KEYBOARD_SIDE ? 6 : 7;
const byte ROW_3_PIN = IS_LEFT_KEYBOARD_SIDE ? 5 : 6;

const byte COL_0_PIN = A1;
const byte COL_1_PIN = A0;
const byte COL_2_PIN = 15;
const byte COL_3_PIN = 14;
const byte COL_4_PIN = 16;
const byte COL_5_PIN = 10;

const byte ROWS[ROW_COUNT] = { ROW_0_PIN, ROW_1_PIN, ROW_2_PIN, ROW_3_PIN };
const byte COLS[COLUMN_COUNT] = { COL_0_PIN, COL_1_PIN, COL_2_PIN, COL_3_PIN, COL_4_PIN, COL_5_PIN };

#define KC_NULL 0x00
#define KC_LM 0x00
#define KEY_PRINT_SCREEN 0xCE

const int LEFT_SIDE_DESIGNATOR = 420;
const int RIGHT_SIDE_DESIGNATOR = 69;

//Left Layer 0
const unsigned char LEFT_LAYER0_KEYMAP[ROW_COUNT][COLUMN_COUNT] =
    {
        { 'q',           'w',     'e',     'r',     't',        'y' },
        { 'a',           's',     'd',     'f',     'g',        'h' },
        { 'z',           'x',     'c',     'v',     'b',        'n' },
        { KEY_LEFT_CTRL, KC_NULL, KC_NULL, KC_NULL, KEY_RETURN, ' ' }
    };

//Left Layer 1
const int LEFT_LAYER1_MODIFIER_KEY_ROW_INDEX = 3;
const int LEFT_LAYER1_MODIFIER_KEY_COL_INDEX = 4;

const unsigned char LEFT_LAYER1_KEYMAP[ROW_COUNT][COLUMN_COUNT] =
    {
        { KEY_ESC,        KEY_PRINT_SCREEN, KEY_F1,  KEY_F2,  KEY_F3,  KEY_F4 },
        { KEY_TAB,        KC_NULL,          KEY_F5,  KEY_F6,  KEY_F7,  KEY_F8 },
        { KEY_LEFT_SHIFT, KC_NULL,          KEY_F9,  KEY_F10, KEY_F11, KEY_F12 },
        { KEY_LEFT_ALT,   KC_NULL,          KC_NULL, KC_NULL, KC_LM,   ' ' }
    };
const bool LEFT_LAYER1_IS_UNSTICK_KEY[ROW_COUNT][COLUMN_COUNT] =
    {
        { 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 0, 0, 0 },
    };

//Left Layer 2
const int LEFT_LAYER2_MODIFIER_KEY_ROW_INDEX = 3;
const int LEFT_LAYER2_MODIFIER_KEY_COL_INDEX = 5;

const unsigned char LEFT_LAYER2_KEYMAP[ROW_COUNT][COLUMN_COUNT] =
    {
        { KEY_ESC,        '0',      '1',     '2',     '3',   '~'     },
        { KC_NULL,        '`',      '4',     '5',     '6',   '$'     },
        { KEY_LEFT_SHIFT, ':',      '7',     '8',     '9',   KC_NULL },
        { KEY_LEFT_GUI,   KC_NULL, KC_NULL,  KC_NULL, KC_LM, ' '     }
    };

const bool LEFT_LAYER2_IS_UNSTICK_KEY[ROW_COUNT][COLUMN_COUNT] =
    {
        { 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 0, 0, 0 },
    };

//Right Layer 0
const unsigned char RIGHT_LAYER0_KEYMAP[ROW_COUNT][COLUMN_COUNT] =
    {
        { 'u',           'i',   'o',     'p',     '(',             ')' },
        { 'j',           'k',   'l',     ';',     '\'',            KC_NULL },
        { 'm',           ',',   '.',     '/',     KEY_RIGHT_SHIFT, KEY_RIGHT_SHIFT },
        { KEY_BACKSPACE, KC_LM, KC_NULL, KC_NULL, KC_NULL,         KEY_RIGHT_CTRL }
    };

//Right Layer 1
const int RIGHT_LAYER1_MODIFIER_KEY_ROW_INDEX = 3;
const int RIGHT_LAYER1_MODIFIER_KEY_COL_INDEX = 1;

const unsigned char RIGHT_LAYER1_KEYMAP[ROW_COUNT][COLUMN_COUNT] =
    {
        { KC_NULL,        KEY_UP_ARROW,   KC_NULL,         KC_NULL,  KEY_DELETE,      KC_NULL },
        { KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, KC_NULL,  '\\',            KC_NULL },
        { KC_NULL,        KC_NULL,        KC_NULL,         KC_NULL,  KEY_RIGHT_SHIFT, KEY_RIGHT_SHIFT },
        { KC_LM,          KC_LM,          KC_NULL,         KC_NULL,  KC_NULL,         KEY_RIGHT_ALT }
    };
const bool RIGHT_LAYER1_IS_UNSTICK_KEY[ROW_COUNT][COLUMN_COUNT] =
    {
        { 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 1 },
    };

//Right Layer 2
const int RIGHT_LAYER2_MODIFIER_KEY_ROW_INDEX = 3;
const int RIGHT_LAYER2_MODIFIER_KEY_COL_INDEX = 0;

const unsigned char RIGHT_LAYER2_KEYMAP[ROW_COUNT][COLUMN_COUNT] =
    {
        { '&',     '*',     '[',     ']',     '-',             KC_NULL },
        { '+',     '_',     '|',     '{',     '}',             KC_NULL },
        { '<',     '>',     '!',     '=',     KEY_RIGHT_SHIFT, KEY_RIGHT_SHIFT },
        { KC_LM,   KC_LM,   KC_NULL, KC_NULL, KC_NULL,         KEY_RIGHT_GUI }
    };

const bool RIGHT_LAYER2_IS_UNSTICK_KEY[ROW_COUNT][COLUMN_COUNT] =
    {
        { 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 1 },
    };


//Classes
class KeymapProvider
{
    public:
        static unsigned char get_keycode_at(int sidedesignator, int layerindex, int row, int col)
        {
            if (LEFT_SIDE_DESIGNATOR == sidedesignator)
            {
                switch(layerindex)
                {
                    case 0:
                        return LEFT_LAYER0_KEYMAP[row][col];
                    case 1:
                        return LEFT_LAYER1_KEYMAP[row][col];
                    case 2:
                        return LEFT_LAYER2_KEYMAP[row][col];
                }
            }
            else if (RIGHT_SIDE_DESIGNATOR == sidedesignator)
            {
                switch(layerindex)
                {
                    case 0:
                        return RIGHT_LAYER0_KEYMAP[row][col];
                    case 1:
                        return RIGHT_LAYER1_KEYMAP[row][col];
                    case 2:
                        return RIGHT_LAYER2_KEYMAP[row][col];
                }
            }

            return KC_NULL;
        }

        static bool is_unstick_key(int sidedesignator, int layerindex, int row, int col)
        {
            if (LEFT_SIDE_DESIGNATOR == sidedesignator)
            {
                switch(layerindex)
                {
                    case 0:
                        return true;
                    case 1:
                        return LEFT_LAYER1_IS_UNSTICK_KEY[row][col];
                    case 2:
                        return LEFT_LAYER2_IS_UNSTICK_KEY[row][col];
                }
            }
            else if (RIGHT_SIDE_DESIGNATOR == sidedesignator)
            {
                switch(layerindex)
                {
                    case 0:
                        return true;
                    case 1:
                        return RIGHT_LAYER1_IS_UNSTICK_KEY[row][col];
                    case 2:
                        return RIGHT_LAYER2_IS_UNSTICK_KEY[row][col];
                }
            }

            return false;
        }

        static int get_layer1_modifier_key_row(int sidedesignator)
        {
            switch(sidedesignator)
            {
                case LEFT_SIDE_DESIGNATOR:
                    return LEFT_LAYER1_MODIFIER_KEY_ROW_INDEX;
                case RIGHT_SIDE_DESIGNATOR:
                    return RIGHT_LAYER1_MODIFIER_KEY_ROW_INDEX;
            }
            return -1;
        }

        static int get_layer1_modifier_key_col(int sidedesignator)
        {
            switch(sidedesignator)
            {
                case LEFT_SIDE_DESIGNATOR:
                    return LEFT_LAYER1_MODIFIER_KEY_COL_INDEX;
                case RIGHT_SIDE_DESIGNATOR:
                    return RIGHT_LAYER1_MODIFIER_KEY_COL_INDEX;
            }
            return -1;
        }

        static int get_layer2_modifier_key_row(int sidedesignator)
        {
            switch(sidedesignator)
            {
                case LEFT_SIDE_DESIGNATOR:
                    return LEFT_LAYER2_MODIFIER_KEY_ROW_INDEX;
                case RIGHT_SIDE_DESIGNATOR:
                    return RIGHT_LAYER2_MODIFIER_KEY_ROW_INDEX;
            }
            return -1;
        }

        static int get_layer2_modifier_key_col(int sidedesignator)
        {
            switch(sidedesignator)
            {
                case LEFT_SIDE_DESIGNATOR:
                    return LEFT_LAYER2_MODIFIER_KEY_COL_INDEX;
                case RIGHT_SIDE_DESIGNATOR:
                    return RIGHT_LAYER2_MODIFIER_KEY_COL_INDEX;
            }

            return -1;
        }

    private:
        KeymapProvider() { }
};

//Variables
int _sideDesignator = -1;

byte _switchMatrix[ROW_COUNT][COLUMN_COUNT] = {0};
byte _switchMatrixPrev[ROW_COUNT][COLUMN_COUNT] = {0};

// Layer Variables
bool _isLayer1ModifierKeyHeld = false;
bool _isLayer1ModifierActionQueued = false;
bool _hasLayer1ActionBeenPerformed = false;
unsigned long _layer1HoldStart = 0;
bool _isLayer2ModifierKeyHeld = false;
bool _isLayer2ModifierActionQueued = false;
bool _hasLayer2ActionBeenPerformed = false;
unsigned long _layer2HoldStart = 0;

//Init
void setup()
{
    // Init serial output
    Serial.begin(TESTING_SERIAL_BAUD_RATE);
    // Wait for serial to boot up...
    delay(1000);
    Serial.println("Starting keyboard...");

    // Init keymap
    if (IS_LEFT_KEYBOARD_SIDE)
    {
        // Use left keymap.
        _sideDesignator = LEFT_SIDE_DESIGNATOR;
        Serial.println("Selecting LeftKeymap...");
    }
    else
    {
        // Use right keymap.
        _sideDesignator = RIGHT_SIDE_DESIGNATOR;
        Serial.println("Selecting RightKeymap...");
    }

    // Init default pin modes;
	for(int i = 0; i < ROW_COUNT; i++)
    {
		pinMode(ROWS[i], INPUT_PULLUP);
	}
	for (int i = 0; i < COLUMN_COUNT; i++)
    {
		pinMode(COLS[i], INPUT);
	}
}

//Main Method
void loop()
{
    delay(LOOP_DELAY_TIME);

    copy_matrix_state_to_prev();
    read_matrix();

    if (SWITCH_TESTING_MODE)
    {
        print_matrix_to_serial_out();
    }
    else
    {
        set_key_states();
    }
}

//Methods
void read_matrix()
{
    for (int row = 0; row < ROW_COUNT; row++)
    {
        // set the row to output low
        byte curRow = ROWS[row];
        pinMode(curRow, OUTPUT);
        digitalWrite(curRow, LOW);

        // iterate through the columns reading the value - should be zero if switch is pressed
        for (int col = 0; col < COLUMN_COUNT; col++)
        {
            byte rowCol = COLS[col];
            pinMode(rowCol, INPUT_PULLUP);
            _switchMatrix[row][col] = digitalRead(rowCol);
            pinMode(rowCol, INPUT);
        }

        // disable the row, turn the pullup resistor off
        pinMode(curRow, INPUT);
    }
}

void set_key_states()
{
    for (int i = 0; i < ROW_COUNT; i++)
    {
        for (int j = 0; j < COLUMN_COUNT; j++)
        {
            // If the swich changed state..
            if (_switchMatrix[i][j] != _switchMatrixPrev[i][j])
            {
                if (_switchMatrix[i][j] == 0 && _switchMatrixPrev[i][j] == 1)
                {
                    // We started pressing a key.
                    if (KeymapProvider::get_layer1_modifier_key_row(_sideDesignator) == i
                        && KeymapProvider::get_layer1_modifier_key_col(_sideDesignator) == j)
                    {
                        // We've started pressing down the layer 1 modifier key.
                        _isLayer1ModifierKeyHeld = true;
                        _isLayer1ModifierActionQueued = true;
                        _hasLayer1ActionBeenPerformed = false;
                        _layer1HoldStart = millis();

                        // Cancel our Layer2 action.
                        if (!_isLayer2ModifierKeyHeld)
                            _isLayer2ModifierActionQueued = false;
                    }
                    else if (KeymapProvider::get_layer2_modifier_key_row(_sideDesignator) == i
                        && KeymapProvider::get_layer2_modifier_key_col(_sideDesignator) == j)
                    {
                        // We've started pressing down the layer 2 modifier key.
                        _isLayer2ModifierKeyHeld = true;
                        _isLayer2ModifierActionQueued = true;
                        _hasLayer2ActionBeenPerformed = false;
                        _layer2HoldStart = millis();

                        // Cancel our Layer1 action.
                        if (!_isLayer1ModifierKeyHeld)
                            _isLayer1ModifierActionQueued = false;
                    }
                    else
                    {
                        // A non-layer key has been pressed.
                        unsigned char keycode = KeymapProvider::get_keycode_at(
                            _sideDesignator,
                            get_current_layer_based_on_modifier_state(),
                            i,
                            j);

                        if (_isLayer2ModifierKeyHeld)
                            _hasLayer2ActionBeenPerformed = true;
                        if (_isLayer1ModifierKeyHeld)
                            _hasLayer1ActionBeenPerformed = true;

                        if (keycode != KC_NULL)
                            Keyboard.press(keycode);

                        if (KeymapProvider::is_unstick_key(_sideDesignator,
                            get_current_layer_based_on_modifier_state(), i, j))
                        {
                            // If we've pressed a layer unstick key, then we've satisfied
                            // our queued action if it exists
                            _isLayer1ModifierActionQueued = false;
                            _isLayer2ModifierActionQueued = false;
                        }
                    }
                }
                else
                {
                    // We released a key.
                    if (KeymapProvider::get_layer1_modifier_key_row(_sideDesignator) == i
                        && KeymapProvider::get_layer1_modifier_key_col(_sideDesignator) == j)
                    {
                        // The layer 1 modifier key is no longer held.
                        _isLayer1ModifierKeyHeld = false;

                        // Perform our tap action if we meet the requirements.
                        if (!has_reached_mod_tap_timeout(_layer1HoldStart)
                            && !_hasLayer1ActionBeenPerformed)
                        {
                            _isLayer1ModifierActionQueued = false;
                            Keyboard.write(KeymapProvider::get_keycode_at(_sideDesignator,
                              0,
                              KeymapProvider::get_layer1_modifier_key_row(_sideDesignator),
                              KeymapProvider::get_layer1_modifier_key_col(_sideDesignator)));
                        }
                    }
                    else if (KeymapProvider::get_layer2_modifier_key_row(_sideDesignator) == i
                        && KeymapProvider::get_layer2_modifier_key_col(_sideDesignator) == j)
                    {
                        // The layer 2 key is no longer held.
                        _isLayer2ModifierKeyHeld = false;

                        // Perform our tap action if we meet the requirements.
                        if (!has_reached_mod_tap_timeout(_layer2HoldStart)
                            && !_hasLayer2ActionBeenPerformed)
                        {
                            _isLayer2ModifierActionQueued = false;
                            Keyboard.write(KeymapProvider::get_keycode_at(_sideDesignator,
                              0,
                              KeymapProvider::get_layer2_modifier_key_row(_sideDesignator),
                              KeymapProvider::get_layer2_modifier_key_col(_sideDesignator)));
                        }
                    }
                    else
                    {
                        // A non-layer related key has been released.
                        for (int k = 0; k < LAYER_COUNT; k++)
                        {
                            // Attempt to release all keys across all layers at this location.
                            // This is to prevent bugs when swapping layers with another key held.
                            unsigned char keycode = KeymapProvider::get_keycode_at(_sideDesignator, k, i, j);
                            if (keycode != KC_NULL)
                                Keyboard.release(keycode);
                        }
                    }
                }
            }
        }
    }
}

bool has_reached_mod_tap_timeout(unsigned long holdStart)
{
    return ((millis()-holdStart) >= TAP_ACTION_TIMEOUT);
}

bool has_reached_mod_application_delay(unsigned long holdStart)
{
    return ((millis()-holdStart) >= MODIFIER_APPLY_DELAY);
}

int get_current_layer_based_on_modifier_state()
{
    if ((_isLayer2ModifierKeyHeld || _isLayer2ModifierActionQueued)
        && has_reached_mod_application_delay(_layer2HoldStart))
        return 2;
    if ((_isLayer1ModifierKeyHeld || _isLayer1ModifierActionQueued)
        && has_reached_mod_application_delay(_layer1HoldStart))
        return 1;
    return 0;
}

void copy_matrix_state_to_prev()
{
    for (int i = 0; i < ROW_COUNT; i++)
    {
        for (int j = 0; j < COLUMN_COUNT; j++)
        {
            _switchMatrixPrev[i][j] = _switchMatrix[i][j];
        }
    }
}

//Utility Methods
void print_matrix_to_serial_out()
{
    String matrixstr = "";
    for (int row = 0; row < ROW_COUNT; row++)
    {
        if (row < 10) {
           matrixstr += String("0");
        }
        matrixstr += String(row);
        matrixstr += String(": ");

        for (int col = 0; col < COLUMN_COUNT; col++)
        {
            matrixstr += String(_switchMatrix[row][col]);
            if (col < COLUMN_COUNT)
                matrixstr += String(", ");
        }
        matrixstr += String("\n");
    }
    Serial.print(matrixstr);
}
