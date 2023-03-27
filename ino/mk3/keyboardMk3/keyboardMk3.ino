//Imports
#include "Keyboard.h"

//Constants
const bool ENABLE_LOGGING = true;
const bool SWITCH_TESTING_MODE = false;
const bool IS_LEFT_KEYBOARD_SIDE = true;

const int TESTING_SERIAL_BAUD_RATE = 115200;
const int LOOP_DELAY_TIME = 20;

const unsigned long DEFAULT_TAP_ACTION_TIMEOUT = 200;
const unsigned long DEFAULT_BASE_APPLY_DELAY = 50;

const int COLUMN_COUNT = 7;
const int ROW_COUNT = 3;

const int LAYER_COUNT = 3;

const byte ROW_0_PIN = IS_LEFT_KEYBOARD_SIDE ? 7 : 9;
const byte ROW_1_PIN = IS_LEFT_KEYBOARD_SIDE ? 9 : 8;
const byte ROW_2_PIN = IS_LEFT_KEYBOARD_SIDE ? 8 : 7;

const byte COL_0_PIN = IS_LEFT_KEYBOARD_SIDE ? A0 : 10;
const byte COL_1_PIN = IS_LEFT_KEYBOARD_SIDE ? A2 : 16;
const byte COL_2_PIN = IS_LEFT_KEYBOARD_SIDE ? 15 : 15;
const byte COL_3_PIN = IS_LEFT_KEYBOARD_SIDE ? 14 : 14;
const byte COL_4_PIN = IS_LEFT_KEYBOARD_SIDE ? 16 : A0;
const byte COL_5_PIN = IS_LEFT_KEYBOARD_SIDE ? 10 : A1;
const byte COL_6_PIN = IS_LEFT_KEYBOARD_SIDE ? A1 : A2;

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

class IKeyboardStateContainer
{
    public:
        virtual unsigned int get_current_layer() = 0;
        virtual void set_current_layer(unsigned int currentLayer) = 0;
};

//Classes
class KeyboardHelper
{
    public:
        static bool has_reached_time_threshold(unsigned long holdStart, unsigned long timeout)
        {
            return ((millis()-holdStart) >= timeout);
        }

        static void try_log(String message)
        {
            if (ENABLE_LOGGING)
            {
                Serial.println("> "+message);
                delay(5);
            }
        }

    private:
        KeyHelper() { }
};

class KeyboardLayoutStateContainer : public IKeyboardStateContainer
{
    public:
        KeyboardLayoutStateContainer()
        {
            _currentLayer = 0;
        }

        unsigned int get_current_layer()
        {
            return _currentLayer;
        }

        void set_current_layer(unsigned int currentLayer)
        {
            _currentLayer = currentLayer;
        }

    private:
        unsigned int _currentLayer;
};

class KeyswitchPressHandler : public IKeyswitchPressedHandler
{
    public:
        KeyswitchPressHandler(IIndexedLayerInfoServiceProvider& layerInfoProvider,
            IKeyboardStateContainer& keyboardStateContainer)
        {
            _layerInfoProvider = &layerInfoProvider;
            _keyboardStateContainer = &keyboardStateContainer;
        }

        void handle_switch_press(unsigned int row, unsigned int col)
        {
            KeyboardHelper::try_log("R:"+String(row)+"C:"+String(col)+", "+String("pressed"));
            unsigned int currentLayer = _keyboardStateContainer->get_current_layer();
            ILayerInfoService* layerInfo = _layerInfoProvider->get_layer_info_for_index(currentLayer);
            unsigned char keycode = layerInfo->get_base_keycode_at(row,col);
            KeyboardHelper::try_log("Keycode:"+String(keycode)+" on layer:"+String(currentLayer));

            switch (keycode)
            {
                case KC_LM1:
                    _keyboardStateContainer->set_current_layer(1);
                    KeyboardHelper::try_log("Entering layer 1");
                    break;
                case KC_LM2:
                    _keyboardStateContainer->set_current_layer(2);
                    KeyboardHelper::try_log("Entering layer 2");
                    break;
                case KC_REPEAT:
                    KeyboardHelper::try_log("Repeating last instruction:");
                    break;
                case KC_NULL:
                    // Do nothing if we hit the null keycode.
                    KeyboardHelper::try_log("Declining to send null keycode.");
                    break;
                default:
                    // We have no special keycode handling.
                    KeyboardHelper::try_log("Sending press of keycode: "+String(keycode));
                    //Keyboard.press(keycode);
                    break;
            }
        }

    private:
        IIndexedLayerInfoServiceProvider* _layerInfoProvider;
        IKeyboardStateContainer* _keyboardStateContainer;
};

class KeyswitchReleaseHandler : public IKeyswitchReleasedHandler
{
    public:
        KeyswitchReleaseHandler(IIndexedLayerInfoServiceProvider& layerInfoProvider,
            IKeyboardStateContainer& keyboardStateContainer)
        {
            _layerInfoProvider = &layerInfoProvider;
            _keyboardStateContainer = &keyboardStateContainer;
        }

        void handle_switch_release(unsigned int row, unsigned int col)
        {
            KeyboardHelper::try_log("R:"+String(row)+"C:"+String(col)+", "+String("released"));
            unsigned int currentLayer = _keyboardStateContainer->get_current_layer();
            ILayerInfoService* layerInfo = _layerInfoProvider->get_layer_info_for_index(currentLayer);
            unsigned char keycode = layerInfo->get_base_keycode_at(row,col);
            KeyboardHelper::try_log("Keycode:"+String(keycode)+" on layer:"+String(currentLayer));

            switch (keycode)
            {
                case KC_LM1:
                case KC_LM2:
                    _keyboardStateContainer->set_current_layer(0);
                    KeyboardHelper::try_log("Entering layer 0");
                    break;
                case KC_REPEAT:
                case KC_NULL:
                    // Do nothing if we hit the null keycode.
                    KeyboardHelper::try_log("Released a key where no action was required.");
                    break;
                default:
                    // We have no special keycode handling.
                    KeyboardHelper::try_log("Sending release of keycode: "+String(keycode));
                    //Keyboard.release(keycode);
                    break;
            }
        }

    private:
        IIndexedLayerInfoServiceProvider* _layerInfoProvider;
        IKeyboardStateContainer* _keyboardStateContainer;
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
                            _pressHandler->handle_switch_press(i,j);
                        }
                        else
                        {
                            // We released a key.
                            //TODO handle state call
                            _releaseHandler->handle_switch_release(i,j);
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
                    //KeyboardHelper::try_log("R:"+String(row)+"C:"+String(col)+", "+String(_switchMatrix[row][col]));
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
    KeyboardHelper::try_log("Starting keyboard...");

    // Init logic managers

    if (IS_LEFT_KEYBOARD_SIDE)
    {
        KeyboardHelper::try_log("Initializing Left Side.");
        //Create the shared tap state container.
        LeftBaseTapStateContainer lBaseTapContainer;
            delay(5);

        //Initialize the layers
        LeftLayerZeroInfo lZeroInfo(lBaseTapContainer, lBaseTapContainer);
            delay(5);
        LeftLayerOneInfo lOneInfo(lBaseTapContainer, lBaseTapContainer);
            delay(5);

        //Collate the layers
        LeftLayerInfoProvider layerInfoProvider;
            delay(5);
        layerInfoProvider.set_layer_info_for_index(0, lZeroInfo);
            delay(5);
        layerInfoProvider.set_layer_info_for_index(1, lOneInfo);
            delay(5);

        //Build generic handling classes with the left code.
        //For some reason this cannot be moved outside of the if
        //conditional due to unknown scoping issues. This block
        //can be shared once that is figured out.
        KeyboardLayoutStateContainer keyboardStateContainer;
            delay(5);
        KeyswitchPressHandler pressHandler(layerInfoProvider, keyboardStateContainer);
            delay(5);
        KeyswitchReleaseHandler releaseHandler(layerInfoProvider, keyboardStateContainer);
            delay(5);
        SwitchMatrixManager manager(pressHandler, releaseHandler);
            delay(5);
        _matrixManager = &manager;
            delay(5);
        KeyboardHelper::try_log("Left side initialization complete.");
    }
    else
    {
        //TODO implement right side
    }



    // Init default pin modes;
    for(int i = 0; i < ROW_COUNT; i++)
    {
        pinMode(ROWS[i], INPUT_PULLUP);
        delay(5);
    }
    for (int i = 0; i < COLUMN_COUNT; i++)
    {
        pinMode(COLS[i], INPUT);
        delay(5);
    }
}

void loop()
{
    delay(LOOP_DELAY_TIME);
    _matrixManager->iterate();
}

