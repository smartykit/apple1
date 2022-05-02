;printing 'Hello, World!' at a runtime demo
;More about 'Hello, World!' program: https://en.wikipedia.org/wiki/%22Hello,_World!%22_program
	
RESET = $FF00
ECHO = $FFEF

TXTPTR = $1000

.org $1000
	.byte $0d
	.ASCII  "Hello, World!"
	.byte $0d
	.byte $00

.org $2000
	LDX #00
PRINT_CHAR:
	LDA TXTPTR,X
	BEQ END_PRINT	;end printing at the end of the string (\n=0)
	JSR ECHO
	INX
	JMP PRINT_CHAR
END_PRINT:
	JMP RESET	;return to Woz Monitor

