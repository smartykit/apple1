          .setcpu "6502"
          .feature c_comments
          .segment "PICTURE"
          .byte          %00000000    
          .byte          %01100110
          .byte          %11111111
          .byte          %11111111
          .byte          %11111111
          .byte          %01111110
          .byte          %00111100
          .byte          %00011000
          .byte 00         
          .byte 00
Smiley:   .byte $3c, $42, $a5, $81, $a5, $99, $42, $3c
Woz:      .byte $88, $a8, $50, $07, $61, $92, $94, $67
        ;  .byte "8*8 Pixel Art picture end", $0d, $00

          .code
loop:     lda #$12
          jmp loop

          .segment "C000"
          nop
          .segment "E000"
          JSR COPY_HEART
          JMP $FC00
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


