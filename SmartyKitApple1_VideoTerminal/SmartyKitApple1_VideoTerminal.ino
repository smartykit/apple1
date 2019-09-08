/*  SmartyKit Apple I replica - video driver
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

#include <TVout.h>
#include <avr/pgmspace.h>

const int IRQpin =  2; // write to display

const int pinDA =  12; // read

//int DataBus[8] = {4, 5, 6, 7, 8, 9, 10, 11};
//TV uses pin 7 and pin 9
int DataBus[8] = {4, 5, 6, 3, 8, 13, 10, 11};


int bitDA = 0;

byte scan_code=0;  

TVout TV;

void setup() {
  TV.begin(PAL, 128, 96);
  TV.selectFont(font6x8);
  TV.println("Hello!\r\nI am SmartyKit Apple I replica\n");

   delay(1000);
  for (int count = 1; count <= 8; count++) {
    pinMode(DataBus[count-1], INPUT); 
  };
  pinMode(IRQpin, INPUT); 
  pinMode(pinDA, OUTPUT); 

  //attaching an IRQ to IRQpin
  attachInterrupt(0, videoCharInterrupt, RISING); 
  Serial.begin(9600); 
}

void loop() {
  delay(100);
}


//interruption service routine (ISR)
void videoCharInterrupt(void) {        

  scan_code = 0;
  for (int count = 1; count <= 8 ; count++) {
    int pinValue = digitalRead(DataBus[count-1]);    
    scan_code |= pinValue << (count-1);   
  };

  if (scan_code == 0x7F)
     return; //skip initial setup value
  
  bitDA = 1;
  digitalWrite(pinDA, HIGH);
  
  if (scan_code != 127)
     scan_code -= 128;
   
  if (scan_code == 0xD)
  {
      Serial.println();
      TV.println("");
  }
  else
  {
      Serial.print((char)scan_code); 
      TV.print((char)scan_code); 
  } 

  bitDA = 0;
  digitalWrite(pinDA, LOW); 
}
