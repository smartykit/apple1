# SmartyKit One Apple-1 compatible computer repo structure

SmartyKit One Apple-1 compatible computer's drivers and software (http://www.smartykit.io/):
* **Controllers drivers** – drivers for all used controllers (Video, Keyboard & Hi-Res Video)
    - *Keyboard driver* uses Arduino PS2KeyAdvanced library.
    - *Video driver* uses Arduino custom 2.8" TFT screen driver (based on Adafruit driver) and TV Terminal library.
    - *Hi-Res Video driver* uses library written by Grant Searle and Dave Curran
* **Garage ASCII art** – beautiful Steve Job's garage ASCII art by Adel Faure

* **ROM** – ROM chip firmwarwe source code (6502 assembler) & development configs (Makefile to build your own version of ROM using `ca65` 6502 assembler & config files to run the code in POM1 emulator)

* **POM1 software emulator** – Apple-1 software emulator by Verhille Arnaud to test SmartyKit ROM code before burning firmare 

![SmartyKit 1 assembly](https://github.com/smartykit/apple1/blob/master/SmartyKit-assembly.jpg?raw=true)

# Highlights

## SmartyKit One's loading splash screen ASCII art
Steve Job's garage ASCII art by Adel Faure
![Steve Job's Garage](https://github.com/smartykit/apple1/blob/master/Garage%20ASCII%20art/png/400x480_dark.png)

## SmartyKit One's ROM to run on POM1 Software Emulator 
POM 1 cross-platform emulator by Verhille Arnaud to test SmartyKit One ROM with software.

[![Video to-do](https://j.gifs.com/K1PNZr.gif)](https://youtu.be/rniZDdS6toI)

## SmartyKit One's ROM development console
Easy-to-use development tool to write your own software for SmartyKLit One (you need just run make in your Terminal) and learn how ROM is organized.

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

## SmartyKit One's 8x8 Pixel Art online tool for program at $FC00 in ROM (FC00R command)
You could draw your own pixel art using our online tool (https://smartykit.github.io/pixelart-project/), get the code for this image and load this code it to SmartyKit (or emulator) memory using command:
```
1111: 3C 42 A5 81 A5 99 42 3C (Return)
FC00R (Return)
```

## SmartyKit One's plates for breadboards

PCB version (black) and Wooden version (file for wood laser cutter: [download](https://github.com/smartykit/apple1/blob/01ea2ec54a94a7a31ee613f007602f0c08cb13ae/SmartyKit-Plate-for-breadboards(laser-cut).cdr?raw=true))

![SmartyKit Plates](https://raw.githubusercontent.com/smartykit/apple1/master/SmartyKit-plates.jpeg)


