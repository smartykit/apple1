/*
Copyright (c) 2010 Myles Metzer
Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:
The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/
/*
This library provides a simple method for outputting data to a tv
from a frame buffer stored in sram.  This implementation is done
completly by interupt and will return give as much cpu time to the
application as possible.
*/

#include "TVout.h"

/* call this to start video output with the default resolution.
    Arguments:
        mode: The video standard to follow:
            PAL  = 1 = _PAL
            NTSC = 0 = _NTSC
    Returns:
        0 if no error.
        4 if there is not enough memory.
*/

uint8_t TVout::begin(uint8_t mode) {
    return begin(mode, 128, 96);
}


/* call this to start video output with a specified resolution.
    Arguments:
        mode: The video standard to follow:
            PAL  = 1 = _PAL
            NTSC = 0 = _NTSC
        x: Horizonal resolution must be divisable by 8.
        y: Vertical resolution.
    Returns:
        0 if no error.
        1 if x is not divisable by 8.
        2 if y is to large (NTSC only cannot fill PAL vertical resolution by 8bit limit)
        4 if there is not enough memory for the frame buffer.
*/

uint8_t TVout::begin(uint8_t mode, uint8_t x, uint8_t y) {
    // check if x is divisable by 8
    if (x % 8) {
        return 1;
    }
    x = x / 8;
    screen = (unsigned char*)malloc(x * y * sizeof(unsigned char));
    if (screen == NULL) {
        return 4;
    }	
    _cursorX = 0;
    _cursorY = 0;
    render_setup(mode, x, y, screen);
    clearScreen();
    return 0;
}

// stop video render and free the used memory
 void TVout::end() {
    TIMSK1 = 0;
    free(screen);
}


/* Gets the Horizontal resolution of the screen
    Returns: The horizonal resolution.
*/
unsigned int TVout::hres() {
    return display.hres * 8;
}

/* Gets the Vertical resolution of the screen
    Returns: The vertical resolution
*/
unsigned int TVout::vres() {
    return display.vres;
}

/* Return the number of characters that will fit on a line
    Returns:    The number of characters that will fit on a text line starting from x = 0.
                Will return -1 for dynamic width fonts as this cannot be determined.
*/
char TVout::charLine() {
    return ((display.hres * 8) / pgm_read_byte(font));
}

/* Delay for x ms
    The resolution is 16ms for NTSC and 20ms for PAL
    Arguments:
        x: The number of ms this function should consume.
*/
void TVout::delay(unsigned int x) {
    unsigned long time = millis() + x;
    while (millis() < time);
}

/* Delay for x frames, exits at the end of the last display line.
    delayFrame(1) is useful prior to drawing so there is little/no flicker.
    Arguments:
        x: The number of frames to delay for.
 */
void TVout::delayFrame(unsigned int x) {
    int stop_line = (int)(display.start_render + (display.vres*(display.vscale_const + 1 ))) + 1;
    while (x) {
        while (display.scanLine != stop_line);
        while (display.scanLine == stop_line);
        x--;
    }
}


/* Get the time in ms since begin was called.
    The resolution is 16ms for NTSC and 20ms for PAL
    Returns: The time in ms since video generation has started.
*/
unsigned long TVout::millis() {
    if (display.lines_frame == _NTSC_LINE_FRAME) {
        return display.frames * _NTSC_TIME_SCANLINE * _NTSC_LINE_FRAME / 1000;
    }
    else {
        return display.frames * _PAL_TIME_SCANLINE * _PAL_LINE_FRAME / 1000;
    }
}

void TVout::clearScreen() {
    fill(0);
}

void TVout::invert() {
    fill(2);
}

/* Fill the screen with some color.
    Arguments:
        color: The color to fill the screen with
*/
void TVout::fill(uint8_t color) {
    switch(color) {
        case BLACK:
            _cursorX = 0;
            _cursorY = 0;
            for (int i = 0; i < (display.hres)*display.vres; i++)
                display.screen[i] = 0;
            break;
        case WHITE:
            _cursorX = 0;
            _cursorY = 0;
            for (int i = 0; i < (display.hres)*display.vres; i++)
                display.screen[i] = 0xFF;
            break;
        case INVERT:
            for (int i = 0; i < display.hres*display.vres; i++)
                display.screen[i] = ~display.screen[i];
        break;
    }
}

/* Set the color of a pixel
    Arguments:
        x: The x coordinate of the pixel.
        y: The y coordinate of the pixel.
        c: The color of the pixel
 */
void TVout::setPixel(uint8_t x, uint8_t y, char c) {
    if (x >= display.hres * 8 || y >= display.vres)
        return;
    sp(x, y, c);
}


/* get the color of the pixel at x, y
    Arguments:
        x: The x coordinate of the pixel.
        y: The y coordinate of the pixel.
    Returns:
        The color of the pixel
*/
bool TVout::getPixel(uint8_t x, uint8_t y) {
    if (x >= display.hres * 8 || y >= display.vres)
        return false;
    if (display.screen[x / 8 + y * display.hres] & (0x80 >> (x & 7)))
        return true;
    return false;
}

/* Draw a line from one point to another
    Arguments:
        x0: The x coordinate of point 0.
        y0: The y coordinate of point 0.
        x1: The x coordinate of point 1.
        y1: The y coordinate of point 1.
        c: The color of the line.
 */
void TVout::drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, char c) {
    if (x0 > display.hres*8 || y0 > display.vres || x1 > display.hres*8 || y1 > display.vres)
        return;
    if (x0 == x1)
        drawColumn(x0, y0, y1, c);
    else if (y0 == y1)
        drawRow(y0, x0, x1, c);
    else {
        int e;
        int dx, dy, j, temp;
        char s1, s2, xchange;
        int x, y;

        x = x0;
        y = y0;

        // take absolute value
        if (x1 < x0) {
            dx = x0 - x1;
            s1 = -1;
        } else if (x1 == x0) {
            dx = 0;
            s1 = 0;
        } else {
            dx = x1 - x0;
            s1 = 1;
        }

        if (y1 < y0) {
            dy = y0 - y1;
            s2 = -1;
        } else if (y1 == y0) {
            dy = 0;
            s2 = 0;
        } else {
            dy = y1 - y0;
            s2 = 1;
        }

        xchange = 0;   

        if (dy > dx) {
            temp = dx;
            dx = dy;
            dy = temp;
            xchange = 1;
        } 

        e = ((int)dy << 1) - dx;

        for (j = 0; j <= dx; j++) {
            sp(x, y, c);

            if (e >= 0) {
                if (xchange == 1) {
                     x = x + s1;
                } else {
                    y = y + s2;
                }
                e = e - ((int)dx << 1);
            }
            if (xchange == 1) {
                y = y + s2;
            } else {
                x = x + s1;
            }
            e = e + ((int)dy << 1);
        }
    }
}


/* Fill a row from one point to another
    Argument:
        line: The row that fill will be performed on.
        x0: edge 0 of the fill.
        x1: edge 1 of the fill.
        c: the color of the fill.
*/
void TVout::drawRow(uint8_t line, uint16_t x0, uint16_t x1, uint8_t c) {
    uint8_t lbit, rbit;

    if (x0 == x1) {
        setPixel(x0, line, c);
    } else {
        if (x0 > x1) {
            lbit = x0;
            x0 = x1;
            x1 = lbit;
        }
        lbit = 0xff >> (x0 & 7);
        x0 = x0 / 8 + display.hres * line;
        rbit = ~(0xff >> (x1 & 7));
        x1 = x1 / 8 + display.hres * line;
        if (x0 == x1) {
            lbit = lbit & rbit;
            rbit = 0;
        }
        if (c == WHITE) {
           screen[x0++] |= lbit;
            while (x0 < x1) {
                screen[x0++] = 0xff;
            }
            screen[x0] |= rbit;
        } else if (c == BLACK) {
            screen[x0++] &= ~lbit;
            while (x0 < x1) {
                screen[x0++] = 0;
            }
            screen[x0] &= ~rbit;
        } else if (c == INVERT) {
            screen[x0++] ^= lbit;
            while (x0 < x1) {
                screen[x0++] ^= 0xff;
            }
            screen[x0] ^= rbit;
        }
    }
}


/* Fill a column from one point to another
    Argument:
        row:    The row that fill will be performed on.
        y0:     edge 0 of the fill.
        y1:     edge 1 of the fill.
        c:      the color of the fill.
*/
void TVout::drawColumn(uint8_t row, uint16_t y0, uint16_t y1, uint8_t c) {
    unsigned char bit;
    int byte;

    if (y0 == y1) {
        setPixel(row, y0, c);
    } else {
        if (y1 < y0) {
            bit = y0;
            y0 = y1;
            y1 = bit;
        }
        bit = 0x80 >> (row&7);
        byte = row/8 + y0*display.hres;
        if (c == WHITE) {
            while (y0 <= y1) {
                screen[byte] |= bit;
                byte += display.hres;
                y0++;
            }
        } else if (c == BLACK) {
            while (y0 <= y1) {
                screen[byte] &= ~bit;
                byte += display.hres;
                y0++;
            }
        } else if (c == INVERT) {
            while ( y0 <= y1) {
                screen[byte] ^= bit;
                byte += display.hres;
                y0++;
            }
        }
    }
}


/* draw a rectangle at x,y with a specified width and height
    Arguments:
        x0: The x coordinate of upper left corner of the rectangle.
        y0: The y coordinate of upper left corner of the rectangle.
        w:  The widht of the rectangle.
        h:  The height of the rectangle.
        c:  The color of the rectangle.
        fc: The fill color of the rectangle.
*/
void TVout::drawRect(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, char c, char fc) {
    if (fc != -1) {
        for (unsigned char i = y0; i < y0 + h; i++) {
            drawRow(i, x0, x0 + w, fc);
        }
    }
    drawLine(x0, y0, x0 + w, y0, c);
    drawLine(x0, y0, x0, y0 + h, c);
    drawLine(x0 + w, y0, x0 + w, y0 + h, c);
    drawLine(x0, y0 + h, x0 + w, y0 + h, c);
}


/* draw a circle given a coordinate x,y and radius both filled and non filled.
    Arguments:
        x0: The x coordinate of the center of the circle.
        y0: The y coordinate of the center of the circle.
        radius: The radius of the circle.
        c:   The color of the circle.
        fc:  The color to fill the circle.
 */
void TVout::drawCircle(uint8_t x0, uint8_t y0, uint8_t radius, char c, char fc) {
    int f = 1 - radius;
    int ddF_x = 1;
    int	ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
    uint8_t pyy = y, pyx = x;

    // there is a fill color
    if (fc != -1) {
        drawRow(y0, x0 - radius, x0 + radius, fc);
    }

    sp(x0, y0 + radius, c);
    sp(x0, y0 - radius, c);
    sp(x0 + radius, y0, c);
    sp(x0 - radius, y0, c);
	
    while(x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        // there is a fill color
        if (fc != -1) {
            // prevent double draws on the same rows
            if (pyy != y) {
                drawRow(y0+y, x0 - x, x0 + x, fc);
                drawRow(y0-y, x0 - x, x0 + x, fc);
            }
            if (pyx != x && x != y) {
                drawRow(y0 + x, x0 - y, x0 + y, fc);
                drawRow(y0 - x, x0 - y, x0 + y, fc);
            }
            pyy = y;
            pyx = x;
        }
        sp(x0 + x, y0 + y,c);
        sp(x0 - x, y0 + y,c);
        sp(x0 + x, y0 - y,c);
        sp(x0 - x, y0 - y,c);
        sp(x0 + y, y0 + x,c);
        sp(x0 - y, y0 + x,c);
        sp(x0 + y, y0 - x,c);
        sp(x0 - y, y0 - x,c);
    }
}


/* place a bitmap at x,y where the bitmap is defined as {width,height,imagedata....}
    Arguments:
        x:      The x coordinate of the upper left corner.
        y:      The y coordinate of the upper left corner.
        bmp:    The bitmap data to print.
        i:      The offset into the image data to start at.  This is mainly used for fonts 
                default = 0
        width:  Override the bitmap width. This is mainly used for fonts.
                default = 0 (do not override)
        height: Override the bitmap height. This is mainly used for fonts.
                default	= 0 (do not override)
*/
void TVout::bitmap(uint8_t x, uint8_t y, const unsigned char * bmp,
                   uint16_t i, uint8_t width, uint8_t lines) {
    uint8_t temp, lshift, rshift, save, xtra;
    uint16_t si = 0;

    rshift = x & 7;
    lshift = 8 - rshift;
    if (width == 0) {
        width = pgm_read_byte((uint32_t)(bmp) + i);
        i++;
    }
    if (lines == 0) {
        lines = pgm_read_byte((uint32_t)(bmp) + i);
        i++;
    }

    if (width & 7) {
        xtra = width & 7;
        width = width / 8;
        width++;
    } else {
        xtra = 8;
        width = width / 8;
    }

    for (uint8_t l = 0; l < lines; l++) {
        si = (y + l) * display.hres + x / 8;
        if (width == 1) {
            temp = 0xff >> rshift + xtra;
        } else {
            temp = 0;
        }
        save = screen[si];
        screen[si] &= ((0xff << lshift) | temp);
        temp = pgm_read_byte((uint32_t)(bmp) + i++);
        screen[si++] |= temp >> rshift;
        for (uint16_t b = i + width - 1; i < b; i++) {
            save = screen[si];
            screen[si] = temp << lshift;
            temp = pgm_read_byte((uint32_t)(bmp) + i);
            screen[si++] |= temp >> rshift;
        }
        if (rshift + xtra < 8) {
            screen[si - 1] |= (save & (0xff >> rshift + xtra));
        }
        if (rshift + xtra - 8 > 0) {
            screen[si] &= (0xff >> rshift + xtra - 8);
        }
        screen[si] |= temp << lshift;
    }
}

/* shift the pixel buffer in any direction
    This function will shift the screen in a direction by any distance.
    Arguments:
        distance:   The distance to shift the screen
        direction:  The direction to shift the screen the direction and the integer values:
            UP      = 0
            DOWN    = 1
            LEFT	= 2
            RIGHT	= 3
*/

void TVout::shift(uint8_t distance, uint8_t direction) {
    uint8_t * src;
    uint8_t * dst;
    uint8_t * end;
    uint8_t shift;
    uint8_t tmp;
    switch (direction) {
        case UP:
            dst = display.screen;
            src = display.screen + distance*display.hres;
            end = display.screen + display.vres*display.hres;
            while (src <= end) {
                *dst = *src;
                *src = 0;
                dst++;
                src++;
            }
            break;
        case DOWN:
            dst = display.screen + display.vres*display.hres;
            src = dst - distance*display.hres;
            end = display.screen;
            while (src >= end) {
            *dst = *src;
            *src = 0;
                dst--;
                src--;
            }
            break;
        case LEFT:
            shift = distance & 7;
            for (uint8_t line = 0; line < display.vres; line++) {
                dst = display.screen + display.hres*line;
                src = dst + distance/8;
                end = dst + display.hres-2;
                while (src <= end) {
                    tmp = 0;
                    tmp = *src << shift;
                    *src = 0;
                    src++;
                    tmp |= *src >> (8 - shift);
                    *dst = tmp;
                    dst++;
                }
                tmp = 0;
                tmp = *src << shift;
                *src = 0;
                *dst = tmp;
            }
            break;
        case RIGHT:
            shift = distance & 7;
            for (uint8_t line = 0; line < display.vres; line++) {
                dst = display.screen + display.hres-1 + display.hres*line;
                src = dst - distance/8;
                end = dst - display.hres+2;
                while (src >= end) {
                    tmp = 0;
                    tmp = *src >> shift;
                    *src = 0;
                    src--;
                    tmp |= *src << (8 - shift);
                    *dst = tmp;
                    dst--;
                }
                tmp = 0;
                tmp = *src >> shift;
                *src = 0;
                *dst = tmp;
            }
            break;
    }
}

void TVout::printChar(uint8_t x, uint8_t y, unsigned char c) {
    c -= pgm_read_byte(font + 2);
    bitmap(x, y, font, (c * pgm_read_byte(font + 1)) + 3, pgm_read_byte(font), pgm_read_byte(font + 1));
}

void TVout::setCursor(uint8_t x, uint8_t y) {
    _cursorX = x;
    _cursorY = y;
}

void TVout::selectFont(const unsigned char* f) {
    font = f;
}

void TVout::write(const char *str) {
    while (*str) {
        write(*str++);
    }
}

void TVout::write(const uint8_t *buffer, uint8_t size) {
    while (size--) {
        write(*buffer++);
    }
}

void TVout::write(uint8_t c) {
    switch(c) {
        // null
        case '\0':
            break;
        // line feed
        case '\n':
            _cursorX = 0;
            incTxtLine();
            break;
        // backspace
        case 8:
            _cursorX -= pgm_read_byte(font);
            printChar(_cursorX, _cursorY,' ');
            break;
        // carriage return
        case 13:
            _cursorX = 0;
            break;
        // form feed new page(clear screen)
        case 14:
            //clearScreen();
            break;
        default:
            if (_cursorX >= (display.hres * 8 - pgm_read_byte(font))) {
                _cursorX = 0;
                incTxtLine();
                printChar(_cursorX, _cursorY, c);
            } else {
                printChar(_cursorX, _cursorY, c);
            }
            _cursorX += pgm_read_byte(font);
    }
}

void TVout::print(const char str[]) {
    write(str);
}

void TVout::print(char c, int base) {
    print((long) c, base);
}

void TVout::print(unsigned char b, int base) {
    print((unsigned long) b, base);
}

void TVout::print(int n, int base) {
    print((long) n, base);
}

void TVout::print(unsigned int n, int base) {
    print((unsigned long) n, base);
}

void TVout::print(long n, int base) {
    if (base == 0) {
        write(n);
    } else if (base == 10) {
        if (n < 0) {
            print('-');
        n = -n;
        }
        printNumber(n, 10);
    } else {
        printNumber(n, base);
    }
}

void TVout::print(unsigned long n, int base) {
    if (base == 0) {
        write(n);
    } else {
        printNumber(n, base);
    }
}

void TVout::print(float n, int digits) {
    printFloat(n, digits);
}

void TVout::println(void) {
    print('\r');
    print('\n');  
}

void TVout::println(const char c[]) {
    print(c);
    println();
}

void TVout::println(char c, int base) {
    print(c, base);
    println();
}

void TVout::println(unsigned char b, int base) {
    print(b, base);
    println();
}

void TVout::println(int n, int base) {
    print(n, base);
    println();
}

void TVout::println(unsigned int n, int base) {
    print(n, base);
    println();
}

void TVout::println(long n, int base) {
    print(n, base);
    println();
}

void TVout::println(unsigned long n, int base) {
    print(n, base);
    println();
}

void TVout::println(float n, int digits) {
    print(n, digits);
    println();
}

void TVout::printPGM(const char str[]) {
    char c;
    while ((c = pgm_read_byte(str))) {
        str++;
        write(c);
    }
}

void TVout::printPGM(uint8_t x, uint8_t y, const char str[]) {
    char c;
    _cursorX = x;
    _cursorY = y;
    while ((c = pgm_read_byte(str))) {
        str++;
        write(c);
    }
}

void TVout::print(uint8_t x, uint8_t y, const char str[]) {
    _cursorX = x;
    _cursorY = y;
    write(str);
    
}

void TVout::print(uint8_t x, uint8_t y, char c, int base) {
    _cursorX = x;
    _cursorY = y;
    print((long) c, base);
}

void TVout::print(uint8_t x, uint8_t y, unsigned char b, int base) {
    _cursorX = x;
    _cursorY = y;
    print((unsigned long) b, base);
}

void TVout::print(uint8_t x, uint8_t y, int n, int base) {
    _cursorX = x;
    _cursorY = y;
    print((long) n, base);
}

void TVout::print(uint8_t x, uint8_t y, unsigned int n, int base) {
    _cursorX = x;
    _cursorY = y;
    print((unsigned long) n, base);
}

void TVout::print(uint8_t x, uint8_t y, long n, int base) {
    _cursorX = x;
    _cursorY = y;
    print(n,base);
}

void TVout::print(uint8_t x, uint8_t y, unsigned long n, int base) {
    _cursorX = x;
    _cursorY = y;
    print(n,base);
}

void TVout::print(uint8_t x, uint8_t y, float n, int digits) {
    _cursorX = x;
    _cursorY = y;
    print(n,digits);
}

void TVout::println(uint8_t x, uint8_t y, const char c[]) {
    _cursorX = x;
    _cursorY = y;
    print(c);
    println();
}

void TVout::println(uint8_t x, uint8_t y, char c, int base) {
    _cursorX = x;
    _cursorY = y;
    print(c, base);
    println();
}

void TVout::println(uint8_t x, uint8_t y, unsigned char b, int base) {
    _cursorX = x;
    _cursorY = y;
    print(b, base);
    println();
}

void TVout::println(uint8_t x, uint8_t y, int n, int base) {
    _cursorX = x;
    _cursorY = y;
    print(n, base);
    println();
}

void TVout::println(uint8_t x, uint8_t y, unsigned int n, int base) {
    _cursorX = x;
    _cursorY = y;
    print(n, base);
    println();
}

void TVout::println(uint8_t x, uint8_t y, long n, int base) {
    _cursorX = x;
    _cursorY = y;
    print(n, base);
    println();
}

void TVout::println(uint8_t x, uint8_t y, unsigned long n, int base) {
    _cursorX = x;
    _cursorY = y;
    print(n, base);
    println();
}

void TVout::println(uint8_t x, uint8_t y, float n, int digits) {
    _cursorX = x;
    _cursorY = y;
    print(n, digits);
    println();
}

void TVout::printNumber(unsigned long n, uint8_t base) { 
    unsigned char buf[8 * sizeof(long)]; 
    unsigned long i = 0;
    if (n == 0) {
        print('0');
        return;
    } 

    while (n > 0) {
        buf[i++] = n % base;
        n /= base;
    }

    for (; i > 0; i--) {
        print((char) (buf[i - 1] < 10 ?
        '0' + buf[i - 1] :
        'A' + buf[i - 1] - 10));
    }
}

void TVout::printFloat(float number, uint8_t digits) {
    // Handle negative numbers
    if (number < 0.0) {
        print('-');
        number = -number;
    }

    // Round correctly so that print(1.999, 2) prints as "2.00"
    float rounding = 0.5;
    for (uint8_t i = 0; i < digits; ++i) {
        rounding /= 10.0;
    }
    number += rounding;

    // Extract the integer part of the number and print it
    unsigned long int_part = (unsigned long)number;
    float remainder = number - (float)int_part;
    print(int_part);

    // Print the decimal point, but only if there are digits beyond
    if (digits > 0) {
        print(".");
    }

    // Extract digits from the remainder one at a time
    while (digits-- > 0) {
        remainder *= 10.0;
        int toPrint = int(remainder);
        print(toPrint);
        remainder -= toPrint; 
    }
}

/* Simple tone generation
    Arguments:
        frequency:  the frequency of the tone courtesy of adamwwolf
 */
void TVout::tone(unsigned int frequency) {
    tone(frequency, 0);
}

/* Simple tone generation
    Arguments:
        frequency:      the frequency of the tone
        durationMS:    the duration to play the tone in ms courtesy of adamwwolf
*/
void TVout::tone(unsigned int frequency, unsigned long durationMS) {
    if (frequency == 0) {
        return;
    }

    #define TIMER 2
    // this is init code
    TCCR2A = 0;
    TCCR2B = 0;
    TCCR2A |= _BV(WGM21);
    TCCR2B |= _BV(CS20);
    // end init code

    // most of this is taken from Tone.cpp from Arduino
    uint8_t prescalarbits = 0b001;
    uint32_t ocr = 0;
  
    // set pb3 (digital pin 11) to output
    DDR_SND |= _BV(SND_PIN);

    // we are using an 8 bit timer, scan through prescalars to find the best fit
    ocr = F_CPU / frequency / 2 - 1;
    // ck/1: same for both timers
    prescalarbits = 0b001;
    if (ocr > 255) {
        ocr = F_CPU / frequency / 2 / 8 - 1;
        // ck/8: same for both timers
        prescalarbits = 0b010;

        if (ocr > 255) {
            ocr = F_CPU / frequency / 2 / 32 - 1;
            prescalarbits = 0b011;
        }

        if (ocr > 255) {
            ocr = F_CPU / frequency / 2 / 64 - 1;
            prescalarbits = TIMER == 0 ? 0b011 : 0b100;
            if (ocr > 255) {
                ocr = F_CPU / frequency / 2 / 128 - 1;
                prescalarbits = 0b101;
            }

            if (ocr > 255) {
                ocr = F_CPU / frequency / 2 / 256 - 1;
                prescalarbits = TIMER == 0 ? 0b100 : 0b110;
                if (ocr > 255) {
                    // can't do any better than / 1024
                    ocr = F_CPU / frequency / 2 / 1024 - 1;
                    prescalarbits = TIMER == 0 ? 0b101 : 0b111;
                }
            }
        }
    }

    TCCR2B = prescalarbits;

    if (durationMS > 0) {
        // 60 here represents the framerate
        remainingToneVsyncs = durationMS * 60 / 1000;
    } else {
        remainingToneVsyncs = -1;
    }
 
    // set the OCR for the given timer,
    OCR2A = ocr;
    // set it to toggle the pin by itself
    // set COM2A1 to 0
    TCCR2A &= ~(_BV(COM2A1));
    TCCR2A |= _BV(COM2A0);
}

/* stops tone generation
*/
void TVout::noTone() {
    TCCR2B = 0;
    // set pin 11 to 0
    PORT_SND &= ~(_BV(SND_PIN));
}

/* set the vertical blank function call
    The function passed to this function will be called one per frame. The function should be quickish.
    Arguments:
        func: The function to call
*/
void TVout::setVBIHook(void (*func)()) {
    vbi_hook = func;
}


/* set the horizonal blank function call
    This function passed to this function will be called one per scan line.
    The function MUST be VERY FAST(~2us max).
    Arguments:
        funct: The function to call
*/
void TVout::setHBIHook(void (*func)()) {
    hbi_hook = func;
}


/* force the number of times to display each line
    Arguments:
        sfactor: The scale number of times to repeate each line.
*/
void TVout::forceVscale(char sfactor) {
    delayFrame(1);
    display.vscale_const = sfactor - 1;
    display.vscale = sfactor - 1;
}


/* force the output start time of a scanline in micro seconds
    Arguments:
        time: The new output start time in micro seconds.
*/
void TVout::forceOutStart(uint8_t time) {
    delayFrame(1);
    display.output_delay = ((time * _CYCLES_PER_US) - 1);
}


/* force the start line for active video
    Arguments:
        line: The new active video output start line
*/
void TVout::forceLineStart(uint8_t line) {
    delayFrame(1);
    display.start_render = line;
}

void TVout::incTxtLine() {
    if (_cursorY >= (display.vres - pgm_read_byte(font + 1)))
        shift(pgm_read_byte(font + 1), UP);
    else
        _cursorY += pgm_read_byte(font + 1);
}

/* Inline version of setPixel that does not perform a bounds check
*/
static void inline sp(uint8_t x, uint8_t y, char c) {
    if (c == 1) {
        display.screen[(x / 8) + (y * display.hres)] |= 0x80 >> (x & 7);
    } else if (c == 0) {
    display.screen[(x / 8) + (y * display.hres)] &= ~0x80 >> (x & 7);
    } else {
        display.screen[(x / 8) + (y * display.hres)] ^= 0x80 >> (x & 7);
    }
}
