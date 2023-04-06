          .feature c_comments
/*  SmartyKit 1 - ROM source
 *  http://www.smartykit.io/ 
 *  Copyright (C) 2020, Sergey Panarin <sergey@smartykit.io>
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

          .setcpu "6502"
          .segment "PICTURE"
Woz:      .byte $88, $a8, $50, $07, $61, $92, $94, $67
        ;  .byte "8*8 Pixel Art picture end", $0d, $00

          .code
          nop
          .segment "C000"
          nop
          .segment "E000"
          nop
          .segment "F000"
          ;Woz face
          .include "Apple30th_Woz.asm"

          .segment "F800"
          ;Test from Apple-1 Operation Manual – printing all ASCII symbols in a loop
          .include "TestFromManual.asm"

          .segment "FA00"
          ;Power-On Self Test (POST)
          .include "POST.asm"

           .segment "FC00"
          ;printing 8x8 picture in the center with '*'
          .include "8x8art.asm"

          .segment "FD00"
          ;Printing 'Hello, World!' 
          .include "HelloWorld.asm"

          .segment "FF00"
          .include "Woz_Monitor.asm"

          .segment "VECTORS"
          ; Interrupt Vectors
          .WORD NMI            ; NMI
          .WORD POST_START     ; RESET (starting point in Woz Monitor) or POST (test)
          .WORD IRQ            ; BRK/IRQ


