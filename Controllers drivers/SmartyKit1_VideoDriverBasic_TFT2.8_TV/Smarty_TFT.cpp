/*  SmartyKit 1 - 2.8" TFT 320x240 Display driver
 *  http://www.smartykit.io/ 
 *  Copyright (C) 2019-2022, Sergey Panarin <contact@smartykit.io>
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

#include "Smarty_TFT.h"

int tftPortrait = TFT_PORTRAIT;

volatile int screenRow = 0;
volatile int screenCol = 0;

// TO-DO: blinking cursor (driver function)


SmartyKit_DisplayDriver::SmartyKit_DisplayDriver(int cs, int dc, int mosi, int clk, int rst, int miso)
{
      _dc = dc;
      _rst = rst;
      _cs = cs;
      _sck = clk;
      _mosi = mosi;
      _miso = miso;
     
      connection = TFT_SOFT_SPI;
}


void SmartyKit_DisplayDriver::setup(uint16_t setupColor, uint16_t setupBgColor, char* madeWithLoveString)
{      
      initSPI();

      uint8_t cmd, x, numArgs;
      const uint8_t *addr = initcmd;
      while ((cmd = pgm_read_byte(addr++)) > 0) {
        x = pgm_read_byte(addr++);
        numArgs = x & 0x7F;

        #if defined(_SMARTY_DEBUG_)
        Serial.print(F("Initcmd: cmd = "));Serial.print(cmd, HEX);
        Serial.print(F(", x = "));Serial.print(x, HEX);
        Serial.print(F(", addr = "));Serial.print((uint8_t)addr, HEX);
        Serial.print(F(", numArgs = "));Serial.print(numArgs, HEX);
        Serial.println();
        #endif

        sendCommand(cmd, addr, numArgs);
        delay(10);
        addr += numArgs;
        if (x & 0x80)
          delay(150);
      }

      clipScreen = SCREEN_FULL_SCREEN;
      scrollLine = 0;
      cursor_x = 0;               
      cursor_y = 0;
      textsize_x = 1;
      textsize_y = 1;
      _TFTwidth = ILI9341_TFTWIDTH;
      _TFTheight = ILI9341_TFTHEIGHT;
      _workingScreenWidth = SCREEN_WIDTH;
      _workingScreenHeight = SCREEN_HEIGHT; 
      screen_col = 0;
      screen_row = 0;
      
      color = setupColor;
      bgColor = setupBgColor;
  
      if (tftPortrait == TFT_PORTRAIT)
      {
        setRotation(0);
        clearFullScreen(bgColor);
        //start right from the top-left corner 
        _workingScreenTopMargin = 0;
        _workingScreenLeftMargin = 0; 
      }
      if (tftPortrait == TFT_LANDSCAPE) 
      {
        setRotation(3);
        clearFullScreen(bgColor);
        _workingScreenTopMargin = (_TFTheight - SCREEN_ROWS*LINE_HEIGHT)/2;
        _workingScreenLeftMargin = (_TFTwidth - SCREEN_COLS*LINE_WIDTH)/2; 
      }
      //drawing splash screen
      strcpy(madeWithLove, madeWithLoveString);
      splashScreen();

      if (tftPortrait == TFT_PORTRAIT)
      {
        //set built-in hardware scrolling
        setScrollMargins(0, ILI9341_TFTHEIGHT - SCREEN_HEIGHT);
        clipScreen = SCREEN_CLIPPED;        
      }
 
      bCursorOn = false;
      setCursor(0,0);
      clearScreen(bgColor);
      // test ASCII art (a person)
//      print(' ',color);print('o', color);print(' ', color); print('\n', color); 
//      print('/',color);print('|', color);print('\\', color); print('\n', color);
//      print('/',color);print(' ', color);print('\\', color); print('\n', color);
      // startup ASCII art
      ASCIIart();
}


void SmartyKit_DisplayDriver::ASCIIart(void)
{ 

  char c = '\0';
  char* ptrBuffer;

  for (int i = 0; i < SCREEN_ROWS; i++)
  {
    ptrBuffer = (char*) malloc(2*SCREEN_COLS);
    if (ptrBuffer != NULL)
    {
      //reading current string from PROGMEM to RAM
      strcpy_P(ptrBuffer, (char *)pgm_read_word(&(string_table[i])));
   
      for (int j = 0; j < SCREEN_COLS; j++)
      {
           c = ptrBuffer[j];
           print(c,color);
      }
      free(ptrBuffer);
    }
  }
  return;
}

void SmartyKit_DisplayDriver::initSPI(void)
{
  if (_cs >= 0) {
    pinMode(_cs, OUTPUT);
    digitalWrite(_cs, HIGH); // Deselect
    delay(100);
  }
  
  pinMode(_dc, OUTPUT);
  digitalWrite(_dc, HIGH); // Data mode

  if (connection == TFT_HARD_SPI)
  {   
      pinMode(SS, OUTPUT);
     // SPI.begin();
      spiClass = &SPI;

      #if defined(_SMARTY_DEBUG_)
      Serial.print(F("SmartyKit TFT_HARD_SPI freq = "));Serial.println(DEFAULT_SPI_FREQ, DEC);
      #endif
          
      spiSettings = SPISettings(DEFAULT_SPI_FREQ, MSBFIRST, SPI_MODE0);
      spiClass->begin();
      spiClass->beginTransaction(spiSettings);
      pinMode(SS, OUTPUT);
  }
  else if (connection == TFT_SOFT_SPI)
  {
      #if defined(_SMARTY_DEBUG_)
      Serial.println(F("SmartyKit TFT_SOFT_SPI"));
      #endif 
      pinMode(_mosi, OUTPUT);
      digitalWrite(_mosi, LOW);
      pinMode(_sck, OUTPUT);
      digitalWrite(_sck, LOW);
      if (_miso >= 0) {
        pinMode(_miso, INPUT);
    }
  }
 
  if (_rst >= 0) {
    // Toggle _rst low to reset
    pinMode(_rst, OUTPUT);
    digitalWrite(_rst, HIGH);
    delay(100);
    digitalWrite(_rst, LOW);
    delay(100);
    digitalWrite(_rst, HIGH);
    delay(200);
  }
}


void SmartyKit_DisplayDriver::splashScreen()
{
  int logoWidth = 19;
  //draw Smarty logo in the center
  if (rotation == 0 || rotation == 3)
  {
    startWrite();
    setAddrWindow(_TFTwidth / 2 - logoWidth/2,  _TFTheight / 2 - logoWidth/2, logoWidth, logoWidth); 
    //white filled square     
    for (uint16_t i = 0; i < logoWidth; i++)
    {      
        for (int x = 0; x < logoWidth; x++)
          SPI_WRITE16(ILI9341_WHITE);
    }  

    int logoInnerWidth = logoWidth/2;
    setAddrWindow(_TFTwidth / 2 - logoInnerWidth/2,  _TFTheight / 2 - logoInnerWidth/2, logoInnerWidth, logoInnerWidth); 
    //black filled square inside the white one     
    for (uint16_t i = 0; i < logoInnerWidth; i++)
    {      
        for (int x = 0; x < logoInnerWidth; x++)
          SPI_WRITE16(ILI9341_BLACK);
    }  
    endWrite();

    delay(1000);

    //print 'Made with love by...'
    int madeWithLoveLength = strlen(madeWithLove);
     setCursor(_TFTwidth / 2 - (madeWithLoveLength*LINE_WIDTH)/2, _TFTheight - LINE_HEIGHT- 4, CURSOR_ABSOLUTE);
     for (int i = 0; i < madeWithLoveLength; i++)
     {
        if (madeWithLove[i] == '\x03') //heart 
          print(madeWithLove[i], ILI9341_RED);
        else
         print(madeWithLove[i], ILI9341_WHITE);
        delay(100);
     }
    
    delay(500);
  }       
}


inline void SmartyKit_DisplayDriver::startWrite(void) {
  SPI_BEGIN_TRANSACTION();
  if (_cs >= 0)
    SPI_CS_LOW();
}

inline void SmartyKit_DisplayDriver::endWrite(void) {
  if (_cs >= 0)
    SPI_CS_HIGH();
  SPI_END_TRANSACTION();
}
void SmartyKit_DisplayDriver::writeCommand(uint8_t cmd) {
  SPI_DC_LOW();
  spiWrite(cmd);
  SPI_DC_HIGH();
}

void SmartyKit_DisplayDriver::sendCommand(uint8_t commandByte, const uint8_t *dataBytes,
                                  uint8_t numDataBytes) {
  startWrite();

  #if defined(_SMARTY_DEBUG_)
  Serial.print(F("PGM -> "));
  #endif
  
  writeCommand(commandByte);

  for (int i = 0; i < numDataBytes; i++) {
      #if defined(_SMARTY_DEBUG_)
      Serial.print(F("arg")); Serial.print(i+1, DEC); Serial.print(F(" = "));
      #endif
      uint8_t dataByte = pgm_read_byte(dataBytes++);
      dataByte &= 0xFF;
      spiWrite(dataByte);
  }

  endWrite();
}

void SmartyKit_DisplayDriver::sendCommand(uint8_t commandByte, uint8_t *dataBytes,
                                  uint8_t numDataBytes) {
  startWrite();

  writeCommand(commandByte);

  for (int i = 0; i < numDataBytes; i++) {
      spiWrite(*dataBytes); // Send the data bytes
      dataBytes++;
  }

  endWrite();
}


void SmartyKit_DisplayDriver::spiWrite(uint8_t b) {
  if (connection == TFT_HARD_SPI) {
#if defined(__AVR__)
    AVR_WRITESPI(b);
#else
    char c = spiClass->transfer(b);
    #if defined(_SMARTY_DEBUG_)
    Serial.print(F("spiWrite = "));Serial.println(c, HEX);
    #endif
#endif
  } else if (connection == TFT_SOFT_SPI) 
  {
    for (uint8_t bit = 0; bit < 8; bit++) {
      if (b & 0x80)
        SPI_MOSI_HIGH();
      else
        SPI_MOSI_LOW();
      SPI_SCK_HIGH();
      b <<= 1;
      SPI_SCK_LOW();
    }
  } 
}

void SmartyKit_DisplayDriver::setAddrWindow(uint16_t x1, uint16_t y1, uint16_t w,
                                     uint16_t h) {
  uint16_t x2 = (x1 + w - 1), y2 = (y1 + h - 1);
  writeCommand(ILI9341_CASET); // Column address set
  SPI_WRITE16(x1);
  SPI_WRITE16(x2);
  writeCommand(ILI9341_PASET); // Row address set
  SPI_WRITE16(y1);
  SPI_WRITE16(y2);
  writeCommand(ILI9341_RAMWR); // Write to RAM
}

void SmartyKit_DisplayDriver::SPI_WRITE16(uint16_t w) {

  if (connection == TFT_HARD_SPI) {
#if defined(__AVR__)
    AVR_WRITESPI(w >> 8);
    AVR_WRITESPI(w);
#endif
  } else if (connection == TFT_SOFT_SPI) {
    for (uint8_t bit = 0; bit < 16; bit++) {
      if (w & 0x8000)
        SPI_MOSI_HIGH();
      else
        SPI_MOSI_LOW();
      SPI_SCK_HIGH();
      SPI_SCK_LOW();
      w <<= 1;
   }
  }
}

inline void SmartyKit_DisplayDriver::writeColor(uint16_t color, uint32_t len)
{
  for (uint16_t i = 0; i < len; i++)
        SPI_WRITE16(color);  
}

/* user functions */
void SmartyKit_DisplayDriver::setCursor(int16_t x, int16_t y, uint8_t relative = CURSOR_RELATIVE) {
  if (relative == CURSOR_RELATIVE)
  {
    cursor_x = _workingScreenLeftMargin + x;
    cursor_y = _workingScreenTopMargin + y;
  }
  else if (relative == CURSOR_ABSOLUTE)
  {
    cursor_x = x;
    cursor_y = y;
  }
}

void SmartyKit_DisplayDriver::print(uint8_t c, uint16_t color = ILI9341_GREEN)
{

    if (c == '\n') {              // Newline?
      cursor_x = _workingScreenLeftMargin;               // Reset x to zero,
      cursor_y += textsize_y * 8; // advance y one line

      int maxHeight = _TFTheight;
      if (clipScreen == SCREEN_CLIPPED)
        maxHeight = _workingScreenHeight + _workingScreenTopMargin;
      if (cursor_y >= maxHeight )
      {
         scrollToNextLine();
         cursor_y -= textsize_y * 8;
      }      
    } else if (c != '\r') {       // Ignore carriage returns
      if ((cursor_x + textsize_x * 6) > _workingScreenLeftMargin + _workingScreenWidth) { // Off right?
        cursor_x = _workingScreenLeftMargin;                                       // Reset x to zero,
        cursor_y += textsize_y * 8; // advance y one line
      }
        
      //autoscroll mode
      int maxHeight = _TFTheight;
      if (clipScreen == SCREEN_CLIPPED)
        maxHeight = _workingScreenHeight + _workingScreenTopMargin;
      if (cursor_y >= maxHeight)
      {
        scrollToNextLine();
        cursor_y -= textsize_y * 8;
      }

        //converting screen coordinates to memory coordinates
      int yLine;
      if ((scrollLine + cursor_y) < maxHeight)
        yLine = scrollLine + cursor_y;
      else
        yLine = (scrollLine + cursor_y) - maxHeight;
    
      drawChar(cursor_x, yLine, c, color, bgColor, textsize_x);
      cursor_x += textsize_x * 6; // Advance x one char

      //TO-DO: set blinking cursor position next to printed char

    }
 }

void SmartyKit_DisplayDriver::drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size)
{
  uint8_t size_x = size;
  uint8_t size_y = size;

   if ((x >= _TFTwidth) ||              // Clip right
        (y >= _TFTheight) ||             // Clip bottom
        ((x + 6 * size_x - 1) < 0) || // Clip left
        ((y + 8 * size_y - 1) < 0))   // Clip top
        {
          return;
        }

    startWrite();
      
    for (int8_t i = 0; i < 5; i++) { // Char bitmap = 5 columns
      uint8_t line = pgm_read_byte(&font[c * 5 + i]);
      
      for (int8_t j = 0; j < 8; j++, line >>= 1) {
        if (line & 1) {
          if (size_x == 1 && size_y == 1)
            writePixel(x + i, y + j, color);
          else
            writeFillRect(x + i * size_x, y + j * size_y, size_x, size_y,
                          color);
        } else if (bg != color) {
          if (size_x == 1 && size_y == 1)
            writePixel(x + i, y + j, bg);
          else
            writeFillRect(x + i * size_x, y + j * size_y, size_x, size_y, bg);
        }
      }
    }
   
    if (bg != color) { // If opaque, draw vertical line for last column
      if (size_x == 1 && size_y == 1)
        writeFastVLine(x + 5, y, 8, bg);
      else
        writeFillRect(x + 5 * size_x, y, size_x, 8 * size_y, bg);
    }
    
    endWrite();
  
}

void SmartyKit_DisplayDriver::writePixel(int16_t x, int16_t y, uint16_t color)
{
  // Clip first...
  if ((x >= 0) && (x < _TFTwidth) && (y >= 0) && (y < _TFTheight)) {
    // THEN set up transaction (if needed) and draw...
    startWrite();
    setAddrWindow(x, y, 1, 1);
    SPI_WRITE16(color);
    endWrite();    
  }
}

void SmartyKit_DisplayDriver::writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
  if ((x >= 0) && (x < _TFTwidth) && h) { // X on screen, nonzero height
    if (h < 0) {                       // If negative height...
      y += h + 1;                      //   Move Y to top edge
      h = -h;                          //   Use positive height
    }
    if (y < _TFTheight) { // Not off bottom
      int16_t y2 = y + h - 1;
      if (y2 >= 0) { // Not off top
        // Line partly or fully overlaps screen
        if (y < 0) {
          y = 0;
          h = y2 + 1;
        } // Clip top
        if (y2 >= _TFTheight) {
          h = _TFTheight - y;
        } // Clip bottom
        writeFillRectPreclipped(x, y, 1, h, color);
      }
    }
  }
  
}
void SmartyKit_DisplayDriver::writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) 
{
  if (w && h) {   // Nonzero width and height?
    if (w < 0) {  // If negative width...
      x += w + 1; //   Move X to left edge
      w = -w;     //   Use positive width
    }
    if (x < _TFTwidth) { // Not off right
      if (h < 0) {    // If negative height...
        y += h + 1;   //   Move Y to top edge
        h = -h;       //   Use positive height
      }
      if (y < _TFTheight) { // Not off bottom
        int16_t x2 = x + w - 1;
        if (x2 >= 0) { // Not off left
          int16_t y2 = y + h - 1;
          if (y2 >= 0) { // Not off top
            // Rectangle partly or fully overlaps screen
            if (x < 0) {
              x = 0;
              w = x2 + 1;
            } // Clip left
            if (y < 0) {
              y = 0;
              h = y2 + 1;
            } // Clip top
            if (x2 >= _TFTwidth) {
              w = _TFTwidth - x;
            } // Clip right
            if (y2 >= _TFTheight) {
              h = _TFTheight - y;
            } // Clip bottom
            writeFillRectPreclipped(x, y, w, h, color);
          }
        }
      }
    }
  }
}

inline void SmartyKit_DisplayDriver::writeFillRectPreclipped(int16_t x, int16_t y,
                                                     int16_t w, int16_t h,
                                                     uint16_t color) {
  startWrite();
  setAddrWindow(x, y, w, h);
  writeColor(color, (uint32_t)w * h);
  endWrite();
}




void SmartyKit_DisplayDriver::setRotation(uint8_t m) {
  rotation = m % 4; // can't be higher than 3
  switch (rotation) {
  case 0:
    m = (MADCTL_MX | MADCTL_BGR);
    _TFTwidth = ILI9341_TFTWIDTH;
    _TFTheight = ILI9341_TFTHEIGHT;
    break;
  case 1:
    m = (MADCTL_MV | MADCTL_BGR);
    _TFTwidth = ILI9341_TFTHEIGHT;
    _TFTheight = ILI9341_TFTWIDTH;
    break;
  case 2:
    m = (MADCTL_MY | MADCTL_BGR);
    _TFTwidth = ILI9341_TFTWIDTH;
    _TFTheight = ILI9341_TFTHEIGHT;
    break;
  case 3:
   // m = (MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
    m = (MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
    m = (MADCTL_MX | MADCTL_MY |  MADCTL_MV | MADCTL_ML | MADCTL_MH | MADCTL_BGR);
    _TFTwidth = ILI9341_TFTHEIGHT;
    _TFTheight = ILI9341_TFTWIDTH;
    break;
  }

  sendCommand(ILI9341_MADCTL, &m, 1);
}

void SmartyKit_DisplayDriver::clearFullScreen(uint16_t color = ILI9341_WHITE)
{
  startWrite();
  setAddrWindow(0, 0, _TFTwidth, _TFTheight);
  for (int y = 0; y < _TFTheight; y++)
  {
    
   for (int x = 0; x < _TFTwidth; x++)
    {   
        SPI_WRITE16(color);
    }
  }
  endWrite();
}


void SmartyKit_DisplayDriver::clearScreen(uint16_t color = ILI9341_WHITE)
{
  if (rotation == 3)
  {
      uint16_t color2 = color;
      startWrite();
      setAddrWindow(_workingScreenLeftMargin, _workingScreenTopMargin, _workingScreenWidth, _workingScreenHeight);
      for (int y = 0; y < _workingScreenHeight; y++)
      {      
       for (int x = 0; x < _workingScreenWidth; x++)
        {   
            if (y % 2 == 0)
              SPI_WRITE16(color);
            else
              SPI_WRITE16(color2);
        }
      }
      endWrite();
  }
  else if (rotation == 0)
  {
      uint16_t color2 = color;
      startWrite();
      setAddrWindow(_workingScreenLeftMargin, _workingScreenTopMargin, _workingScreenWidth, _workingScreenHeight);
      for (int y = 0; y < _workingScreenHeight; y++)
      {
       for (int x = 0; x < _workingScreenWidth; x++)
        {   
            if (y % 2 == 0)
              SPI_WRITE16(color);
            else
              SPI_WRITE16(color2);
        }
      }
      endWrite();
  }
}

void SmartyKit_DisplayDriver::scrollTo(uint16_t y) {

  int scroll = y;
  if (y > SCREEN_HEIGHT)
    scroll = SCREEN_HEIGHT;

  startWrite();
  setAddrWindow(0,  0, SCREEN_WIDTH, scroll); 
  //draw bgColor line to erase      
  for (uint16_t i = 0; i < scroll; i++)
  {      
      for (int x = 0; x < SCREEN_WIDTH; x++)   
        SPI_WRITE16(bgColor);
  }  
  endWrite();
  //scroll screen
  uint8_t data[2];
  data[0] = (y) >> 8;
  data[1] = (y) & 0xff;
  sendCommand(ILI9341_VSCRSADD, (uint8_t *)data, 2);
}

void SmartyKit_DisplayDriver::drawScreenRect(uint16_t color)
{
  if (rotation == 0 || rotation == 3)
  {
    startWrite();
    setAddrWindow(_workingScreenLeftMargin,  _workingScreenTopMargin + _workingScreenHeight, _workingScreenWidth, 1);         
    for (int x = 0; x < _workingScreenWidth; x++)
          SPI_WRITE16(color);
    endWrite();
  }
}

void SmartyKit_DisplayDriver::drawHLine(uint16_t y, uint16_t color)
{
  //converting screen coordinates to memory coordinates
  int yLine;
  if ((scrollLine + y) < SCREEN_HEIGHT)
    yLine = scrollLine + y;
  else
    yLine = (scrollLine + y) - SCREEN_HEIGHT;
    
  if (rotation == 0)
  {
    startWrite();
    setAddrWindow(0,  yLine, SCREEN_WIDTH, 1);         
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {   
          SPI_WRITE16(color);
    }
    endWrite();
  }
}

void SmartyKit_DisplayDriver::setScrollMargins(uint16_t top, uint16_t bottom) {
  // TFA+VSA+BFA must equal 320
  if (top + bottom <= ILI9341_TFTHEIGHT) {
    uint16_t middle = ILI9341_TFTHEIGHT - top - bottom;
    uint8_t data[6];
    data[0] = top >> 8;
    data[1] = top & 0xff;
    data[2] = middle >> 8;
    data[3] = middle & 0xff;
    data[4] = bottom >> 8;
    data[5] = bottom & 0xff;
    sendCommand(ILI9341_VSCRDEF, (uint8_t *)data, 6);
  }
}

void SmartyKit_DisplayDriver::scrollToNextLine(void) 
{ 
  if (rotation == 0 || rotation == 3) //build-in hardware scroll
  {
    startWrite();
    setAddrWindow(0,  scrollLine, _workingScreenWidth, LINE_HEIGHT); 
    //draw bgColor line to erase      
    for (uint16_t i = 0; i < LINE_HEIGHT; i++)
    {      
        for (int x = 0; x < SCREEN_WIDTH; x++) 
          SPI_WRITE16(bgColor);
    }  
    endWrite();
  
    if ((scrollLine + LINE_HEIGHT) < SCREEN_HEIGHT)
      scrollLine += LINE_HEIGHT;
    else
      scrollLine = (scrollLine + LINE_HEIGHT) - SCREEN_HEIGHT;
        
    //scroll screen
    uint8_t data[2];
    data[0] = (scrollLine) >> 8;
    data[1] = (scrollLine) & 0xff;
    sendCommand(ILI9341_VSCRSADD, (uint8_t *)data, 2);
  }
}
