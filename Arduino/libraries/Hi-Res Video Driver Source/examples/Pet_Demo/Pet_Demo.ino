/*
 * This is a simple example of the multi-mode tv out terminal which shows an emulation of the Commodore Pet startup message
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

void setup() {
  // set the cursor to a block
  term.cursorBlock();

  // show startup messages  
  term.printLine("*** commodore basic 4.0 ***");
  term.sendCRLF();
  term.printLine(" 31743 bytes free");
  term.sendCRLF();
  term.printLine("ready.");
}

void loop() {

}


