//Imports
#include "Keyboard.h"

//Constants
const bool SWITCH_TESTING_MODE = true;
const bool IS_LEFT_KEYBOARD_SIDE = false;

const int TESTING_SERIAL_BAUD_RATE = 115200;
const int LOOP_DELAY_TIME = 20;

const unsigned long DEFAULT_TAP_ACTION_TIMEOUT = 200;
const unsigned long DEFAULT_BASE_APPLY_DELAY = 50;

const int COLUMN_COUNT = 7;
const int ROW_COUNT = 3;

const int LAYER_COUNT = 3;

const byte ROW_0_PIN = IS_LEFT_KEYBOARD_SIDE ? 8 : 9;
const byte ROW_1_PIN = IS_LEFT_KEYBOARD_SIDE ? 7 : 8;
const byte ROW_2_PIN = IS_LEFT_KEYBOARD_SIDE ? 6 : 7;

const byte COL_0_PIN = IS_LEFT_KEYBOARD_SIDE ? 0 : 10;
const byte COL_1_PIN = IS_LEFT_KEYBOARD_SIDE ? 0 : 16;
const byte COL_2_PIN = IS_LEFT_KEYBOARD_SIDE ? 0 : 15;
const byte COL_3_PIN = IS_LEFT_KEYBOARD_SIDE ? 0 : 14;
const byte COL_4_PIN = IS_LEFT_KEYBOARD_SIDE ? 0 : A0;
const byte COL_5_PIN = IS_LEFT_KEYBOARD_SIDE ? 0 : A1;
const byte COL_6_PIN = IS_LEFT_KEYBOARD_SIDE ? 0 : A2;

const byte ROWS[ROW_COUNT] = { ROW_0_PIN, ROW_1_PIN, ROW_2_PIN };
const byte COLS[COLUMN_COUNT] = { COL_0_PIN, COL_1_PIN, COL_2_PIN, COL_3_PIN, COL_4_PIN, COL_5_PIN, COL_6_PIN };

#define KC_NULL 0x00
#define KC_LM1 0x01 //(STX) //Repurposing obsolete ascii codes for our layer modifier codes
#define KC_LM2 0x02 //(ETX)
#define KC_REPEAT 0x07 //(BEL)
#define KEY_PRINT_SCREEN 0xCE

//Enums
enum KeyboardSide
{
    left = 420,
    right = 69
};

//Interfaces
class IBaseKeymap
{
    public:
        virtual unsigned char get_base_keycode_at(unsigned int row, unsigned int col) = 0;
};

class IBaseTapStateProvider
{
    public:
        virtual bool get_is_base_tap_enabled_key(unsigned int row, unsigned int col) = 0;
        virtual bool get_tap_keycode_at(unsigned int row, unsigned int col) = 0;

        virtual bool get_has_tap_timed_out(unsigned int row, unsigned int col) = 0;
        virtual bool get_has_base_timed_in(unsigned int row, unsigned int col) = 0;
        virtual bool get_has_base_chord_action_been_performed(unsigned int row, unsigned int col) = 0;
};

class IBaseTapStateSetter
{
    public:
        virtual void set_start_key_press(unsigned int row, unsigned int col) = 0;
        virtual void set_has_base_chord_action_performed(
            unsigned int row, unsigned int col, bool hasBaseChordActionBeenPerfomed) = 0;
};

class ILayerInfoService :
    public IBaseKeymap,
    public IBaseTapStateProvider,
    public IBaseTapStateSetter
{
};

class IIndexedLayerInfoServiceProvider
{
    public:
        virtual ILayerInfoService* get_layer_info_for_index(unsigned int layerIndex) = 0;
};

class IKeyswitchPressedHandler
{
    public:
        virtual void handle_switch_press(unsigned int row, unsigned int col) = 0;
};

class IKeyswitchReleasedHandler
{
    public:
        virtual void handle_switch_release(unsigned int row, unsigned int col) = 0;
};

//Classes
class KeyboardHelper
{
    public:
        static bool has_reached_time_threshold(unsigned long holdStart, unsigned long timeout)
        {
            return ((millis()-holdStart) >= timeout);
        }

    private:
        KeyHelper() { }
};

class KeyswitchPressHandler : public IKeyswitchPressedHandler
{
    public:
        KeyswitchPressHandler(IIndexedLayerInfoServiceProvider& layerInfoProvider)
        {
            _layerInfoProvider = &layerInfoProvider;
        }

        void handle_switch_press(unsigned int row, unsigned int col) 
        {
            //TODO handle press
        }

    private:
        IIndexedLayerInfoServiceProvider* _layerInfoProvider;
};

class KeyswitchReleaseHandler : public IKeyswitchReleasedHandler
{
    public:
        KeyswitchReleaseHandler(IIndexedLayerInfoServiceProvider& layerInfoProvider)
        {
            _layerInfoProvider = &layerInfoProvider;
        }

        void handle_switch_release(unsigned int row, unsigned int col)
        {
            //TODO handle release
        }
    
    private:
        IIndexedLayerInfoServiceProvider* _layerInfoProvider;
};

// For SOME reason these matrices can't be placed in SwitchMatrixManager
// because row one bugs out like crazy. Still don't understand why yet.
byte _switchMatrix[ROW_COUNT][COLUMN_COUNT] = {0};
byte _switchMatrixPrev[ROW_COUNT][COLUMN_COUNT] = {0};
class SwitchMatrixManager
{
    public:
        //Constructor
        SwitchMatrixManager(IKeyswitchPressedHandler& pressHandler,
            IKeyswitchReleasedHandler& releaseHandler)
        {
            _pressHandler = &pressHandler;
            _releaseHandler = &releaseHandler;
        }

        //Public Methods
        void iterate()
        {
            read_matrix();
            handle_switch_state_changes();
            copy_matrix_state_to_prev();

            if (SWITCH_TESTING_MODE)
            {
                print_matrix_to_serial_out();
            }
            else
            {
                handle_switch_state_changes();
            }
        }

    private:
        //Private Variables
        IKeyswitchPressedHandler* _pressHandler;
        IKeyswitchReleasedHandler* _releaseHandler;

        //Private Methods
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
            //print_matrix_to_serial_out();
        }

        void handle_switch_state_changes()
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
                            //TODO handle state call
                            Serial.println("R:"+String(i)+"C:"+String(j)+", "+String("pressed"));
                        }
                        else
                        {
                            // We released a key.
                            //TODO handle state call
                            Serial.println("R:"+String(i)+"C:"+String(j)+", "+String("released"));
                        }
                    }
                }
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

        void print_matrix_to_serial_out()
        {
            String matrixstr = "";
            for (int row = 0; row < ROW_COUNT; row++)
            {
                // print row labels
                if (row < 10) {
                   matrixstr += String("0");
                }
                matrixstr += String(row);
                matrixstr += String(": ");

                // get byte vals
                for (int col = 0; col < COLUMN_COUNT; col++)
                {
                    //Serial.println("R:"+String(row)+"C:"+String(col)+", "+String(_switchMatrix[row][col]));
                    matrixstr += String(_switchMatrix[row][col]);
                    if (col < COLUMN_COUNT)
                        matrixstr += String(", ");
                }
                matrixstr += String("\n");
            }
            Serial.print(matrixstr);
        }
};

class LeftBaseTapStateContainer : public IBaseTapStateProvider, public IBaseTapStateSetter
{
    public:
        LeftBaseTapStateContainer() { }

        //IBaseTapStateProvider
        bool get_is_base_tap_enabled_key(unsigned int row, unsigned int col)
        {
            return (TAP_KEYS[row][col] != KC_NULL);
        }
        bool get_tap_keycode_at(unsigned int row, unsigned int col)
        {
            return TAP_KEYS[row][col];
        }
        bool get_has_tap_timed_out(unsigned int row, unsigned int col)
        {
            return !KeyboardHelper::has_reached_time_threshold(
                _pressStart[row][col], DEFAULT_TAP_ACTION_TIMEOUT);
        }
        bool get_has_base_timed_in(unsigned int row, unsigned int col)
        {
            return KeyboardHelper::has_reached_time_threshold(
                _pressStart[row][col], DEFAULT_BASE_APPLY_DELAY);
        }
        bool get_has_base_chord_action_been_performed(unsigned int row, unsigned int col)
        {
            return _chordPerformed[row][col];
        }

        //IBaseTapStateSetter
        void set_start_key_press(unsigned int row, unsigned int col)
        {
            _chordPerformed[row][col] = false;
            _pressStart[row][col] = millis();
        }
        void set_has_base_chord_action_performed(
            unsigned int row, unsigned int col, bool hasBaseChordActionBeenPerfomed)
        {
            _chordPerformed[row][col] = true;
        }

    private:
        //Private Constants
        const unsigned char TAP_KEYS[ROW_COUNT][COLUMN_COUNT] =
        {
            { KEY_ESC,  KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KEY_TAB },
            { KC_NULL,  KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, ' ' },
            { KC_NULL,  KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_REPEAT },
        };

        //Private Variables
        unsigned long _pressStart[ROW_COUNT][COLUMN_COUNT] = {0};
            //{
            //    { 0, 0, 0, 0, 0, 0, 0 },
            //    { 0, 0, 0, 0, 0, 0, 0 },
            //    { 0, 0, 0, 0, 0, 0, 0 },
            //};
        bool _chordPerformed[ROW_COUNT][COLUMN_COUNT] = {0};
            //{
            //    { 0, 0, 0, 0, 0, 0, 0 },
            //    { 0, 0, 0, 0, 0, 0, 0 },
            //    { 0, 0, 0, 0, 0, 0, 0 },
            //};
};

class LeftLayerZeroInfo : public ILayerInfoService
{
    public:
        //Constructor
        LeftLayerZeroInfo(IBaseTapStateProvider& tapStateProvider,
            IBaseTapStateSetter& tapStateSetter)
        {
            _baseTapStateProvider = &tapStateProvider;
            _baseTapStateSetter = &tapStateSetter;
        }

        //Public Methods
        //IBaseKeymap
        unsigned char get_base_keycode_at(unsigned int row, unsigned int col)
        {
            return BASE_KEYS[row][col];
        }

        //IBaseTapStateProvider
        bool get_is_base_tap_enabled_key(unsigned int row, unsigned int col)
        {
            return _baseTapStateProvider->get_is_base_tap_enabled_key(row,col);
        }
        bool get_tap_keycode_at(unsigned int row, unsigned int col)
        {
            return _baseTapStateProvider->get_tap_keycode_at(row,col);
        }
        bool get_has_tap_timed_out(unsigned int row, unsigned int col)
        {
            return _baseTapStateProvider->get_has_tap_timed_out(row,col);
        }
        bool get_has_base_timed_in(unsigned int row, unsigned int col)
        {
            return _baseTapStateProvider->get_has_base_timed_in(row,col);
        }
        bool get_has_base_chord_action_been_performed(unsigned int row, unsigned int col)
        {
            return _baseTapStateProvider->get_has_base_chord_action_been_performed(row,col);
        }

        //IBaseTapStateSetter
        void set_start_key_press(unsigned int row, unsigned int col)
        {
            return _baseTapStateSetter->set_start_key_press(row,col);
        }
        void set_has_base_chord_action_performed(
            unsigned int row, unsigned int col, bool hasBaseChordActionBeenPerfomed)
        {
            return _baseTapStateSetter->set_has_base_chord_action_performed(
                row,col,hasBaseChordActionBeenPerfomed);
        }

    private:
        //Private Constants
        // NOTE: The left layer maps use the right shift because left shift is what is
        // pressed and released during the 'Keyboard.write()' calls. Thus firing unwanted
        // release events if the physical left shift key is held during that.
        const unsigned char BASE_KEYS[ROW_COUNT][COLUMN_COUNT] =
        {
            { KEY_LEFT_CTRL, 'q', 'w', 'e', 'r', 't', KC_LM1 },
            { KC_NULL,       'a', 's', 'd', 'f', 'g', KC_LM2 },
            { KC_NULL,       'z', 'x', 'c', 'v', 'b', KEY_RIGHT_SHIFT },
        };

        //Private Variables
        IBaseTapStateProvider* _baseTapStateProvider;
        IBaseTapStateSetter* _baseTapStateSetter;
};

class LeftLayerOneInfo : public ILayerInfoService
{
    public:
        //Constructor
        LeftLayerOneInfo(IBaseTapStateProvider& tapStateProvider,
            IBaseTapStateSetter& tapStateSetter)
        {
            _baseTapStateProvider = &tapStateProvider;
            _baseTapStateSetter = &tapStateSetter;
        }

        //Public Methods
        //IBaseKeymap
        unsigned char get_base_keycode_at(unsigned int row, unsigned int col)
        {
            return BASE_KEYS[row][col];
        }

        //IBaseTapStateProvider
        bool get_is_base_tap_enabled_key(unsigned int row, unsigned int col)
        {
            return _baseTapStateProvider->get_is_base_tap_enabled_key(row,col);
        }
        bool get_tap_keycode_at(unsigned int row, unsigned int col)
        {
            return _baseTapStateProvider->get_tap_keycode_at(row,col);
        }
        bool get_has_tap_timed_out(unsigned int row, unsigned int col)
        {
            return _baseTapStateProvider->get_has_tap_timed_out(row,col);
        }
        bool get_has_base_timed_in(unsigned int row, unsigned int col)
        {
            return _baseTapStateProvider->get_has_base_timed_in(row,col);
        }
        bool get_has_base_chord_action_been_performed(unsigned int row, unsigned int col)
        {
            return _baseTapStateProvider->get_has_base_chord_action_been_performed(row,col);
        }

        //IBaseTapStateSetter
        void set_start_key_press(unsigned int row, unsigned int col)
        {
            return _baseTapStateSetter->set_start_key_press(row,col);
        }
        void set_has_base_chord_action_performed(
            unsigned int row, unsigned int col, bool hasBaseChordActionBeenPerfomed)
        {
            return _baseTapStateSetter->set_has_base_chord_action_performed(
                row,col,hasBaseChordActionBeenPerfomed);
        }

    private:
        //Private Constants
        // NOTE: The left layer maps use the right shift because left shift is what is
        // pressed and released during the 'Keyboard.write()' calls. Thus firing unwanted
        // release events if the physical left shift key is held during that.
        const unsigned char BASE_KEYS[ROW_COUNT][COLUMN_COUNT] =
        {
            { KEY_LEFT_ALT, KEY_F1,  KEY_F2,  KEY_F3,  KEY_F4,  KEY_F5,  KC_LM1 },
            { KC_NULL,      KEY_F6,  KEY_F7,  KEY_F8,  KEY_F9,  KEY_F10, KC_LM2 },
            { KC_NULL,      KEY_F11, KEY_F12, KEY_F13, KEY_F14, KEY_F15, KEY_RIGHT_SHIFT },
        };

        //Private Variables
        IBaseTapStateProvider* _baseTapStateProvider;
        IBaseTapStateSetter* _baseTapStateSetter;
};

class LeftLayerInfoProvider : public IIndexedLayerInfoServiceProvider
{
    public:
        LayerInfoProvider() { }

        ILayerInfoService* get_layer_info_for_index(unsigned int layerIndex)
        {
            return _layerInfos[layerIndex];
        }

        void set_layer_info_for_index(unsigned int layerIndex, ILayerInfoService& layerInfo)
        {
            _layerInfos[layerIndex] = &layerInfo;
        }

    private:
        ILayerInfoService* _layerInfos[LAYER_COUNT];
};


//Main
SwitchMatrixManager* _matrixManager;

void setup()
{
    // Init serial output
    Serial.begin(TESTING_SERIAL_BAUD_RATE);
    // Wait for serial to boot up...
    delay(1000);
    Serial.println("Starting keyboard...");

    // Init logic managers
    if (IS_LEFT_KEYBOARD_SIDE)
    {
        LeftBaseTapStateContainer lBaseTapContainer;

        LeftLayerInfoProvider lLayerProvder;
        LeftLayerZeroInfo lZeroInfo(lBaseTapContainer, lBaseTapContainer);
        lLayerProvder.set_layer_info_for_index(0, lZeroInfo);

        KeyswitchPressHandler pressHandler(lLayerProvder);
        KeyswitchReleaseHandler releaseHandler(lLayerProvder);
        SwitchMatrixManager manager(pressHandler, releaseHandler);
        _matrixManager = &manager;
        Serial.println("Initializing Left Side.");
    }
    else
    {
        //TODO implement right side
        //LeftLayerInfoProvider lLayerProvder;
        //KeyswitchPressHandler pressHandler(lLayerProvder);
        //KeyswitchReleaseHandler releaseHandler(lLayerProvder);
        //SwitchMatrixManager manager(pressHandler, releaseHandler);
        //_matrixManager = &manager;
        //Serial.println("Initializing Left Side.");
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

void loop()
{
    delay(LOOP_DELAY_TIME);
    _matrixManager->iterate();
}

