 /*  SmartyKit 1 - 40 keys Keyboard driver v.1.0
 *  http://www.smartykit.io/ 
 *  Copyright (C) 2021, Sergey Panarin <sergey@smartykit.io>
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
#undef DEBUG

const int KEYBOARD_ROWS = 4;
const int KEYBOARD_COLS = 10;

const int keyboardRowsPins[KEYBOARD_ROWS] = {A2, A3, A4, A5};
const int keyboardColsPins[KEYBOARD_COLS] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

const int latchPin = 2;
const int clockPin = A1;
const int dataPin = A0;

const int keyReadyPin = 3;
static boolean BIT7flag = false;

const char cShift = char(0x80);
const char cEnter = char(0x0D);
const char cSpace = char(0x20);
const char cDelete = char(0x7F);

const unsigned char keyboard[KEYBOARD_ROWS][KEYBOARD_COLS] = 
{
    {'1','2','3','4','5','6','7','8','9','0',},
    {'Q','W','E','R','T','Y','U','I','O','P',},
    {'A','S','D','F','G','H','J','K','L', cEnter,},
    {cShift,'Z','X','C','V','B','N', 'M',cSpace,cDelete,},
  };

const unsigned char keyboardShift[KEYBOARD_ROWS][KEYBOARD_COLS] = 
{
    {'!','@','#','$','%','^','&','*','(',')',},
    {'Q','{','}','[',']','\\','_','-','+','=',},
    {'A','S','D','F','G',':',';','"','\'', cEnter,},
    {cShift,'Z','<','>',',','.','?', '/',cSpace,cDelete,},
  };

void setup() {
  // put your setup code here, to run once:
  for (int i=0; i < KEYBOARD_ROWS; i++)
    pinMode(keyboardRowsPins[i], INPUT_PULLUP);
  for (int i=0; i < KEYBOARD_COLS; i++)
    pinMode(keyboardColsPins[i], OUTPUT);


  pinMode(keyReadyPin, OUTPUT);
  digitalWrite(keyReadyPin, HIGH);
  
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

 #ifdef DEBUG
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, '1'); # hex code 0x31 = 0011.0001b
  digitalWrite(latchPin, HIGH);
 #endif

 Serial.begin(115200);
}

void loop() {

  // Read user input if available.
  if (Serial.available()){
    char c = Serial.read();
    sendCharToKeyboardPort(c);
  }

  // put your main code here, to run repeatedly:
  char c = getKey();
  if(c)
  {
    if (c == cEnter)
      Serial.println();
    else
      Serial.print(c);

    sendCharToKeyboardPort(c);
  }
}

char getKey()
{
  char c = NULL;
  bool bShift = getShift();
  for (int j=0; j < KEYBOARD_COLS; j++)
  {
    scanCol(j, bShift);
    for (int i=KEYBOARD_ROWS-1; i >= 0; i--) //start from bottom-left corner with SHIFT button
    {
      int val = digitalRead(keyboardRowsPins[i]);
      if (val == 0)
      {
        c = keyboard[i][j];
        if (c == cShift)
          c = NULL;
        else
        {
           if (bShift)
            c = keyboardShift[i][j];       
        }
        delay(150);
      }
    }
  }   
  return c;
}

bool getShift()
{
  bool bShift = false;
  int shiftCol = 0; // first column
  int shiftRow = KEYBOARD_ROWS-1; // A row
  
  scanCol(shiftCol, false);
  int val = digitalRead(keyboardRowsPins[shiftRow]);
  if (val == 0)
    bShift = true;
    
  return bShift;
}

void scanCol(int col, bool bShift)
{
  if(bShift)
      digitalWrite(keyboardColsPins[0], LOW);
      
  for (int i=0; i < KEYBOARD_COLS; i++)
  {
    if (i == col)
        digitalWrite(keyboardColsPins[i], LOW);
    else
        digitalWrite(keyboardColsPins[i], HIGH);
    
  }
}



void cpuReadsKeyboard(void)
{
  KeyboardBIT7_Disable();
}

void KeyboardBIT7_Enable()
{
  digitalWrite(keyReadyPin, HIGH);
  BIT7flag = true;
}
void KeyboardBIT7_Disable()
{
  digitalWrite(keyReadyPin, LOW);
  BIT7flag = false;
}

void sendCharToKeyboardPort(char c)
{
//  while(BIT7flag == true) //wait untill the previous char is read by CPU
//    delay(5);
    
  digitalWrite(keyReadyPin, LOW);
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, c);
  digitalWrite(latchPin, HIGH);
  delay(30);
  digitalWrite(keyReadyPin, HIGH);
  KeyboardBIT7_Enable(); 
}
