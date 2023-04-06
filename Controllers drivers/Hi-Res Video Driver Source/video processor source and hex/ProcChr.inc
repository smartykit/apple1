;******************************************************
; ProcChr - decode host command and update display
;
; Original design by Daryl Rictor (c)2003-2004
;
; Major redesign by Grant Searle 2007-13
;    - Commands modified
;    - 40 char or 80 char support
;    - Multi fonts and sizes
;    - Medium resolution graphics
;    - Line attributes to define text/graphics and font
;******************************************************
processChar:
	rcall	setYfromRowCol

	; restore chr under cursor
	mov		temp,inpt
	mov		inpt,charUnderCursor
	rcall	putCharAtY
	mov		inpt,temp

	mov		J,cmdVal			; Was previous byte 1st char of a multi-byte command?
	cpi		J, 0x00
	brne	processCommandPart2
	mov		J, inpt
	; If delete char then jump
	cpi		J,0x7F
	brne	notDelete
	rjmp	delete
notDelete:
	; If control code then handle it
	cpi		J,0x20
	brlo	controlCode
	; Otherwise print the character
	rjmp	printableASCII
controlCode:
	ldi 	ZH, 0x08			; no, setup jump table page address
	mov		ZL, inpt			; put the input chr into Z
	ijmp						; jump table based on INPT


;---------------------------------------------------------------------------------------------------------------------------
processCommandPart2:
cmd1:
	mov		J,cmdVal			
	cpi		J, 0x0E				; set column
	brne	cmd2
	cpi		inpt, 0x50			; check column = 0-79
	brlo	setColumn
	rjmp	cmdComplete
setColumn:
	mov		column, inpt		; update hpos
	rcall	putCursorOnScreen	; put cursor back on screen if >39 on a 40 char line
	rcall	setYfromRowCol
	ld		charUnderCursor, Y	; save chr under cursor
	rjmp	cmdComplete

cmd2:
	cpi		J, 0x0F				; set row
	brne	cmd3
	cpi		inpt, 0x19			; check row = 0-24
	brlo	setRow
	rjmp	cmdComplete
setRow:
	mov		row, inpt			; save new vertical position
	rcall	getCurrentLineAtt	; set the current attribute to match the cursor line
	rcall	setLineAtt			; to ensure double-height lines are reset to top line at cursor
	rcall	setYfromRowCol
	ld		charUnderCursor, Y	; save chr under cursor
	rjmp	cmdComplete

cmd3:
	cpi		J, 0x1A				; Force Char Into RAM
	brne	cmd4
	rcall	printableASCII
	rjmp	cmdComplete

cmd4:
	cpi		J, 0x18				; Set font attribute
	brne	cmd5
	mov		activeLineAtt, inpt	; Set the attribute to use for all subsequent lines
	rcall	setLineAtt			; Set the attribute on the current line to match
	rcall	putCursorOnScreen	; put cursor back on screen if >39 on a 40 char line
	rjmp	cmdComplete

cmd5:
	cpi		J, 0x02				; Set cursor character
	brne	cmd6
	mov		cursorChar, inpt
	rjmp	cmdComplete

cmd6:
	cpi		J, 0x05				; Set pixel
	brne	cmd7
	mov		J,previousInpt
	cpi		J, 0xFF				; If previous input was FF then this is first param
	brne	setPixel			; otherwise this is second param so method can be called
	mov		previousInpt, inpt	; Store current input as the previous input value
	ret							; Just return, don't terminate command
		
cmd7:
	cpi		J, 0x06				; Reset pixel
	brne	cmdComplete
	mov		J,previousInpt
	cpi		J, 0xFF
	brne	resetPixel
	mov		previousInpt, inpt
	ret							; Just return, don't terminate command
	
cmdComplete:
	ldi		J,0x00
	mov		cmdVal, J
	ret

;---------------------------------------------------------------------------------------------------------------------------
resetPixel:
	ldi		J,0x00
	mov		temp,J
	rjmp	setOrResetPixel
setPixel:
	ldi		J,0x01
	mov		temp,J

setOrResetPixel:
	; Validate coordinates and exit if out of range
	mov		J,inpt			; Y=0..99
	cpi		J,100
	brsh	cmdComplete
	mov		J,previousInpt	; X=0..159
	cpi		J,160
	brsh	cmdComplete

	; inpt contains the Y coordinate, previousInpt contains X coordinate
	push	row
	push	column
	; Get the row of location that needs to be manipulated
	mov		J,inpt
	lsr		J
	lsr		J
	andi	J,0x1F
	mov		row,J

	; Get attribute location into Z
	ldi		ZH, 0x08
	ldi		ZL, 0xD0
	add		ZL, row

	; Get line attribute into J
	ld		J,Z

	; If already set then skip
	sbrc	J,ATT_GRAPHICS
	rjmp	graphicsLineSet

	; If not already graphics then set the attribute and clear the line
	ldi		column,0x00
	; Get the location for start of line
	rcall	setYfromRowCol

	ldi		J, 0x00
clrGraphics:
	st		Y+, J
	inc		column
	cpi		column, 0x50
	brne	clrGraphics			; clear to end of line

	; Force graphics property for the row
	ldi		J,0x00
	ori		J, 1<<ATT_GRAPHICS
	ori		J, 1<<ATT_80_CHAR_PER_LINE
	st		Z, J
graphicsLineSet:

	; Get column of byte to be changed
	mov		J,previousInpt
	lsr		J
	andi	J,0x7F
	mov		column,J

	mov		J,previousInpt		; X coord
	andi	J,0x01
	mov		K,J
	mov		J,inpt				; Y coord
	andi	J,0x03
	lsl		J
	or		K,J
	; K now contains the bit number that needs to be set (0..7)

	ldi		J,0x01
	cpi		K,0x00
	breq	setBitDone			; Bitmap already correct for bit number 0
setBit:
	lsl		J
	dec		K
	brne	setBit
	; J now contains the bitmap with bit J set
setBitDone:

	rcall	setYfromRowCol
	; Put the display byte in K
	ld		K,Y					; Retrieve the byte

	; if temp=1 then set the pixel
	sbrc	temp,0
	or		K,J					; Set the pixel

	; if temp=0 then reset the pixel
	sbrs	temp,0
	ldi		ZH,0xFF
	sbrs	temp,0
	eor		J,ZH
	sbrs	temp,0
	and		K,J

	st		Y,K					; Store the byte

	pop		column
	pop		row
	ldi		J, 0xFF
	mov		previousInpt, J		; reset value for next call
	rjmp	cmdComplete

;---------------------------------------------------------------------------------------------------------------------------
tab:
	ldi		inpt, 0x20			; convert tabs to spaces
	rcall	putCharAtY
	rcall	moveToNext
	mov		K, column			; tabs are fixed  0,8,16... (will wrap to next line if needed)	
	andi	K, 0x07				; colums 0-7 only
	brne	tab					; not to next tab, so do again
	ret

;---------------------------------------------------------------------------------------------------------------------------
delEndOfLine:
	ldi		inpt, 0x20
    mov		temp2,YL
	mov		temp3,YH
	mov		temp,column
deleol1:
	rcall	putCharAtY
	adiw	Y,0x01
	inc		column
	cpi		column, 0x50
	brne	deleol1				; clear to end of line
	mov		column,temp
	mov		YH,temp3
	mov		YL,temp2
	ld		charUnderCursor, Y	; save chr under cursor
	ret

;---------------------------------------------------------------------------------------------------------------------------
delStartOfLine:
	ldi		inpt, 0x20
    mov		temp2,YL
	mov		temp3,YH
	mov		temp,column
	rcall	setYfromRowCol
delsol1:
	rcall	putCharAtY
	sbiw	YL, 0x01
	dec		column
	cpi		column, 0x00
	brne	delsol1				; clear to start of line
	mov		column,temp
	mov		YH,temp3
	mov		YL,temp2
	ld		charUnderCursor, Y	; save chr under cursor
	ret

;---------------------------------------------------------------------------------------------------------------------------
delStartOfScreen:
	ldi		inpt, 0x20
    mov		temp2,YL
	mov		temp3,YH
delsos1:
	rcall	putCharAtY
	sbiw	YL,0x01
	cpi		YH, 0x01
	brne	delsos1
	cpi		YL, 0x00
	brne	delsos1
	mov		YH,temp3
	mov		YL,temp2
	ld		charUnderCursor, Y
	ret

;---------------------------------------------------------------------------------------------------------------------------
delEndOfScreen:
	ldi		inpt, 0x20
    mov		temp2,YL
	mov		temp3,YH
deleos1:
	st		Y+, inpt
	cpi		YH, 0x08
	brne	deleos1
	cpi		YL, 0xD0
	brne	deleos1
	mov		YH,temp3
	mov		YL,temp2
	ld		charUnderCursor, Y
	ret

;---------------------------------------------------------------------------------------------------------------------------
setLineAtt:
	; Get attribute location into Z
	ldi		ZH, 0x08
	ldi		ZL, 0xD0
	add		ZL, row

	ldi		J, 0x00
	sbrc	activeLineAtt,ATT_GRAPHICS
	rjmp	setGraphicsAtts

	sbrc	activeLineAtt,ATT_80_CHAR_PER_LINE
	ori		J, 1<<ATT_80_CHAR_PER_LINE
	sbrc	activeLineAtt,ATT_BOLD
	ori		J, 1<<ATT_BOLD

	; If double-height then set the double top and double bottom attributes
	sbrc	activeLineAtt,ATT_DBL_HEIGHT
	rjmp	setDoubleLineAtts

	st		Z, J
	ret

setDoubleLineAtts:
	; If at row 25 then scroll up first otherwise it won't fit
	mov		temp,J
	cpi		row,0x18
	brne	notAtLastLine
	rcall	singleScrollUp
	dec		row
	rcall	setYfromRowCol
	; reset attribute location
	ldi		ZH, 0x08
	ldi		ZL, 0xD0
	add		ZL, row
	mov		J,temp
		
notAtLastLine:
	; Set first double line attribute	
	ori		J, 1<<ATT_DBL_TOP			; Set double top bit
	st		Z+, J
	; Set second double line attribute	
	andi	J, 0xFF - (1<<ATT_DBL_TOP)	; Clear double top bit
	ori		J, 1<<ATT_DBL_BOTTOM		; Set double bottom bit
	st		Z, J
	ret

setGraphicsAtts:
	; Override any other attribute property if graphics
	ori		J, 1<<ATT_GRAPHICS
	ori		J, 1<<ATT_80_CHAR_PER_LINE
	st		Z, J
	ret

;---------------------------------------------------------------------------------------------------------------------------
getRawCurrentLineAtt:
	; Get attribute location into Z
	ldi		ZH, 0x08
	ldi		ZL, 0xD0
	add		ZL, row
	; Get line attribute into J
	ld		J,Z
	ret

;---------------------------------------------------------------------------------------------------------------------------
getCurrentLineAtt:
	; Get attribute location into Z
	ldi		ZH, 0x08
	ldi		ZL, 0xD0
	add		ZL, row
	; Get line attribute into J
	ld		J,Z

	; Map the line attribute into cursor line attribute
	ldi		K, 0x00
	sbrc	J,ATT_GRAPHICS
	rjmp	getGraphicsAtts

	sbrc	J,ATT_80_CHAR_PER_LINE
	ori		K, 1<<ATT_80_CHAR_PER_LINE
	sbrc	J,ATT_BOLD
	ori		K, 1<<ATT_BOLD
	sbrc	J,ATT_DBL_TOP
	ori		K, 1<<ATT_DBL_HEIGHT
	sbrc	J,ATT_DBL_BOTTOM
	ori		K, 1<<ATT_DBL_HEIGHT
	mov		activeLineAtt,K
	ret

getGraphicsAtts:
	; Override any other attribute property if graphics
	ori		K, 1<<ATT_GRAPHICS
	ori		K, 1<<ATT_80_CHAR_PER_LINE
	mov		activeLineAtt,K
	ret

;---------------------------------------------------------------------------------------------------------------------------
printableASCII:
	rcall	putCharAtY
	rcall	moveToNext
;	rcall	cleanUpDisplay
	ret

;---------------------------------------------------------------------------------------------------------------------------
setYfromRowCol:
	ldi		YL, 0x50			; # chrs per line
	ldi		YH, 0x01			; offset to start of display 
	mul		YL, row				; multiply by chrs per line
	ldi		K, 0x00				; need a zero for upper byte addition
	add		R1, YH				; add display start offset to result
	movw	YL, R0				; mov it back to Y reg
	add		YL, column			; add in column
	adc		YH, K				; add the carry bit
	ret

;---------------------------------------------------------------------------------------------------------------------------
putCharAtY:
	st		Y, inpt				; store chr

	sbrs	activeLineAtt,ATT_DBL_HEIGHT
	ret
	; If double height then store char on next line as well if not past end of screen
	cpi		row,0x18			; Check if on last line (24)
	breq	putEnd
	adiw	YL, 0x20			; Get to next line
	adiw	YL, 0x30
	st		Y, inpt				; store chr
	sbiw	YL, 0x20			; Get back to original line
	sbiw	YL, 0x30
putEnd:
	ret

;---------------------------------------------------------------------------------------------------------------------------
moveToNext:
	adiw	YL,0x01
	inc		column				; inc hpos
wrap:
	sbrs	activeLineAtt,ATT_80_CHAR_PER_LINE
	rjmp	wrap40
	cpi		column, 0x50		; past column 80?
	brne	wrapExit			; no, continue
	rjmp	wrap0
wrap40:
	cpi		column, 0x28		; past column 40?
	brne	wrapExit			; no, continue

wrap0:
	ldi		column, 0x00		; back to start of line
	sbrc	activeLineAtt,ATT_DBL_HEIGHT
	rjmp	doubleWrap

normalWrap:
	inc		row					; next line
	cpi		row, 0x19			; is it below last line (25)?
	brlo	wrapExit			; no, do cursor and exit
	dec		row					; Screen is moving up a line, so move the current row pointer up one
	ldi		column, 0x00		; column back to zero
	rcall	singleScrollUp
	rjmp	wrapExit

doubleWrap:
	inc		row					; next line
	inc		row					; inc again (two lines per char)
	cpi		row, 0x18			; is it below last line (23)?
	brlo	wrapExit			; no, do cursor and exit
	dec		row					; Screen is moving up two lines, so move the current row pointer up two
	dec		row
	ldi		column, 0x00		; column back to zero
	rcall	doubleScrollUp	

wrapExit:
	rcall	setLineAtt			; Set the attribute for the cursor line
	rcall	setYfromRowCol
	ld		charUnderCursor, Y	; save chr under cursor
	ret

;---------------------------------------------------------------------------------------------------------------------------
return: 
	ldi		column, 0x00		; column back to zero
	rcall	setYfromRowCol
	ld		charUnderCursor, Y	; save chr under cursor
	ret							; return to Main

;---------------------------------------------------------------------------------------------------------------------------
linefeed:
	sbrc	activeLineAtt,ATT_DBL_HEIGHT
	rjmp	doubleLinefeed
	rjmp	singleLinefeed

singleLinefeed:
	cpi		row, 0x18			; are we at line 24 (for normal height)?
	brlo	noSingleScroll
	rcall	singleScrollUp		; yes, need to scroll up one line
	rcall	setLineAtt			; Set the attribute for the cursor line
	ld		charUnderCursor, Y	; save chr under cursor
;	rcall	cleanUpDisplay
	ret
noSingleScroll:
	inc		row					; No scroll so move current line pointer down one
	rcall	setYfromRowCol
	rcall	setLineAtt			; Set the attribute for the cursor line
	ld		charUnderCursor, Y	; save chr under cursor
;	rcall	cleanUpDisplay
	ret

doubleLinefeed:
	cpi		row, 0x16			; are we at line 22 (for double height)?
	brlo	noDoubleScroll
	rcall	doubleScrollUp		; yes, need to scroll up two lines
	rcall	setLineAtt			; Set the attribute for the cursor line
	ld		charUnderCursor, Y	; save chr under cursor
;	rcall	cleanUpDisplay
	ret
noDoubleScroll:
	inc		row					; No scroll so move current line pointer down two
	inc		row
	rcall	setYfromRowCol
	rcall	setLineAtt			; Set the attribute for the cursor line
	ld		charUnderCursor, Y	; save chr under cursor
;	rcall	cleanUpDisplay
	ret

;---------------------------------------------------------------------------------------------------------------------------
delete:
	ldi		inpt, 0x20			; space
	rcall	putCharAtY			; save to SRAM
	mov		charUnderCursor, inpt	; save chr under cursor (space)
	ret							; return to Main

;---------------------------------------------------------------------------------------------------------------------------
backspace:
	cpi		column, 0x00		; are we already at the left edge?
	brne	bs1					; no, move left one chr
	cpi		row, 0x00			; are we already on the top line?
	brne	bsToPrevLine		; no, so go up a line
	ret
bsToPrevLine:
	dec		row
	call	getRawCurrentLineAtt; Unconverted, into J
	sbrc	J,ATT_DBL_BOTTOM	; If now at the bottom of a double line, go up again
	dec		row

	rcall	getCurrentLineAtt	; set the current attribute to match the cursor line
	ldi		column,0x4F			; set column to end of an 80 column line
	rcall	putCursorOnScreen	; adjust if now on a 40 column line
	rjmp	bs2

bs1:	
	dec		column				; move cursor left one chr
bs2:
	ldi		inpt, 0x20			; space
	rcall	setYfromRowCol
	rcall	putCharAtY
	mov		charUnderCursor, inpt	; save chr under cursor (space)
	ret							; return to Main

;---------------------------------------------------------------------------------------------------------------------------
putCursorOnScreen:
	; If moving from an 80 col line to a 40 col line, the
	; column number has now exceeded the line width
	; reset it to the end of the line
	sbrc	activeLineAtt,ATT_80_CHAR_PER_LINE	; if on an 80 col line then nothing to do
	ret

	; On a 40 char line...
	cpi		column, 0x28		; if less that column 40 then nothing to do
	brlo	endOfPutCursor

	ldi		column,0x27			; Set column to be 39
	rcall	setYfromRowCol
	rcall	putCharAtY
	mov		charUnderCursor, inpt	; save chr under cursor (space)
endOfPutCursor:
	ret

;---------------------------------------------------------------------------------------------------------------------------
clrScr:							; Clear the Screen

	; Reset all line atts
	ldi		ZL,25
	ldi		YL, 0xD0
	ldi		YH, 0x08
	mov		J,activeLineAtt
clrAtt:
	st		Y+,J
	dec		ZL
	brne	clrAtt

	ldi		row, 0x00			
	rcall	setLineAtt			; Set the attribute for the top line to be current

	ldi		ZL, 0x00
	ldi		ZH, 0x01			; set to start of display RAM
	ldi		YL, 0xD0
	ldi		YH,	0x07			; set Y to 2000
	ldi		inpt, 0x20			; " " space chracter
clsloop:
	st 		Z+, inpt			; save to SRAM			
	sbiw	YL, 0x01			; dec Y
	brne	clsloop				; do until Y=0
cursorHome:						; move cursor to Home w/o clear
	ldi		column, 0x00		; set cursor to top left pos
	ldi		row, 0x00			
	rcall	setYfromRowCol
	ld		charUnderCursor, Y	; save chr under cursor
	rcall	getCurrentLineAtt	; set the current attribute to match the cursor line
;	rcall	cleanUpDisplay
	ret							; return to Main

;---------------------------------------------------------------------------------------------------------------------------
scrollUp:
	sbrc	activeLineAtt,ATT_DBL_HEIGHT
	rcall	doubleScrollUp
	sbrs	activeLineAtt,ATT_DBL_HEIGHT
	rcall	singleScrollUp

	rcall	getCurrentLineAtt
	rcall   putCursorOnScreen	; if cursor is now past the end of a 40 char line then move it back on screen
	ld		charUnderCursor, Y	; save chr under cursor
;	rcall	cleanUpDisplay
	ret

singleScrollUp:
    mov		temp2,YL
	mov		temp3,YH
	ldi		YL, 0x00			; start of first line
	ldi		YH, 0x01			; 
	ldi		ZL, 0x50			; start of second line		
	ldi		ZH, 0x01			; 
scup1:
	ld		inpt, Z+			; get line 2 
	st		Y+, inpt			; place in line 1
	cpi		ZL, 0xD0
	brne	scup1
	cpi		ZH, 0x08			; at the end of disp RAM?
	brne	scup1				; no, do again
	ldi		inpt, 0x20			; space
scup2:
	st		Y+, inpt			; fill last line with spaces
	cpi		YL, 0xD0
	brne	scup2

	; Scroll the attributes up
	ldi		ZL,24
	ldi		YL, 0xD1			; start of attributes +1
	ldi		YH, 0x08
scrollAttsUp:
	ld		J,Y
	sbiw	Y, 0x01
	st		Y,J
	adiw	Y, 0x02
	dec		ZL
	brne	scrollAttsUp

	mov		YH,temp3
	mov		YL,temp2

	ret

doubleScrollUp:
    mov		temp2,YL
	mov		temp3,YH
	ldi		YL, 0x00			; start of first line
	ldi		YH, 0x01			; 
	ldi		ZL, 0xA0			; start of third line		
	ldi		ZH, 0x01			; 
dscup1:
	ld		inpt, Z+			; get line 3 
	st		Y+, inpt			; place in line 1
	cpi		ZL, 0xD0
	brne	dscup1
	cpi		ZH, 0x08			; at the end of disp RAM?
	brne	dscup1				; no, do again
	ldi		inpt, 0x20			; space
dscup2:
	st		Y+, inpt			; fill last two lines with spaces
	cpi		YL, 0xD0
	brne	dscup2

	; Scroll the attributes up two
	ldi		ZL,23
	ldi		YL, 0xD2			; start of attributes +2
	ldi		YH, 0x08
dscrollAttsUp:
	ld		J,Y
	sbiw	Y, 0x02
	st		Y,J
	adiw	Y, 0x03
	dec		ZL
	brne	dscrollAttsUp

	mov		YH,temp3
	mov		YL,temp2
	ret

;---------------------------------------------------------------------------------------------------------------------------
scrollDown:
	sbrc	activeLineAtt,ATT_DBL_HEIGHT
	rcall	doubleScrollDown
	sbrs	activeLineAtt,ATT_DBL_HEIGHT
	rcall	singleScrollDown

	rcall	getCurrentLineAtt
	rcall   putCursorOnScreen	; if cursor is now past the end of a 40 char line then move it back on screen

	ld		charUnderCursor, Y	; save chr under cursor
;	rcall	cleanUpDisplay
	ret

singleScrollDown:
    mov		temp2,YL
	mov		temp3,YH
	ldi		YL, 0x80			; end of line 24
	ldi		YH, 0x08			; 
	ldi		ZL, 0xD0			; end of line 25	
	ldi		ZH, 0x08			; 
scdn1:
	ld		inpt, -Y			; get line 25 
	st		-Z, inpt			; place in line 24
	cpi		YL, 0x00
	brne	scdn1
	cpi		YH, 0x01			; at the end of disp RAM?
	brne	scdn1				; no, do again
	ldi		inpt, 0x20			; space
scdn2:
	st		-Z, inpt			; fill first line with spaces
	cpi		ZL, 0x00
	brne	scdn2
	cpi		ZH, 0x01			; at the start of disp RAM?
	brne	scdn2				; no, do again

	; Scroll the attributes down
	ldi		ZL,24
	ldi		YL, 0xE7			; end of attributes -1
	ldi		YH, 0x08
scrollAttsDn:
	ld		J,Y+
	st		Y,J
	sbiw	Y, 0x02
	dec		ZL
	brne	scrollAttsDn

	mov		YH,temp3
	mov		YL,temp2
	ret

doubleScrollDown:
    mov		temp2,YL
	mov		temp3,YH
	ldi		YL, 0x30			; end of line 23 + 1
	ldi		YH, 0x08			; 
	ldi		ZL, 0xD0			; end of line 25 + 1
	ldi		ZH, 0x08			; 
dscdn1:
	ld		inpt, -Y			; get line 25
	st		-Z, inpt			; place in line 23
	cpi		YL, 0x00
	brne	dscdn1
	cpi		YH, 0x01			; at the end of disp RAM?
	brne	dscdn1				; no, do again
	ldi		inpt, 0x20			; space
dscdn2:
	st		-Z, inpt			; fill first two lines with spaces
	cpi		ZL, 0x00
	brne	dscdn2
	cpi		ZH, 0x01			; at the start of disp RAM?
	brne	dscdn2				; no, do again

	; Scroll the attributes down two lines
	ldi		ZL,23
	ldi		YL, 0xE6			; end of attributes -2
	ldi		YH, 0x08
dscrollAttsDn:
	ld		J,Y
	adiw	Y, 0x2
	st		Y,J
	sbiw	Y, 0x03
	dec		ZL
	brne	dscrollAttsDn

	mov		YH,temp3
	mov		YL,temp2
	ret

;---------------------------------------------------------------------------------------------------------------------------
scrollLeft:
    mov		temp2,YL
	mov		temp3,YH
	ldi		YL, 0x00			; start of first col
	ldi		YH, 0x01			; 
	ldi		ZL, 0x01			; start of second col		
	ldi		ZH, 0x01			; 
sclf1:
	ld		inpt, Z+			; get col 2 
	st		Y+, inpt			; place in col 1
	cpi		ZL, 0xD0
	brne	sclf1
	cpi		ZH, 0x08			; at the end of disp RAM?
	brne	sclf1				; no, do again
	ldi		inpt, 0x20			; space
sclf2:
	st		Y, inpt				; fill last line with spaces
	sbiw	YL, 0x30			
	sbiw	YL, 0x20			
	cpi		YL, 0xFF			
	brne	sclf2				
	cpi		YH, 0x00			; at the end of display RAM?
	brne	sclf2				; no, do again
	mov		YH,temp3
	mov		YL,temp2
	ld		charUnderCursor, Y	; save chr under cursor
	ret

;---------------------------------------------------------------------------------------------------------------------------
scrollRight:
    mov		temp2,YL
	mov		temp3,YH
	ldi		YL, 0xCF			; end char
	ldi		YH, 0x08			; 
	ldi		ZL, 0xD0			; end char +1	
	ldi		ZH, 0x08			; 
scrt1:
	ld		inpt, -Y			; get line 2 
	st		-Z, inpt			; place in line 1
	cpi		YL, 0x00
	brne	scrt1
	cpi		YH, 0x01			; at the start of display RAM?
	brne	scrt1				; no, do again
	ldi		inpt, 0x20			; space
scrt2:
	st		Y, inpt				; fill left column with spaces
	adiw	YL, 0x30			 
	adiw	YL, 0x20			 
	cpi		YL, 0xD0
	brne	scrt2
	cpi		YH, 0x08			; at the end of disp RAM?
	brne	scrt2				; no, do again
	mov		YH,temp3
	mov		YL,temp2
	ld		charUnderCursor, Y	; save chr under cursor
	ret

;---------------------------------------------------------------------------------------------------------------------------
cursorBlink:
	ldi		cursorClk, 0x00
	ret

;---------------------------------------------------------------------------------------------------------------------------
cursorSolid:
	ldi		cursorClk, 0xff
	ret

;---------------------------------------------------------------------------------------------------------------------------
cursorUp:
	cpi		row, 0x00
	breq	Null				; already at top, nothing to do
	dec		row

	rcall	getCurrentLineAtt
	rcall	getRawCurrentLineAtt; Unconverted, into J
	sbrc	J,ATT_DBL_BOTTOM	; If now at the bottom of a double line, go up again (if not at top of screen)
	rjmp	cursorUp

	rcall	setYfromRowCol
	ld		charUnderCursor, Y	; save chr under cursor
	ret

;---------------------------------------------------------------------------------------------------------------------------
cursorDown:
	cpi		row, 0x18
	breq	Null				; already at bottom, nothing to do
	inc		row
	
	rcall	getCurrentLineAtt
	rcall	getRawCurrentLineAtt; Unconverted, into J
	sbrc	J,ATT_DBL_BOTTOM	; If now at the bottom of a double line, go down again (if not at end of screen)
	rjmp	cursorDown

	rcall	setYfromRowCol
	ld		charUnderCursor, Y	; save chr under cursor
	ret

;---------------------------------------------------------------------------------------------------------------------------
cursorLeft:
	cpi		column, 0x00
	breq	Null
	dec		column
	rcall	setYfromRowCol
	ld		charUnderCursor, Y	; save chr under cursor
	ret

;---------------------------------------------------------------------------------------------------------------------------
cursorRight:
	call	getCurrentLineAtt
	sbrc	activeLineAtt,ATT_80_CHAR_PER_LINE ; 0 = 40 cols, 1=80 cols
	cpi		column, 0x4F		; 79
	sbrs	activeLineAtt,ATT_80_CHAR_PER_LINE
	cpi		column, 0x27		; 39
	breq	Null				; already at right, nothing to do
	inc		column				;
	rcall	setYfromRowCol
	ld		charUnderCursor, Y	; save chr under cursor
	ret

;---------------------------------------------------------------------------------------------------------------------------
cleanUpDisplay:

	; IMPROVEMENTS TO DO - NOT USED AT THE MOMENT

	; If current att is double
	;    If cursor has been repositioned to the bottom line of a double then
	;       Set the first of the double lines to non-double
	;    If the current line is not double then
	;       Set the following line to be the bottom of a double
	;       Copy this line to the next to display the double properly (overwriting the line below)

	; If current att is normal
	;    If cursor has been repositioned to the top line of a double then
	;       Set the next line to non-double
	;    If cursor has been repositioned to the bottom line of a double then
	;       Set the previous line to non-double


	ldi		ZL,24
	ldi		YL, 0xD0			; start of attributes
	ldi		YH, 0x08
cleanFirstLine:
	; If first line is the bottom of a double-height char then turn off the double-height
	; so that it is fully visible again
	ld		J,Y
	sbrc	J,ATT_DBL_BOTTOM
	rjmp	firstNotDblBottom
	andi	J,0xFF - (1<<ATT_DBL_BOTTOM)
	st		Y,J
firstNotDblBottom:

cleanLastLine:
	; If last line is the top of a double-height char then turn off the double-height
	; so that it is fully visible again
	ldi		YL, 0xE8			; end of attributes
	ld		J,Y
	sbrc	J,ATT_DBL_TOP
	rjmp	lastNotDblTop
	andi	J,0xFF - (1<<ATT_DBL_TOP)
	st		Y,J
lastNotDblTop:

;cleanUp1:
;	ld		J,Y
;	adiw	YL, 0x01
;	dec		ZL
;	brne	cleanUp1

	rcall	getCurrentLineAtt
	rcall   putCursorOnScreen	; if cursor is now past the end of a 40 char line then move it back on screen
	rcall	setYfromRowCol
	ld		charUnderCursor, Y	; save chr under cursor
	ret

;---------------------------------------------------------------------------------------------------------------------------
multiByteCommand:
	mov 	cmdVal,inpt			; Store the command ready for the second byte. Process once 2nd byte received
	ret

;---------------------------------------------------------------------------------------------------------------------------
NULL:
	ret

;---------------------------------------------------------------------------------------------------------------------------
.cseg
.org 0x800
;
; jump table for control codes 00 - 1F
;
	rjmp	null				; 00 [SPARE]
	rjmp	cursorHome			; 01 Ctrl-A Standard ASCII
	rjmp	multiByteCommand	; 02 Ctrl-B define cursor character (next byte = cursor [char 0 = off])
	rjmp	cursorBlink			; 03 Ctrl-C cursor blinking
	rjmp	cursorSolid			; 04 Ctrl-D cursor solid
	rjmp	multiByteCommand	; 05 Ctrl-E Set pixel (next two bytes = x,y)
	rjmp	multiByteCommand	; 06 Ctrl-F Reset pixel (next two bytes = x,y)
	rjmp	null				; 07 Ctrl-G [SPARE]
	rjmp	backspace			; 08 Ctrl-H Standard ASCII
	rjmp	tab					; 09 Ctrl-I Standard ASCII
	rjmp	linefeed			; 0A Ctrl-J Standard ASCII
	rjmp	null				; 0B Ctrl-K [SPARE]
	rjmp	clrScr				; 0C Ctrl-L Standard ASCII
	rjmp	return				; 0D Ctrl-M Standard ASCII
	rjmp	multiByteCommand	; 0E Ctrl-N SetColumn command (next byte = col number)
	rjmp	multiByteCommand	; 0F Ctrl-O SetRow command (next byte = row number)
	rjmp	delStartOfLine		; 10 Ctrl-P Delete to start of line
	rjmp	delEndOfLine		; 11 Ctrl-Q Delete to end of line
	rjmp	delStartOfScreen	; 12 Ctrl-R Delete to start of screen
	rjmp	delEndOfScreen		; 13 Ctrl-S Delete to end of screen
	rjmp	scrollUp			; 14 Ctrl-T Scroll the complete screen up one text line
	rjmp	scrollDown			; 15 Ctrl-U Scroll the complete screen down one text line
	rjmp	scrollLeft			; 16 Ctrl-V Scroll the complete screen left
	rjmp	scrollRight			; 17 Ctrl-W Scroll the complete screen right
	rjmp	multiByteCommand	; 18 Ctrl-X Set font attribute
	rjmp	null				; 19 Ctrl-Y [SPARE]
	rjmp	multiByteCommand	; 1A Ctrl-Z Force next byte into RAM (for 00 to 1F chars)
	rjmp	null				; 1B Don't use - reserved for ANSI ESC
	rjmp	cursorRight			; 1C
	rjmp	cursorLeft			; 1D
	rjmp	cursorUp			; 1E
	rjmp	cursorDown			; 1F
