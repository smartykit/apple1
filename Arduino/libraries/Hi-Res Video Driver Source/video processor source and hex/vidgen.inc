;******************************************************************************
; NTSC/PAL Video Generation Code (16MHZ System Clock)
;
;  Originally designed and written by Daryl Rictor (c)2003-2004
;
;  Modified by Grant Searle 2007-13
;     - Multi size fonts
;     - Now uses a single clock interrupt
;     - Supports 40 chars or 80 chars per line
;******************************************************************************

	push	acc
	push	accH
	push	ZL
	push	ZH
	push	J
	in		J,SREG
	push 	J

;Get exact sync with clock (remove jitter)
	lds      J, TCNT1L				  
	cpi     J, 0x14
	breq	clkSync0
	cpi     J, 0x15
	breq	clkSync1
	cpi     J, 0x16
	breq	clkSync2
	cpi     J, 0x17
	breq	clkSync3
	cpi     J, 0x18
	breq	clkSync4
	nop
	nop
	nop
clkSync0:	 
	nop
	nop
	nop
clkSync1:	 
	nop
	nop
	nop
clkSync2:	 
	nop
	nop
	nop
clkSync3:	 
	nop
	nop
	nop
clkSync4:

; Timer now always 0x24 at this point 
	cbi		portb, syncpin			; drop the csync pin

LINECHECK:
	cpi		vlineh, 0x00		
	brne	NOTFIRST256				

	cpi		vline, 0x04			
	brlo	VSYNC					; no, wait for hsync end
	rjmp	CHECKTOPBLANK

VSYNC:
	rjmp	EOL						; line 0 is a VSYNC line, we're done

CHECKTOPBLANK:
	cp		vline, line1
	brlo	TOPBLANK
	rjmp	CHECKFIRSTLINE

TOPBLANK:
	rjmp	BLANK					 

CHECKFIRSTLINE:
	cp		vline, line1
	brne	CHECKLASTLINE

FIRSTLINE:
	ldi		chrln, 0x00				; sync chrlin with first active line	
	rjmp	DISPLAY				

CHECKLASTLINE:
	cpi		chrln, 0xC8				; have we passed line 200?
	brlo	DISPLAY					; no, get ready for active display line
	rjmp	BLANK

NOTFIRST256:
	cpi		chrln, 0xC8				; have we passed line 200?
	brlo	DISPLAY					; no, get ready for active display line

	cp		vline, lastline			
	brne	BLANK					; no, wait for hsync end

	ldi		vlineh, 0x00			; yes, reset vert counters
	ldi		vline, 0x00				;
	cpi		cursorClk, 0xff			; 
	breq	vs1						;
	inc		cursorClk					; inc cursor clock
vs1:

BLANK:

	ldi		chrln, 0xFF				; reset pointer
	rjmp	WAITSYNCEND				; 

graphics:
	ori		ZH,0x28
	rjmp	WAITSYNCEND

DISPLAY:
	mov		J, chrln				; Get current display line
	lsr		J						; divide by 8 
	lsr		J						; 
	lsr		J						; J now contains the text line number (0..24)

	; get attribute definition for current line
	ldi		XL, 0xD0
	ldi		XH, 0x08				; set to start of attribute SRAM
	add		XL, J
	ld		currLineAtt,X

	; set the SRAM character pointer (X) to the start of the current line (chrln)
	ldi		XL, 0x50				; # chrs per line
	mul		XL, J					; multiply by chrs per line
	ldi		J, 0x01					; offset to start of display
	add		R1, J
	movw	XL, R0					; mov it to X reg

	; set Z to point to base of font row
	ldi		ZL, 0x00				; ZL=0, ASCII code will be added for each character
	mov 	ZH, chrln				; ZH= current display line 
	andi	ZH, 0x07				; do ZH MOD 8

	; If graphics then point to the graphics block font
	sbrc	currLineAtt,ATT_GRAPHICS
	rjmp	graphics

	; Check if single or double height to be drawn
	sbrc	currLineAtt,ATT_DBL_TOP
	lsr		ZH						; If double height top then linecounter incremented at half speed
	sbrc	currLineAtt,ATT_DBL_BOTTOM
	lsr		ZH						; If double height bottom then linecounter incremented at half speed
	sbrc	currLineAtt,ATT_DBL_BOTTOM
	ori		ZH,0x04					; Display bottom 4 lines if bottom of a double line

	; Check if bold or normal font
	sbrs	currLineAtt,ATT_BOLD
	ori		ZH,0x20					;0x20 (Normal) or 0x40 (Bold)
	sbrc	currLineAtt,ATT_BOLD
	ori		ZH,0x40					;0x20 (Normal) or 0x40 (Bold)

	; Check if 40 or 80 chars
	sbrs	currLineAtt,ATT_80_CHAR_PER_LINE
	ori		ZH, 0x10				; add $1000 for offset to start of wide font table

WAITSYNCEND:                        ;  else wait sync pulse end
	lds      J, TCNT1L				;  
	cpi     J, 0x5A	               
	brlo    WAITSYNCEND				; no, look again
; Get exact sync with clock (remove jitter)
	lds      J, TCNT1L				  
	cpi     J, 0x5C
	breq	syncEnd0
	cpi     J, 0x5D
	breq	syncEnd1
	cpi     J, 0x5E
	breq	syncEnd2
	cpi     J, 0x5F
	breq	syncEnd3
	cpi     J, 0x60
	breq	syncEnd4
	cpi     J, 0x61
	breq	syncEnd5
	cpi     J, 0x62
	breq	HSYNCEND
	nop
	nop
	nop
syncEnd0:	 
	nop
	nop
	nop
syncEnd1:	 
	nop
	nop
	nop
syncEnd2:	 
	nop
	nop
	nop
syncEnd3:	 
	nop
	nop
	nop
syncEnd4:	 
	nop
	nop
	nop
syncEnd5:
	nop
	nop
	nop
; Timer now always 0x72 at this point 
HSYNCEND:        
	sbi		portb, syncpin			; raise sync (approx 4.7uS hsync pulse)
	cpi		chrln, 0xFF				; are we on an active display line?
	brne	WAITVISIBLEPORTION		; yes, active display line
	rjmp	EOL						; no, blank line, we're done

WAITVISIBLEPORTION:        
	
	ldi		J,0
leftBlank:
	inc 	J
	cpi 	J,42
	brlo	leftBlank

	in		J,PORTC					; read current port C
	mov		temp1s,J				; store in temp
	andi	J, 0xF7					; Clear sh/ld bit
	mov		temp0s,J				; store in temp

	; Check if 40 or 80 chars per line to be drawn
	sbrs	currLineAtt,ATT_80_CHAR_PER_LINE
	rjmp	DRAWLINE40
	rjmp	DRAWLINE80

DRAWLINE80:
;
; each line consists of 80 macro calls, each 8 clocks long.  Here is the macro:
.macro DispChr
;
;  gets the font byte of the current character and outputs it to the shift register
;	
;  8 clocks

	ld 		ZL, X+				; 2   move curr chr in ZL
	lpm 	J, Z				; 3   get font byte for current chr on curr line
	out		PORTD, J			; 1
	out		PORTC, temp0s		; 1   lower load pin
	out		PORTC, temp1s	    ; 1   raise load pin
.endmacro

	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr


	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	DispChr							; display 1 chr
	jmp EndOfChars

DRAWLINE40:
	nop							; Exact sync with 80 char lines
;
; each line consists of 40 macro calls, each 16 clocks long.  Here is the macro:
.macro DispChrWide
;
;  gets the two font bytes of the current character and output them to the shift register
;	
;  16 clocks

	ld 		ZL, X+				; 2   move curr chr in ZL
	lpm 	J, Z				; 3   get left half font byte for current chr on curr line
	out		PORTD, J			; 1
	out		PORTC, temp0s		; 1   lower load pin
	out		PORTC, temp1s	    ; 1   raise load pin

	ori		ZH, 0x08			; 1   get next font page
	lpm 	J, Z				; 3   get right half font byte for current chr on curr line
	andi	ZH, 0xF7			; 1   get back to first font page
	out		PORTD, J			; 1
	out		PORTC, temp0s		; 1   lower load pin
	out		PORTC, temp1s	    ; 1   raise load pin

.endmacro

	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr
	DispChrWide					; display 1 wide chr

EndOfChars:
	inc		chrln					; inc line counter

EOL:								; end of line, we're done
	inc		vline					; inc vertical line counter
	brne	eol1
	inc		vlineh					;

eol1:
	pop		J
	out		SREG,J
	pop		J
	pop		ZH
	pop		ZL
	pop		accH
	pop		acc	

	reti						; all done, go back to main program

