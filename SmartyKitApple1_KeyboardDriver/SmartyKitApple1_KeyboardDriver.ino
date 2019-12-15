/*  SmartyKit Apple I replica - keyboard driver
 *  http://apple1.smartykit.org/ 
 *  Copyright (C) 2019, Sergey Panarin <contact@smartykit.org>
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

const int DataPin = 3;
const int IRQpin =  2;


const int pinKBDCR =  12; // 

int DataBus[8] = {4, 5, 6, 7, 8, 9, 10, 11};

PS2Keyboard keyboard;

void setup()
{
   for (int count = 1; count <= 8; count++) {
    pinMode(DataBus[count-1], OUTPUT); 
  };
  pinMode(pinKBDCR, OUTPUT); 
  KBDCR_Disable();
  
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  Serial.println("Keyboard:");
 
}

void KBDCR_Enable()
{
  digitalWrite(pinKBDCR, HIGH);
}
void KBDCR_Disable()
{
  digitalWrite(pinKBDCR, LOW);
}

void loop() {
  KBDCR_Disable();
  
  if (keyboard.available()) {
    
    // read the next key
    char c = keyboard.read();
    /*
    // check for some of the special keys
    if (c == PS2_ENTER) {
      Serial.println();
    } else if (c == PS2_TAB) {
      Serial.print("[Tab]");
    } else if (c == PS2_ESC) {
      Serial.print("[ESC]");
    } else if (c == PS2_PAGEDOWN) {
      Serial.print("[PgDn]");
    } else if (c == PS2_PAGEUP) {
      Serial.print("[PgUp]");
    } else if (c == PS2_LEFTARROW) {
      Serial.print("[Left]");
    } else if (c == PS2_RIGHTARROW) {
      Serial.print("[Right]");
    } else if (c == PS2_UPARROW) {
      Serial.print("[Up]");
    } else if (c == PS2_DOWNARROW) {
      Serial.print("[Down]");
    } else if (c == PS2_DELETE) {
      Serial.print("[Del]");
    } else {
      
      // otherwise, just print all normal characters
      Serial.print(c);
    }
    */


    //process Backspace, Left Arrow, Delete as Apple I backspace '_'
    if (c == PS2_BACKSPACE) {
      c = '_';
    } else if (c == PS2_LEFTARROW) {
       c = '_';
    } else if (c == PS2_DELETE) {
      c = '_';
    }
    
    //print c to register
    for (int count = 1; count <= 8 ; count++) 
    {
      if ((int)c & (1 << (count-1))) 
        digitalWrite(DataBus[count-1], HIGH);
      else
        digitalWrite(DataBus[count-1], LOW);
    }
    digitalWrite(DataBus[7], HIGH);
    KBDCR_Enable();
    delay(4);
  }
}
