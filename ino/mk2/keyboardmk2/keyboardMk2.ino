//Imports
#include "Keyboard.h"

//Constants
const int COLUMN_COUNT = 6;
const int ROW_COUNT = 4;

const byte ROW_0_PIN = 2;
const byte ROW_1_PIN = 3;
const byte ROW_2_PIN = 4;
const byte ROW_3_PIN = 5;

const byte COL_0_PIN = 8;
const byte COL_1_PIN = 10;
const byte COL_2_PIN = 9;
const byte COL_3_PIN = 16;
const byte COL_4_PIN = 14;
const byte COL_5_PIN = 15;

const byte ROWS[ROW_COUNT] = { ROW_0_PIN, ROW_1_PIN, ROW_2_PIN, ROW_3_PIN };
const byte COLS[COLUMN_COUNT] = { COL_0_PIN, COL_1_PIN, COL_2_PIN, COL_3_PIN, COL_4_PIN, COL_5_PIN };

#define KC_NULL 0x00
#define KC_LAYER_TOGGLE 0x00
#define KEY_PRINT_SCREEN 0xCE

// Program params
const int TESTING_SERIAL_BAUD_RATE = 115200;
const int LOOP_DELAY_TIME = 20;

// Program flags
const bool SWITCH_TESTING_MODE = false;
const bool IS_LEFT_KEYBOARD_SIDE = true;

//Classes
class LayerSwapKeyLocationProvider
{
    public:
        virtual int getlayerswapkeyrow() = 0;
        virtual int getlayerswapkeycol() = 0;
}

class LayeredKeycodeProvider
{
    public:
        virtual char getlayerkeycode(int layer, int row, int col) = 0;
}

class LeftKeymap: public LayeredKeycodeProvider, public LayerSwapKeyLocationProvider
{
    private:
        const int LAYER_KEY_ROW_INDEX = 3;
        const int LAYER_KEY_COL_INDEX = 4;

        const int _layer1keymap[ROW_COUNT][COLUMN_COUNT] =
            {
                { 'q', 'w', 'e', 'r', 't', 'y' },
                { 'a', 's', 'd', 'f', 'g', 'h' },
                { 'z', 'x', 'c', 'v', 'b', 'n' },
                { KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, KEY_ESC, KC_LAYER_TOGGLE , ' ' }
            }
        const int _layer2keymap[ROW_COUNT][COLUMN_COUNT] =
            {
                { '1', '2', '3', '4', '5', '6' },
                { '`', KC_NULL, KC_NULL, KEY_HOME, KEY_END, KEY_LEFT_ARROW },
                { KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6 },
                { KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, KEY_ESC, KC_LAYER_TOGGLE, ' ' }
            }
    public:
        char getlayerkeycode(int layer, int row, int col)
        {
            switch(layer)
            {
                case 1:
                    _layer1keymap[row][col];
                    break;
                case 2:
                    _layer2keymap[row][col];
                    break;
            }
            return KC_NULL;
        }

        int getlayerswapkeyrow()
        {
            return LAYER_KEY_ROW_INDEX;
        }

        int getlayerswapkeycol()
        {
            return LAYER_KEY_COL_INDEX;
        }
}

class RightKeymap: public LayeredKeycodeProvider, public LayerSwapKeyLocationProvider
{
    private:
        const int LAYER_KEY_ROW_INDEX = 3;
        const int LAYER_KEY_COL_INDEX = 1;

        //todo fix these keymaps
        const int _layer1keymap[ROW_COUNT][COLUMN_COUNT] =
            {
                { 'q', 'w', 'e', 'r', 't', 'y' },
                { 'a', 's', 'd', 'f', 'g', 'h' },
                { 'z', 'x', 'c', 'v', 'b', 'n' },
                { KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, KEY_ESC, KC_LAYER_TOGGLE , ' ' }
            }
        const int _layer2keymap[ROW_COUNT][COLUMN_COUNT] =
            {
                { '1', '2', '3', '4', '5', '6' },
                { '`', KC_NULL, KC_NULL, KEY_HOME, KEY_END, KEY_LEFT_ARROW },
                { KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6 },
                { KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, KEY_ESC, KC_LAYER_TOGGLE, ' ' }
            }
}

//Variables
byte _switchMatrix[KEY_ROW_COUNT][KEY_COLUMN_COUNT] = {0};
byte _switchMatrixPrev[KEY_ROW_COUNT][KEY_COLUMN_COUNT] = {0};
LayerSwapKeyLocationProvider* _layerKeyProvider;
LayeredKeycodeProvider* _keycodeProvider;

//Init
void setup()
{
    // Init serial output
    Serial.begin(TESTING_SERIAL_BAUD_RATE);

    // Init keymap
    if (IS_LEFT_KEYBOARD_SIDE)
    {
        // Use left keymap.
        LeftKeymap lmap;
        _layerKeyProvider = &lmap;
        _keycodeProvider = &lmap;
    }
    else
    {
        // Use right keymap.
        RightKeymap rmap;
        _layerKeyProvider = &rmap;
        _keycodeProvider = &rmap;
    }

    // Init default pin modes;
	for(int i = 0; i < KEY_ROW_COUNT; i++)
    {
		pinMode(ROWS[i], INPUT_PULLUP);
	}
	for (int i = 0; i < KEY_COLUMN_COUNT; i++)
    {
		pinMode(COLS[i], INPUT);
	}
}

//Main Method
void loop()
{
    delay(LOOP_DELAY_TIME);
}

//Methods

//Utility Methods

