/*
 * multi-mode tv out terminal library for Arduino
 *
 * Dave Curran 2013-09-06
 *
 * Arduino Terminal Library - Dave Curran (www.tynemouthsoftware.co.uk)
 * Concept and Microcontroller Firmware - Daryl Rictor, Grant Searle
 *
 * 2013-09-06 - V0.1 - Initial Release
 * 2013-09-13 - V0.2 - Added 4 bit mode plus minor tidy up
 * 2013-09-16 - V0.3 - Added I2C mode
 * 2013-09-23 - V0.4 - I2C mode writing direct and bypassing Wire
 * 2013-09-28 - V0.5 - Added font and graphics options
 */

#include "Terminal.h"
#include "Arduino.h"

// ***************************************
// * CONSTRUCTORS 
// ***************************************

// Initialise the display for 8 bit mode
// The pins can be any that are convenient. 
Terminal::Terminal(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t avail, uint8_t ack)
{
  // store pin numbers
  _avail_pin = avail;
  _ack_pin = ack;

  _data_pins[0] = d0;
  _data_pins[1] = d1;
  _data_pins[2] = d2;
  _data_pins[3] = d3; 
  _data_pins[4] = d4;
  _data_pins[5] = d5;
  _data_pins[6] = d6;
  _data_pins[7] = d7; 

  // set pin modes
  pinMode(_ack_pin, INPUT);        
  pinMode(_avail_pin, OUTPUT);      

  for(uint8_t i=0; i<8; i++)
  {
    pinMode(_data_pins[i], OUTPUT);      
    digitalWrite(_data_pins[i], LOW);
  }

  _4bit_mode = false;
  _i2c_mode = false;

  clear();
}

// Initialise the display for 4 bit mode
// The pins can be any that are convenient. If using an Arduino, using pin 13 for ack will show activity
Terminal::Terminal(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t avail, uint8_t ack)
{
  // store pin numbers
  _avail_pin = avail;
  _ack_pin = ack;

  _data_pins[0] = d0;
  _data_pins[1] = d1;
  _data_pins[2] = d2;
  _data_pins[3] = d3; 
  _data_pins[4] = 0;
  _data_pins[5] = 0;
  _data_pins[6] = 0;
  _data_pins[7] = 0; 

  // set pin modes
  pinMode(_ack_pin, INPUT);        
  pinMode(_avail_pin, OUTPUT);      

  for(uint8_t i=0; i<4; i++)
  {
    pinMode(_data_pins[i], OUTPUT);      
    digitalWrite(_data_pins[i], LOW);
  }

  _4bit_mode = true;
  _i2c_mode = false;

  clear();
}

// initialise for I2C mode
Terminal::Terminal()
{
  _4bit_mode = false;
  _i2c_mode = true;
  _transmitting = false;

  DDRC |= 0x30; // set the two I2C pins as outputs

  // Two wire speed initialisation
  // SCL freq = CPU freq / (16+2*TWBR*Prescaler)
  TWSR = 0; // Prescaler = 1
  TWBR = 12; // Bit rate 12 = 400KHz for 16MHz clk

  clear();
}

// ***************************************
// * Display control functions
// ***************************************

// Clear the screen
void Terminal::clear()
{
  send(TERMINAL_CLEAR_SCREEN);
}

// Blink the cursor
void Terminal::cursorBlink()
{
  send(TERMINAL_CURSOR_BLINKING);
}

// use a solid cursor
void Terminal::cursorBlinkOff()
{
  send(TERMINAL_CURSOR_SOLID);
}

// Change the cursor to a block
void Terminal::cursorBlock()
{
  cursorCustom(0xDB);
}

// Change the cursor to an underscore (default)
void Terminal::cursorUnderscore()
{
  cursorCustom('_');
}

// no cursor
void Terminal::cursorOff()
{
  send(TERMINAL_CURSOR_SOLID);
  cursorCustom(0x00);
}

// set any character as the cursor character, 0x00 for off
void Terminal::cursorCustom(uint8_t c)
{
  send(TERMINAL_CURSOR_SET);
  send(c);
}

// set the font (use combinations of TERMAIN_FONT_x
void Terminal::setFont(uint8_t c)
{
  send(TERMINAL_SET_FONT);
  send(c);
}

// Set the cursor location
void Terminal::setCursor(uint8_t column, uint8_t row)
{
  setColumn(column);
  setRow(row);
}

// Set location to a given column
void Terminal::setColumn(uint8_t column)
{
  send(TERMINAL_SET_COLUMN);
  send(column);
}

// Set location to a given row
void Terminal::setRow(uint8_t row)
{
  send(TERMINAL_SET_ROW);
  send(row);
}

// Send the CTRL+LF pair
void Terminal::sendCRLF()
{
  send(TERMINAL_CARRIAGE_RETURN);
  send(TERMINAL_LINE_FEED);  
}

// ***************************************
// * Graphics functions
// ***************************************

// Set a pixel in 160x100 graphics - note any text on this line will be cleared
void Terminal::setPixel(uint8_t x, uint8_t y)
{
  if (x<160 && y<100)
  {
    send(TERMINAL_SET_PIXEL);
    send(x);  
    send(y);
  }
}

// Clear a pixel in 160x100 graphics - note any text on this line will be cleared
void Terminal::clearPixel(uint8_t x, uint8_t y)
{
  if (x<160 && y<100)
  {
    send(TERMINAL_CLEAR_PIXEL);
    send(x);  
    send(y);
  }
}

// draw a line from x1,y1 to x2,y2
void Terminal::drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
  int xdiff = x2 - x1;
  int ydiff = y2 - y1;
  int maxdiff = max(abs(xdiff),abs(ydiff));
  for(int n=0; n<maxdiff; n++)
  {
    setPixel(x1 + xdiff*n/maxdiff, y1 + ydiff*n/maxdiff);
  }
  // set the final pixel in case of rounding errors
  setPixel(x2, y2);
}

// clear a line from x1,y1 to x2,y2
void Terminal::clearLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
  int xdiff = x2 - x1;
  int ydiff = y2 - y1;
  int maxdiff = max(abs(xdiff),abs(ydiff));
  for(int n=0; n<maxdiff; n++)
  {
    clearPixel(x1 + xdiff*n/maxdiff, y1 + ydiff*n/maxdiff);
  }
  // clear the final pixel in case of rounding errors
  clearPixel(x2, y2);
}

// draw the outline of a box with opposite corners at x1,y1 and x2,y2
void Terminal::drawBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
  drawLine(x1,y1, x2,y1);
  drawLine(x2,y1, x2,y2);
  drawLine(x2,y2, x1,y2);
  drawLine(x1,y2, x1,y1);
}

// draw the filled box with opposite corners at x1,y1 and x2,y2
void Terminal::fillBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
  uint8_t ymin = min(y1,y2);
  uint8_t ymax = max(y1,y2);
  for(int y=ymin; y<=ymax; y++)
  {
    drawLine(x1,y, x2,y);
  }
}

// clear the area of a box with opposite corners at x1,y1 and x2,y2
void Terminal::clearBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
  uint8_t ymin = min(y1,y2);
  uint8_t ymax = max(y1,y2);
  for(int y=ymin; y<=ymax; y++)
  {
    clearLine(x1,y, x2,y);
  }
}

// draw the outline of a circle centred on x0,y0 with a radius of radius
void Terminal::drawCircle(uint8_t x0, uint8_t y0, uint8_t radius)
{
  int8_t x = radius;
  int8_t y = 0;
  int8_t radiusError = 1-x;

  while(x >= y)
  {
    setPixel(x + x0, y + y0);
    setPixel(y + x0, x + y0);
    setPixel(-x + x0, y + y0);
    setPixel(-y + x0, x + y0);
    setPixel(-x + x0, -y + y0);
    setPixel(-y + x0, -x + y0);
    setPixel(x + x0, -y + y0);
    setPixel(y + x0, -x + y0);

    y++;
    if(radiusError<0)
      radiusError+=2*y+1;
    else
    {
      x--;
      radiusError+=2*(y-x+1);
    }
  }
}

// fill a circle centred on x0,y0 with a radius of radius
void Terminal::fillCircle(uint8_t x0, uint8_t y0, uint8_t radius)
{
  for(int y=-radius; y<=radius; y++)
  {
    for(int x=-radius; x<=radius; x++)
    {
      if(x*x+y*y <= radius*radius)
      {
        setPixel(x0+x, y0+y);
      }
    }
  }
}

// clear a circle centred on x0,y0 with a radius of radius
void Terminal::clearCircle(uint8_t x0, uint8_t y0, uint8_t radius)
{
  for(int y=-radius; y<=radius; y++)
  {
    for(int x=-radius; x<=radius; x++)
    {
      if(x*x+y*y <= radius*radius)
      {
        clearPixel(x0+x, y0+y);
      }
    }
  }
}

// ***************************************
// * Send functions
// ***************************************

// Print a string with a linefeed at the end
void Terminal::printLine(String s)
{
  print(s);
  sendCRLF();
}

// Print a string
void Terminal::print(String s)
{
  // send character by character
  for(unsigned int n=0; n<s.length(); n++)
  {
    send(s[n]);
  }
}

// send a single byte
uint8_t Terminal::send(uint8_t c)
{
  if (_i2c_mode)
  {		
    return sendI2C(c);
  }
  else if (_4bit_mode)
  {
    return send4Bit(c);
  }
  else
  {
    return send8Bit(c);
  }	
}

// ***************************************
// * 4 and 8 bit parallel send functions
// ***************************************

// Internal 4 bit send
uint8_t Terminal::send4Bit(uint8_t c)
{
  uint8_t i=0;

  // Should already be low, set just in case
  digitalWrite(_avail_pin, LOW); 

  // Check to see if the acknowledge pin is low
  // If not then wait until it is (the display processor will change to low when ready)
  while (digitalRead(_ack_pin) == HIGH);

  // Move the data into the appropriate output pins
  // Start with the upper nibble
  for(i=0; i<4; i++)
  {
    digitalWrite(_data_pins[i], bitRead(c, i + 4));		
  }

  // wait for a bit
  asm volatile ("nop");
  asm volatile ("nop");
  asm volatile ("nop");
  asm volatile ("nop");

  // Flip the data avail bit to tell the display that high 4 bits are ready for display
  digitalWrite(_avail_pin, HIGH);

  // Check to see if the acknowledge pin is high
  // If not then wait until it is (the display processor will change to high when ready)
  while (digitalRead(_ack_pin) == LOW);

  // Move the data into the appropriate output pins
  // Now the lower nibble
  for(i=0; i<4; i++)
  {
    digitalWrite(_data_pins[i], bitRead(c, i));		
  }

  // wait a bit
  asm volatile ("nop");
  asm volatile ("nop");
  asm volatile ("nop");
  asm volatile ("nop");

  // Flip the data avail bit to tell the display that low 4 bits are ready for display
  digitalWrite(_avail_pin, LOW);	

  // success
  return 0;
}

// Internal 8 bit send
uint8_t Terminal::send8Bit(uint8_t c)
{  
  // Check to see if the acknowledge pin is the same as the data available pin
  // If not then wait until it is (the display processor will change it to be the same when ready)
  while (digitalRead(_avail_pin) != digitalRead(_ack_pin));

  // Move the data into the appropriate output pins
  for(uint8_t i=0; i<8; i++)
  {
    digitalWrite(_data_pins[i], bitRead(c, i));
  }

  // Flip the data avail bit to tell the display that there is a character/command ready for display
  digitalWrite(_avail_pin, !digitalRead(_avail_pin));

  // success
  return 0;
}

// ***************************************
// * I2C Functions
// ***************************************

// Two-wire interface definitions
#define TW_START		0x08
#define TW_MT_SLA_ACK 	0x18
#define TW_MT_DATA_ACK 	0x28
#define TW_WRITE		0
// this can be changed in the firmware
#define TWI_ADDRESS		0x01

uint8_t Terminal::sendI2C(uint8_t c)
{
  uint8_t retCode = 0;

  if (!_transmitting)
  {
    // send start
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); 

    // wait for response (blocking)
    while ((TWCR & (1<<TWINT))==0) 
    {
    }
    retCode = TWSR & 0xF8;
    if (retCode != TW_START)
    {
      // ERROR			
      return retCode; 
    }

    // Load SLA_W (address of display and low-write bit) into TWDR
    TWDR = TW_WRITE | (TWI_ADDRESS << 1);
    // Clear TWINT bit in TWCR to start transmission of address
    TWCR = (1<<TWINT) | (1<<TWEN);

    // Wait for confirmation
    while ((TWCR & (1<<TWINT))==0)
    {
    }		

    retCode=TWSR & 0xF8;
    if (retCode != TW_MT_SLA_ACK) 
    {
      // ERROR			
      return retCode; 
    }

    _transmitting = true;
  }

  // send the data
  TWDR = c;
  // Clear TWINT bit in TWCR to start transmission of data
  TWCR = (1<<TWINT) | (1<<TWEN); 

  // Wait
  while ((TWCR & (1<<TWINT))==0)
  {
  }
  retCode = TWSR & 0xF8;
  if (retCode != TW_MT_DATA_ACK)
  {
    // ERROR			
    return retCode; 
  }	

  // success
  return 0;
}
