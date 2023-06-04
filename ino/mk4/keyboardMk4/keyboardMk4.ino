//Imports
#include <Keyboard.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//CAUTION: Do not add any more imports to the mk3 code.
//This code has grown large enough to cause instability
//in the Pro Micro if much more is added. Do not add more
//codebases until the microcontroller for this project
//has been upgraded.

//Constants
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

const bool ENABLE_SERIAL_LOGGING = true;
const bool ENABLE_KEYBOARD_COMMANDS = false;
const bool SWITCH_TESTING_MODE = true;

const bool IS_LEFT_KEYBOARD_SIDE = true;

const int COLUMN_COUNT = 7;
const int ROW_COUNT = 3;

int RIGHT_SIDE_I2C_ADDRESS = 0x45;
//Note: The Wire library has a cap of 32 bytes per transmission.
const int I2C_TRANSMISSION_BYTE_COUNT = COLUMN_COUNT*ROW_COUNT;

const int TESTING_SERIAL_BAUD_RATE = 115200;
const int LOOP_DELAY_TIME = 1000;

const byte SWITCH_PRESSED_VALUE = 0;
const byte SWITCH_NOT_PRESSED_VALUE = 1;

const unsigned long DEFAULT_TAP_ACTION_TIMEOUT = 200;
const unsigned long DEFAULT_BASE_APPLY_DELAY = 50;

const int LAYER_COUNT = 3;

const byte ROW_0_PIN = IS_LEFT_KEYBOARD_SIDE ? 22 : 14;
const byte ROW_1_PIN = IS_LEFT_KEYBOARD_SIDE ? 11 : 15;
const byte ROW_2_PIN = IS_LEFT_KEYBOARD_SIDE ? 12 : 16;

const byte COL_0_PIN = IS_LEFT_KEYBOARD_SIDE ? 2 : 27;
const byte COL_1_PIN = IS_LEFT_KEYBOARD_SIDE ? 6 : 26;
const byte COL_2_PIN = IS_LEFT_KEYBOARD_SIDE ? 8 : 25;
const byte COL_3_PIN = IS_LEFT_KEYBOARD_SIDE ? 14 : 24;
const byte COL_4_PIN = IS_LEFT_KEYBOARD_SIDE ? 16 : 22;
const byte COL_5_PIN = IS_LEFT_KEYBOARD_SIDE ? 18 : 21;
const byte COL_6_PIN = IS_LEFT_KEYBOARD_SIDE ? 20 : 20;

const byte ROWS[ROW_COUNT] = { ROW_0_PIN, ROW_1_PIN, ROW_2_PIN };
const byte COLS[COLUMN_COUNT] = { COL_0_PIN, COL_1_PIN, COL_2_PIN, COL_3_PIN, COL_4_PIN, COL_5_PIN, COL_6_PIN };

#define KC_NULL 0x00
#define KC_LM1 0x01 //(STX) //Repurposing obsolete ascii codes for our custom codes
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
    { KEY_LEFT_ALT, KEY_F1,   KEY_F4,  KEY_F7,  KEY_F10,  KEY_F13,  KC_LM1 },
    { KC_NULL,      KEY_F2,   KEY_F5,  KEY_F8,  KEY_F11,  KEY_F14,  KC_LM2 },
    { KC_NULL,      KEY_F3,   KEY_F6,  KEY_F9,  KEY_F12,  KEY_F15,  KEY_RIGHT_SHIFT },
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
    { KC_NULL,       KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KEY_RETURN },
    { KEY_BACKSPACE, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL },
    { KC_NULL,       KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL, KC_NULL },
};

//Interfaces
class IBaseKeymap
{
    public:
        virtual unsigned char get_base_keycode_at(unsigned int row, unsigned int col) = 0;
};

class IKeyboardStateContainer
{
    public:
        //Getters
        virtual bool get_is_lm1_pressed() = 0;
        virtual bool get_is_lm2_pressed() = 0;
        virtual bool get_is_alt_pressed() = 0;
        virtual bool get_is_gui_pressed() = 0;
        virtual bool get_is_ctrl_pressed() = 0;
        virtual bool get_is_shift_pressed() = 0;
        virtual unsigned int get_current_layer() = 0;
        virtual bool get_has_chord_action_been_performed() = 0;

        //Setters
        virtual void set_is_lm1_pressed(bool isLm1Pressed) = 0;
        virtual void set_is_lm2_pressed(bool isLm2Pressed) = 0;
        virtual void set_is_alt_pressed(bool isAltPressed) = 0;
        virtual void set_is_gui_pressed(bool isGuiPressed) = 0;
        virtual void set_is_ctrl_pressed(bool isCtrlPressed) = 0;
        virtual void set_is_shift_pressed(bool isShiftPressed) = 0;
        virtual void set_has_chord_action_been_performed(bool chordActionPeformed) = 0;
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

class ISwitchStateProvider
{
    public:
        virtual bool get_is_switch_currently_pressed(unsigned int row, unsigned int col) = 0;
        virtual bool get_was_switch_previous_pressed(unsigned int row, unsigned int col) = 0;
};

class IUpdatableSwitchStateProvider : public ISwitchStateProvider
{
    public:
        virtual void update() = 0;
};

//Helpers
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
        KeyboardHelper() { }
};

class SwitchStateHelper
{
    public:
        static void copy_matrix_state_to_prev(
            byte (&currMatrix)[ROW_COUNT][COLUMN_COUNT], byte (&prevMatrix)[ROW_COUNT][COLUMN_COUNT])
        {
            for (int i = 0; i < ROW_COUNT; i++)
            {
                for (int j = 0; j < COLUMN_COUNT; j++)
                {
                    prevMatrix[i][j] = currMatrix[i][j];
                }
            }
        }

        static void print_matrices_to_serial_out(ISwitchStateProvider* leftProvider, ISwitchStateProvider* rightProvider)
        {
            for (int i = 0; i < ROW_COUNT; i++)
            {
                String leftRowStr = SwitchStateHelper::get_row_string(leftProvider, i);
                String rightRowStr = SwitchStateHelper::get_row_string(rightProvider, i);
                Serial.println(String(leftRowStr+" | "+rightRowStr));
            }
        }

        static void print_matrix_to_serial_out(ISwitchStateProvider* switchStateProvider)
        {
            for (int row = 0; row < ROW_COUNT; row++)
            {
                Serial.println(get_row_string(switchStateProvider, row));
                delay(5);
            }
        }

        static String get_row_string(ISwitchStateProvider* switchStateProvider, int rowIndex)
        {
            // print row label
            String rowStr = "0"+String(rowIndex)+": ";

            // get byte vals
            for (int col = 0; col < COLUMN_COUNT; col++)
            {
                rowStr += String(switchStateProvider->get_is_switch_currently_pressed(rowIndex,col)
                    ? SWITCH_PRESSED_VALUE : SWITCH_NOT_PRESSED_VALUE)+", ";
            }

            return rowStr;
        }

    private:
        SwitchStateHelper() { }
};

//Classes
class KeyboardLayoutStateContainer : public IKeyboardStateContainer
{
    public:
        KeyboardLayoutStateContainer()
        {
            _quant_lm1_pressed = 0;
            _quant_lm2_pressed = 0;
            _lastLayerPressed = 0;
            _quant_alt_pressed = 0;
            _quant_gui_pressed = 0;
            _quant_ctrl_pressed = 0;
            _quant_shift_pressed = 0;
        }

        //Get Methods
        bool get_is_lm1_pressed()
        {
            return _quant_lm1_pressed > 0;
        }

        bool get_is_lm2_pressed()
        {
            return _quant_lm2_pressed > 0;
        }

        bool get_is_alt_pressed()
        {
            return _quant_alt_pressed > 0;
        }

        bool get_is_gui_pressed()
        {
            return _quant_gui_pressed > 0;
        }

        bool get_is_ctrl_pressed()
        {
            return _quant_ctrl_pressed > 0;
        }

        bool get_is_shift_pressed()
        {
            return _quant_shift_pressed > 0;
        }

        unsigned int get_current_layer()
        {
            if (get_is_lm1_pressed() && get_is_lm2_pressed())
                return _lastLayerPressed;
            if (get_is_lm2_pressed())
                return 2;
            if (get_is_lm1_pressed())
                return 1;
            return 0;
        }

        bool get_has_chord_action_been_performed()
        {
            return _chordActionPeformed;
        }

        //Set Methods
        void set_is_lm1_pressed(bool isLm1Pressed)
        {
            if (isLm1Pressed)
            {
                _quant_lm1_pressed++;
                _lastLayerPressed = 1;
            }
            else
            {
                _quant_lm1_pressed = max(_quant_lm1_pressed-1, 0);
            }
        }

        void set_is_lm2_pressed(bool isLm2Pressed)
        {
            if (isLm2Pressed)
            {
                _quant_lm2_pressed++;
                _lastLayerPressed = 2;
            }
            else
            {
                _quant_lm2_pressed = max(_quant_lm2_pressed-1, 0);
            }
        }

        void set_is_alt_pressed(bool isAltPressed)
        {
            if (isAltPressed)
                _quant_alt_pressed++;
            else
                _quant_alt_pressed = max(_quant_alt_pressed-1, 0);
        }

        void set_is_gui_pressed(bool isGuiPressed)
        {
            if (isGuiPressed)
                _quant_gui_pressed++;
            else
                _quant_gui_pressed = max(_quant_gui_pressed-1, 0);
        }

        void set_is_ctrl_pressed(bool isCtrlPressed)
        {
            if (isCtrlPressed)
                _quant_ctrl_pressed++;
            else
                _quant_ctrl_pressed = max(_quant_ctrl_pressed-1, 0);
        }

        void set_is_shift_pressed(bool isShiftPressed)
        {
            if (isShiftPressed)
                _quant_shift_pressed++;
            else
                _quant_shift_pressed = max(_quant_shift_pressed-1, 0);
        }

        void set_has_chord_action_been_performed(bool chordActionPeformed)
        {
            _chordActionPeformed = chordActionPeformed;
        }

    private:
        unsigned int _quant_lm1_pressed = 0;
        unsigned int _quant_lm2_pressed = 0;
        unsigned int _quant_alt_pressed = 0;
        unsigned int _quant_gui_pressed = 0;
        unsigned int _quant_ctrl_pressed = 0;
        unsigned int _quant_shift_pressed = 0;
        unsigned int _lastLayerPressed = 0;
        bool _chordActionPeformed;
};

class BaseTapStateContainer : public IBaseTapStateProvider, public IBaseTapStateSetter
{
    public:
        BaseTapStateContainer(
            const unsigned char (&tapLayer)[ROW_COUNT][COLUMN_COUNT],
            IKeyboardStateContainer& keyboardStateContainer)
        {
            _tapLayerKeys = &tapLayer;
            _fullKeyboardStateContainer = &keyboardStateContainer;
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
            return _fullKeyboardStateContainer->get_has_chord_action_been_performed();
        }

        //IBaseTapStateSetter
        void set_start_key_press(unsigned int row, unsigned int col)
        {
            _fullKeyboardStateContainer->set_has_chord_action_been_performed(false);
            _pressStart[row][col] = millis();
        }
        void notify_chord_action_performed()
        {
            _fullKeyboardStateContainer->set_has_chord_action_been_performed(true);
        }

    private:
        //Private Variables
        const unsigned char (*_tapLayerKeys)[ROW_COUNT][COLUMN_COUNT];
        IKeyboardStateContainer* _fullKeyboardStateContainer;

        //TODO this could be space optimized. It's fairly greedy.
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
        const unsigned char (*_baseKeys)[ROW_COUNT][COLUMN_COUNT];
};

class KeyswitchPressHandler : public IKeyswitchPressedHandler
{
    public:
        KeyswitchPressHandler(LayerInfoContainer (&layerArray)[LAYER_COUNT],
            IKeyboardStateContainer& keyboardStateContainer)
        {
            _layerArray = &layerArray;
            _keyboardStateContainer = &keyboardStateContainer;
        }

        void handle_switch_press(unsigned int row, unsigned int col)
        {
            KeyboardHelper::try_log("R:"+String(row)+"C:"+String(col)+", "+String("pressed"));
            unsigned int currentLayer = _keyboardStateContainer->get_current_layer();
            LayerInfoContainer& layerInfo = (*_layerArray)[currentLayer];
            unsigned char keycode = layerInfo.get_base_keycode_at(row,col);
            KeyboardHelper::try_log("Keycode:"+String(keycode)+" on layer:"+String(currentLayer));

            if (layerInfo.get_is_base_tap_enabled_key(row,col))
            {
                KeyboardHelper::try_log("Starting down timer on R:"+String(row)+"C:"+String(col));
                layerInfo.set_start_key_press(row,col);
            }
            else
            {
                // TODO I worry this might cause bugs with chords only involving tap enabled keys.
                KeyboardHelper::try_log("Notifying chord action performed");
                layerInfo.notify_chord_action_performed();
            }

            bool shouldSendPressCode = true;
            switch (keycode)
            {
                case KC_LM1:
                    shouldSendPressCode = false;
                    _keyboardStateContainer->set_is_lm1_pressed(true);
                    KeyboardHelper::try_log("Entering layer 1");
                    break;
                case KC_LM2:
                    shouldSendPressCode = false;
                    _keyboardStateContainer->set_is_lm2_pressed(true);
                    KeyboardHelper::try_log("Entering layer 2");
                    break;
                case KC_REPEAT:
                    shouldSendPressCode = false;
                    KeyboardHelper::try_log("Repeating last instruction:");
                    break;
                case KC_NULL:
                    // Do nothing if we hit the null keycode.
                    shouldSendPressCode = false;
                    KeyboardHelper::try_log("Declining to send null keycode.");
                    break;
                case KEY_LEFT_ALT:
                case KEY_RIGHT_ALT:
                    _keyboardStateContainer->set_is_alt_pressed(true);
                    KeyboardHelper::try_log("Alt physically pressed.");
                    break;
                case KEY_LEFT_GUI:
                case KEY_RIGHT_GUI:
                    _keyboardStateContainer->set_is_gui_pressed(true);
                    KeyboardHelper::try_log("Gui physically pressed.");
                    break;
                case KEY_LEFT_CTRL:
                case KEY_RIGHT_CTRL:
                    _keyboardStateContainer->set_is_ctrl_pressed(true);
                    KeyboardHelper::try_log("Ctrl physically pressed.");
                    break;
                case KEY_LEFT_SHIFT:
                case KEY_RIGHT_SHIFT:
                    _keyboardStateContainer->set_is_shift_pressed(true);
                    KeyboardHelper::try_log("Shift physically pressed.");
                    break;
            }

            if (ENABLE_KEYBOARD_COMMANDS && shouldSendPressCode)
            {
                KeyboardHelper::try_log("Sending press of keycode: "+String(keycode));
                Keyboard.press(keycode);
            }
        }

    private:
        LayerInfoContainer (*_layerArray)[LAYER_COUNT];
        IKeyboardStateContainer* _keyboardStateContainer;
};

class KeyswitchReleaseHandler : public IKeyswitchReleasedHandler
{
    public:
        KeyswitchReleaseHandler(LayerInfoContainer (&layerArray)[LAYER_COUNT],
            KeyboardLayoutStateContainer& keyboardStateContainer)
        {
            _layerArray = &layerArray;
            _keyboardStateContainer = &keyboardStateContainer;
        }

        void handle_switch_release(unsigned int row, unsigned int col)
        {
            KeyboardHelper::try_log("R:"+String(row)+"C:"+String(col)+", "+String("released"));
            KeyboardLayoutStateContainer& keyboardStateContainer = *_keyboardStateContainer;
            unsigned int currentLayer = keyboardStateContainer.get_current_layer();
            LayerInfoContainer& layerInfo = (*_layerArray)[currentLayer];
            unsigned char keycode = layerInfo.get_base_keycode_at(row,col);
            KeyboardHelper::try_log("Keycode:"+String(keycode)+" on layer:"+String(currentLayer));

            bool shouldSendReleaseCodes = true;
            switch (keycode)
            {
                case KC_LM1:
                    shouldSendReleaseCodes = false;
                    keyboardStateContainer.set_is_lm1_pressed(false);
                    KeyboardHelper::try_log("Layer 1 physically released.");
                    break;
                case KC_LM2:
                    shouldSendReleaseCodes = false;
                    keyboardStateContainer.set_is_lm2_pressed(false);
                    KeyboardHelper::try_log("Layer 2 physically released.");
                    break;
                case KC_REPEAT:
                case KC_NULL:
                    shouldSendReleaseCodes = false;
                    // Do nothing if we hit the null keycode.
                    KeyboardHelper::try_log("Released a key where no action was required.");
                    break;
                case KEY_LEFT_ALT:
                case KEY_RIGHT_ALT:
                    keyboardStateContainer.set_is_alt_pressed(false);
                    KeyboardHelper::try_log("Alt physically released.");
                    break;
                case KEY_LEFT_GUI:
                case KEY_RIGHT_GUI:
                    keyboardStateContainer.set_is_gui_pressed(false);
                    KeyboardHelper::try_log("Gui physically released.");
                    break;
                case KEY_LEFT_CTRL:
                case KEY_RIGHT_CTRL:
                    keyboardStateContainer.set_is_ctrl_pressed(false);
                    KeyboardHelper::try_log("Ctrl physically released.");
                    break;
                case KEY_LEFT_SHIFT:
                case KEY_RIGHT_SHIFT:
                    keyboardStateContainer.set_is_shift_pressed(false);
                    KeyboardHelper::try_log("Shift physically released.");
                    break;
            }

            if(ENABLE_KEYBOARD_COMMANDS && shouldSendReleaseCodes)
            {
                for (int i = 0; i < LAYER_COUNT; i++)
                {
                    // Release all keycodes at this location across all layers.
                    LayerInfoContainer& layerInfoAtIndex = (*_layerArray)[i];
                    unsigned char keycodeOnLayer = layerInfoAtIndex.get_base_keycode_at(row,col);
                    // Don't release duplicate keys we keep state for, if applicable.
                    switch (keycodeOnLayer)
                    {
                        //Note: This case is here because we duplicate right shift on both
                        //halves and we don't want the release firing if it's still physically down.
                        case KEY_RIGHT_SHIFT:
                            if (keyboardStateContainer.get_is_shift_pressed())
                                continue;
                            break;
                    }
                    KeyboardHelper::try_log("Sending release of keycode: "+String(keycodeOnLayer));
                    Keyboard.release(keycodeOnLayer);
                }
            }

            // Now that any mod/base actions have been released on this key, fire the
            // tap event, if applicable.
            // NOTE: If we want to make separate tap events for each layer, the starting
            // layer will need to be recorded somewhere on key down.
            if (layerInfo.get_is_base_tap_enabled_key(row,col))
            {
                if(!layerInfo.get_has_tap_timed_out(row,col)
                    && !layerInfo.get_has_chord_action_been_performed())
                {
                    unsigned char tapKeycode = layerInfo.get_tap_keycode_at(row,col);
                    KeyboardHelper::try_log("Sending tap of keycode: "+String(tapKeycode));
                    if (ENABLE_KEYBOARD_COMMANDS)
                        Keyboard.write(tapKeycode);
                }
                else
                    KeyboardHelper::try_log("Tap action has timed out.");
            }
        }

    private:
        LayerInfoContainer (*_layerArray)[LAYER_COUNT];
        KeyboardLayoutStateContainer* _keyboardStateContainer;
};

class NativeSwitchStateProvider : public IUpdatableSwitchStateProvider
{
    public:
        NativeSwitchStateProvider()
        {
            //This is called to set intitial values before an external
            //entity begins querying for state.
            update();
        }

        void update()
        {
            SwitchStateHelper::copy_matrix_state_to_prev(_switchMatrix, _switchMatrixPrev);
            read_matrix();
        }

        bool get_is_switch_currently_pressed(unsigned int row, unsigned int col)
        {
            return _switchMatrix[row][col] == 0;
        }

        bool get_was_switch_previous_pressed(unsigned int row, unsigned int col)
        {
            return _switchMatrixPrev[row][col] == 0;
        }

    private:
        byte _switchMatrix[ROW_COUNT][COLUMN_COUNT] = {0};
        byte _switchMatrixPrev[ROW_COUNT][COLUMN_COUNT] = {0};

        void read_matrix()
        {
            for (int row = 0; row < ROW_COUNT; row++)
            {
                // Pull the row pins LOW. With the INPUT_PULLUP cols high and the diodes pointed
                // toward the rows, we will allow current to flow from Col->Row.
                byte curRow = ROWS[row];
                pinMode(curRow, OUTPUT);
                digitalWrite(curRow, LOW);

                for (int col = 0; col < COLUMN_COUNT; col++)
                {
                    byte currCol = COLS[col];
                    // Attempt connection to the pullup resistor (pulled to high/up) that should already be set.
                    // Should read zero if switch is pressed.
                    _switchMatrix[row][col] = digitalRead(currCol);
                }

                // Disable the row output
                pinMode(curRow, INPUT);
            }
        }
};

class I2cSwitchStateProvider : public IUpdatableSwitchStateProvider
{
    public:
        I2cSwitchStateProvider(void (*updateSwitchStateFuncPtr)())
        {
            stateUpdateFuncPtr = updateSwitchStateFuncPtr;
        }

        void update()
        {
            SwitchStateHelper::copy_matrix_state_to_prev(_switchMatrix, _switchMatrixPrev);
            // Call our external update method. Wire crashes inside object context.
            (*stateUpdateFuncPtr)();
        }

        bool get_is_switch_currently_pressed(unsigned int row, unsigned int col)
        {
            return _switchMatrix[row][col] == 0;
        }

        bool get_was_switch_previous_pressed(unsigned int row, unsigned int col)
        {
            return _switchMatrixPrev[row][col] == 0;
        }

        //Note:Only intended to be called by the main loop.
        void set_is_switch_currently_pressed(unsigned int row, unsigned int col, byte value)
        {
            _switchMatrix[row][col] = value;
        }

    private:
        void (*stateUpdateFuncPtr)();
        //These arrays are created like this to avoid firing all the release events upon
        //first update after construction since the switch state source is not availble
        //when the constructor is called.
        byte _switchMatrix[ROW_COUNT][COLUMN_COUNT] =
        {
            { SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE },
            { SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE },
            { SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE }
        };
        byte _switchMatrixPrev[ROW_COUNT][COLUMN_COUNT] =
        {
            { SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE },
            { SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE },
            { SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE, SWITCH_NOT_PRESSED_VALUE }
        };
};

class SwitchMatrixManager : public ISwitchStateProvider
{
    public:
        //Constructor
        SwitchMatrixManager(IUpdatableSwitchStateProvider &switchStateProvider,
            IKeyswitchPressedHandler& pressHandler, IKeyswitchReleasedHandler& releaseHandler,
            bool printSwitchTestingOutput)
        {
            _switchStateProvider = &switchStateProvider;
            _pressHandler = &pressHandler;
            _releaseHandler = &releaseHandler;
            _printSwitchTestingOutput = printSwitchTestingOutput;
        }

        //Public Methods
        void iterate()
        {
            _switchStateProvider->update();

            if (SWITCH_TESTING_MODE && _printSwitchTestingOutput)
            {
                SwitchStateHelper::print_matrix_to_serial_out(_switchStateProvider);
            }
            else
            {
                handle_switch_state_changes();
            }
        }

        bool get_is_switch_currently_pressed(unsigned int row, unsigned int col)
        {
            return _switchStateProvider->get_is_switch_currently_pressed(row, col);
        }

        bool get_was_switch_previous_pressed(unsigned int row, unsigned int col)
        {
            return _switchStateProvider->get_was_switch_previous_pressed(row, col);
        }

    private:
        //Private Variables
        IUpdatableSwitchStateProvider* _switchStateProvider;
        IKeyswitchPressedHandler* _pressHandler;
        IKeyswitchReleasedHandler* _releaseHandler;
        bool _printSwitchTestingOutput;

        //Private Methods
        void handle_switch_state_changes()
        {
            for (int i = 0; i < ROW_COUNT; i++)
            {
                for (int j = 0; j < COLUMN_COUNT; j++)
                {
                    bool switchCurrPress = _switchStateProvider->get_is_switch_currently_pressed(i,j);
                    bool switchPrevPress = _switchStateProvider->get_was_switch_previous_pressed(i,j);
                    // If the swich changed state..
                    if (switchCurrPress != switchPrevPress)
                    {
                        if (switchCurrPress == true && switchPrevPress == false)
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
};

//Global Variables
//Left Controller Variables
//Build the state container that will serve the entire keyboard.
KeyboardLayoutStateContainer _keyboardStateContainer;

//Create the left layer shared tap state container.
BaseTapStateContainer _leftBaseTapContainer(L_TAP_KEYS, _keyboardStateContainer);

//Collate the left layers
LayerInfoContainer _leftLayers[LAYER_COUNT] =
{
    LayerInfoContainer(L0_BASE_KEYCODES, _leftBaseTapContainer, _leftBaseTapContainer),
    LayerInfoContainer(L1_BASE_KEYCODES, _leftBaseTapContainer, _leftBaseTapContainer),
    LayerInfoContainer(L2_BASE_KEYCODES, _leftBaseTapContainer, _leftBaseTapContainer)
};

//Create the right layer shared tap state container.
BaseTapStateContainer _rightBaseTapContainer(R_TAP_KEYS, _keyboardStateContainer);

//Collate the right layers
LayerInfoContainer _rightLayers[LAYER_COUNT] =
{
    LayerInfoContainer(R0_BASE_KEYCODES, _rightBaseTapContainer, _rightBaseTapContainer),
    LayerInfoContainer(R1_BASE_KEYCODES, _rightBaseTapContainer, _rightBaseTapContainer),
    LayerInfoContainer(R2_BASE_KEYCODES, _rightBaseTapContainer, _rightBaseTapContainer),
};

//Build left press handlers and manager.
KeyswitchPressHandler _leftPressHandler(_leftLayers, _keyboardStateContainer);
KeyswitchReleaseHandler _leftReleaseHandler(_leftLayers, _keyboardStateContainer);
NativeSwitchStateProvider _leftSwitchStateProvider;
SwitchMatrixManager _leftSwitchManager(_leftSwitchStateProvider, _leftPressHandler, _leftReleaseHandler, false);

//Build right press handlers and manager.
KeyswitchPressHandler _rightPressHandler(_rightLayers, _keyboardStateContainer);
KeyswitchReleaseHandler _rightReleaseHandler(_rightLayers, _keyboardStateContainer);
void (*i2cUpdateFuncPtr)(){ update_i2c_switch_state_provider };
I2cSwitchStateProvider _rightSwitchStateProvider(i2cUpdateFuncPtr);
SwitchMatrixManager _rightSwitchManager(_rightSwitchStateProvider, _rightPressHandler, _rightReleaseHandler, false);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Right Controller Variables
NativeSwitchStateProvider _peripheralSwitchStateProvider;

//Main
void setup()
{
    // Init serial output
    Serial.begin(TESTING_SERIAL_BAUD_RATE);
    // Wait for serial to boot up...
    delay(3000);
    KeyboardHelper::try_log("Starting keyboard...");

    // Init logic managers
    int initDelay = 20;
    if (IS_LEFT_KEYBOARD_SIDE)
    {
        KeyboardHelper::try_log("Initializing Left Side.");

        //Join I2C bus as a controller.
        Wire.begin();
        KeyboardHelper::try_log("Joining I2C bus as controller.");
            delay(initDelay);

        bool displayInitSuccess = display.begin(
            SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS, true, false);
        KeyboardHelper::try_log(String("Display initialization success: "+String(displayInitSuccess)));
            delay(1000);

        display.clearDisplay();
        display.setTextSize(2);             // Draw 2X-scale text
        display.setTextColor(SSD1306_WHITE);
        display.println(F("VOK-SL"));
        display.println(F("MkII"));
        display.display();

        KeyboardHelper::try_log("Left side initialization complete.");
    }
    else
    {
        KeyboardHelper::try_log("Initializing Right Side.");

        //Join I2C bus as a transmitter.
        Wire.begin(RIGHT_SIDE_I2C_ADDRESS);
        KeyboardHelper::try_log("Joining I2C bus with address: "+String(RIGHT_SIDE_I2C_ADDRESS));
            delay(initDelay);

        Wire.onRequest(transmit_peripheral_matrix);
            delay(initDelay);

        KeyboardHelper::try_log("Right side initialization complete.");
    }

    // Init default pin modes;
    for(int i = 0; i < ROW_COUNT; i++)
    {
        pinMode(ROWS[i], INPUT);
        delay(5);
    }
    for (int i = 0; i < COLUMN_COUNT; i++)
    {
        // Columns should init to HIGH via INPUT_PULLUP. The Pico seems fine
        // leaving this state on for long periods.
        pinMode(COLS[i], INPUT_PULLUP);
        delay(5);
    }
}

void loop()
{
    delay(LOOP_DELAY_TIME);

    if (IS_LEFT_KEYBOARD_SIDE)
    {
        //USB connection side logic
        //KeyboardHelper::try_log("Iterating right side...");
        _rightSwitchManager.iterate();
        //KeyboardHelper::try_log("Right iteration complete!");
        //KeyboardHelper::try_log("Iterating left side...");
        _leftSwitchManager.iterate();
        //KeyboardHelper::try_log("Left iteration complete!");

        if (SWITCH_TESTING_MODE)
            SwitchStateHelper::print_matrices_to_serial_out(&_leftSwitchStateProvider, &_rightSwitchStateProvider);
    }
    else
    {
        //Peripheral over TRRS side logic
        if (SWITCH_TESTING_MODE)
        {
             _peripheralSwitchStateProvider.update();
            SwitchStateHelper::print_matrix_to_serial_out(&_peripheralSwitchStateProvider);
        }
    }

}

//Global Methods
void update_i2c_switch_state_provider()
{
    //NOTE:This method is run outside of the state provider as Wire
    //seems to crash inside of an object.
    byte bytesAvaible = Wire.requestFrom(RIGHT_SIDE_I2C_ADDRESS, I2C_TRANSMISSION_BYTE_COUNT);
    //KeyboardHelper::try_log("Sent request for matrix state...");
    int byteIndex = 0;
    //bool loggedResponse = false;
    //KeyboardHelper::try_log(String("There are "+String(bytesAvaible)+" bytes available..."));
    while (Wire.available())
    {
        //if (!loggedResponse)
        //{
        //    KeyboardHelper::try_log("Made connection with right half!");
        //    loggedResponse = true;
        //}
        _rightSwitchStateProvider.set_is_switch_currently_pressed(
            byteIndex/COLUMN_COUNT, byteIndex%COLUMN_COUNT, Wire.read());

        byteIndex++;
    }
    //KeyboardHelper::try_log(String("Completed right matrix state request with "+String(byteIndex)+" bytes."));
}

void transmit_peripheral_matrix()
{
    KeyboardHelper::try_log("Received request for matrix state!");
    _peripheralSwitchStateProvider.update();
    int byteIndex = 0;
    byte transmissionArray[I2C_TRANSMISSION_BYTE_COUNT];
    for (int i = 0; i < ROW_COUNT; i++)
    {
        for (int j = 0; j < COLUMN_COUNT; j++)
        {
            bool isSwitchPressed = _peripheralSwitchStateProvider.get_is_switch_currently_pressed(i, j);
            transmissionArray[byteIndex]
                = isSwitchPressed ? SWITCH_PRESSED_VALUE : SWITCH_NOT_PRESSED_VALUE;
            byteIndex++;
        }
    }
    Wire.write(transmissionArray, byteIndex);
    KeyboardHelper::try_log(String("Transmitted "+String(byteIndex)+ " matrix bytes"));
}
