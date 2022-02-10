To use this library you need an additional ATMega328P to act as a video processor, and a 74HCT166 shift register to generate the video bit stream.

The video processor hex file needs to be programmed into an ATMega328P with the following fuses set:
E6 D9 FF

In avrdude that is: (change the com port as appropriate)

avrdude -P COM3 -b 19200 -c avrisp -p m328p -n
avrdude -P COM3 -b 19200 -c avrisp -p m328p -U lfuse:w:0xe6:m
avrdude -P COM3 -b 19200 -c avrisp -p m328p -U hfuse:w:0xd9:m
avrdude -P COM3 -b 19200 -c avrisp -p m328p -U efuse:w:0xff:m
avrdude -P COM3 -b 19200 -c avrisp -p m328p -U flash:w:SBCVideo.hex

The video processor code is written by Grant Searle, based on code by Daryl Rictor.

Their pages are as follows:

http://searle.hostei.com/grant/MonitorKeyboard/index.html
http://sbc.rictor.org/vid3.html

80x25 Terminal library by Dave Curran, based on code from the above. For more info see:

http://blog.tynemouthsoftware.co.uk/2013/09/arduino-80x25-tv-video-output-library.html
http://blog.tynemouthsoftware.co.uk/2013/09/arduino-80x25-tv-video-output-library_15.html
