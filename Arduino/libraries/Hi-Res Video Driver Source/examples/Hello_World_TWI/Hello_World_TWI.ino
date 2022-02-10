/*
 * This is a simple example of the multi-mode tv out terminal which sends a Hello World message and shows the character set
 *
 * Dave Curran 2013-09-28
 *
 * Arduino Terminal Library - Dave Curran (www.tynemouthsoftware.co.uk)
 * Concept and Microcontroller Firmware - Daryl Rictor, Grant Searle
 *
 * The display microcontroller is wired as follows:
 * pin 28 (SCL) ==> Display pin 28 (SCL)
 * pin 27 (SDA) ==> Display pin 27 (SDA)
 * Arduino Reset ==> Display pin 1 (Reset) - Reset (Optional)
 *
 * The two I2C data lines need to be pulled high to 5V via 2K2 resistors.
 *
 */

#include <Terminal.h>

// Create a terminal in TWI mode
Terminal term;

void setup() 
{
  // Initialise the terminal 
  term.cursorOff();

  // show hello world
  term.setCursor(34,0);
  term.printLine("Hello World!");
  term.printLine("");
  term.printLine("     80x25 text output library for Arduino in two wire interface (I" "\xFD" "C) Mode");
  term.printLine("");
  // Show the 80 character positions
  term.print("00000000001111111111222222222233333333334444444444555555555566666666667777777777");
  term.printLine("01234567890123456789012345678901234567890123456789012345678901234567890123456789");

  // Show the character set  
  term.printLine("    0 1 2 3 4 5 6 7 8 9 A B C D E F         0 1 2 3 4 5 6 7 8 9 A B C D E F");
  for(byte a=0; a<2; a++)
  {
    term.print("  \xDA");
    for(int n=0; n<33; n++)
    {
      term.send(0xC4);
    }
    term.print("\xBF   ");  
  }

  for (byte a=0; a<8; a++)
  {
    for (byte b=0; b<2; b++)
    {
      term.send(' ');
      
      byte msb = b*8 + a;
      
      if (msb>9)
      {
        term.send(msb + 0x37);
      }
      else
      {
        term.send(msb + 0x30);
      }
            
      byte base = (msb * 0x10);
      term.print("\xB3 ");      
      for (uint8_t n = 0; n<0x10; n++)
      {
        byte c=base + n;
        if (c<0x20 || c==0x7f)
        {
          term.send(TERMINAL_NEXT_IS_CHAR);
        }
        term.send(c);
        term.send(' ');
      }
      term.send(0xB3);
      if (msb>9)
      {
        term.send(msb + 0x37);
      }
      else
      {
        term.send(msb + 0x30);
      }
      term.print("  ");
    }
  }

  for(byte a=0; a<2; a++)
  {
    term.print("  \xC0");
    for(int n=0; n<33; n++)
    {
      term.send(0xC4);
    }
    term.print("\xD9   ");  
  }
  term.printLine("    0 1 2 3 4 5 6 7 8 9 A B C D E F         0 1 2 3 4 5 6 7 8 9 A B C D E F");
  
  // useful web addresses 
  term.setCursor(28, 21);
  term.printLine("searle.hostei.com/grant");

  term.setCursor(26, 23);
  term.printLine("www.tynemouthsoftware.co.uk");


}

#define DELAY 250

void loop() 
{
  setCharacterAtCorners(0xC4);
  delay(DELAY);
  setCharacterAtCorners('\\');
  delay(DELAY);
  setCharacterAtCorners(0xB3);
  delay(DELAY);
  setCharacterAtCorners('/');
  delay(DELAY);
}

void setCharacterAtCorners(char c)
{
  // draw the corners (note if you draw at (79,24) it will scroll down to the next line and the top line will scroll off the top of the display)
  term.setCursor(0,0);   
  term.send(c);   
  term.setCursor(79,0);
  term.send(c);   
  term.setCursor(0,23);   
  term.send(c);
  term.setCursor(79,23);
  term.send(c);
}




