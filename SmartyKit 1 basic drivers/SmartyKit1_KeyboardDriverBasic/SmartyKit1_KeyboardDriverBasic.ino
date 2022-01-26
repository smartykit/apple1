 /*  SmartyKit 1 - PS/2 keyboard driver v.1.1
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

#include <PS2KeyAdvanced.h>
#include <PS2KeyMap.h>

// Keyboard Driver pins connections:
// D0 & D1 – reserved for Serial connection
// D2 –> PS/2 Socket Data pin
// D3 -> 4-16 ports decoder Kbd (2) out pin (signal is active when CPU reads Keyboatrd port)
// D4 -> PS/2 Socket Clk pin
// D5 -> Keyboard BIT7 pin output 
// D6-D13 -> Keyboard data bus output (8 pins) to connect to Keyboard port (char code is transfered here) 
// A4 -> Low-rate clock output for CPU CLK input
// A5 -> Low-rate clock output for indicating LED connection 

#define PS2KEYBOARDCLOCK_PIN  2
#define KEYBOARD_RD_PIN       3
#define PS2KEYBOARD_DATA_PIN  4
#define KEYBOARD_BIT7_PIN     5 

const int KeyboardPort[8] = {6, 7, 8, 9, 10, 11, 12, 13};

static boolean autoMode = false; //run pre-set command or wait for user input from PS/2 keyboard
static boolean autoCommandSent = false; // run pre-set command only once after reboot of Keyboard controller

//low-rate clock for tests on A4-A5
#define LORATE_CLOCK_PIN      A4
#define LORATE_CLOCK_LED_PIN  A5

//10 milliseconds = 100 times per second (100 Hz)
#define LORATE_CLOCK_PERIOD_MILLIS 100

PS2KeyAdvanced keyboard;
PS2KeyMap keymap;

void setup()
{
  pinMode(LORATE_CLOCK_PIN, OUTPUT);
  pinMode(LORATE_CLOCK_LED_PIN, OUTPUT);

  pinMode(KEYBOARD_RD_PIN, INPUT_PULLUP); 
  
  for (int bit = 0; bit < 8; bit++) {
    pinMode(KeyboardPort[bit], OUTPUT); 
  }
  pinMode(KEYBOARD_BIT7_PIN, OUTPUT); 
  digitalWrite(KEYBOARD_BIT7_PIN, LOW);

  Serial.begin(9600);
  Serial.println("SmartyKit 1 PS2 Keyboard is ready...");

  if (autoMode)
    delay(7500); //for start without Keyboard connected
  else
    delay(500);

  keyboard.begin(PS2KEYBOARD_DATA_PIN, PS2KEYBOARDCLOCK_PIN);
  keyboard.echo();
  delay( 6 );
  uint16_t scan_code = keyboard.read();

  if( (scan_code & 0xff) == PS2_KEY_ECHO || (scan_code & 0xff) == PS2_KEY_BAT || (scan_code & 0xff) == 0xe8 )
    Serial.println( "Keyboard OK.." );    // Response was Echo or power up
  else
    if ((scan_code & 0xff) == 0)
    {
      Serial.println( "Keyboard Not Found" );
    }
    else
    {
      Serial.print( "Invalid Code received of 0x" );
      Serial.println(scan_code, HEX);
    }

  keyboard.setNoBreak(1);
  keyboard.setNoRepeat(1);
  keymap.selectMap((char *)"UK");
  attachInterrupt(digitalPinToInterrupt(KEYBOARD_RD_PIN), cpuReadsKeyboard, FALLING); 
}

void cpuReadsKeyboard(void)
{
  digitalWrite(KEYBOARD_BIT7_PIN, LOW);
}

void sendCharToKeyboardPort(char c)
{  
  if (c == '\r') 
    Serial.println();
  else
    Serial.print(c);

  for (int bit = 0; bit < 8 ; bit++) 
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
  //run pre-set command in auto-mode when PS/2 keyboard is not connected
  //only once after reboot of Keyboard controller 
  if (autoMode && !autoCommandSent)
  {
    autoCommandSent = true;
    runAutoModeCommand();
  }

  //check PS2 input
  if (!digitalRead(KEYBOARD_BIT7_PIN) && keyboard.available()) 
  {
    uint16_t scan_code = keymap.remapKey(keyboard.read());
    char c = scan_code & 0xff;

    Serial.print(":0x");
    Serial.print(scan_code, HEX);
    Serial.print(":");

    //process Backspace, Left Arrow, Delete as Apple I backspace '_'
    switch (c) 
    {
      case PS2_KEY_TAB:
        runCommand();
        break;
      case PS2_KEY_BS:
      case PS2_KEY_DELETE:
      case PS2_KEY_L_ARROW:
        c = '_';
        break;
      case PS2_KEY_ENTER:
        c = '\r';
        break;
      case PS2_KEY_SPACE:
        c = ' ';
        break;
    }

    //make all symbols uppercase (from 'a' (ASCII code 0x61) to 'z' (ASCII code 0x7A))
    //as in original Apple-1
    c = toupper(c);
    //print c to Keyboard Port to be read by CPU
    sendCharToKeyboardPort(c);
  }

  //low-rate clock
  digitalWrite(LORATE_CLOCK_PIN, HIGH);
  digitalWrite(LORATE_CLOCK_LED_PIN, HIGH);
  delay(LORATE_CLOCK_PERIOD_MILLIS);                       // wait for a LORATE_CLOCK_PERIOD_MILLIS
  digitalWrite(LORATE_CLOCK_PIN, LOW);
  digitalWrite(LORATE_CLOCK_LED_PIN, LOW);    
  delay(LORATE_CLOCK_PERIOD_MILLIS);                       // wait for a LORATE_CLOCK_PERIOD_MILLIS
}

//running pre-set Woz OS command for auto mode
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
//running pre-set Woz OS command (drawing 8x8 pixel art)
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
