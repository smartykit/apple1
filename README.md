# SmartyKit Apple I - apple1
SmartyKit Apple I replica drivers and software (http://www.smartykit.io/).

All needed libraries included in repository in /Arduino/libraries

## Keyboard Driver
Keyboard driver uses Arduino PS2Keyboard library.

## Video Driver 
Video driver uses Arduino TVout library.

## Software Emulator - POM 1
POM 1 cross-platform emulator by Verhille Arnaud to test SmartyKit 1 ROM with software.

[![Video to-do](https://j.gifs.com/K1PNZr.gif)](https://youtu.be/rniZDdS6toI)

## SmartyKit 1 Memory Map – ROM and RAM

![SmartyKit 1 Memory Map](https://raw.githubusercontent.com/smartykit/apple1/master/ROM%20development/SmartyKit_1_Memory_Map.png)

## ROM Development – SmartyKit 1 ROM asm source and make file
Easy-to-use development tool to write your own software for SmartyKLit 1 (you need just run make in your Terminal) and learn how ROM is organized.

Here is an example:
```bash
SERGEYs-MacBook:ROM_development spanarin$ make
SmartyKit 1: 6502 assembler & C-compiler to ROM (.bin)
Assembling and linking...
ca65 -l ROM_listing.asm SmartyKit1_ROM.asm
ld65 -m ROM.map -o SmartyKit1_ROM.bin SmartyKit1_ROM.o -C apple1.cfg
ld65 -o SmartyKit1_ROM_symon.bin SmartyKit1_ROM.o -C symon.cfg
SERGEYs-MacBook:ROM_development spanarin$
```

## SmartyKit 8x8 Pixel Art online tool for program at $FC00 in ROM (FC00R command)
You could draw your own pixel art using our online tool (https://smartykit.io/instructions/pixelart), get the code for this image and load this code it to SmartyKit (or emulator) memory using command:
```
1111: 3C 42 A5 81 A5 99 42 3C (Return)
FC00R (Return)
```

Here is an example of how it works in emulator:

[![Video to-do](https://j.gifs.com/2xjPxP.gif)](https://youtu.be/1KdQEKLvOHM)

And a screenshot:
![SmartyKit 8x8 Pixel Art online tool](https://raw.githubusercontent.com/smartykit/apple1/master/SmartyKit%20Pixel%20Art%20example.png)

## SmartyKit plates for breadboards

PCB version (black) and Wooden version (file for wood laser cutter: [download](https://github.com/smartykit/apple1/blob/01ea2ec54a94a7a31ee613f007602f0c08cb13ae/SmartyKit-Plate-for-breadboards(laser-cut).cdr?raw=true))

![SmartyKit Plates](https://raw.githubusercontent.com/smartykit/apple1/master/SmartyKit-plates.jpeg)


