/*
 * multi-mode tv out terminal library for Arduino
 *
 * Dave Curran 2013-09-28
 *
 * Arduino Terminal Library - Dave Curran (www.tynemouthsoftware.co.uk)
 * Concept and Microcontroller Firmware - Daryl Rictor, Grant Searle
 *
 */

#ifndef Terminal_h
#define Terminal_h

#include <arduino.h>

// Control Codes
#define TERMINAL_CURSOR_HOME        0x01
#define TERMINAL_CURSOR_SET         0x02
#define TERMINAL_CURSOR_BLINKING    0x03
#define TERMINAL_CURSOR_SOLID 		0x04
#define TERMINAL_SET_PIXEL			0x05
#define TERMINAL_CLEAR_PIXEL		0x06
#define TERMINAL_BACKSPACE          0x08
#define TERMINAL_TAB                0x09
#define TERMINAL_LINE_FEED          0x0A
#define TERMINAL_CLEAR_SCREEN       0x0C
#define TERMINAL_CARRIAGE_RETURN    0x0D
// Set column 0 to 79 (2nd uint8_t is the column number)
#define TERMINAL_SET_COLUMN         0x0E
// Set row 0 to 24 (2nd uint8_t is the row number)
#define TERMINAL_SET_ROW            0x0F
// Delete to the start of the line
#define TERMINAL_DELETE_BEFORE_LINE 0x10 
// Delete to the end of the line
#define TERMINAL_DELETE_AFTER_LINE  0x11
// Delete to start of screen
#define TERMINAL_DELETE_BEFORE_PAGE 0x12
// Delete to end of screen
#define TERMINAL_DELETE_AFTER_PAGE  0x13
#define TERMINAL_SCROLL_UP          0x14
#define TERMINAL_SCROLL_DOWN        0x15
#define TERMINAL_SCROLL_LEFT        0x16
#define TERMINAL_SCROLL_RIGHT       0x17
#define TERMINAL_SET_FONT			0x18

// Treat next uint8_t as a character (to allow PC DOS char codes 1 to 31 to be displayed on screen)
#define TERMINAL_NEXT_IS_CHAR       0x1A 
// ESC - reserved for ANSI sequences
#define TERMINAL_ESCAPE             0x1B
#define TERMINAL_CURSOR_RIGHT       0x1C
#define TERMINAL_CURSOR_LEFT        0x1D
#define TERMINAL_CURSOR_UP          0x1E
#define TERMINAL_CURSOR_DOWN        0x1F

#define TERMINAL_DELETE             0x7F

// font options
#define TERMINAL_FONT_40_CHAR		0x00
#define TERMINAL_FONT_80_CHAR		0x01
#define TERMINAL_FONT_NORMAL		0x00
#define TERMINAL_FONT_BOLD			0x02
#define TERMINAL_FONT_SINGLE_HEIGHT	0x00
#define TERMINAL_FONT_DOUBLE_HEIGHT	0x04
#define TERMINAL_FONT_GRAPHICS		0x80

#define TERMINAL_FONT_40_NORMAL_SINGLE	0x00
#define TERMINAL_FONT_80_NORMAL_SINGLE	0x01
#define TERMINAL_FONT_40_BOLD_SINGLE	0x02
#define TERMINAL_FONT_80_BOLD_SINGLE	0x03
#define TERMINAL_FONT_40_NORMAL_DOUBLE	0x04
#define TERMINAL_FONT_80_NORMAL_DOUBLE	0x05
#define TERMINAL_FONT_40_BOLD_DOUBLE	0x06
#define TERMINAL_FONT_80_BOLD_DOUBLE	0x07

class Terminal
{
public:
  Terminal(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t avail, uint8_t ack);
  Terminal(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t avail, uint8_t ack);
  Terminal();

  void begin();
  void clear();
  void cursorBlink();
  void cursorBlinkOff();
  void cursorUnderscore();	
  void cursorBlock();
  void cursorOff();
  void cursorCustom(uint8_t c);
  void setFont(uint8_t c);
  void setCursor(uint8_t column, uint8_t row);
  void setColumn(uint8_t column);
  void setRow(uint8_t row);
  void setPixel(uint8_t x, uint8_t y);
  void clearPixel(uint8_t x, uint8_t y);
  void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
  void clearLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
  void drawBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
  void fillBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
  void clearBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
  void drawCircle(uint8_t x0, uint8_t y0, uint8_t radius);
  void fillCircle(uint8_t x0, uint8_t y0, uint8_t radius);
  void clearCircle(uint8_t x0, uint8_t y0, uint8_t radius);
  void sendCRLF();
  void printLine(String s);
  void print(String s);
  uint8_t send(uint8_t c);
  
private:
  uint8_t send4Bit(uint8_t c);
  uint8_t send8Bit(uint8_t c);
  uint8_t sendI2C(uint8_t c);
  
  uint8_t _data_pins[8]; // data outputs  
  uint8_t _avail_pin; // output, tell the display that new data is available
  uint8_t _ack_pin; // input, the display acknowledges the input
  bool _4bit_mode; // is the interface in 4 bit mode
  bool _i2c_mode; // is this in I2C mode
  bool _transmitting; // in the middle of an I2C packet
};

#endif


