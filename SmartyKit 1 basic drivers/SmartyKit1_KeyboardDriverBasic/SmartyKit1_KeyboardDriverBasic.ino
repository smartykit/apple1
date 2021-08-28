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

#include "PS2Keyboard.h"

// Keyboard Driver pins connections:
// D0 & D1 – reserved for Serial connection
// D2 –> PS/2 Socket Data pin
// D3 -> 4-16 ports decoder Kbd (2) out pin (signal is active when CPU reads Keyboatrd port)
// D4 -> PS/2 Socket Clk pin
// D5 -> Keyboard BIT7 pin output 
// D6-D13 -> Keyboard data bus output (8 pins) to connect to Keyboard port (char code is transfered here) 
// A4 -> Low-rate clock output for CPU CLK input
// A5 -> Low-rate clock output for indicating LED connection 

const int PS2Socket_Data =  2;
const int CPUreadsKeyboardPin = 3;
const int PS2Socket_Clk = 4;


const int KeyboardBIT7pin =  5; // 
const int DataBus[8] = {6, 7, 8, 9, 10, 11, 12, 13};
static boolean BIT7flag = false;
static boolean autoMode = true; //run pre-set command or wait for user input from PS/2 keyboard
static boolean autoCommandSent = false; // run pre-set command only once after reboot of Keyboard controller

//low-rate clock for tests on A4-A5
#define CLOCK A4
#define LED A5
int lowRateClockPeriod = 10; //10 milliseconds = 100 times per second (100 Hz)

//#define _WITH_SERIAL_
#define _WITH_PS2_

#ifdef _WITH_PS2_
PS2Keyboard keyboard;
#endif

void setup()
{
  pinMode(CLOCK, OUTPUT);
  pinMode(LED, OUTPUT);

  pinMode(CPUreadsKeyboardPin, INPUT_PULLUP); 
  
   for (int count = 1; count <= 8; count++) {
    pinMode(DataBus[count-1], OUTPUT); 
  };
  pinMode(KeyboardBIT7pin, OUTPUT); 
  KeyboardBIT7_Disable();
  
  if (autoMode)
    delay(7500); //for start without Keyboard connected
  else
    delay(500);

#ifdef _WITH_PS2_
  keyboard.begin(PS2Socket_Clk, PS2Socket_Data);
#endif
  attachInterrupt(1, cpuReadsKeyboard, FALLING); 

#ifdef _WITH_SERIAL_
  Serial.begin(9600);
  Serial.println("SmartyKit 1 Serial Keyboard is ready...");
 #endif
}

void cpuReadsKeyboard(void)
{
  KeyboardBIT7_Disable();
}

void KeyboardBIT7_Enable()
{
  digitalWrite(KeyboardBIT7pin, HIGH);
  BIT7flag = true;
}
void KeyboardBIT7_Disable()
{
  digitalWrite(KeyboardBIT7pin, LOW);
  BIT7flag = false;
}

void sendCharToKeyboardPort(char c)
{
  while(BIT7flag == true) //wait untill the previous char is read by CPU
    delay(5);
    
  for (int count = 1; count <= 8 ; count++) 
  {
     if (c & (1 << (count-1))) 
        digitalWrite(DataBus[count-1], HIGH);
      else
        digitalWrite(DataBus[count-1], LOW);
  }
  digitalWrite(DataBus[7], HIGH);
  KeyboardBIT7_Enable(); 
}

void loop() { 

  //run pre-set command in auto-mode when PS/2 keyboard is not connected
  //only once after reboot of Keyboard controller 
  if (autoMode && !autoCommandSent)
  {
    autoCommandSent = true;
    runAutoModeCommand();
  }

#ifdef _WITH_PS2_
  //check PS2 input
  if (keyboard.available()) {
    char c = keyboard.read();

    if (c == PS2_TAB)  
      runCommand();
    
    //process Backspace, Left Arrow, Delete as Apple I backspace '_'
    if (c == PS2_BACKSPACE) {
      c = '_';
    } else if (c == PS2_LEFTARROW) {
       c = '_';
    } else if (c == PS2_DELETE) {
      c = '_';
    }

    int scan_code = (int)c;
    //make all symbols uppercase (from 'a' (ASCII code 0x61) to 'z' (ASCII code 0x7A))
    //as in original Apple-1
     if (scan_code >= 0x61 && scan_code <= 0x7A)
      scan_code -= 0x20;
    c = (char) scan_code;
    //print c to Keyboard Port to be read by CPU
    sendCharToKeyboardPort(c);
    #ifdef _WITH_SERIAL_
    Serial.print(c);
    if (c == '\r')
      Serial.println();
    #endif
  }
#endif

  //low-rate clock
  digitalWrite(CLOCK, HIGH);
  digitalWrite(LED, HIGH);
  delay(lowRateClockPeriod);                       // wait for a lowRateClockPeriod
  digitalWrite(CLOCK, LOW);
  digitalWrite(LED, LOW);    
  delay(lowRateClockPeriod);                       // wait for a lowRateClockPeriod
}

//running pre-set Woz OS command for auto mode
void runAutoModeCommand()
{
  const int CMD_COUNT = 1;
  String cmd1 = String("F000R\r"); // Woz face demo program at $F000 
  String commands[] = {cmd1};
  for (int i = 0; i < CMD_COUNT; i++)
    for (int j = 0; j < commands[i].length(); j++)
    {
      char c = commands[i].charAt(j);
      sendCharToKeyboardPort(c);
    }
}
//running pre-set Woz OS command (drawing 8x8 pixel art)
void runCommand()
{
  const int CMD_COUNT = 4;
  String cmd1 = String("1111: 88 A8 50\r");
  String cmd2 = String(":07 61 92\r");
  String cmd3 = String(":94 67\r");
  String cmd4 = String("FC00R\r");
  String commands[] = {cmd1, cmd2, cmd3, cmd4};
  for (int i = 0; i < CMD_COUNT; i++)
    for (int j = 0; j < commands[i].length(); j++)
    {
      char c = commands[i].charAt(j);
      sendCharToKeyboardPort(c);
    }
  
}
