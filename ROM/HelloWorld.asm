;printing 'Hello, World!'
;More about 'Hello, World!' program: https://en.wikipedia.org/wiki/%22Hello,_World!%22_program
	LDX #00
PRINT_CHAR:
	LDA HelloWorldText, X
	BEQ END_PRINT	;end printing at the end of the string (\n=0)
	JSR ECHO
	INX
	JMP PRINT_CHAR
END_PRINT:
	JMP RESET	;return to Woz Monitor

HelloWorldText:
	.byte $0d, "Hello, World!", $0d, "This is SmartyKit 1.", $0d, $0d, $00