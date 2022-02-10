/*
 * This is a simple example of the multi-mode tv out terminal which shows the various font options in I2C mode
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
  term.printLine("This is the default font set in hardware");

  term.setFont(TERMINAL_FONT_80_NORMAL_SINGLE);
  term.sendCRLF();
  term.printLine("80 Character normal single line");
  term.setFont(TERMINAL_FONT_80_BOLD_SINGLE);
  term.printLine("80 Character bold single line");
  term.sendCRLF();

  term.setFont(TERMINAL_FONT_80_NORMAL_DOUBLE);
  term.printLine("80 Character normal double height");
  term.setFont(TERMINAL_FONT_80_BOLD_DOUBLE);
  term.printLine("80 Character bold double height");

  term.setFont(TERMINAL_FONT_40_NORMAL_SINGLE);
  term.sendCRLF();
  term.printLine("40 Character normal single line");
  term.setFont(TERMINAL_FONT_40_BOLD_SINGLE);
  term.printLine("40 Character bold single line");
  term.sendCRLF();

  term.setFont(TERMINAL_FONT_40_NORMAL_DOUBLE);
  term.printLine("40 Character normal double height");
  term.setFont(TERMINAL_FONT_40_BOLD_DOUBLE);
  term.printLine("40 Character bold double height");

  term.setFont(TERMINAL_FONT_80_NORMAL_SINGLE);
  term.sendCRLF();
  term.printLine("Normal Font:");
  term.printLine("01234567890 ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz !\"#$%^&*()-+=*");

  term.setFont(TERMINAL_FONT_80_BOLD_SINGLE);
  term.printLine("Bold Font:");
  term.print("01234567890 ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz !\"#$%^&*()-+=*");
}

void loop() 
{
}





