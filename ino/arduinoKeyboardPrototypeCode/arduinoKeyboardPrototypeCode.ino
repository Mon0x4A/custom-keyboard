//File: Keyboard.ino
//Author: rcb5126
//Date: 10/9/2020
#include "Keyboard.h"

// define number of rows and colums and your corresponding keyboard pins
#define ROWS_COUNT 6
#define ROW0 2   // pin_d0
#define ROW1 3   // pin_d1
#define ROW2 4   // pin_d2
#define ROW3 5   // pin_d3
#define ROW4 6   // pin_d4
#define ROW5 7   // pin_d5

#define CAPSLOCK 6 // pin_d6

#define COLS_COUNT 8
#define COL0 8   // pin_d7
#define COL1 10   // pin_e0
#define COL2 9   // pin_e1
#define COL3 16  // pin_c0
#define COL4 14  // pin_c1
#define COL5 15  // pin_c2
#define COL6 18  // pin_c3
#define COL7 19  // pin_c4
// #define COL8 20  // pin_c5
// #define COL9 16  // pin_c6
// #define COL10 17 // pin_c7
// #define COL11 18 // pin_e6
// #define COL12 19 // pin_e7
// #define COL13 20 // pin_b0
// #define COL14 21 // pin_b1
// #define COL15 22 // pin_b2

 // define the debounce time
#define DEBOUNCE_TIME 20


// function lock
#define FUNCTION_LOCK

// set the row and column pins in the array
byte cols[8] = {COL0, COL1, COL2, COL3, COL4, COL5, COL6, COL7};//, COL8, COL9, COL10, COL11, COL12, COL13, COL14, COL15 };
byte rows[6] = {ROW0, ROW1, ROW2, ROW3, ROW4, ROW5};
// set up the state machine 
byte switchMatrix[ROWS_COUNT][COLS_COUNT] = {0};
byte switchMatrixLast[ROWS_COUNT][COLS_COUNT] = {0};

// this array holds the corresponding keys for the switches
// I used a teensy 2.0++, this is the corresponding chart I referenced
// https://www.pjrc.com/teensy/usb_keyboard.html
#define KC_NULL 0x00
#define KC_FN 0xFF
#define KEY_SP0 0xFF0
#define KEY_SP1 0xFF1
#define KEY_SP2 0xFF2
#define KEY_SP3 0xFF3

// could move this to a search function but defined constants are just fine for me
#define FUNCTION_ROW 5
#define FUNCTION_COL 10

unsigned int characterKeys[ROWS_COUNT][COLS_COUNT] = {
   /*{esc,   f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, ins, pgup, home},
     {grv,    1,  2,  3,  4,  5,  6,  7,  8,  9,  0,   -,   =,  bksp,   no, del}, 
     {tab,    q,  w,  e,  r,  t,  y,  u,  i,  o,  p,    [,   ],   no,    \, pgdn}, 
     {caps,   a,  s,  d,  f,  g,  h,  j,  k,  l,  ;,    ',    ,  ret,   no, end}, 
     {lsft,   z,  x,  c,  v,  b,  n,  m, no,',',  .,    /,rsft,   no,   up, menu}, 
     {ctrl, alt, wnd,no, no,spc, no, no, no, no, fn, ctrl, lft,   no,   dn, right}*/
     {KEY_ESC,        KEY_F1,       KEY_F2,       KEY_F3,  KEY_F4,  KEY_F5,    KEY_F6,  KEY_F7,  KEY_F8,  KEY_F9,    KEY_F10,       KEY_F11,        KEY_F12,         KEY_INSERT,    KEY_PAGE_UP,   KEY_HOME},
     {KEY_TILDE,      KEY_1,        KEY_2,        KEY_3,   KEY_4,   KEY_5,     KEY_6,   KEY_7,   KEY_8,   KEY_9,     KEY_0,         KEY_MINUS,      KEY_EQUAL,       KEY_BACKSPACE, KC_NULL,       KEY_DELETE}, 
     {KEY_TAB,        KEY_Q,        KEY_W,        KEY_E,   KEY_R,   KEY_T,     KEY_Y,   KEY_U,   KEY_I,   KEY_O,     KEY_P,         KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KC_NULL,       KEY_BACKSLASH, KEY_PAGE_DOWN}, 
     {KEY_CAPS_LOCK,  KEY_A,        KEY_S,        KEY_D,   KEY_F,   KEY_G,     KEY_H,   KEY_J,   KEY_K,   KEY_L,     KEY_SEMICOLON, KEY_QUOTE,      KC_NULL,         KEY_ENTER,     KC_NULL,       KEY_END}, 
     {KEY_LEFT_SHIFT, KEY_Z,        KEY_X,        KEY_C,   KEY_V,   KEY_B,     KEY_N,   KEY_M,   KC_NULL, KEY_COMMA, KEY_PERIOD,    KEY_SLASH,      KEY_RIGHT_SHIFT, KC_NULL,       KEY_UP,        KEY_RIGHT_GUI}, 
     {KEY_LEFT_CTRL,  KEY_LEFT_ALT, KEY_LEFT_GUI, KC_NULL, KC_NULL, KEY_SPACE, KC_NULL, KC_NULL, KC_NULL, KC_NULL,   KC_FN,         KEY_RIGHT_CTRL, KEY_LEFT,        KC_NULL,       KEY_DOWN,      KEY_RIGHT}
};

unsigned int functionKeys[ROWS_COUNT][COLS_COUNT] = {
   /*{esc,   f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, ins, pgup, home},
     {grv,    1,  2,  3,  4,  5,  6,  7,  8,  9,  0,   -,   =,  bksp,   no, del}, 
     {tab,    q,  w,  e,  r,  t,  y,  u,  i,  o,  p,    [,   ],   no,    \, pgdn}, 
     {caps,   a,  s,  d,  f,  g,  h,  j,  k,  l,  ;,    ',    ,  ret,   no, end}, 
     {lsft,   z,  x,  c,  v,  b,  n,  m, no,',',  .,    /,rsft,   no,   up, menu}, 
     {ctrl, alt, wnd,no, no,spc, no, no, no, no, fn, ctrl, lft,   no,   dn, right}*/
     {KC_NULL,        KC_NULL,        KC_NULL,       KC_NULL,  KC_NULL,  KC_NULL,    KC_NULL,  KC_NULL,  KC_NULL,  KC_NULL,    KC_NULL,       KC_NULL,        KC_NULL,         KC_NULL,    KC_NULL,   KC_NULL},
     {KEY_TILDE,      KEY_1,        KEY_2,        KEY_3,   KEY_4,   KEY_5,     KEY_6,   KEY_7,   KEY_8,   KEY_9,     KEY_0,         KEY_MINUS,      KEY_EQUAL,       KEY_BACKSPACE, KC_NULL,       KEY_DELETE}, 
     {KEY_TAB,        KEY_Q,        KEY_W,        KEY_E,   KEY_R,   KEY_T,     KEY_Y,   KEY_U,   KEY_I,   KEY_O,     KEY_P,         KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KC_NULL,       KEY_BACKSLASH, KEY_PAGE_DOWN}, 
     {KEY_CAPS_LOCK,  KEY_A,        KEY_S,        KEY_D,   KEY_F,   KEY_G,     KEY_H,   KEY_J,   KEY_K,   KEY_L,     KEY_SEMICOLON, KEY_QUOTE,      KC_NULL,         KEY_ENTER,     KC_NULL,       KEY_END}, 
     {KEY_LEFT_SHIFT, KEY_SP0,      KEY_SP1,      KEY_SP2, KEY_SP3, KEY_B,     KEY_N,   KEY_M,   KC_NULL, KEY_COMMA, KEY_PERIOD,    KEY_SLASH,      KEY_RIGHT_SHIFT, KC_NULL,       KEY_UP,        KEY_RIGHT_GUI}, 
     {KEY_LEFT_CTRL,  KEY_LEFT_ALT, KEY_LEFT_GUI, KC_NULL, KC_NULL, KEY_SPACE, KC_NULL, KC_NULL, KC_NULL, KC_NULL,   KC_FN,         KEY_RIGHT_CTRL, KEY_LEFT,        KC_NULL,       KEY_DOWN,      KEY_RIGHT}
};

bool bCapsLock = false;

#ifdef FUNCTION_LOCK
     bool bFnLock = false;
#endif

#define TESTING
void setup()
{
     // this is the baud rate
     Serial.begin(115200);
     
     // initialize the rows pins to use pullup resistor
     for (int i = 0; i < ROWS_COUNT; i++) {
          pinMode(rows[i], INPUT_PULLUP);
     }
     
     // initialize the columns pins to NOT use pullup resistor
     for (int i = 0; i < COLS_COUNT; i++) {
          pinMode(cols[i], INPUT);
     }

#ifndef TESTING
     Keyboard.begin();
#ifdef CAPSLOCK
     pinMode(CAPSLOCK, OUTPUT);
#endif
#endif
}

// most guides online dictate this wiring schematic
// with the row set to low and the column set to input pullup for reading it will make the column pin go high if the switch isn't pressed and zero if the pin is. 
// so anywhere in the matrix you have a zero it means that switch is pressed
void readMatrix() {
    // iterate the rows
    for (int rowIndex=0; rowIndex < ROWS_COUNT; rowIndex++) {
        // set the row to output low
        byte curRow = rows[rowIndex];
        pinMode(curRow, OUTPUT);
        digitalWrite(curRow, LOW);
        
        // iterate through the columns reading the value - should be zero if switch is pressed
        for (int colIndex=0; colIndex < COLS_COUNT; colIndex++) {
            byte rowCol = cols[colIndex];
            pinMode(rowCol, INPUT_PULLUP);
            switchMatrix[rowIndex][colIndex] = digitalRead(rowCol);
            pinMode(rowCol, INPUT);
        }
        
        // disable the row, turn the pullup resistor off
        pinMode(curRow, INPUT);
    }
}

// build the pretty print string - for debugging
void printMatrix() {
    String matrixString = "";
    for (int rowIndex = 0; rowIndex < ROWS_COUNT; rowIndex++) {
        if (rowIndex < 10) {
           matrixString += String("0");
        }
        matrixString += String(rowIndex); 
        matrixString += String(": ");
 
        for (int colIndex = 0; colIndex < COLS_COUNT; colIndex++) {  
            matrixString += String(switchMatrix[rowIndex][colIndex]);
            if (colIndex < COLS_COUNT)
                matrixString += String(", ");
        }   
        matrixString += String("\n");
    }
    Serial.print(matrixString);
}

// bool isSpecialKey(unsigned int val)
// {
//      if (val > KC_FN) {
//           return true;
//      } else {
//           return false;
//      }
// }

// void sendSpecialKeys(unsigned int val)
// {
//      switch(val) {
//           case KEY_SP0:
//                Keyboard.press(KEY_LEFT_CTRL);
//                Keyboard.press(KEY_Z);
//                Keyboard.release(KEY_LEFT_CTRL);
//                Keyboard.release(KEY_Z);
//                break;
//           case KEY_SP1:
//                Keyboard.press(KEY_LEFT_CTRL);
//                Keyboard.press(KEY_X);
//                Keyboard.release(KEY_LEFT_CTRL);
//                Keyboard.release(KEY_X);
//                break;
//           case KEY_SP2:
//                Keyboard.press(KEY_LEFT_CTRL);
//                Keyboard.press(KEY_C);
//                Keyboard.release(KEY_LEFT_CTRL);
//                Keyboard.release(KEY_C);
//                break;
//           case KEY_SP3:
//                Keyboard.press(KEY_LEFT_CTRL);
//                Keyboard.press(KEY_V);
//                Keyboard.release(KEY_LEFT_CTRL);
//                Keyboard.release(KEY_V);
//                break;
//      }
// }

// // call keyboard press/release for the appropriate states
// void setKeyStates() {
//      bool bFunction = switchMatrix[FUNCTION_ROW][FUNCTION_COL] == 0;
//      for (int i = 0; i < ROWS_COUNT; i++) {
//           for (int j = 0; j < COLS_COUNT; j++) {
//                if (switchMatrix[i][j] != switchMatrixLast[i][j]) {
                    
// #ifdef FUNCTION_LOCK
//                     if (switchMatrix[i][j] == 0 && switchMatrixLast[i][j] == 1) { // key is pressed and wasn't before
//                          if (bFnLock) { // using function lock
//                               if (!isSpecialKey(functionKeys[i][j])) {
//                                    Keyboard.press(functionKeys[i][j]);
//                                    if (characterKeys[i][j] == KC_FN) { // second press of the lock key
//                                         bFnLock = !bFnLock;
//                                    }
//                               }
//                          } else { // not using function lock
//                               Keyboard.press(characterKeys[i][j]);
//                               // capslock led
//                               if (characterKeys[i][j] == KEY_CAPS_LOCK) {
//                                    bCapsLock = !bCapsLock;
// #ifdef CAPSLOCK
//                                    digitalWrite(CAPSLOCK, bCapsLock ? HIGH : LOW);
// #endif
//                               }

//                               // setting the lock key
//                               if (characterKeys[i][j] == KC_FN) {
//                                    bFnLock = !bFnLock;
//                               }
//                          }
//                     } else { // key is not pressed and was before
//                          if (bFnLock) { // using function lock
//                               if (isSpecialKey(functionKeys[i][j])) { // send the macro keys
//                                    sendSpecialKeys(functionKeys[i][j]);
//                               } else { // release the normal keys
//                                    Keyboard.release(functionKeys[i][j]);
//                               }
//                          } else { // not using function lock
//                               Keyboard.release(characterKeys[i][j]);
//                               if (characterKeys[i][j] == KEY_CAPS_LOCK && bCapsLock == false) {
//                                    // do nothing
//                               }
//                          }
//                     }
// #else
//                     if (switchMatrix[i][j] == 0 && switchMatrixLast[i][j] == 1) { // key is pressed and wasn't before
//                          // skip writing of the function keys
//                          if (i == FUNCTION_ROW && j == FUNCTION_COL) {
//                               continue;
//                          }
                    
//                          if (bFunction) {
//                               Keyboard.press(functionKeys[i][j]);
//                          } else {
//                               Keyboard.press(characterKeys[i][j]);
                         
//                               // capslock led
//                               if (characterKeys[i][j] == KEY_CAPS_LOCK) {
//                                    bCapsLock = !bCapsLock;
// #ifdef CAPSLOCK
//                                    digitalWrite(CAPSLOCK, bCapsLock ? HIGH : LOW);
// #endif
//                               }
//                          }
//                     } else { // key is not pressed and was before
//                          if (bFunction) {
//                               Keyboard.release(functionKeys[i][j]);
//                          } else {
//                               Keyboard.release(characterKeys[i][j]);
//                               if (characterKeys[i][j] == KEY_CAPS_LOCK && bCapsLock == false) {
//                                    // do nothing
//                               }
//                          }
//                     }
// #endif
//                }
//           }
//      }
// }

// manages the simple state machine
// copies the current matrix to the last matrix for comparison after reading
void copyMatrix() {
     for (int i = 0; i < ROWS_COUNT; i++) {
          for (int j = 0; j < COLS_COUNT; j++) {
               switchMatrixLast[i][j] = switchMatrix[i][j];         
          }
     }
}


// the show
int count = 0;
void loop()
{
#ifdef TESTING
     // debounce timer
     delay(DEBOUNCE_TIME);
     readMatrix();
     // if connected to actual serial terminal - like putty - this will clear the screen, if to arduino this will just print garbage
     //Serial.write(27);       // ESC command
     //Serial.print("[2J");    // clear screen command
     //Serial.write(27);
     //Serial.print("[H");     // cursor to home command

     // print the matrix
     Serial.print("writing matrix");
     Serial.println(String(count));
     printMatrix();
     count ++;
#else
    //  // do the actual keyboard stuff here
    //  // state machine - something something something - darkside
    //  delay(DEBOUNCE_TIME);
     
    //  // get the last key state
    //  copyMatrix();

    //  // read the switch matrix
    //  readMatrix();

    //  // set the key presses and release states
    //  setKeyStates();
#endif
}