/*
 * This is a simple example of the multi-mode tv out terminal which shows graphics drawing capabilities with a missile command style demo
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
  term.clear();
  term.cursorOff(); 
}

void loop() 
{
  // clear the screen
  term.clear();

  // draw the base line
  term.fillBox(0,99, 159,100);

  // draw the bases
  for(int b=0; b<3; b++)
  {
    byte pos = 27 + (b*54);
    term.setPixel(pos, 96);    
    term.drawLine(pos-2, 97, pos+2, 97);
    term.drawLine(pos-4, 98, pos+4, 98);    
  }

  // fire 5 shots
  for(int n=0; n<5; n++)
  {
    fireShot();
    delay(1000);
  }

  // game over
  term.clear();
  term.setFont(TERMINAL_FONT_40_BOLD_DOUBLE);
  term.setCursor(15, 12);
  term.setFont(TERMINAL_FONT_40_BOLD_DOUBLE);
  term.print("GAME OVER!");

  delay(5000);  
}

// fire a shot
void fireShot()
{
  // take aim
  uint8_t origin = random(0,159);
  uint8_t destination = random(0,159); 

  // fire
  // could have used term.drawLine(origin,0, destination,99);, but this adds a delay
  int diff = destination-origin;
  for(int y=0; y<99; y++)
  {
    term.setPixel(origin + (diff*y/99), y);
    delay(100);
  }

  // bang
  term.fillCircle(destination,99, 10);
  delay(200);
  term.clearCircle(destination,99, 10);
  delay(200);

  // clear it up
  term.clearLine(origin,0, destination,99);
  term.fillCircle(destination,99, 15);
  delay(200);
  term.clearCircle(destination,99, 15);
  delay(200);
}










