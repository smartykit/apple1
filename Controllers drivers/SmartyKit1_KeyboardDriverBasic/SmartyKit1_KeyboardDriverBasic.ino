/*  SmartyKit 1 - PS/2 keyboard driver v.1.2 (2023)
*  (with automatic mode if no PS/2 keyboard is connected)
*  http://www.smartykit.io/
*  Copyright (C) 2020, Sergey Panarin <sergey@smartykit.io>
*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "PS2KeyAdvanced.h"

// Keyboard Driver pins connections:
// D0 & D1 – reserved for Serial connection
// D2 –> PS/2 Socket Data pin
// D3 -> 4-16 ports decoder Kbd (2) out pin (signal is active when CPU reads Keyboatrd port)
// D4 -> PS/2 Socket Clk pin
// D5 -> Keyboard BIT7 pin output
// D6-D13 -> Keyboard data bus output (8 pins) to connect to Keyboard port (char code is transfered here)
// A4 -> Low-rate clock output for CPU CLK input
// A5 -> Low-rate clock output for indicating LED connection

#define PS2KEYBOARDCLOCK_PIN 2
#define KEYBOARD_RD_PIN 3
#define PS2KEYBOARD_DATA_PIN 4
#define KEYBOARD_BIT7_PIN 5

const int KeyboardPort[8] = {6, 7, 8, 9, 10, 11, 12, 13};

static boolean autoMode = false;        // run pre-set command or wait for user input from PS/2 keyboard
static boolean autoCommandSent = false; // run pre-set command only once after reboot of Keyboard controller

// low-rate clock for tests on A4-A5
#define LORATE_CLOCK_PIN A4
#define LORATE_CLOCK_LED_PIN A5

// 100 milliseconds = 10 times per second (10 Hz)
#define LORATE_CLOCK_PERIOD_MILLIS 100

// Uncomment any of following defines to include those mappings
// or comment to exclude
// #define GERMAN
// #define FRENCH
// #define SPANISH
// #define ITALIAN
// #define SPECIAL

/* UTF-8 single byte LATIN encodings
   128 to 159 (0x80 to 0x9F) are control characters application generated
   160 to 255 (0xA0 to 0XFF) are used depending on keymap tables
   These defines are used to insert them into correct tables */

/****************************************************************
  IMPORTANT NOTE EURO currency Symbol is NOT supported in UTF-8 single
  byte codings, as EURO symbol came after UTF-8 single byte codings
****************************************************************/
#define PS2_NO_BREAK_SPACE 160          // nbsp
#define PS2_INVERTED_EXCLAMATION 161    // ¡
#define PS2_CENT_SIGN 162               // ¢
#define PS2_POUND_SIGN 163              // £
#define PS2_CURRENCY_SIGN 164           // ¤
#define PS2_YEN_SIGN 165                // ¥
#define PS2_BROKEN_BAR 166              // ¦
#define PS2_SECTION_SIGN 167            // §
#define PS2_DIAERESIS 168               // ¨
#define PS2_COPYRIGHT_SIGN 169          // ©
#define PS2_FEMININE_ORDINAL 170        // ª
#define PS2_LEFT_DOUBLE_ANGLE_QUOTE 171 // «
#define PS2_NOT_SIGN 172                // ¬
#define PS2_HYPHEN 173
#define PS2_REGISTERED_SIGN 174          // ®
#define PS2_MACRON 175                   // ¯
#define PS2_DEGREE_SIGN 176              // °
#define PS2_PLUS_MINUS_SIGN 177          // ±
#define PS2_SUPERSCRIPT_TWO 178          // ²
#define PS2_SUPERSCRIPT_THREE 179        // ³
#define PS2_ACUTE_ACCENT 180             // ´
#define PS2_MICRO_SIGN 181               // µ
#define PS2_PILCROW_SIGN 182             // ¶
#define PS2_MIDDLE_DOT 183               // ·
#define PS2_CEDILLA 184                  // ¸
#define PS2_SUPERSCRIPT_ONE 185          // ¹
#define PS2_MASCULINE_ORDINAL 186        // º
#define PS2_RIGHT_DOUBLE_ANGLE_QUOTE 187 // »
#define PS2_FRACTION_ONE_QUARTER 188     // ¼
#define PS2_FRACTION_ONE_HALF 189        // ½
#define PS2_FRACTION_THREE_QUARTERS 190  // ¾
#define PS2_INVERTED_QUESTION_MARK 191   // ¿
#define PS2_A_GRAVE 192                  // À
#define PS2_A_ACUTE 193                  // Á
#define PS2_A_CIRCUMFLEX 194             // Â
#define PS2_A_TILDE 195                  // Ã
#define PS2_A_DIAERESIS 196              // Ä
#define PS2_A_RING_ABOVE 197             // Å
#define PS2_AE 198                       // Æ
#define PS2_C_CEDILLA 199                // Ç
#define PS2_E_GRAVE 200                  // È
#define PS2_E_ACUTE 201                  // É
#define PS2_E_CIRCUMFLEX 202             // Ê
#define PS2_E_DIAERESIS 203              // Ë
#define PS2_I_GRAVE 204                  // Ì
#define PS2_I_ACUTE 205                  // Í
#define PS2_I_CIRCUMFLEX 206             // Î
#define PS2_I_DIAERESIS 207              // Ï
#define PS2_ETH 208                      // Ð
#define PS2_N_TILDE 209                  // Ñ
#define PS2_O_GRAVE 210                  // Ò
#define PS2_O_ACUTE 211                  // Ó
#define PS2_O_CIRCUMFLEX 212             // Ô
#define PS2_O_TILDE 213                  // Õ
#define PS2_O_DIAERESIS 214              // Ö
#define PS2_MULTIPLICATION 215           // ×
#define PS2_O_STROKE 216                 // Ø
#define PS2_U_GRAVE 217                  // Ù
#define PS2_U_ACUTE 218                  // Ú
#define PS2_U_CIRCUMFLEX 219             // Û
#define PS2_U_DIAERESIS 220              // Ü
#define PS2_Y_ACUTE 221                  // Ý
#define PS2_THORN 222                    // Þ
#define PS2_SHARP_S 223                  // ß
#define PS2_a_GRAVE 224                  // à
#define PS2_a_ACUTE 225                  // á
#define PS2_a_CIRCUMFLEX 226             // â
#define PS2_a_TILDE 227                  // ã
#define PS2_a_DIAERESIS 228              // ä
#define PS2_a_RING_ABOVE 229             // å
#define PS2_ae 230                       // æ
#define PS2_c_CEDILLA 231                // ç
#define PS2_e_GRAVE 232                  // è
#define PS2_e_ACUTE 233                  // é
#define PS2_e_CIRCUMFLEX 234             // ê
#define PS2_e_DIAERESIS 235              // ë
#define PS2_i_GRAVE 236                  // ì
#define PS2_i_ACUTE 237                  // í
#define PS2_i_CIRCUMFLEX 238             // î
#define PS2_i_DIAERESIS 239              // ï
#define PS2_eth 240                      // ð
#define PS2_n_TILDE 241                  // ñ
#define PS2_o_GRAVE 242                  // ò
#define PS2_o_ACUTE 243                  // ó
#define PS2_o_CIRCUMFLEX 244             // ô
#define PS2_o_TILDE 245                  // õ
#define PS2_o_DIAERESIS 246              // ö
#define PS2_DIVISION 247                 // ÷
#define PS2_o_STROKE 248                 // ø
#define PS2_u_GRAVE 249                  // ù
#define PS2_u_ACUTE 250                  // ú
#define PS2_u_CIRCUMFLEX 251             // û
#define PS2_u_DIAERESIS 252              // ü
#define PS2_y_ACUTE 253                  // ý
#define PS2_thorn 254                    // þ
#define PS2_y_DIAERESIS 255              // ÿ

/* Public class definition */
class SmartyPS2KeyMap
{
public:
  /**
   * This constructor just sets the default key mapping to US. */
  SmartyPS2KeyMap();

  /**
   Pass in 2 character string for the ISO 2 letter country code in use
      For UK "UK" or "GB" are valid
      "US" is built-in default
   Returns 1 for done or 0 for not found.
   */
  uint8_t selectMap(char *);

  /**
   Return selected map as a string pointer (2 chars and terminator)    */
  const char *getMap(void);

  /**
   Pass in unsigned int returned from PS2KeyAdvanced
              Returns 0 for error
                      uint16_t for valid code
   */
  uint16_t remapKey(uint16_t);

  /**
    Returns uint8_t version of remapKey ONLY for standard ASCII/UTF-8 codes
    Invalid codes returned as 0
   */
  uint8_t remapKeyByte(uint16_t);
};

/* Standard ASCII/UTF-8 control Characters */
#define PS2_BACKSPACE 0x08
#define PS2_TAB 0x09
#define PS2_ENTER 0x0D
#define PS2_ESC 0x1B
#define PS2_DELETE 0x7F
#define PS2_SPACE 0x20

/* Standard ASCII control characters array */
/* in order of PS2_KEY_* values order is important */
const uint8_t _control_codes[] = {
    PS2_DELETE, PS2_ESC, PS2_BACKSPACE,
    PS2_TAB, PS2_ENTER, PS2_SPACE};

// convert codes based on SHIFT and not SHIFT only for base US-ASCII
const uint16_t _US_ASCII[][2] = {
    {PS2_SHIFT + PS2_KEY_1, '!'},
    {PS2_SHIFT + PS2_KEY_2, '@'},
    {PS2_SHIFT + PS2_KEY_3, '#'},
    {PS2_SHIFT + PS2_KEY_4, '$'},
    {PS2_SHIFT + PS2_KEY_5, '%'},
    {PS2_SHIFT + PS2_KEY_6, '^'},
    {PS2_SHIFT + PS2_KEY_7, '&'},
    {PS2_SHIFT + PS2_KEY_8, '*'},
    {PS2_SHIFT + PS2_KEY_9, '('},
    {PS2_SHIFT + PS2_KEY_0, ')'},
    {PS2_KEY_KP_DOT, '.'},
    {PS2_KEY_KP_ENTER, PS2_ENTER},
    {PS2_KEY_KP_PLUS, '+'},
    {PS2_KEY_KP_MINUS, '-'},
    {PS2_KEY_KP_TIMES, '*'},
    {PS2_KEY_KP_DIV, '/'},
    {PS2_KEY_KP_COMMA, ','},
    {PS2_KEY_KP_EQUAL, '='},
    {PS2_KEY_APOS, '\''},
    {PS2_SHIFT + PS2_KEY_APOS, '"'},
    {PS2_KEY_COMMA, ','},
    {PS2_SHIFT + PS2_KEY_COMMA, '<'},
    {PS2_KEY_MINUS, '-'},
    {PS2_SHIFT + PS2_KEY_MINUS, '_'},
    {PS2_KEY_DOT, '.'},
    {PS2_SHIFT + PS2_KEY_DOT, '>'},
    {PS2_KEY_DIV, '/'},
    {PS2_SHIFT + PS2_KEY_DIV, '?'},
    {PS2_KEY_SINGLE, '`'},
    {PS2_SHIFT + PS2_KEY_SINGLE, '~'},
    {PS2_KEY_SEMI, ';'},
    {PS2_SHIFT + PS2_KEY_SEMI, ':'},
    {PS2_KEY_BACK, '\\'},
    {PS2_SHIFT + PS2_KEY_BACK, '|'},
    {PS2_KEY_OPEN_SQ, '['},
    {PS2_SHIFT + PS2_KEY_OPEN_SQ, '{'},
    {PS2_KEY_CLOSE_SQ, ']'},
    {PS2_SHIFT + PS2_KEY_CLOSE_SQ, '}'},
    {PS2_KEY_EQUAL, '='},
    {PS2_SHIFT + PS2_KEY_EQUAL, '+'}};

const uint16_t _UKmap[][2] = {
    {PS2_SHIFT + '@', '"'},
    {PS2_SHIFT + '"', '@'},
    {PS2_ALT_GR + '`', PS2_BROKEN_BAR},
    {PS2_SHIFT + '`', PS2_NOT_SIGN},
    {PS2_SHIFT + '#', PS2_POUND_SIGN},
    {'\\', '#'},
    {PS2_SHIFT + '|', '~'},
    {PS2_KEY_EUROPE2, '\\'},
    {PS2_SHIFT + PS2_KEY_EUROPE2, '|'},
};
#ifdef FRENCH
const uint16_t _FRmap[][2] = {
    {'`', PS2_SUPERSCRIPT_TWO},
    {PS2_SHIFT + '~', PS2_SUPERSCRIPT_TWO},
    {'q', 'a'},
    {'Q', 'A'},
    {'1', '&'},
    {PS2_SHIFT + '!', '1'},
    {PS2_ALT_GR + '1', 0},
    {PS2_ALT_GR + PS2_SHIFT + '!', 0},
    {'z', 'w'},
    {'Z', 'W'},
    {'a', 'q'},
    {'A', 'Q'},
    {'w', 'z'},
    {'W', 'Z'},
    {PS2_ALT_GR + '2', '~'},
    {PS2_SHIFT + PS2_ALT_GR + '@', '~'},
    {'2', PS2_e_ACUTE},
    {PS2_SHIFT + '@', '2'},
    {PS2_ALT_GR + '3', PS2_CENT_SIGN},
    {PS2_SHIFT + PS2_ALT_GR + '#', PS2_CENT_SIGN},
    {'3', '"'},
    {PS2_SHIFT + '#', '3'},
    {PS2_ALT_GR + '4', '{'},
    {PS2_SHIFT + PS2_ALT_GR + '$', '{'},
    {'4', '\''},
    {PS2_SHIFT + '$', '4'},
    {PS2_ALT_GR + '5', '['},
    {PS2_SHIFT + PS2_ALT_GR + '%', '['},
    {'5', '('},
    {PS2_SHIFT + '%', '5'},
    {PS2_ALT_GR + '6', '|'},
    {PS2_SHIFT + PS2_ALT_GR + '^', '|'},
    {'6', '-'},
    {PS2_SHIFT + '^', '6'},
    {'m', ','},
    {'M', '?'},
    {PS2_ALT_GR + '7', '`'},
    {PS2_SHIFT + PS2_ALT_GR + '&', '`'},
    {'7', PS2_e_GRAVE},
    {PS2_SHIFT + '&', '7'},
    {PS2_ALT_GR + '8', '\\'},
    {PS2_SHIFT + PS2_ALT_GR + '*', '\\'},
    {'8', '_'},
    {PS2_SHIFT + '*', '8'},
    {',', ';'},
    {PS2_SHIFT + '<', '.'},
    {PS2_ALT_GR + '9', '^'},
    {PS2_SHIFT + PS2_ALT_GR + '(', '^'},
    {'9', PS2_c_CEDILLA},
    {PS2_SHIFT + '(', '9'},
    {PS2_ALT_GR + '0', '@'},
    {PS2_ALT_GR + ')', '@'},
    {'0', PS2_a_GRAVE},
    {PS2_SHIFT + ')', '0'},
    {'.', ':'},
    {PS2_SHIFT + '>', '/'},
    {'/', '!'},
    {PS2_SHIFT + '?', PS2_SECTION_SIGN},
    {';', 'm'},
    {PS2_SHIFT + ':', 'M'},
    {PS2_ALT_GR + '-', ']'},
    {PS2_SHIFT + PS2_ALT_GR + '_', ']'},
    {'-', ')'},
    {PS2_SHIFT + '_', PS2_DEGREE_SIGN},
    {'\'', PS2_u_GRAVE},
    {PS2_SHIFT + '"', '%'},
    {PS2_ALT_GR + '\'', 0},
    {PS2_SHIFT + PS2_ALT_GR + '"', 0},
    {'[', '^'},
    {PS2_SHIFT + '{', PS2_DIAERESIS},
    {PS2_ALT_GR + '=', '}'},
    {PS2_SHIFT + PS2_ALT_GR + '+', '}'},
    {PS2_ALT_GR + ']', PS2_CURRENCY_SIGN},
    {PS2_SHIFT + PS2_ALT_GR + '}', 0},
    {']', '$'},
    {PS2_SHIFT + '}', PS2_POUND_SIGN},
    {'\\', '*'},
    {PS2_SHIFT + '|', PS2_MICRO_SIGN},
    {PS2_SHIFT + PS2_ALT_GR + '|', 0},
    {PS2_ALT_GR + '\\', 0},
    {PS2_KEY_EUROPE2 + PS2_SHIFT + PS2_ALT_GR, '|'},
    {PS2_KEY_EUROPE2 + PS2_ALT_GR, '|'},
    {PS2_SHIFT + PS2_KEY_EUROPE2, '>'},
    {PS2_KEY_EUROPE2, '<'}};
#endif
#ifdef GERMAN
const uint16_t _DEmap[][2] = {
    {'`', '^'},
    {PS2_SHIFT + '~', PS2_DEGREE_SIGN},
    {PS2_ALT_GR + 'q', '@'},
    {PS2_ALT_GR + 'Q', '@'},
    {'y', 'z'},
    {'Y', 'Z'},
    {PS2_ALT_GR + '2', PS2_SUPERSCRIPT_TWO},
    {PS2_SHIFT + PS2_ALT_GR + '@', PS2_SUPERSCRIPT_TWO},
    {PS2_SHIFT + '@', '"'},
    {PS2_ALT_GR + 'e', PS2_CURRENCY_SIGN},
    {PS2_ALT_GR + 'E', PS2_CURRENCY_SIGN},
    {PS2_ALT_GR + '3', PS2_SUPERSCRIPT_THREE},
    {PS2_SHIFT + PS2_ALT_GR + '#', PS2_SUPERSCRIPT_THREE},
    {PS2_SHIFT + '#', PS2_SECTION_SIGN},
    {'z', 'y'},
    {'Z', 'Y'},
    {PS2_SHIFT + '^', '&'},
    {PS2_ALT_GR + 'm', PS2_MICRO_SIGN},
    {PS2_ALT_GR + 'M', PS2_MICRO_SIGN},
    {PS2_SHIFT + '&', '/'},
    {PS2_ALT_GR + '7', '{'},
    {PS2_SHIFT + PS2_ALT_GR + '&', '{'},
    {PS2_SHIFT + '*', '('},
    {PS2_ALT_GR + '8', '['},
    {PS2_SHIFT + PS2_ALT_GR + '*', '['},
    {PS2_SHIFT + '<', ';'},
    {PS2_SHIFT + ')', '='},
    {PS2_ALT_GR + '0', '}'},
    {PS2_SHIFT + PS2_ALT_GR + ')', '}'},
    {PS2_SHIFT + '(', ')'},
    {PS2_ALT_GR + '9', ']'},
    {PS2_SHIFT + PS2_ALT_GR + '(', ']'},
    {PS2_SHIFT + '>', ':'},
    {';', PS2_o_DIAERESIS},
    {PS2_SHIFT + ':', PS2_O_DIAERESIS},
    {PS2_ALT_GR + '-', '\\'},
    {PS2_SHIFT + PS2_ALT_GR + '_', '\\'},
    {'-', PS2_SHARP_S},
    {PS2_SHIFT + '_', '?'},
    {'\'', PS2_a_DIAERESIS},
    {PS2_SHIFT + '"', PS2_A_DIAERESIS},
    {'[', PS2_u_DIAERESIS},
    {PS2_SHIFT + '{', PS2_U_DIAERESIS},
    {'=', '\''},
    {PS2_SHIFT + '+', '`'},
    {']' + PS2_ALT_GR, '~'},
    {PS2_SHIFT + '}' + PS2_ALT_GR, '~'},
    {']', '+'},
    {PS2_SHIFT + '}', '*'},
    {'\\', '#'},
    {PS2_SHIFT + '|', '\''},
    {PS2_KEY_EUROPE2 + PS2_SHIFT + PS2_ALT_GR, '|'},
    {PS2_KEY_EUROPE2 + PS2_ALT_GR, '|'},
    {PS2_SHIFT + PS2_KEY_EUROPE2, '>'},
    {PS2_KEY_EUROPE2, '<'}};
#endif
#ifdef SPANISH
const uint16_t _ESmap[][2] = {
    {PS2_KEY_SINGLE, PS2_MASCULINE_ORDINAL},
    {PS2_SHIFT + PS2_KEY_SINGLE, PS2_FEMININE_ORDINAL},
    {PS2_KEY_SINGLE + PS2_ALT_GR, '\\'},
    {'1' + PS2_ALT_GR, '|'},
    {PS2_SHIFT + '@', '"'},
    {'2' + PS2_ALT_GR, '@'},
    {PS2_SHIFT + '#', PS2_MIDDLE_DOT},
    {'3' + PS2_ALT_GR, '#'},
    {'4' + PS2_ALT_GR, '~'},
    {PS2_SHIFT + '^', '&'},
    {'6' + PS2_ALT_GR, PS2_NOT_SIGN},
    {PS2_SHIFT + '&', '/'},
    {PS2_SHIFT + '*', '('},
    {PS2_SHIFT + '(', ')'},
    {PS2_SHIFT + ')', '='},
    {'-', '\''},
    {PS2_SHIFT + '_', '?'},
    {'=', PS2_INVERTED_EXCLAMATION},
    {PS2_SHIFT + '+', PS2_INVERTED_QUESTION_MARK},
    {'[', '`'},
    {PS2_SHIFT + '{', '^'},
    {'[' + PS2_ALT_GR, '['},
    {']', '+'},
    {PS2_SHIFT + '}', '*'},
    {']' + PS2_ALT_GR, ']'},
    {';', PS2_n_TILDE},
    {PS2_SHIFT + ':', PS2_N_TILDE},
    {'\'', PS2_ACUTE_ACCENT},
    {PS2_SHIFT + '"', PS2_DIAERESIS},
    {'\'' + PS2_ALT_GR, '{'},
    {'\\', PS2_c_CEDILLA},
    {PS2_SHIFT + '|', PS2_C_CEDILLA},
    {'\\' + PS2_ALT_GR, '}'},
    {PS2_SHIFT + PS2_KEY_EUROPE2, '>'},
    {PS2_KEY_EUROPE2, '<'},
    {PS2_SHIFT + '<', ';'},
    {PS2_SHIFT + '>', ':'},
    {PS2_KEY_DIV, '-'},
    {PS2_SHIFT + PS2_KEY_DIV, '+'}};
#endif
#ifdef ITALIAN
const uint16_t _ITmap[][2] = {
    {PS2_KEY_SINGLE, '\\'},
    {PS2_SHIFT + PS2_KEY_SINGLE, '|'},
    {'@', '"'},
    {PS2_SHIFT + '#', PS2_POUND_SIGN},
    {'3' + PS2_ALT_GR, '#'},
    {PS2_SHIFT + '^', '&'},
    {PS2_SHIFT + '&', '/'},
    {'7' + PS2_ALT_GR, '{'},
    {PS2_SHIFT + '*', '('},
    {'8' + PS2_ALT_GR, '['},
    {PS2_SHIFT + '(', ')'},
    {'9' + PS2_ALT_GR, ']'},
    {PS2_SHIFT + ')', '='},
    {'0' + PS2_ALT_GR, '}'},
    {'-', '\''},
    {PS2_SHIFT + '_', '?'},
    {'=', PS2_i_GRAVE},
    {PS2_SHIFT + '+', '^'},
    {'q' + PS2_ALT_GR, '@'},
    {'[', PS2_e_GRAVE},
    {PS2_SHIFT + '{', PS2_e_ACUTE},
    {']', '+'},
    {PS2_SHIFT + '}', '*'},
    {']' + PS2_ALT_GR, '~'},
    {';', PS2_o_GRAVE},
    {PS2_SHIFT + ':', PS2_c_CEDILLA},
    {'\'', PS2_a_GRAVE},
    {PS2_SHIFT + '"', PS2_DEGREE_SIGN},
    {'\\', PS2_u_GRAVE},
    {PS2_SHIFT + '|', PS2_SECTION_SIGN},
    {PS2_SHIFT + PS2_KEY_EUROPE2, '>'},
    {PS2_KEY_EUROPE2, '<'},
    {PS2_SHIFT + '<', ';'},
    {PS2_SHIFT + '>', ':'},
    {PS2_KEY_DIV, '-'},
    {PS2_SHIFT + PS2_KEY_DIV, '+'}};
#endif
#ifdef SPECIAL
const uint16_t _SpecialMap[][2] = {
    // Insert your Special mapping DIFFERENCES from US-ASCII here
};
#endif

// The following structures define the key maps available
typedef struct
{
  char *name;    // 2 Character ISO country code
  uint8_t size;  // Number of entries in map array
  uint16_t *map; // Map array pointer
} PS2Advmap;

// Actual map structure array ( 2 entries for GB and UK for same map
// Because many people don't know ISO code for UK is GB )
const PS2Advmap _KeyMaps[] = {
    {"US", sizeof(_US_ASCII) / (2 * sizeof(uint16_t)), (uint16_t *)_US_ASCII},
#ifdef FRENCH
    {"FR", sizeof(_FRmap) / (2 * sizeof(uint16_t)), (uint16_t *)_FRmap},
#endif
#ifdef GERMAN
    {"DE", sizeof(_DEmap) / (2 * sizeof(uint16_t)), (uint16_t *)_DEmap},
#endif
#ifdef SPANISH
    {"ES", sizeof(_ESmap) / (2 * sizeof(uint16_t)), (uint16_t *)_ESmap},
#endif
#ifdef ITALIAN
    {"IT", sizeof(_ITmap) / (2 * sizeof(uint16_t)), (uint16_t *)_ITmap},
#endif
#ifdef SPECIAL
    {"--", sizeof(_SpecialMap) / (2 * sizeof(uint16_t)), (uint16_t *)_SpecialMap},
#endif
    {"UK", sizeof(_UKmap) / (2 * sizeof(uint16_t)), (uint16_t *)_UKmap},
    {"GB", sizeof(_UKmap) / (2 * sizeof(uint16_t)), (uint16_t *)_UKmap}};

uint8_t _selected_map;

// Private country code strings
const char *_USStr[] = {"US"};

/* Common function to scan a Look up table table and
   return a value or 0 for not found

   Checks using default mask of keycode plus ALT_GR and SHIFT
   To add in match other modifiers set mask to combination of
        PS2_CTRL        match either Control key as well
        PS2_ALT         match left ALT as well
        PS2_GUI         match either GUI key as well

   Assumes map table has 2 dimensions of type prog_uint16_t (in Flash memory)
   i.e. an array like test[ ][ 2 ]
        First entry  (test[][ 0 ]) is item to match
        Second entry (test[][ 1 ]) is item to return

   Parameters are
        data    unsigned int 16 from PS2KeyAdvanced library
        index   index of mapping table to use
*/
uint16_t scan_map(uint16_t data, uint8_t index)
{
  uint16_t idx, result, size;
  uint16_t *maparray;

  // Convert entries count to number of ints
  size = (_KeyMaps[index].size) << 1;
  maparray = (uint16_t *)_KeyMaps[index].map;

  // Leave only required bits for checking against
  result = data & (PS2_ALT_GR + PS2_SHIFT + 0xFF);

  // scan Lookup Table (array) jumping 2 integers at a time
  for (idx = 0; idx < size; idx += 2)
  {
    if (result == *(maparray + idx))
    { // second integer is the replacement value
      result = *(maparray + idx + 1);
      data &= ~0xFF;  // clear old bits retaining CTRL etc
      data |= result; // Make new code
      break;
    }
  }
  return data;
}

/*
   Pass in 2 character string for the ISO 2 letter country code in use
   For UK "UK" or "GB" are valid
      "US" is built-in default

     Returns 1 for done
          or 0 for not found.
*/
uint8_t SmartyPS2KeyMap::selectMap(char *ISO = (char *)_USStr)
{
  uint8_t outer, idx, end;

  end = sizeof(_KeyMaps) / sizeof(PS2Advmap);

  for (outer = 0; outer < end; outer++)
  {
    for (idx = 0; idx < 3; idx++)
    {
      if (_KeyMaps[outer].name[idx] != ISO[idx])
        break; // No match
    }
    if (idx == 3) // done whole match
      break;
  }
  if (outer < end) // found entry
  {
    _selected_map = outer; // Copy over to selected
    return 1;
  }
  return 0;
}

/*
   Return selected map as a string pointer (2 chars and terminator)
*/
const char *SmartyPS2KeyMap::getMap(void)
{
  return (_KeyMaps[_selected_map].name);
}

/* Pass in unsigned int returned from PS2KeyAdvanced
     Returns 0 for error
         uint16_t for valid code
   Converts code to US-ASCII first (honouring SHIFT ONLY)
   then if additional map defined scan and remap those keys
*/
uint16_t SmartyPS2KeyMap::remapKey(uint16_t code)
{
  uint8_t temp;

  // for bottom byte checks
  temp = code & 0xFF;

  // Sort standard ASCII control codes
  if (temp >= PS2_KEY_DELETE && temp <= PS2_KEY_SPACE)
  {
    code &= ~(PS2_FUNCTION + 0xFF); // convert to ASCII code not function
    temp = _control_codes[temp - PS2_KEY_DELETE];
    code |= temp;
  }
  else
    // Remainder convert printable to US-ASCII
    if (!(code & PS2_FUNCTION))
    { // Some codes are straight return values We deal with ones that need work
      // When A-Z not shifted create lower case a - z
      if (temp >= PS2_KEY_A && temp <= PS2_KEY_Z)
      {
        // Deal with Caps Lock by inverting PS2_SHIFT and remove caps lock
        if ((code & PS2_CAPS))
          code ^= (PS2_SHIFT + PS2_CAPS);
        if (!(code & PS2_SHIFT))
          code |= 0x20;
        // When shifted pass through code as received as the codes are A - Z
        else
          code &= ~PS2_SHIFT;
      }
      else
        // Convert KeyPad 0-9 to number codes
        if (temp >= PS2_KEY_KP0 && temp <= PS2_KEY_KP9)
        {
          code |= 0x10;
          code &= ~(PS2_SHIFT + PS2_ALT + PS2_ALT_GR + PS2_CTRL + PS2_GUI + PS2_CAPS);
        }
        else
        {
          // Some keys ignore shift, the extra keys on numeric keypad
          if ((temp >= PS2_KEY_KP_DOT && temp <= PS2_KEY_KP_DIV) || temp == PS2_KEY_KP_EQUAL || temp == PS2_KEY_KP_COMMA)
            code &= ~PS2_SHIFT;
          // Do default US-ASCII mapping of remainders excluding (CTRL, ALT, GUI)
          code = (code & PS2_ALT_GR) + scan_map(code & ~PS2_ALT_GR, 0);
        }
      // Now do remap if necessary for all modifiers
      if (code > 0 && _selected_map > 0)
        code = scan_map(code, _selected_map);
      else // For USASCII ignore extra key in case
        if ((temp == PS2_KEY_EUROPE2))
          code = 0;
      code &= ~(PS2_SHIFT + PS2_ALT_GR); // Now clear shift status
    }
    else
      code = 0;
  return code;
}

/*
   Returns uint8_t version of remapKey ONLY for standard ASCII/UTF-8 codes
   Invalid codes returned as 0
   Also any key with BREAK condition are returned as 0
*/
uint8_t SmartyPS2KeyMap::remapKeyByte(uint16_t code)
{
  uint16_t data;

  // Invalid codes returned as 0
  if (code & (PS2_FUNCTION + PS2_BREAK))
    return 0;
  data = remapKey(code);
  return (uint8_t)(data & 0xFF);
}

/*  Class constructor
   At construction ensure default map selected
*/
SmartyPS2KeyMap::SmartyPS2KeyMap()
{
  _selected_map = 0;
}

PS2KeyAdvanced keyboard;
SmartyPS2KeyMap keymap;

void setup()
{
  pinMode(0, INPUT);
  pinMode(1, INPUT);

  pinMode(LORATE_CLOCK_PIN, OUTPUT);
  pinMode(LORATE_CLOCK_LED_PIN, OUTPUT);

  pinMode(KEYBOARD_RD_PIN, INPUT_PULLUP);

  for (int bit = 0; bit < 8; bit++)
  {
    pinMode(KeyboardPort[bit], OUTPUT);
  }
  pinMode(KEYBOARD_BIT7_PIN, OUTPUT);
  digitalWrite(KEYBOARD_BIT7_PIN, LOW);

  if (autoMode)
    delay(7500); // for start without Keyboard connected
  else
    delay(500);

  keyboard.begin(PS2KEYBOARD_DATA_PIN, PS2KEYBOARDCLOCK_PIN);
  keyboard.echo();
  delay(6);
  uint16_t scan_code = keyboard.read();

  keyboard.setNoBreak(1);
  keyboard.setNoRepeat(1);
  //  keymap.selectMap((char *)"UK");
  //  keymap.selectMap((char *)"FR");
  //  keymap.selectMap((char *)"DE");
  //  keymap.selectMap((char *)"IT");
  //  keymap.selectMap((char *)"ES");
  attachInterrupt(digitalPinToInterrupt(KEYBOARD_RD_PIN), cpuReadsKeyboard, FALLING);
}

void cpuReadsKeyboard(void)
{
  digitalWrite(KEYBOARD_BIT7_PIN, LOW);
}

void sendCharToKeyboardPort(char c)
{
  for (int bit = 0; bit < 8; bit++)
  {
    if (c & (1 << (bit)))
      digitalWrite(KeyboardPort[bit], HIGH);
    else
      digitalWrite(KeyboardPort[bit], LOW);
  }
  digitalWrite(KeyboardPort[7], HIGH);
  digitalWrite(KEYBOARD_BIT7_PIN, HIGH);
}

void loop()
{
  // run pre-set command in auto-mode when PS/2 keyboard is not connected
  // only once after reboot of Keyboard controller
  if (autoMode && !autoCommandSent)
  {
    autoCommandSent = true;
    runAutoModeCommand();
  }

  // check PS2 input
  if (!digitalRead(KEYBOARD_BIT7_PIN) && keyboard.available())
  {
    uint16_t scan_code = keymap.remapKey(keyboard.read());
    uint8_t c = scan_code & 0xff;

    if (scan_code > 0)
    {
      // process Backspace, Left Arrow, Delete as Apple I backspace '_'
      switch (c)
      {
      case PS2_TAB:
      case PS2_KEY_TAB:
        runCommand();
        break;
      case PS2_BACKSPACE:
      case PS2_DELETE:
      case PS2_KEY_L_ARROW:
        c = '_';
        break;
      }
      // make all symbols uppercase (from 'a' (ASCII code 0x61) to 'z' (ASCII code 0x7A))
      // as in original Apple-1
      c = toupper(c);
      // print c to Keyboard Port to be read by CPU
      sendCharToKeyboardPort(c);
    }
  }

  // low-rate clock
  digitalWrite(LORATE_CLOCK_PIN, HIGH);
  digitalWrite(LORATE_CLOCK_LED_PIN, HIGH);
  delay(LORATE_CLOCK_PERIOD_MILLIS); // wait for a LORATE_CLOCK_PERIOD_MILLIS
  digitalWrite(LORATE_CLOCK_PIN, LOW);
  digitalWrite(LORATE_CLOCK_LED_PIN, LOW);
  delay(LORATE_CLOCK_PERIOD_MILLIS); // wait for a LORATE_CLOCK_PERIOD_MILLIS
}

// running pre-set Woz OS command for auto mode
void runAutoModeCommand()
{
  const int cmd_count = 1;
  String cmd1 = String("F000R\r"); // Woz face demo program at $F000
  String commands[] = {cmd1};
  for (int i = 0; i < cmd_count; i++)
    for (int j = 0; j < commands[i].length(); j++)
    {
      char c = commands[i].charAt(j);
      sendCharToKeyboardPort(c);
    }
}
// running pre-set Woz OS command (drawing 8x8 pixel art)
void runCommand()
{
  const int cmd_count = 4;
  String cmd1 = String("1111: 88 A8 50\r");
  String cmd2 = String(":07 61 92\r");
  String cmd3 = String(":94 67\r");
  String cmd4 = String("FC00R\r");
  String commands[] = {cmd1, cmd2, cmd3, cmd4};
  for (int i = 0; i < cmd_count; i++)
    for (int j = 0; j < commands[i].length(); j++)
    {
      char c = commands[i].charAt(j);
      sendCharToKeyboardPort(c);
    }
}