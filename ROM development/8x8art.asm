;printing 8x8 picture in the center with '*'
PIC_WIDTH = 8
PIC_HEIGHT = 8
OFFSET_X = (40 - PIC_WIDTH)/2
PIC_ADDRESS = $1111
ROW_ADDRESS = PIC_ADDRESS + PIC_HEIGHT


; Y - row number
; X - column (pixel) number 
				JSR NEXT_ROW
				LDA #$0
				STA ROW_ADDRESS	;initialize row counter with 0
				LDY #PIC_HEIGHT

ROWS_LOOP:		JSR PRINT_OFFSET
				LDA ROW_ADDRESS
				TAX
				LDA PIC_ADDRESS, X
				LDX #PIC_WIDTH
NEXT_PIXEL:		ASL
				BCC NO_PIXEL
				JSR PRINT_STAR
				JMP AFTER_PIXEL
NO_PIXEL:		JSR PRINT_BLANK
AFTER_PIXEL:	DEX
				BNE NEXT_PIXEL
				JSR NEXT_ROW
				INC ROW_ADDRESS
				DEY
				BNE ROWS_LOOP
				JSR NEXT_ROW
				JMP RESET

;printing offset subroutine (optional: save registers A and X)
PRINT_OFFSET:	PHA ;save A
				TXA ;X->A
				PHA	;save X
				LDX #OFFSET_X
OFFSET_LOOP:	LDA #' '
				JSR ECHO
			    DEX
			    BNE OFFSET_LOOP 

			    PLA ;restore X
			    TAX ;A->X
			    PLA	;restore A
			    RTS

PRINT_STAR:		PHA
				LDA #'*'
				JSR ECHO
				PLA
				RTS
PRINT_BLANK:	PHA
				LDA #' '
				JSR ECHO
				PLA
				RTS
NEXT_ROW:		PHA
				LDA #$0d
				JSR ECHO
				PLA
				RTS
;from HeartPicture
;to PIC_ADDRESS
COPY_HEART:		PHA
				TXA
				PHA

				LDX #PIC_HEIGHT
COPY_LOOP:		LDA HeartPicture, X
				STA PIC_ADDRESS, X
				DEX
				BPL COPY_LOOP

				PLA
				TAX
				PLA
				RTS


HeartPicture:
          .byte          %00000000    
          .byte          %01100110
          .byte          %11111111
          .byte          %11111111
          .byte          %11111111
          .byte          %01111110
          .byte          %00111100
          .byte          %00011000
SmileyPicture:   .byte $3c, $42, $a5, $81, $a5, $99, $42, $3c
WozPicture:      .byte $88, $a8, $50, $07, $61, $92, $94, $67
SmartyLogo:		 .byte $ff, $81, $bd, $bd, $bd, $bd, $81, $ff
RocketPicture:	 .byte $18, $24, $24, $24, $7e, $a5, $FF, $a5
	.byte "8*8 Pixel Art program end", $0d, $00