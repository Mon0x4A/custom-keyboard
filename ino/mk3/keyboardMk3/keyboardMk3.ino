//Imports
#include "Keyboard.h"

//Constants
const bool ENABLE_SERIAL_LOGGING = false;
const bool ENABLE_KEYBOARD_COMMANDS = true;
const bool SWITCH_TESTING_MODE = false;

const bool IS_LEFT_KEYBOARD_SIDE = false;

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

// Layer Arrays
// NOTE: The left layer maps use the right shift because left shift is what is
// pressed and released during the 'Keyboard.write()' calls. Thus firing unwanted
// release events if the physical left shift key is held during that.
const unsigned char L0_BASE_KEYCODES[ROW_COUNT][COLUMN_COUNT] =
{
    { KEY_LEFT_CTRL, 'q', 'w', 'e', 'r', 't', KC_LM1 },
    { KC_NULL,       'a', 's', 'd', 'f', 'g', KC_LM2 },
    { KC_NULL,       'z', 'x', 'c', 'v', 'b', KEY_RIGHT_SHIFT },
};

const unsigned char L1_BASE_KEYCODES[ROW_COUNT][COLUMN_COUNT] =
{
    { KEY_LEFT_ALT, KEY_F1,  KEY_F2,  KEY_F3,  KEY_F4,  KEY_F5,  KC_LM1 },
    { KC_NULL,      KEY_F6,  KEY_F7,  KEY_F8,  KEY_F9,  KEY_F10, KC_LM2 },
    { KC_NULL,      KEY_F11, KEY_F12, KEY_F13, KEY_F14, KEY_F15, KEY_RIGHT_SHIFT },
};

const unsigned char L2_BASE_KEYCODES[ROW_COUNT][COLUMN_COUNT] =
{
    { KEY_LEFT_GUI, '`', '0', '1', '2', '3', KC_LM1 },
    { KC_NULL,      '@', '$', '4', '5', '6', KC_LM2 },
    { KC_NULL,      '<', '>', '7', '8', '9', KEY_RIGHT_SHIFT },
};

const unsigned char L_TAP_KEYS[ROW_COUNT][COLUMN_COUNT] =
{
    { KEY_ESC,  KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KEY_TAB },
    { KC_NULL,  KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, ' ' },
    { KC_NULL,  KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_REPEAT },
};

const unsigned char R0_BASE_KEYCODES[ROW_COUNT][COLUMN_COUNT] =
{
    { KC_LM1,          'y', 'u', 'i', 'o', 'p', KEY_RIGHT_CTRL },
    { KC_LM2,          'h', 'j', 'k', 'l', ';', KC_NULL },
    { KEY_RIGHT_SHIFT, 'n', 'm', ',', '.', '/', KC_NULL },
};

const unsigned char R1_BASE_KEYCODES[ROW_COUNT][COLUMN_COUNT] =
{
    { KC_LM1,          KEY_HOME,         KEY_PAGE_DOWN,  KEY_PAGE_UP,  KEY_END,         KEY_DELETE, KEY_RIGHT_ALT },
    { KC_LM2,          KEY_LEFT_ARROW,   KEY_DOWN_ARROW, KEY_UP_ARROW, KEY_RIGHT_ARROW, KC_NULL,    KC_NULL },
    { KEY_RIGHT_SHIFT, KEY_PRINT_SCREEN, KC_NULL,        KC_NULL,      KC_NULL,         KC_NULL,    KC_NULL },
};

const unsigned char R2_BASE_KEYCODES[ROW_COUNT][COLUMN_COUNT] =
{
    { KC_LM1,          '&', '*', '(', ')', '=',  KEY_RIGHT_GUI },
    { KC_LM2,          '-', '_', '{', '}', '\'', KC_NULL },
    { KEY_RIGHT_SHIFT, '+', '!', '[', ']', '\\', KC_NULL },
};

const unsigned char R_TAP_KEYS[ROW_COUNT][COLUMN_COUNT] =
{
    { KEY_RETURN,    KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL },
    { KEY_BACKSPACE, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL },
    { ':',           KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL },
};

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
        virtual unsigned char get_tap_keycode_at(unsigned int row, unsigned int col) = 0;

        virtual bool get_has_tap_timed_out(unsigned int row, unsigned int col) = 0;
        virtual bool get_has_base_timed_in(unsigned int row, unsigned int col) = 0;
        virtual bool get_has_chord_action_been_performed() = 0;
};

class IBaseTapStateSetter
{
    public:
        virtual void set_start_key_press(unsigned int row, unsigned int col) = 0;
        virtual void notify_chord_action_performed() = 0;
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
            if (ENABLE_SERIAL_LOGGING)
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

            if (layerInfo->get_is_base_tap_enabled_key(row,col))
            {
                KeyboardHelper::try_log("Starting down timer on R:"+String(row)+"C:"+String(col));
                layerInfo->set_start_key_press(row,col);
            }
            else
            {
                // TODO I worry this might cause bugs with chords only involving tap enabled keys.
                KeyboardHelper::try_log("Notifying chord action performed");
                layerInfo->notify_chord_action_performed();
            }

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
                    KeyboardHelper::try_log("Sending press of keycode: "+String(keycode));
                    if (ENABLE_KEYBOARD_COMMANDS)
                        Keyboard.press(keycode);
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
                    for (int i = 0; i < LAYER_COUNT; i++)
                    {
                        // Release all keycodes at this location across all layers.
                        ILayerInfoService* iLayerService = _layerInfoProvider->get_layer_info_for_index(i);
                        unsigned char keycodeOnLayer = iLayerService->get_base_keycode_at(row,col);
                        KeyboardHelper::try_log("Sending release of keycode: "+String(keycodeOnLayer));
                        if (ENABLE_KEYBOARD_COMMANDS)
                            Keyboard.release(keycodeOnLayer);
                    }
                    break;
            }

            // Now that any mod/base actions have been released on this key, fire the
            // tap event, if applicable.
            // NOTE: If we want to make separate tap events for each layer, the starting
            // layer will need to be recorded somewhere on key down.
            if (layerInfo->get_is_base_tap_enabled_key(row,col))
            {
                if(!layerInfo->get_has_tap_timed_out(row,col)
                    && !layerInfo->get_has_chord_action_been_performed())
                {
                    unsigned char tapKeycode = layerInfo->get_tap_keycode_at(row,col);
                    KeyboardHelper::try_log("Sending tap of keycode: "+String(tapKeycode));
                    if (ENABLE_KEYBOARD_COMMANDS)
                        Keyboard.write(tapKeycode);
                }
                else
                    KeyboardHelper::try_log("Tap action has timed out.");
            }
        }

    private:
        IIndexedLayerInfoServiceProvider* _layerInfoProvider;
        IKeyboardStateContainer* _keyboardStateContainer;
};

// For SOME reason these matrices can't be placed in SwitchMatrixManager
// because row zero bugs out like crazy. Still don't understand why yet.
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

            if (SWITCH_TESTING_MODE)
            {
                print_matrix_to_serial_out();
            }
            else
            {
                handle_switch_state_changes();
            }

            copy_matrix_state_to_prev();
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
                            _pressHandler->handle_switch_press(i,j);
                        }
                        else
                        {
                            // We released a key.
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

class BaseTapStateContainer : public IBaseTapStateProvider, public IBaseTapStateSetter
{
    public:
        BaseTapStateContainer(
            const unsigned char (&tapLayer)[ROW_COUNT][COLUMN_COUNT])
        {
            _tapLayerKeys = &tapLayer;
        }

        //IBaseTapStateProvider
        bool get_is_base_tap_enabled_key(unsigned int row, unsigned int col)
        {
            return ((*_tapLayerKeys)[row][col] != KC_NULL);
        }
        unsigned char get_tap_keycode_at(unsigned int row, unsigned int col)
        {
            return (*_tapLayerKeys)[row][col];
        }
        bool get_has_tap_timed_out(unsigned int row, unsigned int col)
        {
            return KeyboardHelper::has_reached_time_threshold(
                _pressStart[row][col], DEFAULT_TAP_ACTION_TIMEOUT);
        }
        bool get_has_base_timed_in(unsigned int row, unsigned int col)
        {
            return KeyboardHelper::has_reached_time_threshold(
                _pressStart[row][col], DEFAULT_BASE_APPLY_DELAY);
        }
        bool get_has_chord_action_been_performed()
        {
            return _chordPerformed;
        }

        //IBaseTapStateSetter
        void set_start_key_press(unsigned int row, unsigned int col)
        {
            //_chordPerformed[row][col] = false;
            _chordPerformed = false;
            _pressStart[row][col] = millis();
        }
        void notify_chord_action_performed()
        {
            _chordPerformed = true;
            //_chordPerformed[row][col] = true;
        }

    private:
        //Private Variables
        unsigned char (*_tapLayerKeys)[ROW_COUNT][COLUMN_COUNT];

        bool _chordPerformed;
        unsigned long _pressStart[ROW_COUNT][COLUMN_COUNT] = {0};
};

class LayerInfoContainer : public ILayerInfoService
{
    public:
        //Constructor
        LayerInfoContainer(
            const unsigned char (&baseKeymap)[ROW_COUNT][COLUMN_COUNT],
            IBaseTapStateProvider& tapStateProvider,
            IBaseTapStateSetter& tapStateSetter)
        {
            _baseKeys = &baseKeymap;
            _baseTapStateProvider = &tapStateProvider;
            _baseTapStateSetter = &tapStateSetter;
        }

        //Public Methods
        //IBaseKeymap
        unsigned char get_base_keycode_at(unsigned int row, unsigned int col)
        {
            return (*_baseKeys)[row][col];
        }

        //IBaseTapStateProvider
        bool get_is_base_tap_enabled_key(unsigned int row, unsigned int col)
        {
            return _baseTapStateProvider->get_is_base_tap_enabled_key(row,col);
        }
        unsigned char get_tap_keycode_at(unsigned int row, unsigned int col)
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
        bool get_has_chord_action_been_performed()
        {
            return _baseTapStateProvider->get_has_chord_action_been_performed();
        }

        //IBaseTapStateSetter
        void set_start_key_press(unsigned int row, unsigned int col)
        {
            return _baseTapStateSetter->set_start_key_press(row,col);
        }
        void notify_chord_action_performed()
        {
            _baseTapStateSetter->notify_chord_action_performed();
        }

    private:
        //Private Variables
        IBaseTapStateProvider* _baseTapStateProvider;
        IBaseTapStateSetter* _baseTapStateSetter;
        unsigned char (*_baseKeys)[ROW_COUNT][COLUMN_COUNT];
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
    int initDelay = 20;
    if (IS_LEFT_KEYBOARD_SIDE)
    {
        KeyboardHelper::try_log("Initializing Left Side.");
        //Create the shared tap state container.
        BaseTapStateContainer lBaseTapContainer(L_TAP_KEYS);
            delay(initDelay);

        //Initialize the layers
        LayerInfoContainer lZeroInfo(L0_BASE_KEYCODES, lBaseTapContainer, lBaseTapContainer);
            delay(initDelay);
        LayerInfoContainer lOneInfo(L1_BASE_KEYCODES, lBaseTapContainer, lBaseTapContainer);
            delay(initDelay);
        LayerInfoContainer lTwoInfo(L2_BASE_KEYCODES, lBaseTapContainer, lBaseTapContainer);
            delay(initDelay);

        //Collate the layers
        LeftLayerInfoProvider layerInfoProvider;
            delay(initDelay);
        layerInfoProvider.set_layer_info_for_index(0, lZeroInfo);
            delay(initDelay);
        layerInfoProvider.set_layer_info_for_index(1, lOneInfo);
            delay(initDelay);
        layerInfoProvider.set_layer_info_for_index(2, lTwoInfo);
            delay(initDelay);

        //Build generic handling classes with the left code.
        //For some reason this cannot be moved outside of the if
        //conditional due to unknown scoping issues. This block
        //can be shared once that is figured out.
        KeyboardLayoutStateContainer keyboardStateContainer;
            delay(initDelay);
        KeyswitchPressHandler pressHandler(layerInfoProvider, keyboardStateContainer);
            delay(initDelay);
        KeyswitchReleaseHandler releaseHandler(layerInfoProvider, keyboardStateContainer);
            delay(initDelay);
        SwitchMatrixManager manager(pressHandler, releaseHandler);
            delay(initDelay);
        _matrixManager = &manager;
            delay(initDelay);
        KeyboardHelper::try_log("Left side initialization complete.");
    }
    else
    {
        KeyboardHelper::try_log("Initializing Right Side.");
        //Create the shared tap state container.
        BaseTapStateContainer rBaseTapContainer(R_TAP_KEYS);
            delay(initDelay);

        //Initialize the layers
        LayerInfoContainer rZeroInfo(R0_BASE_KEYCODES, rBaseTapContainer, rBaseTapContainer);
            delay(initDelay);
        LayerInfoContainer rOneInfo(R1_BASE_KEYCODES, rBaseTapContainer, rBaseTapContainer);
            delay(initDelay);
        LayerInfoContainer rTwoInfo(R2_BASE_KEYCODES, rBaseTapContainer, rBaseTapContainer);
            delay(initDelay);

        //Collate the layers
        LeftLayerInfoProvider layerInfoProvider;
            delay(initDelay);
        layerInfoProvider.set_layer_info_for_index(0, rZeroInfo);
            delay(initDelay);
        layerInfoProvider.set_layer_info_for_index(1, rOneInfo);
            delay(initDelay);
        layerInfoProvider.set_layer_info_for_index(2, rTwoInfo);
            delay(initDelay);

        //Build generic handling classes with the left code.
        //For some reason this cannot be moved outside of the if
        //conditional due to unknown scoping issues. This block
        //can be shared once that is figured out.
        KeyboardLayoutStateContainer keyboardStateContainer;
            delay(initDelay);
        KeyswitchPressHandler pressHandler(layerInfoProvider, keyboardStateContainer);
            delay(initDelay);
        KeyswitchReleaseHandler releaseHandler(layerInfoProvider, keyboardStateContainer);
            delay(initDelay);
        SwitchMatrixManager manager(pressHandler, releaseHandler);
            delay(initDelay);
        _matrixManager = &manager;
            delay(initDelay);
        KeyboardHelper::try_log("Right side initialization complete.");
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

