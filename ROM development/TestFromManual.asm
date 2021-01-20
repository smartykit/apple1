;Test from Apple-1 Operation Manual – printing all ASCII symbols in a loop
			LDA #$00
TEST_LOOP: 	TAX
			JSR ECHO
			INX
			TXA
			JMP TEST_LOOP
