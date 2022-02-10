/*
 * This is a simple example of the multi-mode tv out terminal which displays the status of the 4 unused analogue inputs
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

// Analogue inputs
byte inputs[] = { A0, A1, A2, A3 };

void setup() {
}

void loop() {
  byte v;
  for (byte a = 0; a<4; a++)
  {
    // read the input
    v = analogRead(inputs[a]);    
    term.send('A');
    term.send(a+'0');
    term.print(" [");
    for(byte n=7; n>0; n--)
    {
      term.send(bitRead(v, n) ? '*' : '.');
    }
    term.print("]  ");
  }
  term.sendCRLF();

  // add a delay if it's going too fast
  //delay(1000);                  
}



