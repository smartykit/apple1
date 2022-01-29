/*  SmartyKit 1 - 2.8" TFT 320x240 screen video driver (+TV)
 *  http://www.smartykit.io/ 
 *  Copyright (C) 2019, Sergey Panarin <contact@smartykit.io>
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

#define _SMARTYKIT_DISPLAY_DRIVER_IL9341H_
#define _SMARTY_DEBUG_

#include <SPI.h>



#undef _TERMINAL_ //turn off Terminal
//#define _TERMINAL_ //turn on Terminal

#ifdef _TERMINAL_
#include <Terminal.h>
// Create a terminal in TWI mode
Terminal term; //uses A4 (SDA) and A5 (SCL) that conflict with other usage of A4-A5
               //so we need to put CS on low, RST = A0, DC = A1, MOSI = A2, SCK = A3, MISO = not connected (NC)
#endif
 

// Video Driver pins connections:
// D0 & D1 – reserved for Serial connection
// D2 -> NC
// D3 –> 4-16 ports decoder Video (9) out pin (signal is active when CPU writes to Video port)
// D4 -> NC
// D5 -> Video BIT7 pin output 
// D6-D13 -> Video data bus input (8 pins) to connect to Video port (char code is transfered here) 
// A0-A3 -> 2.8" TFT 320x240 screen connection
// A4-A5 -> TV terminal via I2C (TWI)

// Standard ASCII 5x7 font

static const unsigned char font[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x5B, 0x4F, 0x5B, 0x3E, 0x3E, 0x6B,
    0x4F, 0x6B, 0x3E, 0x1C, 0x3E, 0x7C, 0x3E, 0x1C, 0x18, 0x3C, 0x7E, 0x3C,
    0x18, 0x1C, 0x57, 0x7D, 0x57, 0x1C, 0x1C, 0x5E, 0x7F, 0x5E, 0x1C, 0x00,
    0x18, 0x3C, 0x18, 0x00, 0xFF, 0xE7, 0xC3, 0xE7, 0xFF, 0x00, 0x18, 0x24,
    0x18, 0x00, 0xFF, 0xE7, 0xDB, 0xE7, 0xFF, 0x30, 0x48, 0x3A, 0x06, 0x0E,
    0x26, 0x29, 0x79, 0x29, 0x26, 0x40, 0x7F, 0x05, 0x05, 0x07, 0x40, 0x7F,
    0x05, 0x25, 0x3F, 0x5A, 0x3C, 0xE7, 0x3C, 0x5A, 0x7F, 0x3E, 0x1C, 0x1C,
    0x08, 0x08, 0x1C, 0x1C, 0x3E, 0x7F, 0x14, 0x22, 0x7F, 0x22, 0x14, 0x5F,
    0x5F, 0x00, 0x5F, 0x5F, 0x06, 0x09, 0x7F, 0x01, 0x7F, 0x00, 0x66, 0x89,
    0x95, 0x6A, 0x60, 0x60, 0x60, 0x60, 0x60, 0x94, 0xA2, 0xFF, 0xA2, 0x94,
    0x08, 0x04, 0x7E, 0x04, 0x08, 0x10, 0x20, 0x7E, 0x20, 0x10, 0x08, 0x08,
    0x2A, 0x1C, 0x08, 0x08, 0x1C, 0x2A, 0x08, 0x08, 0x1E, 0x10, 0x10, 0x10,
    0x10, 0x0C, 0x1E, 0x0C, 0x1E, 0x0C, 0x30, 0x38, 0x3E, 0x38, 0x30, 0x06,
    0x0E, 0x3E, 0x0E, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5F,
    0x00, 0x00, 0x00, 0x07, 0x00, 0x07, 0x00, 0x14, 0x7F, 0x14, 0x7F, 0x14,
    0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x23, 0x13, 0x08, 0x64, 0x62, 0x36, 0x49,
    0x56, 0x20, 0x50, 0x00, 0x08, 0x07, 0x03, 0x00, 0x00, 0x1C, 0x22, 0x41,
    0x00, 0x00, 0x41, 0x22, 0x1C, 0x00, 0x2A, 0x1C, 0x7F, 0x1C, 0x2A, 0x08,
    0x08, 0x3E, 0x08, 0x08, 0x00, 0x80, 0x70, 0x30, 0x00, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x00, 0x00, 0x60, 0x60, 0x00, 0x20, 0x10, 0x08, 0x04, 0x02,
    0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00, 0x42, 0x7F, 0x40, 0x00, 0x72, 0x49,
    0x49, 0x49, 0x46, 0x21, 0x41, 0x49, 0x4D, 0x33, 0x18, 0x14, 0x12, 0x7F,
    0x10, 0x27, 0x45, 0x45, 0x45, 0x39, 0x3C, 0x4A, 0x49, 0x49, 0x31, 0x41,
    0x21, 0x11, 0x09, 0x07, 0x36, 0x49, 0x49, 0x49, 0x36, 0x46, 0x49, 0x49,
    0x29, 0x1E, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x40, 0x34, 0x00, 0x00,
    0x00, 0x08, 0x14, 0x22, 0x41, 0x14, 0x14, 0x14, 0x14, 0x14, 0x00, 0x41,
    0x22, 0x14, 0x08, 0x02, 0x01, 0x59, 0x09, 0x06, 0x3E, 0x41, 0x5D, 0x59,
    0x4E, 0x7C, 0x12, 0x11, 0x12, 0x7C, 0x7F, 0x49, 0x49, 0x49, 0x36, 0x3E,
    0x41, 0x41, 0x41, 0x22, 0x7F, 0x41, 0x41, 0x41, 0x3E, 0x7F, 0x49, 0x49,
    0x49, 0x41, 0x7F, 0x09, 0x09, 0x09, 0x01, 0x3E, 0x41, 0x41, 0x51, 0x73,
    0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00, 0x41, 0x7F, 0x41, 0x00, 0x20, 0x40,
    0x41, 0x3F, 0x01, 0x7F, 0x08, 0x14, 0x22, 0x41, 0x7F, 0x40, 0x40, 0x40,
    0x40, 0x7F, 0x02, 0x1C, 0x02, 0x7F, 0x7F, 0x04, 0x08, 0x10, 0x7F, 0x3E,
    0x41, 0x41, 0x41, 0x3E, 0x7F, 0x09, 0x09, 0x09, 0x06, 0x3E, 0x41, 0x51,
    0x21, 0x5E, 0x7F, 0x09, 0x19, 0x29, 0x46, 0x26, 0x49, 0x49, 0x49, 0x32,
    0x03, 0x01, 0x7F, 0x01, 0x03, 0x3F, 0x40, 0x40, 0x40, 0x3F, 0x1F, 0x20,
    0x40, 0x20, 0x1F, 0x3F, 0x40, 0x38, 0x40, 0x3F, 0x63, 0x14, 0x08, 0x14,
    0x63, 0x03, 0x04, 0x78, 0x04, 0x03, 0x61, 0x59, 0x49, 0x4D, 0x43, 0x00,
    0x7F, 0x41, 0x41, 0x41, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00, 0x41, 0x41,
    0x41, 0x7F, 0x04, 0x02, 0x01, 0x02, 0x04, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x00, 0x03, 0x07, 0x08, 0x00, 0x20, 0x54, 0x54, 0x78, 0x40, 0x7F, 0x28,
    0x44, 0x44, 0x38, 0x38, 0x44, 0x44, 0x44, 0x28, 0x38, 0x44, 0x44, 0x28,
    0x7F, 0x38, 0x54, 0x54, 0x54, 0x18, 0x00, 0x08, 0x7E, 0x09, 0x02, 0x18,
    0xA4, 0xA4, 0x9C, 0x78, 0x7F, 0x08, 0x04, 0x04, 0x78, 0x00, 0x44, 0x7D,
    0x40, 0x00, 0x20, 0x40, 0x40, 0x3D, 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00,
    0x00, 0x41, 0x7F, 0x40, 0x00, 0x7C, 0x04, 0x78, 0x04, 0x78, 0x7C, 0x08,
    0x04, 0x04, 0x78, 0x38, 0x44, 0x44, 0x44, 0x38, 0xFC, 0x18, 0x24, 0x24,
    0x18, 0x18, 0x24, 0x24, 0x18, 0xFC, 0x7C, 0x08, 0x04, 0x04, 0x08, 0x48,
    0x54, 0x54, 0x54, 0x24, 0x04, 0x04, 0x3F, 0x44, 0x24, 0x3C, 0x40, 0x40,
    0x20, 0x7C, 0x1C, 0x20, 0x40, 0x20, 0x1C, 0x3C, 0x40, 0x30, 0x40, 0x3C,
    0x44, 0x28, 0x10, 0x28, 0x44, 0x4C, 0x90, 0x90, 0x90, 0x7C, 0x44, 0x64,
    0x54, 0x4C, 0x44, 0x00, 0x08, 0x36, 0x41, 0x00, 0x00, 0x00, 0x77, 0x00,
    0x00, 0x00, 0x41, 0x36, 0x08, 0x00, 0x02, 0x01, 0x02, 0x04, 0x02, 0x3C,
    0x26, 0x23, 0x26, 0x3C, 0x1E, 0xA1, 0xA1, 0x61, 0x12, 0x3A, 0x40, 0x40,
    0x20, 0x7A, 0x38, 0x54, 0x54, 0x55, 0x59, 0x21, 0x55, 0x55, 0x79, 0x41,
    0x22, 0x54, 0x54, 0x78, 0x42, // a-umlaut
    0x21, 0x55, 0x54, 0x78, 0x40, 0x20, 0x54, 0x55, 0x79, 0x40, 0x0C, 0x1E,
    0x52, 0x72, 0x12, 0x39, 0x55, 0x55, 0x55, 0x59, 0x39, 0x54, 0x54, 0x54,
    0x59, 0x39, 0x55, 0x54, 0x54, 0x58, 0x00, 0x00, 0x45, 0x7C, 0x41, 0x00,
    0x02, 0x45, 0x7D, 0x42, 0x00, 0x01, 0x45, 0x7C, 0x40, 0x7D, 0x12, 0x11,
    0x12, 0x7D, // A-umlaut
    0xF0, 0x28, 0x25, 0x28, 0xF0, 0x7C, 0x54, 0x55, 0x45, 0x00, 0x20, 0x54,
    0x54, 0x7C, 0x54, 0x7C, 0x0A, 0x09, 0x7F, 0x49, 0x32, 0x49, 0x49, 0x49,
    0x32, 0x3A, 0x44, 0x44, 0x44, 0x3A, // o-umlaut
    0x32, 0x4A, 0x48, 0x48, 0x30, 0x3A, 0x41, 0x41, 0x21, 0x7A, 0x3A, 0x42,
    0x40, 0x20, 0x78, 0x00, 0x9D, 0xA0, 0xA0, 0x7D, 0x3D, 0x42, 0x42, 0x42,
    0x3D, // O-umlaut
    0x3D, 0x40, 0x40, 0x40, 0x3D, 0x3C, 0x24, 0xFF, 0x24, 0x24, 0x48, 0x7E,
    0x49, 0x43, 0x66, 0x2B, 0x2F, 0xFC, 0x2F, 0x2B, 0xFF, 0x09, 0x29, 0xF6,
    0x20, 0xC0, 0x88, 0x7E, 0x09, 0x03, 0x20, 0x54, 0x54, 0x79, 0x41, 0x00,
    0x00, 0x44, 0x7D, 0x41, 0x30, 0x48, 0x48, 0x4A, 0x32, 0x38, 0x40, 0x40,
    0x22, 0x7A, 0x00, 0x7A, 0x0A, 0x0A, 0x72, 0x7D, 0x0D, 0x19, 0x31, 0x7D,
    0x26, 0x29, 0x29, 0x2F, 0x28, 0x26, 0x29, 0x29, 0x29, 0x26, 0x30, 0x48,
    0x4D, 0x40, 0x20, 0x38, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x38, 0x2F, 0x10, 0xC8, 0xAC, 0xBA, 0x2F, 0x10, 0x28, 0x34, 0xFA, 0x00,
    0x00, 0x7B, 0x00, 0x00, 0x08, 0x14, 0x2A, 0x14, 0x22, 0x22, 0x14, 0x2A,
    0x14, 0x08, 0x55, 0x00, 0x55, 0x00, 0x55, // #176 (25% block) missing in old
                                              // code
    0xAA, 0x55, 0xAA, 0x55, 0xAA,             // 50% block
    0xFF, 0x55, 0xFF, 0x55, 0xFF,             // 75% block
    0x00, 0x00, 0x00, 0xFF, 0x00, 0x10, 0x10, 0x10, 0xFF, 0x00, 0x14, 0x14,
    0x14, 0xFF, 0x00, 0x10, 0x10, 0xFF, 0x00, 0xFF, 0x10, 0x10, 0xF0, 0x10,
    0xF0, 0x14, 0x14, 0x14, 0xFC, 0x00, 0x14, 0x14, 0xF7, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x14, 0x14, 0xF4, 0x04, 0xFC, 0x14, 0x14, 0x17,
    0x10, 0x1F, 0x10, 0x10, 0x1F, 0x10, 0x1F, 0x14, 0x14, 0x14, 0x1F, 0x00,
    0x10, 0x10, 0x10, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x10, 0x10, 0x10,
    0x10, 0x1F, 0x10, 0x10, 0x10, 0x10, 0xF0, 0x10, 0x00, 0x00, 0x00, 0xFF,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xFF, 0x10, 0x00,
    0x00, 0x00, 0xFF, 0x14, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x1F,
    0x10, 0x17, 0x00, 0x00, 0xFC, 0x04, 0xF4, 0x14, 0x14, 0x17, 0x10, 0x17,
    0x14, 0x14, 0xF4, 0x04, 0xF4, 0x00, 0x00, 0xFF, 0x00, 0xF7, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0xF7, 0x00, 0xF7, 0x14, 0x14, 0x14, 0x17,
    0x14, 0x10, 0x10, 0x1F, 0x10, 0x1F, 0x14, 0x14, 0x14, 0xF4, 0x14, 0x10,
    0x10, 0xF0, 0x10, 0xF0, 0x00, 0x00, 0x1F, 0x10, 0x1F, 0x00, 0x00, 0x00,
    0x1F, 0x14, 0x00, 0x00, 0x00, 0xFC, 0x14, 0x00, 0x00, 0xF0, 0x10, 0xF0,
    0x10, 0x10, 0xFF, 0x10, 0xFF, 0x14, 0x14, 0x14, 0xFF, 0x14, 0x10, 0x10,
    0x10, 0x1F, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x10, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFF, 0xFF, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x38, 0x44, 0x44,
    0x38, 0x44, 0xFC, 0x4A, 0x4A, 0x4A, 0x34, // sharp-s or beta
    0x7E, 0x02, 0x02, 0x06, 0x06, 0x02, 0x7E, 0x02, 0x7E, 0x02, 0x63, 0x55,
    0x49, 0x41, 0x63, 0x38, 0x44, 0x44, 0x3C, 0x04, 0x40, 0x7E, 0x20, 0x1E,
    0x20, 0x06, 0x02, 0x7E, 0x02, 0x02, 0x99, 0xA5, 0xE7, 0xA5, 0x99, 0x1C,
    0x2A, 0x49, 0x2A, 0x1C, 0x4C, 0x72, 0x01, 0x72, 0x4C, 0x30, 0x4A, 0x4D,
    0x4D, 0x30, 0x30, 0x48, 0x78, 0x48, 0x30, 0xBC, 0x62, 0x5A, 0x46, 0x3D,
    0x3E, 0x49, 0x49, 0x49, 0x00, 0x7E, 0x01, 0x01, 0x01, 0x7E, 0x2A, 0x2A,
    0x2A, 0x2A, 0x2A, 0x44, 0x44, 0x5F, 0x44, 0x44, 0x40, 0x51, 0x4A, 0x44,
    0x40, 0x40, 0x44, 0x4A, 0x51, 0x40, 0x00, 0x00, 0xFF, 0x01, 0x03, 0xE0,
    0x80, 0xFF, 0x00, 0x00, 0x08, 0x08, 0x6B, 0x6B, 0x08, 0x36, 0x12, 0x36,
    0x24, 0x36, 0x06, 0x0F, 0x09, 0x0F, 0x06, 0x00, 0x00, 0x18, 0x18, 0x00,
    0x00, 0x00, 0x10, 0x10, 0x00, 0x30, 0x40, 0xFF, 0x01, 0x01, 0x00, 0x1F,
    0x01, 0x01, 0x1E, 0x00, 0x19, 0x1D, 0x17, 0x12, 0x00, 0x3C, 0x3C, 0x3C,
    0x3C, 0x00, 0x00, 0x00, 0x00, 0x00 // #255 NBSP
};

// allow clean compilation with [-Wunused-const-variable=] and [-Wall]
static inline void avoid_unused_const_variable_compiler_warning(void) {
  (void)font;
}


#define BEEPER_PIN 6

//SmartyKit Display Driver parameters
#define ILI9341_TFTWIDTH 240  ///< ILI9341 max TFT width
#define ILI9341_TFTHEIGHT 320 ///< ILI9341 max TFT height


//driver commands and parameters
#define ILI9341_NOP 0x00     ///< No-op register
#define ILI9341_SWRESET 0x01 ///< Software reset register
#define ILI9341_RDDID 0x04   ///< Read display identification information
#define ILI9341_RDDST 0x09   ///< Read Display Status

#define ILI9341_SLPIN 0x10  ///< Enter Sleep Mode
#define ILI9341_SLPOUT 0x11 ///< Sleep Out
#define ILI9341_PTLON 0x12  ///< Partial Mode ON
#define ILI9341_NORON 0x13  ///< Normal Display Mode ON

#define ILI9341_RDMODE 0x0A     ///< Read Display Power Mode
#define ILI9341_RDMADCTL 0x0B   ///< Read Display MADCTL
#define ILI9341_RDPIXFMT 0x0C   ///< Read Display Pixel Format
#define ILI9341_RDIMGFMT 0x0D   ///< Read Display Image Format
#define ILI9341_RDSELFDIAG 0x0F ///< Read Display Self-Diagnostic Result

#define ILI9341_INVOFF 0x20   ///< Display Inversion OFF
#define ILI9341_INVON 0x21    ///< Display Inversion ON
#define ILI9341_GAMMASET 0x26 ///< Gamma Set
#define ILI9341_DISPOFF 0x28  ///< Display OFF
#define ILI9341_DISPON 0x29   ///< Display ON

#define ILI9341_CASET 0x2A ///< Column Address Set
#define ILI9341_PASET 0x2B ///< Page Address Set
#define ILI9341_RAMWR 0x2C ///< Memory Write
#define ILI9341_RAMRD 0x2E ///< Memory Read

#define ILI9341_PTLAR 0x30    ///< Partial Area
#define ILI9341_VSCRDEF 0x33  ///< Vertical Scrolling Definition
#define ILI9341_MADCTL 0x36   ///< Memory Access Control
#define ILI9341_VSCRSADD 0x37 ///< Vertical Scrolling Start Address
#define ILI9341_PIXFMT 0x3A   ///< COLMOD: Pixel Format Set

#define ILI9341_FRMCTR1                                                        \
  0xB1 ///< Frame Rate Control (In Normal Mode/Full Colors)
#define ILI9341_FRMCTR2 0xB2 ///< Frame Rate Control (In Idle Mode/8 colors)
#define ILI9341_FRMCTR3                                                        \
  0xB3 ///< Frame Rate control (In Partial Mode/Full Colors)
#define ILI9341_INVCTR 0xB4  ///< Display Inversion Control
#define ILI9341_DFUNCTR 0xB6 ///< Display Function Control

#define ILI9341_PWCTR1 0xC0 ///< Power Control 1
#define ILI9341_PWCTR2 0xC1 ///< Power Control 2
#define ILI9341_PWCTR3 0xC2 ///< Power Control 3
#define ILI9341_PWCTR4 0xC3 ///< Power Control 4
#define ILI9341_PWCTR5 0xC4 ///< Power Control 5
#define ILI9341_VMCTR1 0xC5 ///< VCOM Control 1
#define ILI9341_VMCTR2 0xC7 ///< VCOM Control 2

#define ILI9341_RDID1 0xDA ///< Read ID 1
#define ILI9341_RDID2 0xDB ///< Read ID 2
#define ILI9341_RDID3 0xDC ///< Read ID 3
#define ILI9341_RDID4 0xDD ///< Read ID 4

#define ILI9341_GMCTRP1 0xE0 ///< Positive Gamma Correction
#define ILI9341_GMCTRN1 0xE1 ///< Negative Gamma Correction
//#define ILI9341_PWCTR6     0xFC

#define MADCTL_MY 0x80  ///< Bottom to top
#define MADCTL_MX 0x40  ///< Right to left
#define MADCTL_MV 0x20  ///< Reverse Mode
#define MADCTL_NOTMV 0x00  ///< Reverse Mode

#define MADCTL_ML 0x10  ///< LCD refresh Bottom to top
#define MADCTL_RGB 0x00 ///< Red-Green-Blue pixel order
#define MADCTL_BGR 0x08 ///< Blue-Green-Red pixel order
#define MADCTL_MH 0x04  ///< LCD refresh right to left

// Color definitions
#define ILI9341_BLACK 0x0000       ///<   0,   0,   0
#define ILI9341_NAVY 0x000F        ///<   0,   0, 123
#define ILI9341_DARKGREEN 0x03E0   ///<   0, 125,   0
#define ILI9341_DARKCYAN 0x03EF    ///<   0, 125, 123
#define ILI9341_MAROON 0x7800      ///< 123,   0,   0
#define ILI9341_PURPLE 0x780F      ///< 123,   0, 123
#define ILI9341_OLIVE 0x7BE0       ///< 123, 125,   0
#define ILI9341_LIGHTGREY 0xC618   ///< 198, 195, 198
#define ILI9341_DARKGREY 0x7BEF    ///< 123, 125, 123
#define ILI9341_BLUE 0x001F        ///<   0,   0, 255
#define ILI9341_GREEN 0x07E0       ///<   0, 255,   0
#define ILI9341_CYAN 0x07FF        ///<   0, 255, 255
#define ILI9341_RED 0xF800         ///< 255,   0,   0
#define ILI9341_MAGENTA 0xF81F     ///< 255,   0, 255
#define ILI9341_YELLOW 0xFFE0      ///< 255, 255,   0
#define ILI9341_WHITE 0xFFFF       ///< 255, 255, 255
#define ILI9341_ORANGE 0xFD20      ///< 255, 165,   0
#define ILI9341_GREENYELLOW 0xAFE5 ///< 173, 255,  41
#define ILI9341_PINK 0xFC18        ///< 255, 130, 198

// Possible values for SPITFT.connection:
#define TFT_HARD_SPI 0 ///< Display interface = hardware SPI
#define TFT_SOFT_SPI 1 ///< Display interface = software SPI


#ifndef _TERMINAL_
#define TFT_CS A0
#define TFT_RST A1
#define TFT_DC A2
#define TFT_MOSI A3 // 11
#define TFT_CLK A4 //13 
#define TFT_MISO A5

#else
//so we need to put CS on low, RST = A0, DC = A1, MOSI = A2, SCK = A3, MISO = not connected (NC)
#define TFT_CS -1
#define TFT_RST A0
#define TFT_DC A1
#define TFT_MOSI A2
#define TFT_CLK A3 
#define TFT_MISO -1
#endif




#if defined(__AVR__)
#define DEFAULT_SPI_FREQ 2000000 ///< Hardware SPI default speed
#else
#define DEFAULT_SPI_FREQ 4000000L ///< Hardware SPI default speed
#endif

#if defined(__AVR__)
#define AVR_WRITESPI(x) for (SPDR = (x); (!(SPSR & _BV(SPIF)));)
#endif

#define TFT_TFTwidth 320  
#define TFT_TFTheight 240 
#define SCREEN_COLS 40
#define SCREEN_ROWS 24
#define LINE_WIDTH 6
#define LINE_HEIGHT 8
#define SCREEN_WIDTH SCREEN_COLS*LINE_WIDTH
#define SCREEN_HEIGHT SCREEN_ROWS*LINE_HEIGHT
#define MARGIN_TOP 3*LINE_HEIGHT
#define MARGIN_BOTTOM 3*LINE_HEIGHT
#define MARGIN_LEFT (TFT_TFTwidth - SCREEN_COLS*LINE_WIDTH)/2 
#define MARGIN_RIGHT (TFT_TFTwidth - SCREEN_COLS*LINE_WIDTH)/2 
#define SCREEN_TOP MARGIN_TOP
#define SCREEN_BOTTOM (TFT_TFTheight - MARGIN_BOTTOM)
#define SCREEN_LEFT MARGIN_LEFT
#define SCREEN_RIGHT (TFT_TFTwidth - MARGIN_RIGHT)
#define SCREEN_RECT_MARGIN 3


// clang-format off
      static const uint8_t PROGMEM initcmd[] = {
        0xEF, 3, 0x03, 0x80, 0x02,
        0xCF, 3, 0x00, 0xC1, 0x30,             //Power control B (CFh)
        0xED, 4, 0x64, 0x03, 0x12, 0x81,       //Power on sequence control (EDh)
        0xE8, 3, 0x85, 0x00, 0x78,             //Driver timing control A (E8h) 0xE8, 3, 0x85, 0x00, 0x78,
        0xCB, 5, 0x39, 0x2C, 0x00, 0x34, 0x02, //Power control A (CBh)
        0xF7, 1, 0x20,                         //Pump ratio control (F7h)
        0xEA, 2, 0x00, 0x00,                   //Driver timing control B (EAh) 0xEA, 2, 0x00, 0x00, 
        ILI9341_PWCTR1  , 1, 0x23,             // Power control VRH[5:0]
        ILI9341_PWCTR2  , 1, 0x10,             // Power control SAP[2:0];BT[3:0]
        ILI9341_VMCTR1  , 2, 0x3e, 0x28,       // VCM control
        ILI9341_VMCTR2  , 1, 0x86,             // VCM control2
        ILI9341_MADCTL  , 1, 0x48,             // Memory Access Control
        ILI9341_VSCRSADD, 1, 0x00,             // Vertical scroll zero
        ILI9341_PIXFMT  , 1, 0x55,
        ILI9341_FRMCTR1 , 2, 0x00, 0x18,
        ILI9341_DFUNCTR , 3, 0x08, 0x82, 0x27, // Display Function Control
        0xF2, 1, 0x00,                         // 3Gamma Function Disable
        ILI9341_GAMMASET , 1, 0x01,             // Gamma curve selected
        ILI9341_GMCTRP1 , 15, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, // Set Gamma
          0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00,
        ILI9341_GMCTRN1 , 15, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, // Set Gamma
          0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F,
        ILI9341_SLPOUT  , 0x80,                // Exit Sleep
        ILI9341_DISPON  , 0x80,                // Display on
        0x00                                   // End of list
      };
      // clang-format on


#define TFT_PORTRAIT 1
#define TFT_LANDSCAPE 0

#define CURSOR_RELATIVE 1
#define CURSOR_ABSOLUTE 0

#define SCREEN_FULL_SCREEN 0
#define SCREEN_CLIPPED 1

int tftPortrait = TFT_PORTRAIT;
//int tftPortrait = TFT_LANDSCAPE;


#undef USE_FAST_PINIO

//SmartyKit Display Driver Class members
class SmartyKit_DisplayDriver
{
  public:
  SmartyKit_DisplayDriver::SmartyKit_DisplayDriver();

  SmartyKit_DisplayDriver::~SmartyKit_DisplayDriver()
  {
    if(spiClass)
      spiClass->endTransaction();
  }
  SPIClass *spiClass;
  SPISettings spiSettings;
  int connection;
  int clipScreen;
  uint8_t rotation;
  int16_t _TFTwidth;           //full TFT width
  int16_t _TFTheight;          //full TFT height
  int16_t _workingScreenWidth;           //screen area width:   SCREEN_WIDTH
  int16_t _workingScreenHeight;          //screen area height:  SCREEN_HEIGHT
  int16_t _workingScreenTopMargin;
  int16_t _workingScreenLeftMargin;
  int16_t scrollLine;
  int16_t cursor_x;               
  int16_t cursor_y;
  int16_t screen_col;               
  int16_t screen_row;
  
  int16_t textsize_x;
  int16_t textsize_y;
  int8_t _dc;
  int8_t _rst;             ///< Reset pin # (or -1)
  int8_t _cs;              ///< Chip select pin # (or -1)
  int8_t _sck;
  int8_t _mosi;
  int8_t _miso;

  uint16_t color = ILI9341_GREEN;
  uint16_t bgColor = ILI9341_BLACK;

  

  //functions
  void setup();
  void initSPI(void);
  void sendCommand(uint8_t commandByte, const uint8_t *dataBytes, uint8_t numDataBytes);
  void sendCommand(uint8_t commandByte, uint8_t *dataBytes = 0, uint8_t numDataBytes = 0);
  void spiWrite(uint8_t b);          // Write single byte as DATA
  void writeCommand(uint8_t cmd); 
  void setAddrWindow(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h);
  inline void writeColor(uint16_t color, uint32_t len);
  inline void startWrite(void);
  inline void endWrite(void);

  void setRotation(uint8_t m);
  void clearFullScreen(uint16_t color = ILI9341_WHITE);
  void clearScreen(void);
  void splashScreen();
  
  void drawScreenRect(uint16_t color);
  void drawScreenKeyboard(uint16_t color);
  void drawHLine(uint16_t y, uint16_t color);
  void writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  inline void writeFillRectPreclipped(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  void scrollTo(uint16_t y);
  void setScrollMargins(uint16_t top, uint16_t bottom);
  void scrollToNextLine(void);
  void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size, int keyboard = 0);
  void writePixel(int16_t x, int16_t y, uint16_t color);
  void setCursor(int16_t x, int16_t y, uint8_t relative = CURSOR_RELATIVE);
  void print(uint8_t c, uint16_t color = ILI9341_GREEN);

  void printScreenBuffer();

  inline void SPI_BEGIN_TRANSACTION(void){  };
  inline void SPI_END_TRANSACTION(void) { };
  void SPI_DC_HIGH(void);
  void SPI_DC_LOW(void);
  void SPI_CS_HIGH(void);
  void SPI_CS_LOW(void);
  void SPI_WRITE16(uint16_t w);
  //for TFT_SOFT_SPI
//  inline void SPI_MOSI_HIGH(void) { digitalWrite(_mosi, HIGH);};
//  inline void SPI_MOSI_LOW(void) { digitalWrite(_mosi, LOW);};
//  inline void SPI_SCK_HIGH(void) { digitalWrite(_sck, HIGH);};
//  inline void SPI_SCK_LOW(void) { digitalWrite(_sck, LOW);};

#ifndef _TERMINAL_
  inline void SPI_MOSI_HIGH(void) { PORTC = PORTC | B001000; };  //MOSI = A3 = PC3
  inline void SPI_MOSI_LOW(void) {  PORTC = PORTC & B110111;};   //MOSI = A3 = PC3
  inline void SPI_SCK_HIGH(void) { PORTC = PORTC | B010000;};    //SCK = A4 = PC4
  inline void SPI_SCK_LOW(void) {  PORTC = PORTC & B101111;};     //SCK = A4 = PC4

  
#else
  inline void SPI_MOSI_HIGH(void) { PORTC = PORTC | B000100; };  //MOSI = A2 = PC2
  inline void SPI_MOSI_LOW(void) {  PORTC = PORTC & B111011;};   //MOSI = A2 = PC2
  inline void SPI_SCK_HIGH(void) { PORTC = PORTC | B001000;};    //SCK = A3 = PC3
  inline void SPI_SCK_LOW(void) {  PORTC = PORTC & B110111;};     //SCK = A3 = PC3

#endif
  
  
    
  #if defined(_SMARTY_DEBUG_)
  inline void beep() { tone(BEEPER_PIN, 880, 200);   }
  #endif
  
};

volatile int screenRow = 0;
volatile int screenCol = 0;
char screenBuffer[SCREEN_ROWS][SCREEN_COLS];

SmartyKit_DisplayDriver::SmartyKit_DisplayDriver()
{
}


void SmartyKit_DisplayDriver::setup()
{
//      #if defined(_SMARTY_DEBUG_)
//      pinMode(BEEPER_PIN, OUTPUT); 
//      #endif
      _dc = TFT_DC;
      _rst = TFT_RST;
      _cs = TFT_CS;
      _sck = TFT_CLK;
      _mosi = TFT_MOSI;
      _miso = TFT_MISO;

      
      //connection = TFT_HARD_SPI;
      connection = TFT_SOFT_SPI;
      

      initSPI();

     // sendCommand(ILI9341_SWRESET); // Engage software reset
      //delay(200);

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
      
      color = ILI9341_GREEN;
      bgColor = ILI9341_BLACK;
  
      if (tftPortrait == TFT_PORTRAIT)
      {
        setRotation(0);
        clearFullScreen(ILI9341_BLACK);
        //start right from the top-left corner - TO-DO: move to the screen centers
        _workingScreenTopMargin = 0;
        _workingScreenLeftMargin = 0; 
  
       // drawScreenRect(ILI9341_WHITE);
      }
      if (tftPortrait == TFT_LANDSCAPE) 
      {
        setRotation(3);
        clearFullScreen(ILI9341_BLACK);
        _workingScreenTopMargin = (_TFTheight - SCREEN_ROWS*LINE_HEIGHT)/2;
        _workingScreenLeftMargin = (_TFTwidth - SCREEN_COLS*LINE_WIDTH)/2; 
      }
      //drawing splash screen
      splashScreen();

      if (tftPortrait == TFT_PORTRAIT)
      {
        //set built-in hardware scrolling
        setScrollMargins(0, ILI9341_TFTHEIGHT - SCREEN_HEIGHT);
        clipScreen = SCREEN_CLIPPED;
       
        //drawScreenKeyboard(ILI9341_WHITE);
        //drawScreenRect(ILI9341_WHITE);
        
      }
 
      setCursor(0,0);
      clearScreen();
      print('#');
      print('>');
        
      #if defined(_SMARTY_DEBUG_)
      beep(); 
      #endif
}

void SmartyKit_DisplayDriver::initSPI(void)
{

  if (_cs >= 0) {
    pinMode(_cs, OUTPUT);
    digitalWrite(_cs, HIGH); // Deselect
    delay(100);
    //digitalWrite(_cs, LOW); // Select
  }
  
  pinMode(_dc, OUTPUT);
  digitalWrite(_dc, HIGH); // Data mode

  if (connection == TFT_HARD_SPI)
  {   
      pinMode(SS, OUTPUT);
     // SPI.begin();
      spiClass = &SPI;

      #if defined(_SMARTY_DEBUG_)
      Serial.print(F("SmartyKit SPI freq = "));Serial.println(DEFAULT_SPI_FREQ, DEC);
      #endif
          
      spiSettings = SPISettings(DEFAULT_SPI_FREQ, MSBFIRST, SPI_MODE0);
      spiClass->begin();
      spiClass->beginTransaction(spiSettings);
      pinMode(SS, OUTPUT);
  }
  else if (connection == TFT_SOFT_SPI)
  {
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
  
void SmartyKit_DisplayDriver::splashScreen()
{
  int logoWidth = 19;
  //draw Smarty logo in the center
  if (rotation == 0 || rotation == 3)
  {
    startWrite();
    setAddrWindow(_TFTwidth / 2 - logoWidth/2,  _TFTheight / 2 - logoWidth/2, logoWidth, logoWidth); 
    //draw bgColor line to erase      
    for (uint16_t i = 0; i < logoWidth; i++)
    {      
        for (int x = 0; x < logoWidth; x++)
          SPI_WRITE16(ILI9341_WHITE);
    }  
    //endWrite();

    int logoInnerWidth = logoWidth/2;
  //draw Smarty logo in the center
    //startWrite();
    setAddrWindow(_TFTwidth / 2 - logoInnerWidth/2,  _TFTheight / 2 - logoInnerWidth/2, logoInnerWidth, logoInnerWidth); 
    //draw bgColor line to erase      
    for (uint16_t i = 0; i < logoInnerWidth; i++)
    {      
        for (int x = 0; x < logoInnerWidth; x++)
          SPI_WRITE16(ILI9341_BLACK);
    }  
    endWrite();

     //delay(5000);

    delay(1500);

    //print company name
    int chars = 24;
    char company[chars] = "Made with \x03 by SmartyKit";
    //char company[chars] = "MADE WITH \x03 BY SMARTYKIT, INC.";
    
     setCursor(_TFTwidth / 2 - (chars*LINE_WIDTH)/2, _TFTheight - LINE_HEIGHT- 4, CURSOR_ABSOLUTE);
     for (int i = 0; i < chars; i++)
     {
        if (company[i] == '\x03') //heart 
          print(company[i], ILI9341_RED);
        else
         print(company[i], ILI9341_WHITE);
        delay(100);
     }
    
    delay(1500);
  }       
}

void SmartyKit_DisplayDriver::sendCommand(uint8_t commandByte, const uint8_t *dataBytes,
                                  uint8_t numDataBytes) {
  SPI_BEGIN_TRANSACTION();
  if (_cs >= 0)
    SPI_CS_LOW();

  #if defined(_SMARTY_DEBUG_)
  Serial.print(F("PGM -> "));
  #endif
  
  SPI_DC_LOW();          // Command mode
  spiWrite(commandByte); // Send the command byte

  SPI_DC_HIGH();
  for (int i = 0; i < numDataBytes; i++) {
      Serial.print(F("arg")); Serial.print(i+1, DEC); Serial.print(F(" = "));
      uint8_t dataByte = pgm_read_byte(dataBytes++);
      dataByte &= 0xFF;
      spiWrite(dataByte);
  }

  if (_cs >= 0)
    SPI_CS_HIGH();
  SPI_END_TRANSACTION();
}

void SmartyKit_DisplayDriver::sendCommand(uint8_t commandByte, uint8_t *dataBytes,
                                  uint8_t numDataBytes) {
  SPI_BEGIN_TRANSACTION();
  if (_cs >= 0)
    SPI_CS_LOW();

  SPI_DC_LOW();          // Command mode
  spiWrite(commandByte); // Send the command byte

  SPI_DC_HIGH();
  for (int i = 0; i < numDataBytes; i++) {
      spiWrite(*dataBytes); // Send the data bytes
      dataBytes++;
  }
  if (_cs >= 0)
    SPI_CS_HIGH();
  SPI_END_TRANSACTION();
}

//Set the data/command line HIGH (data mode).
void SmartyKit_DisplayDriver::SPI_DC_HIGH(void) {
#if defined(USE_FAST_PINIO)

#else  // !USE_FAST_PINIO
    digitalWrite(_dc, HIGH);
#endif // end !USE_FAST_PINIO
  }

//Set the data/command line LOW (command mode).
void SmartyKit_DisplayDriver::SPI_DC_LOW(void) {
#if defined(USE_FAST_PINIO)

#else  // !USE_FAST_PINIO
    digitalWrite(_dc, LOW);
#endif // end !USE_FAST_PINIO
  }

void SmartyKit_DisplayDriver::SPI_CS_LOW(void) {
#if defined(USE_FAST_PINIO)

#else  // !USE_FAST_PINIO
    digitalWrite(_cs, LOW);
#endif // end !USE_FAST_PINIO
  }

void SmartyKit_DisplayDriver::SPI_CS_HIGH(void) {
#if defined(USE_FAST_PINIO)

#else  // !USE_FAST_PINIO
    digitalWrite(_cs, HIGH);
#endif // end !USE_FAST_PINIO
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

void SmartyKit_DisplayDriver::writeCommand(uint8_t cmd) {
  SPI_DC_LOW();
  spiWrite(cmd);
  SPI_DC_HIGH();
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
        //setAddrWindow(x, y, 1, 1);
        SPI_WRITE16(color);
    }
  }
  endWrite();
}

void SmartyKit_DisplayDriver::clearScreen(void)
{
  if (rotation == 3)
  {
      uint16_t color = ILI9341_BLACK;
      uint16_t color2 = ILI9341_BLACK;
      startWrite();
      setAddrWindow(_workingScreenLeftMargin, _workingScreenTopMargin, _workingScreenWidth, _workingScreenHeight);
      for (int y = 0; y < _workingScreenHeight; y++)
      {      
       for (int x = 0; x < _workingScreenWidth; x++)
        {   
            //setAddrWindow(x, y, 1, 1);
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
      uint16_t color = ILI9341_BLACK;
      uint16_t color2 = ILI9341_BLACK;
      startWrite();
      setAddrWindow(_workingScreenLeftMargin, _workingScreenTopMargin, _workingScreenWidth, _workingScreenHeight);
      for (int y = 0; y < _workingScreenHeight; y++)
      {
       for (int x = 0; x < _workingScreenWidth; x++)
        {   
            //setAddrWindow(x, y, 1, 1);
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


void SmartyKit_DisplayDriver::drawScreenKeyboard(uint16_t color)
{
  int kbdRows = 5;
  int kbdCols = 13;
  int kbdTextSize = 2;
  char kbd[kbdRows][kbdCols] = {
    {'!','@','#','$','%','^', '&', '*', '(', ')', '_',  '+', '<',},
    {'1','2','3','4','5', '6', '7', '8', '9', '0', '-',  '=', '>',},
    {'Q','W','E','R','T','Y', 'U', 'I', 'O', 'P',  ':',  '[', ']',},
    {'A','S','D','F','G','H', 'J', 'K', 'L', ';', '"',  '\'', '\\',  },
    {'Z','X','C','V','B','N', 'M', '\x205', '\x245', '\x244',  'E',  ',', '.', },
  };
  uint16_t kbdColor = ILI9341_WHITE;
  int kbdMargin = 5;
  int kbdMarginH = 6;
  int kbdMarginV = 2;
  
  int keyboardHeight = kbdRows*LINE_HEIGHT + (kbdRows - 1)*kbdMargin;

  int kbdX = _workingScreenLeftMargin + LINE_WIDTH*kbdTextSize/2;
  int kbdY = _workingScreenTopMargin + _workingScreenHeight + kbdMarginH;
//  if (rotation == 0)
//  {
//    startWrite();
//    setAddrWindow(kbbX,  kbdY, _workingScreenWidth, keyboardHeight);         
//    for (int x = 0; x < _workingScreenWidth*keyboardHeight; x++)
//          SPI_WRITE16(kbdColor);
//    endWrite();
//  }
  for (int i = 0; i < kbdRows; i++)
  {
    for (int j = 0; j < kbdCols; j++)
    {
      drawChar(kbdX + j*(LINE_WIDTH*kbdTextSize + kbdMarginH), kbdY + i*(LINE_HEIGHT*kbdTextSize+kbdMarginV), kbd[i][j], 
      ILI9341_BLACK, ILI9341_WHITE, kbdTextSize, 1);  
      //drawChar(cursor_x, yLine, c, color, bgColor, textsize_x);
    }
  }

  //draw Space bar, Enter and Delete
  int buttonsX = kbdX;
  int buttonsY = kbdY + kbdRows*(LINE_HEIGHT*kbdTextSize+kbdMarginV);
  int spaceCols = 6;
  int spaceWidth = spaceCols*kbdTextSize*LINE_WIDTH +  (spaceCols - 1)*kbdMarginH; 
  writeFillRect(buttonsX, buttonsY, spaceWidth, kbdTextSize * LINE_HEIGHT, ILI9341_WHITE);

  int enterCols = 3;
  int enterWidth = enterCols*kbdTextSize*LINE_WIDTH +  (enterCols - 1)*kbdMarginH;
  writeFillRect(buttonsX + spaceWidth + kbdMarginH, buttonsY, enterWidth, kbdTextSize * LINE_HEIGHT, ILI9341_WHITE);
 
  
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
    //TO-DO: add margins - left and top
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
//  else if (rotation == 3)
//  {
//    clearScreen();
//    //2 - shift text buffer for 1 line
//    scrollScreenBuffer(1);
//    //3 - redraw text from buffer 
//    printScreenBuffer();
//  }

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
    
//    char c = spiClass->transfer((uint8_t)w >> 8);
//    #if defined(_SMARTY_DEBUG_)
//    Serial.print(F("SPI_WRIE16 High = "));Serial.print(c, HEX);
//    #endif
//    c = spiClass->transfer((uint8_t)w);
//    #if defined(_SMARTY_DEBUG_)
//    Serial.print(F(", Low = "));Serial.println(c, HEX);
//    #endif
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

void SmartyKit_DisplayDriver::drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size, int keyboard = 0)
{
  uint8_t size_x = size;
  uint8_t size_y = size;

   if ((x >= _TFTwidth) ||              // Clip right
        (y >= _TFTheight) ||             // Clip bottom
        ((x + 6 * size_x - 1) < 0) || // Clip left
        ((y + 8 * size_y - 1) < 0))   // Clip top
        {
//           Serial.print(F("drawChar: clipping -> x = ")); Serial.print(x, DEC); Serial.print(F(", y = ")); Serial.print(y, DEC);
//           Serial.print(F(", _TFTheight = ")); Serial.print(_TFTheight, DEC); Serial.println();
            return;
        }
//    if (!_cp437 && (c >= 176))
//      c++; // Handle 'classic' charset behavior
    startWrite();
    //add first h-line for keyboard
      if(keyboard == 1)
      {
            writeFillRect(x-2, y - 1, size_x*6+2, size_y, bg);
      }
      
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

      //add first v-line for keyboard
      if(keyboard == 1)
      {
         if (size_x == 1 && size_y == 1)
           writeFastVLine(x - 2, y, 8, bg);
        else
            writeFillRect(x - 1*size_x, y, size_x, 8 * size_y, bg);
      }
    }
    
    endWrite();
  
}

void SmartyKit_DisplayDriver::print(uint8_t c, uint16_t color = ILI9341_GREEN)
{

    if (c == '\n') {              // Newline?
      cursor_x = _workingScreenLeftMargin;               // Reset x to zero,
      cursor_y += textsize_y * 8; // advance y one line
      //screen_col = 0;

       int maxHeight = _TFTheight;
      if (clipScreen == SCREEN_CLIPPED)
        maxHeight = _workingScreenHeight + _workingScreenTopMargin;
      if (cursor_y >= maxHeight )
      {
        scrollToNextLine();
        cursor_y -= textsize_y * 8;
        //screen_row = SCREEN_ROWS - 1;
      }
//      else
//        screen_row++;
      
    } else if (c != '\r') {       // Ignore carriage returns
      if ((cursor_x + textsize_x * 6) > _workingScreenLeftMargin + _workingScreenWidth) { // Off right?
        cursor_x = _workingScreenLeftMargin;                                       // Reset x to zero,
 //       screen_col = 0;
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
//        screen_row = SCREEN_ROWS - 1;
      }
//      else
//        screen_row++;

        //converting screen coordinates to memory coordinates
      int yLine;
      if ((scrollLine + cursor_y) < maxHeight)
        yLine = scrollLine + cursor_y;
      else
        yLine = (scrollLine + cursor_y) - maxHeight;
    
      drawChar(cursor_x, yLine, c, color, bgColor, textsize_x);
      cursor_x += textsize_x * 6; // Advance x one char
//      screen_col++;
//      screenBuffer[screen_row][screen_col] = c;
    }


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

//    //save for screen buffer
//    int col = x / LINE_WIDTH;
//    int mask = (1 << (x % LINE_WIDTH)) - 1;
//    if (color == ILI9341_BLACK)
//      mask &= B00000000;
//    else if (color == ILI9341_GREEN)
//      mask |= B11111111;
//      
//    pixelBuffer[x][y] = pixelBuffer[x][y] || mask;
    
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

void SmartyKit_DisplayDriver::printScreenBuffer()
{
  int cursor_x = _workingScreenLeftMargin;
  int cursor_y = _workingScreenTopMargin;
  setCursor(0, 0); //top-left of working screen
  for (int i = 0; i < SCREEN_ROWS; i++)
  {
    for (int j = 0; j < SCREEN_COLS; j++)
    {

         char c = screenBuffer[i][j];
         
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
      
            //screenBuffer
          }
    }
  }
  print('\n');
}

inline void SmartyKit_DisplayDriver::writeColor(uint16_t color, uint32_t len)
{
  for (uint16_t i = 0; i < len; i++)
        SPI_WRITE16(color);  
}
//end: SmartyKit Display Driver Class

// 40 keys 4x10 Keyboard Driver Class
class SmartyKit_40KeysKeyboardDriver
{
  public:
  int colPressed;
  int rowPressed;
  const static int numRows = 4;
  const static int numCols = 10;
  int rowPins[numRows] = {0,1,2,3};
  int colPins[numCols] = {4,5,6,7,8,9,10,11,12,13};

      char kbdTable[numRows][numCols] = {
      {'1','2','3','4','5', '6', '7', '8', '9', '0',},
      {'Q','W','E','R','T','Y', 'U', 'I', 'O', 'P',},
      {'A','S','D','F','G','H', 'J', 'K', 'L', '\n', },
      {'\xE','Z', 'X','C','V','B','N', 'M', '\x20', '\x7F',},
    };

  
  SmartyKit_40KeysKeyboardDriver::SmartyKit_40KeysKeyboardDriver(){};
  SmartyKit_40KeysKeyboardDriver::~SmartyKit_40KeysKeyboardDriver(){};

  void setup()
  {
    //setup
    for (int row = 0; row < numRows; row++)
      pinMode(rowPins[row], INPUT_PULLUP);

    for (int col = 0; col < numCols; col++)
    {
      pinMode(colPins[col], OUTPUT); 
      digitalWrite(colPins[col], HIGH);
    }
  }

  char read()
  {
    char c = '\x0';


  int val = 0;
  
  for (int col = 0; col < numCols; col++)
  {
    //searching with col = LOW
    digitalWrite(colPins[col], LOW);

    for (int row = 0; row < numRows; row++)
    {
        val = digitalRead(rowPins[row]);
        if (val == LOW)
        {
          c = kbdTable[row][col];
          colPressed = col;
          rowPressed = row;
        }
    }
    digitalWrite(colPins[col], HIGH);
  }
  // c = kbdTable[3][7];
    return c;
  }
};
//end: 40 keys 4x10 Keyboard Driver Class


/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

//main code: setup() and loop()
SmartyKit_40KeysKeyboardDriver kbd;
SmartyKit_DisplayDriver tft; //creating instance of our Display Driver



const int CPUwritesToVideoPortPin =  3;
const int VideoBIT7pin =  5; 
int DataBus[8] = {6, 7, 8, 9, 10, 11, 12, 13};
byte scan_code=0; 

void setup() {
  pinMode(VideoBIT7pin, OUTPUT); 
  digitalWrite(VideoBIT7pin, HIGH); //wait until video setup is ready

    // starting TFT screen
  tft.setup();
  
  for (int count = 1; count <= 8; count++) {
    pinMode(DataBus[count-1], INPUT); 
  };
  pinMode(CPUwritesToVideoPortPin, INPUT); 

#ifdef _TERMINAL_
  // Initialise the terminal 
  //term.cursorOff();
  // show hello world
  term.setFont(TERMINAL_FONT_40_NORMAL_SINGLE);
  term.setCursor(0,0);
  term.printLine("Hello!\r\nI'm SmartyKit 1\r\nApple 1-compatible computer\r\nwww.smartykit.io\n");

  term.printLine("\nType address to run:");
  term.printLine("F000R -> Woz's face demo");

  term.printLine("");
  term.printLine("     40x25 text output library for Arduino in two wire interface (I" "\xFD" "C) Mode");
  term.printLine("");
  // Show the 80 character positions
  term.print("00000000001111111111222222222233333333334444444444555555555566666666667777777777");
  term.printLine("01234567890123456789012345678901234567890123456789012345678901234567890123456789");
#endif

  
  //attaching an IRQ to CPUwritesToVideoPortPin
  attachInterrupt(1, videoCharInterrupt, RISING); 
  digitalWrite(VideoBIT7pin, LOW); //default state after restart = 0 (ready to print) 
}

void loop() {
  //intentionally left blank
}


//interruption service routine (ISR)
void videoCharInterrupt(void) {   
  digitalWrite(VideoBIT7pin, HIGH);  
   
  scan_code = 0;
  for (int count = 1; count <= 8 ; count++) {
    int pinValue = digitalRead(DataBus[count-1]);    
    scan_code |= pinValue << (count-1);   
  };
  scan_code = scan_code & 0x7F; //clear bit 7
  
  if (scan_code == 0x7F)
  {
     digitalWrite(VideoBIT7pin, LOW);    
     return; //skip initial setup value
  }
  
  if (scan_code == 0xD)
  {
     tft.print('\n');
     #ifdef _TERMINAL_
     term.printLine("");
     #endif
  }
  else
  {         
    //make all symbols uppercase
    if (scan_code >= 0x60)
      scan_code -= 0x20;

     //print only visible chars, starting from blanc 
     if (scan_code >= 0x20)
     { 
         tft.print((char)scan_code); 
         #ifdef _TERMINAL_
         term.send(scan_code);
         #endif
     }
     //backspace
     if (scan_code == 0x8)
     {
         //TV.print((char)scan_code); 
     }
      
  }
  digitalWrite(VideoBIT7pin, LOW); 
}
