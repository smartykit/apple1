;/**********************************************************************************/
;/  NTSC/PAL Video Display (40/80 character x 25 line monochrome text/graphics)		/
;/																					/
;/  Original 40x25 text designed and written by Daryl Rictor (c)2003-2004			/
;/																					/
;/  Modified by Grant Searle 2007-2013												/
;/      - 80x25 or 40x25 display                                                    /
;/      - Handshaking/data transfer rewritten										/
;/      - 8bit and 4bit and I2C interface (with help from Dave Curran)				/
;/**********************************************************************************/

; include program specific definitions and macros
.include  "defs.inc"

;---------------------------------------------------------------------------------------------------------------------------
; Standard ATmega328 jump vectors

 jmp RESET ; Reset Handler
 jmp EXT_INT0 ; IRQ0 Handler
 jmp EXT_INT1 ; IRQ1 Handler
 jmp PC_INT0 ; PCINT0 Handler
 jmp PC_INT1 ; PCINT1 Handler
 jmp PC_INT2 ; PCINT2 Handler
 jmp WDT ; Watchdog Timer Handler
 jmp TIM2_COMPA ; Timer2 Compare A Handler
 jmp TIM2_COMPB ; Timer2 Compare B Handler
 jmp TIM2_OVF ; Timer2 Overflow Handler
 jmp TIM1_CAPT ; Timer1 Capture Handler
 jmp TIM1_COMPA ; Timer1 Compare A Handler
 jmp TIM1_COMPB ; Timer1 Compare B Handler
 jmp TIM1_OVF ; Timer1 Overflow Handler
 jmp TIM0_COMPA ; Timer0 Compare A Handler
 jmp TIM0_COMPB ; Timer0 Compare B Handler
 jmp TIM0_OVF ; Timer0 Overflow Handler
 jmp SPI_STC ; SPI Transfer Complete Handler
 jmp USART_RXC ; USART, RX Complete Handler
 jmp USART_UDRE ; USART, UDR Empty Handler
 jmp USART_TXC ; USART, TX Complete Handler
 jmp ADCC ; ADC Conversion Complete Handler
 jmp EE_RDY ; EEPROM Ready Handler
 jmp ANA_COMP ; Analog Comparator Handler
 jmp TWI ; 2-wire Serial Interface Handler
 jmp SPM_RDY ; Store Program Memory Ready Handler
	
;---------------------------------------------------------------------------------------------------------------------------
; unused vectors point to software reset code
 EXT_INT0:
 EXT_INT1:
 PC_INT0:
 PC_INT1:
 PC_INT2:
 WDT:
 TIM2_COMPA:
 TIM2_COMPB:
 TIM2_OVF:
 TIM1_CAPT:
 ;TIM1_COMPA: //used elsewhere
 TIM1_COMPB:
 TIM1_OVF:
 TIM0_COMPA:
 TIM0_COMPB:
 TIM0_OVF:
 SPI_STC:
 USART_RXC:
 USART_UDRE:
 USART_TXC:
 ADCC:
 EE_RDY:
 ANA_COMP:
 TWI:
 SPM_RDY:

;---------------------------------------------------------------------------------------------------------------------------
; Program start

RESET:							
	CLI							; disable interupts

; Initialize the I/O Ports
	LDI		J, 0xFF				
	out		PORTB, J			; enable pullups
	out		PORTC, J			; enable pullups
	out		PORTD, J			; enable pullups

	LDI		J, 0x00				; pins 0 - 7 of port D
	out		DDRD, J				; set PORTD pins to inputs TEMPORARILY to read config bits

	LDI		J, 0x01				; pin 1 of port B is output (sync)
	out		DDRB, J			

; Initialize Timer 1 
;   OCR1A will hold the value of 1016/1024 and be used to reset the counter and 
;   cause an IRQ that will start the HSYNC process
;   The counter will count each clock cycle (16MHz - no prescaling)

	ldi     J, 0x00
	sts     TCCR1A, J
	ldi     J, 0x09				; set timer 1 to CTC mode 4
	sts     TCCR1B, J		

	ldi     J, 0x02				; allow OCR1A IRQ's
	sts     TIMSK1, J			

; Initialise other registers
	ldi		J,0x00
	sts		UCSR0B,J			; Turn off serial

	ldi     J, 0x80
	out     ACSR, J				; turn off comparator

	ldi		J, 0x08				; set stack pointer to top of SRAM 
	out		SPH, J				;
	ldi		J, 0xFF				;
	out		SPL, J				;

; Initialise Program Variables
	ldi		chrln, 0x00			; keeps track of font gen line (0-7)
	ldi		vlineh, 0x00		; vertical line counter 0-262
	ldi		vline, 0x00			;			"
	ldi		YL, 0x00			;
	ldi		YH, 0x01			; init y pointer
	ldi		column, 0x00		; keeps track of horizontal chr pos (0-79)
	ldi		row, 0x00			; keeps track of vertical chr pos (0-24)
	ldi		cursorClk, 0x00		; init cursor blink timer
	ld		charUnderCursor, Y	; init cursor character
	ldi		cursorChar, 0x5F	; init cursor '_' character
	ldi		J,	0xFF	
	mov		previousInpt, J
	ldi		J,	0x00
	mov		cmdVal, J

;---------------------------------------------------------------------------------------------------------------------------
; Set configuration from PORTD
	in		configByte,PIND		; Read configuration bits (PORTD pins)

								; Configuration now read, so set PORTD pins to outputs
	ldi		J, 0x00				; 
	out		PORTD, J			; set port D outputs to 0
	LDI		J, 0xFF				; pins 0 - 7 of port B
	out		DDRD, J				; set PORTD pins to outputs

; HARD CODED OVERRIDE IF PREFERRED
;	ldi		J, 1<<CONFIG_PAL | 0<<CONFIG_8_OR_4_BIT | 1<<CONFIG_N_TWI | 1<<CONFIG_80_CHAR_PER_LINE | 1<<CONFIG_SINGLE_HEIGHT | 0<<CONFIG_BOLD
;	mov		configByte,J

;---------------------------------------------------------------------------------------------------------------------------
; Set default font
	ldi		J, 0x00
	sbrc	configByte,CONFIG_80_CHAR_PER_LINE ; 80 if high
	ori		J, 1<<ATT_80_CHAR_PER_LINE
	sbrc	configByte,CONFIG_BOLD ; Bold if high
	ori		J, 1<<ATT_BOLD
	sbrs	configByte,CONFIG_SINGLE_HEIGHT ; Double if low
	ori		J, 1<<ATT_DBL_HEIGHT
	mov		activeLineAtt, J

;---------------------------------------------------------------------------------------------------------------------------
; Select PAL/NTSC System
	sbrs	configByte, CONFIG_PAL	; low = NTSC
	rjmp	setNTSC				; Yes, set NTSC mode

setPAL:
	ldi		J, 0x38				; 0x0138 Last vertical line 312
	mov		lastline, J			;
	ldi		J, 0x40				; first vertical line of active disp
	mov		line1, J			;
	ldi		J, 0x04				;  0x0400 = 1024 clocks per line		
	sts     OCR1AH, J        
	ldi		J, 0x00				;  0x0400 = 1024 clocks per line		
	sts     OCR1AL, J			; set Counter 1 to cycle from 0 to 1024 and IRQ
	rjmp	palOrNtscSet		;

setNTSC:						; no, set NTSC mode
	ldi		J, 0x06				; 0x0106 Last vertical line 262
	mov		lastline, J			;
	ldi		J, 0x28				; first vertical line of active disp
	mov		line1, J			;
	ldi		J, 0x03				; 0x03f8 = 1016 clocks per line (63.5us)
	sts     OCR1AH, J        
	ldi		J, 0xf8				; 0x03f8 = 1016 clocks per line (63.5us)
	sts     OCR1AL, J			; set Counter 1 to cycle from 0 to 1016 and IRQ

palOrNtscSet:

;---------------------------------------------------------------------------------------------------------------------------
;  Initialise TWI if used otherwise setup ack/avail pins
	sbrs	configByte,CONFIG_N_TWI	; low = TWI
	rjmp	twoWireSelected		; Yes, set TWI mode otherwise setup ack/avail pins

twoWireNotUsed:
	LDI		J, 0x18				; pins 3,4 of port C are outputs
	out		DDRC, J	
	rjmp	twiSet

twoWireSelected:
	LDI		J, 0x08				; only pin 3 of port C is an output
	out		DDRC, J	

	ldi		J, 0x02				; Set address to 0x01, format aaaaaaag (a=address, g=general call enable)
	sts		TWAR, J				;
	ldi		J, (1<<TWEA)|(1<<TWEN)	
	sts		TWCR, J				; Enable TWI and allow ACK when slave is addressed.

twiSet:

;---------------------------------------------------------------------------------------------------------------------------
;  Reset Timer 1 and clear Busy Status Flag
	ldi     J, 0x00				; clear timer 1
	sts     TCNT1H, J			; 
	sts     TCNT1L, J			; 

	ldi		J, 0x1C				; clear timer 1 IRQ's
	out		TIFR1, J			; clear timer 1 IRQ's

	; Set the default attributes for each line (Screen 0100-08CF (2000 bytes), Attributes for each line 08D0-08E9 (25 bytes) )
	ldi		ZL, 0xD0
	ldi		ZH, 0x08			; set to start of attribute SRAM
	ldi		YL, 0x19
	ldi		YH,	0x00			; set Y to 25 (19 HEX)
loop1:
	st 		Z+, activeLineAtt	; save to attribute SRAM			
	sbiw	YL, 0x01			; dec Y
	brne	loop1	

	ldi 	inpt,0x0C			; CLS
	rcall	processChar

	SEI							; Initialisation complete. Enable IRQ's
		
;---------------------------------------------------------------------------------------------------------------------------
; Main Loop 

main:
	cpi		cursorChar, 0x00	; is the cursor turned on?
	breq	endOfCursor			; no, skip cursor code
	cpi		cursorClk, 0xff		; is clk at 0xFF?
	breq	solidCursor			; yes - solid cursor (no blink)
	cpi		cursorClk, 0x1C		; is it above 28 frames?
	brpl	blinkCursor			; if >25, show Cursor
	mov		inpt,charUnderCursor
	call	setYfromRowCol
	call	putCharAtY
	rjmp	endOfCursor			
solidCursor:
	mov		inpt,cursorChar
	call	setYfromRowCol
	call	putCharAtY
	rjmp	endOfCursor
blinkCursor:
	mov		inpt,cursorChar
	call	setYfromRowCol
	call	putCharAtY
	cpi		cursorClk, 0x37		; is clock >56 
	brmi	endOfCursor			; no
	clr		cursorClk				; reset timer
endOfCursor:

	sbrs	configByte,CONFIG_N_TWI	; low = TWI
	rjmp	twiMode			; Yes, set TWI mode

eightOrFourBit:
	; If the ack and data rdy are the same state then there is no
	; data waiting
	in		J,PORTC
	andi	J,0x10
	in		K,PINC
	andi	K,0x20
	lsr		K
	eor		J,K
	breq	Main

	; Data ready, so check if 4bit or 8bit data transfer is being used
	sbrs	configByte,CONFIG_8_OR_4_BIT
	rjmp	fourBit			; Low = 4 bit

eightBit:
	; 8 bit Input is split between portB and portC
	; so read both, shift then OR together to form the 8 bit data
	in		J,PINB
	andi	J,0x3E
	lsr		J
	in		inpt,PINC
	andi	inpt,0x07
	lsl		inpt
	lsl		inpt
	lsl		inpt
	lsl		inpt
	lsl		inpt
	or		inpt,J

	; Data read, so flip the ack bit
	in		K,PORTC
	ldi		J,0x10
	eor		K,J
	out		PORTC,K

	rcall	processChar			; process the host data
	rjmp	Main				; repeat

fourBit:
	; 4 bit Input is on portB only
	sbis	PINC,availpin
	rjmp	Nibble2 ; Process lower 4 bits if clear
nibble1:
	in		inpt,PINB
	andi	inpt,0x1E
	lsl		inpt				; Move to upper 4 bits
	lsl		inpt
	lsl		inpt	
	mov		nibbleTemp,inpt			
	; Data read, so flip the ack bit
	in		K,PORTC
	ldi		J,0x10
	eor		K,J
	out		PORTC,K
	rjmp	Main				; repeat
	
nibble2:
	in		J,PINB
	andi	J,0x1E
	lsr		J					; Move to lower 4 bits
	or		nibbleTemp,J		; Combine it with the first 4 bits
	mov		inpt,nibbleTemp

	; Data read, so flip the ack bit
	in		K,PORTC
	ldi		J,0x10
	eor		K,J
	out		PORTC,K
	rcall	processChar			; process the host data
	rjmp	main				; repeat

twiMode:
	lds		J, TWCR				; check the twi status register
	sbrs	J, TWINT			; is the twint bit set?
	rjmp	main				; no, back to main loop

	lds		J, TWSR				; Check status register						
	andi	J, 0xF8				; Ignore bits 0..2 (prescaler and reserved bit)	

;	cpi		J, 0xA0				; Stop - ignore
;	breq	toMain				; no new data

	cpi		J, TW_SR_DATA_ACK   ; 0x80 - address already received received, ACK had been returned
	brne	noTWIdata			; no new data

	lds    	inpt, TWDR			; Store the received data
	ldi		J, (1<<TWINT)|(1<<TWEA)|(1<<TWEN)	; clear the TWINT flag immediately to allow two wire transmission to resume
	sts		TWCR,J
	rcall	processChar			; process the host data
	rjmp	main				; back to main loop
	
noTWIdata:
	ldi		J, (1<<TWINT)|(1<<TWEA)|(1<<TWEN) ; clear the TWINT flag (logic 1)
	sts		TWCR,J
toMain:
	rjmp	main				; back to main loop

;---------------------------------------------------------------------------------------------------------------------------
; IRQ Service routine for the video line generation
TIM1_COMPA:						; IRQ service for OCR1A 
	.include "vidgen.inc"		; file that holds the video generation code	
	reti						; done

;---------------------------------------------------------------------------------------------------------------------------
; include subroutines and fonts

.include "ProcChr.inc"

.include "CGANormalFont.inc"	
.include "CGANormalFontWide.inc"
.include "CGABoldfont.inc"
.include "CGABoldFontWide.inc"
.include "BlockFont.inc"
