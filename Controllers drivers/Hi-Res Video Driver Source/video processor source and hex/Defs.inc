;
;  Originally designed and written by Daryl Rictor (c)2003-2004
;
;  Modified by Grant Searle 2007-13
;

;  Define Registers and Port Pins
;   Acc = R00, R01 (results of multiply command)
.def  Acc		=	R0				; Reserved - maths accumulator for multiply operations
.def  Acch		=	R1				;					" 

.def  nibbleTemp=	R2				; Temp storage for 4-bit (nibble) transfer		

.def configByte =	R3				; As read from PORT D at startup
.set CONFIG_PAL = 7					; 0xxxxxxx = NTSC, 0xxxxxxx = PAL
.set CONFIG_8_OR_4_BIT = 6			; x0xxxxxx = 4 bit, x1xxxxxx= 8 bit
.set CONFIG_N_TWI = 5				; xx1xxxxx = 4/8 bit, xx0xxxxx= Two wire
.set CONFIG_80_CHAR_PER_LINE = 4	; xxx0xxxx = 40, xxx1xxxx=80
.set CONFIG_SINGLE_HEIGHT = 3		; xxxx1xxx = Normal, xxxx0xxx = Double height
.set CONFIG_BOLD = 2				; xxxxx0xx = Normal, xxxxx1xx = Bold

.def  currLineAtt = R4				; Reserved for scanline processing
.set ATT_80_CHAR_PER_LINE = 0		; xxxxxxx0 = 40, xxxxxxx1=80
.set ATT_BOLD = 1			
.set ATT_DBL_TOP = 2				; xxxx00xx = Normal, xxxx01xx = Double top row, xxxx10xx = Double bottom row
.set ATT_DBL_BOTTOM = 3
			
.def  activeLineAtt = R5			; Font/graphic style currently being used
.set ATT_DBL_HEIGHT = 2
.set ATT_GRAPHICS = 7

.def  previousInpt = R6
.def  charUnderCursor	=   R7	; character under the cursor
.def  temp1s    =   R8
.def  temp0s    =   R9
.def  lastline	=	R10
.def  line1		= 	R11
.def  cmdVal	=	R12
.def  temp		=	R13			; General purpose temp
.def  temp2		=	R14			; General purpose temp
.def  temp3		=	R15			; General purpose temp

;-------------------------------------------------
.def  J			=	R16			; scratch 8 bit reg
.def  K			=	R17			; scratch 8 bit reg
.def  column	=	R18			; hor cursor pos  0-79
.def  row		=	R19			; vert cursor pos 0-24
.def  vline		=	R20			;\ vertical display line counter 0-261
.def  vlineh 	=	R21			;/ hi byte of vline counter
.def  chrln		=  	R22			; display chr line 0 - 199
.def  inpt		=	R23			; host input 
.def  cursorChar=   R24			; cursor character
.def  cursorClk	=	R25			; the cursor blink timer

;    X pair = R26,27
;    Y pair = R28,29
;    Z pair = R30,31
;
;  X pair used to point to SRAM by refresh routines
;  Y pair used to point to SRAM by HOST processor
;  Z pair used to point to Font data in Program Memory & scrolling


;PORT pin defs
.set  syncpin		=	PB0			; output
.set  ldsrpin		=	PC3			; output
.set  ackdpin		=	PC4			; output
.set  availpin		=	PC5			; input
.set  ntscpin		=	PD7
.set  datalenpin	=	PD6
.set  twowireselpin =   PD5

; TWI defs
.equ TW_SR_DATA_ACK =   0x80 		; x80 10000000 (the previously addressed (SLA + W) data has been received , ACK has been returned
