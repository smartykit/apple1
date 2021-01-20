;KBD             = $D010         
;KBDCR           = $D011         
;DSP             = $D012        
;DSPCR           = $D013
START_TEST = $EA
END_TEST = $EB


LED_BLINKS = 5
TEST1_REPEATS = 4
TEST2_REPEATS = 16
TEST61_REPEATS = 8
TEST62_REPEATS = 8
TEST7_REPEATS = 16
POSTOK_REPEATS = 4

/*
LED_BLINKS = 1
TEST1_REPEATS = 1
TEST2_REPEATS = 1
TEST61_REPEATS = 1
TEST62_REPEATS = 1
TEST7_REPEATS = 1
POSTOK_REPEATS = 1
*/


POST_START:		NOP
				LDA #START_TEST
			    STA DSP

				LDA #%00000001
				JSR BLINK
;Test 1. Memory addresses decoder (blinking in cycle)
MEM_DECODER: 	LDX #TEST1_REPEATS
LOOPADDR:	 	LDA $FF00
			    LDA $E000
			    LDA $D000
			    LDA $C000
			    DEX
			    BNE LOOPADDR  

			    LDA #%00000010
				JSR BLINK
;Test 2. Ports decoder (blinking in cycle)
				LDA #TEST2_REPEATS
PORTS_DECODER:  TAX
		        LDY KBD
		        LDY KBDCR
		        STX DSP
		        BIT DSP
		        DEX
		        TXA
		        BNE PORTS_DECODER

		        LDA #%00000100
				JSR BLINK
;Test 3. Testing writing to Video port (1->2->4->8->16->32->64->128->256->0)
        		LDA #%00000001
VIDEO_PORT: 	STA DSP
        		ASL A ;shifting 1 to the left
       			BNE VIDEO_PORT

       			LDA #%00001000
				JSR BLINK
;Test 4. Testing writing to Video port via function call (256->128->64->32->16->8->4->2->1->0)
				JSR VIDEO_PORT2


				LDA #%00010000
				JSR BLINK
;Test 5. Testing RAM with write&read (writing TEST_SYMBOL and testing read for every 4Kb block in 32Kb RAM)
;Total blocks tested is 8 (4*8 = 32)
TEST_SYMBOL = $3E

/*
RAMTEST: 		CLD
		        LDX #$00
		        LDY #$00

		        LDA #$FF
		        STA $00
		        LDA #$0F
		        STA $01

RAMLOOP: 		LDA #TEST_SYMBOL
		        STA ($00),Y
		        LDA ($00),Y
		        CMP #TEST_SYMBOL
		        BNE ENDTEST
		        TXA
		        ASL A
		        ADC #$01
		        STA DSP
		        TAX
		        LDA $01
		        ADC #$10
		        STA $01
		        JMP RAMLOOP

		        */

		        LDA #%00100000
				JSR BLINK
;Test 6. Testing BIT7 ports - keyboard and video 
BIT7MASK     = %10000000
KBD7MASK     = %00000111
DSP7MASK     = %00111111
;Test 6.1. Testing keyboard BIT7 port read (turn on 3 LEDs on the left and show BIT7 in the last LED)

KBDBIT7: 		LDX #TEST61_REPEATS
		        LDA #KBD7MASK
		        STA DSP
KBD7LOOP:
		        LDA KBDCR
		        AND #BIT7MASK
		        ORA #KBD7MASK
		        STA DSP
		        DEX
		        BNE KBD7LOOP
;Test 6.2. Testing video BIT7 port read (turn on 6 LEDs on the left and show BIT7 in the last LED)

DSPBIT7: 		LDX #TEST62_REPEATS
		        LDA #DSP7MASK
		        STA DSP
DSP7LOOP:
		        LDA DSP
		        AND #BIT7MASK
		        ORA #DSP7MASK
		        STA DSP
		        DEX
		        BNE DSP7LOOP


		        LDA #%01000000
				JSR BLINK
;Test 7. Testing keyboard port read and write to Video port
KBDTODSP: 		LDX #TEST7_REPEATS
		        LDA #$00
		        STA DSP
KBDDSPLOOP:
		        LDA KBD
		        STA DSP
		        DEX
		        BNE KBDDSPLOOP		        

;POST success and end

ENDPOST: 		LDX #POSTOK_REPEATS
ENDLOOP:
       			LDA #%01010101
		        STA DSP
		        NOP
		        NOP
		        LDA #%10101010
		        STA DSP
		        NOP
		        NOP
		        DEX
		        BNE ENDLOOP   

		        NOP
		        NOP     

;printing ASCII table
		        JSR ASCII_ECHO 

ENDTEST: 		NOP
        		NOP
        		LDA #END_TEST
        		JSR ECHO 	;writing END_TEST to let video driver know that tests are over
				
        		LDX #$00
PRINT_MSG:
				LDA POSTCompletedText, X
				BEQ TO_WOZ_MON	;end printing at the end of the string (\n=0)
				JSR ECHO
				INX
				JMP PRINT_MSG

 TO_WOZ_MON:	JMP RESET	;start Woz Monitor (operating system)

;------------------------------------------------------
; POST subroutines
;------------------------------------------------------
;blinking LEDs in Video port
VIDEO_PORT2: 	LDA #%10000000
TEST2:   		STA DSP
        		LSR A
        		BNE TEST2
       			RTS

;blink with a LED in a position from A register
TURN_OFF = %00000000
BLINK:			LDX #LED_BLINKS
				TAY	;save A
NEXT_BLINK:		TYA ;restore A
				STA DSP
				NOP
				NOP
				LDA #TURN_OFF
				STA DSP
				NOP
				NOP
				DEX
				BNE NEXT_BLINK
				RTS

;printing visible symbols of ACSII table via ECHO function from Woz Monitor
PRINT_ASCII:
			    LDY #32
			    LDX #95 ;80 in hex = 127 in decimal    
ASCII_ECHO:
			    BIT DSP         
			    BMI ASCII_ECHO
			    STY DSP
			    INY
			    DEX
			    BNE ASCII_ECHO
			    RTS

CHAR_ECHO:	   	BIT DSP         
			    BMI CHAR_ECHO
			    STA DSP
			    RTS

POSTCompletedText:
	.byte $0d, $0d, "POST ok (v.1.0). SmartyKit 1 is ready.", $0d, $0d, $00