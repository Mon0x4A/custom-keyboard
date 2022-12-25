//Imports
#include "Keyboard.h"

//Constants
const int KEY_COLUMN_COUNT = 8;
const int KEY_ROW_COUNT = 6;

const byte ROW_0_PIN = 2;
const byte ROW_1_PIN = 3;
const byte ROW_2_PIN = 4;
const byte ROW_3_PIN = 5;
const byte ROW_4_PIN = 6;
const byte ROW_5_PIN = 7;

const byte COL_0_PIN = 8;
const byte COL_1_PIN = 9;
const byte COL_2_PIN = 10;
const byte COL_3_PIN = 16;
const byte COL_4_PIN = 14;
const byte COL_5_PIN = 15;
const byte COL_6_PIN = 18;
const byte COL_7_PIN = 19;

const byte ROWS[KEY_ROW_COUNT] = { ROW_0_PIN, ROW_1_PIN, ROW_2_PIN, ROW_3_PIN, ROW_4_PIN, ROW_5_PIN };
const byte COLS[KEY_COLUMN_COUNT] = { COL_0_PIN, COL_1_PIN, COL_2_PIN, COL_3_PIN, COL_4_PIN, COL_5_PIN, COL_6_PIN, COL_7_PIN };

const int LOOP_DELAY_TIME = 20;

const int TESTING_SERIAL_BAUD_RATE = 115200;

const bool SWITCH_TESTING_MODE = false;

#define KC_NULL 0x00

#define KEY_PRINT_SCREEN 0xCE

const char characterKeys[KEY_ROW_COUNT][KEY_COLUMN_COUNT] =
{
    // !- = spacer for 2u key
    // null = key without current function

    //  {  f7, f8,  f9,  f10,  f11,   f12,   pUp,  pDwn },
    //  {   7,  8,   9,   0,     -,     =,  bspc,    !- },
    //  {   u,  i,   o,   p,     [,     ],     \,   del },
    //  {   j,  k,   l,   ;,     ',   ent,    !-,  home },
    //  {   m,  ,,   .,   /,  shft,    !-,    up,   end },
    //  { spc, !-, alt,  os,  ctrl,  left,  down,  rght }

    { KEY_F7,   KEY_F8,          KEY_F9,         KEY_F10,           KEY_F11,          KEY_F12,       KEY_PAGE_UP,     KEY_PAGE_DOWN },
     {    '7',      '8',             '9',             '0',               '-',              '=',    KEY_BACKSPACE,           KC_NULL },
     {    'u',      'i',             'o',             'p',               '[',              ']',             '\\',        KEY_DELETE },
     {    'j',      'k',             'l',             ';',              '\'',       KEY_RETURN,          KC_NULL,          KEY_HOME },
     {    'm',      ',',             '.',             '/',   KEY_RIGHT_SHIFT,          KC_NULL,     KEY_UP_ARROW,           KEY_END },
     {    ' ',  KC_NULL,   KEY_RIGHT_ALT,   KEY_RIGHT_GUI,    KEY_RIGHT_CTRL,   KEY_LEFT_ARROW,   KEY_DOWN_ARROW,   KEY_RIGHT_ARROW }
};

//Fields
byte switchMatrix[KEY_ROW_COUNT][KEY_COLUMN_COUNT] = {0};
byte switchMatrixPrev[KEY_ROW_COUNT][KEY_COLUMN_COUNT] = {0};

//Setup
void setup()
{
    Serial.begin(TESTING_SERIAL_BAUD_RATE);

	for(int i = 0; i < KEY_ROW_COUNT; i++)
    {
		Serial.print(ROWS[i]);
		pinMode(ROWS[i], INPUT_PULLUP);
	}

	for (int i = 0; i < KEY_COLUMN_COUNT; i++)
    {
		Serial.print(COLS[i]);
		pinMode(COLS[i], INPUT);
	}
}

//Main
void loop()
{
    delay(LOOP_DELAY_TIME);

    copySwitchMatrixToPrev();

    readMatrix();

    if (SWITCH_TESTING_MODE)
    {
        printMatrixToSerialOut();
    }
    else
    {
        setKeyStates();
    }
}

//Methods
void readMatrix()
{
    for (int rowIndex=0; rowIndex < KEY_ROW_COUNT; rowIndex++)
    {
        // set the row to output low
        byte curRow = ROWS[rowIndex];
        pinMode(curRow, OUTPUT);
        digitalWrite(curRow, LOW);

        // iterate through the columns reading the value - should be zero if switch is pressed
        for (int colIndex=0; colIndex < KEY_COLUMN_COUNT; colIndex++)
        {
            byte rowCol = COLS[colIndex];
            pinMode(rowCol, INPUT_PULLUP);
            switchMatrix[rowIndex][colIndex] = digitalRead(rowCol);
            pinMode(rowCol, INPUT);
        }

        // disable the row, turn the pullup resistor off
        pinMode(curRow, INPUT);
    }
}

void setKeyStates()
{
    for (int i = 0; i < KEY_ROW_COUNT; i++)
    {
        for (int j = 0; j < KEY_COLUMN_COUNT; j++)
        {
            // If the swich changed state..
            if (switchMatrix[i][j] != switchMatrixPrev[i][j])
            {
                // If the switch has been pressed...
                if (switchMatrix[i][j] == 0 && switchMatrixPrev[i][j] == 1)
                {
                    Keyboard.press(characterKeys[i][j]);
                }
                // If the switch has been released...
                else
                {
                    Keyboard.release(characterKeys[i][j]);
                }
            }
        }
    }
}

void printMatrixToSerialOut()
{
    String matrixString = "";
    for (int rowIndex = 0; rowIndex < KEY_ROW_COUNT; rowIndex++)
    {
        if (rowIndex < 10) {
           matrixString += String("0");
        }
        matrixString += String(rowIndex);
        matrixString += String(": ");

        for (int colIndex = 0; colIndex < KEY_COLUMN_COUNT; colIndex++)
        {
            matrixString += String(switchMatrix[rowIndex][colIndex]);
            if (colIndex < KEY_COLUMN_COUNT)
                matrixString += String(", ");
        }
        matrixString += String("\n");
    }
    Serial.print(matrixString);
}

//Utility
void copySwitchMatrixToPrev()
{
    for (int i = 0; i < KEY_ROW_COUNT; i++)
    {
        for (int j = 0; j < KEY_COLUMN_COUNT; j++)
        {
            switchMatrixPrev[i][j] = switchMatrix[i][j];
        }
    }
}

