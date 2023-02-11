//Imports
#include "Keyboard.h"

//Constants
const bool SWITCH_TESTING_MODE = false;
const bool IS_LEFT_KEYBOARD_SIDE = false;

const int COLUMN_COUNT = 6;
const int ROW_COUNT = 4;
const int LAYER_COUNT = 2;

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
#define KC_LAYER_SWAP 0x00
#define KC_LAYER_MODIFIER 0x00
#define KEY_PRINT_SCREEN 0xCE

const int LEFT_SIDE_DESIGNATOR = 420;
const int RIGHT_SIDE_DESIGNATOR = 69;

const int RIGHT_LAYER_MODIFIER_KEY_ROW_INDEX = 3;
const int RIGHT_LAYER_MODIFIER_KEY_COL_INDEX = 1;

const char RIGHT_LAYER0_KEYMAP[ROW_COUNT][COLUMN_COUNT] =
    {
        { 'u', 'i', 'o', 'p', '[', ']' },
        { 'j', 'k', 'l', ';', '\'', KEY_RETURN },
        { 'm', ',', '.', '/', KEY_TAB, KEY_BACKSPACE },
        { KEY_RIGHT_SHIFT, KC_LAYER_MODIFIER, KC_LAYER_SWAP, '(', ')', KEY_ESC }
    };
const char RIGHT_LAYER1_KEYMAP[ROW_COUNT][COLUMN_COUNT] =
    {
        { '7', '8', '9', '0', '-', '=' },
        { KEY_DOWN_ARROW, KEY_UP_ARROW, KEY_RIGHT_ARROW, '\\', KEY_DELETE, KEY_RETURN },
        { KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12 },
        { KEY_RIGHT_SHIFT, KC_LAYER_MODIFIER, KC_LAYER_SWAP, KEY_PAGE_UP, KEY_PAGE_DOWN, KEY_ESC }
    };

const int LEFT_LAYER_MODIFIER_KEY_ROW_INDEX = 3;
const int LEFT_LAYER_MODIFIER_KEY_COL_INDEX = 4;

const char LEFT_LAYER0_KEYMAP[ROW_COUNT][COLUMN_COUNT] =
    {
        { 'q', 'w', 'e', 'r', 't', 'y' },
        { 'a', 's', 'd', 'f', 'g', 'h' },
        { 'z', 'x', 'c', 'v', 'b', 'n' },
        { KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, KC_LAYER_SWAP, KC_LAYER_MODIFIER, ' ' }
    };
const char LEFT_LAYER1_KEYMAP[ROW_COUNT][COLUMN_COUNT] =
    {
        { '1', '2', '3', '4', '5', '6' },
        { '`', KEY_PRINT_SCREEN, KEY_HOME, KEY_END, KC_NULL, KEY_LEFT_ARROW },
        { KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6 },
        { KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, KC_LAYER_SWAP, KC_LAYER_MODIFIER, ' ' }
    };

// Program params
const int TESTING_SERIAL_BAUD_RATE = 115200;
const int LOOP_DELAY_TIME = 20;

//Classes
class KeymapProvider
{
    public:
        static char get_keycode(int sidedesignator, int layerindex, int row, int col)
        {
            if (LEFT_SIDE_DESIGNATOR == sidedesignator)
            {
                switch(layerindex)
                {
                    case 0:
                        return LEFT_LAYER0_KEYMAP[row][col];
                    case 1:
                        return LEFT_LAYER1_KEYMAP[row][col];
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
                }
            }

            return KC_NULL;
        }

        static int get_layer_modifier_key_row(int sidedesignator)
        {
            switch(sidedesignator)
            {
                case LEFT_SIDE_DESIGNATOR:
                    return LEFT_LAYER_MODIFIER_KEY_ROW_INDEX;
                case RIGHT_SIDE_DESIGNATOR:
                    return RIGHT_LAYER_MODIFIER_KEY_ROW_INDEX;
            }
            return -1;
        }

        static int get_layer_modifier_key_col(int sidedesignator)
        {
            switch(sidedesignator)
            {
                case LEFT_SIDE_DESIGNATOR:
                    return LEFT_LAYER_MODIFIER_KEY_COL_INDEX;
                case RIGHT_SIDE_DESIGNATOR:
                    return RIGHT_LAYER_MODIFIER_KEY_COL_INDEX;
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

int _currentlayer = 0;
bool _isLayerModifierKeyHeld = false;
bool _isLayerModifierQueued = false;

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
                    if (KeymapProvider::get_layer_modifier_key_row(_sideDesignator) == i
                        && KeymapProvider::get_layer_modifier_key_col(_sideDesignator) == j)
                    {
                        // We've started pressing down the layer modifier key.
                        _isLayerModifierKeyHeld = true;
                        _isLayerModifierQueued = true;
                    }
                    else
                    {
                        // A non-layer key has been pressed.
                        Keyboard.press(KeymapProvider::get_keycode(
                            _sideDesignator,
                            _isLayerModifierKeyHeld || _isLayerModifierQueued ? get_swapped_layer() : _currentlayer,
                            i,
                            j));

                        // We've satisfied our queued action if it exists
                        _isLayerModifierQueued = false;
                    }
                }
                else
                {
                    // We released a key.
                    if (KeymapProvider::get_layer_modifier_key_row(_sideDesignator) == i
                        && KeymapProvider::get_layer_modifier_key_col(_sideDesignator) == j)
                    {
                        // The layer modifier key is no longer held.
                        _isLayerModifierKeyHeld = false;
                    }
                    else
                    {
                        //Keyboard.release(KeymapProvider::get_keycode(
                        //    _sideDesignator,
                        //    _isLayerModifierKeyHeld ? get_swapped_layer() : _currentlayer,
                        //    i,
                        //    j));

                        // A non-layer related key has been released.
                        for (int k = 0; k < LAYER_COUNT; k++)
                        {
                            // Attempt to release all keys across all layers at this location.
                            // This is to prevent bugs when swapping layers with another key held.
                            Keyboard.release(KeymapProvider::get_keycode(_sideDesignator, k, i, j));
                        }
                    }
                }
            }
        }
    }
}

void swap_layer()
{
    _currentlayer = get_swapped_layer();
}

int get_swapped_layer()
{
    switch (_currentlayer)
    {
        case 0:
            return 1;
        case 1:
            return 0;
    }
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
