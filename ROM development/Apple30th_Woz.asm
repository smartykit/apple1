;SYMBOLS_TABLE = $031D
;INSTRUCTIONS_TABLE = $032D

VAR_X = $0006
VAR_Y = $0007

;addresses from Woz Monitor
;ECHO = $FFEF
;KBD = $D010
;KBDCR = $D011

SCREEN_WIDTH = $28

				LDA #$FF
				PHA
				LDA #$00
				PHA
A_0286: 		LDA #<INSTRUCTIONS       
				STA VAR_X ;zp
				LDA #>INSTRUCTIONS       
				STA VAR_Y ;zp
A_028R:			JSR ECHO_CR

A_0291:			LDY #$00       
				LDA (VAR_X),Y   
				BEQ A_02B2    
				LSR A
				LSR A
				LSR A
				LSR A           
				TAX             
				LDA (VAR_X),Y   
				AND #$0F        
				TAY             
				LDA SYMBOLS,Y     
A_02A4: 		JSR ECHO  
				DEX             
				BNE A_02A4    
				INC VAR_X ;zp             
				BNE A_0291    
				INC VAR_Y ;zp              
				BNE A_0291     
A_02B2:			INY           
				SEC             
				LDA #SCREEN_WIDTH  
				SBC (VAR_X),Y   
				LSR A           
				TAX             
				LDA #$A0        
A_02BC:			JSR ECHO  
				DEX
				BNE A_02BC    
				LDA (VAR_X),Y   
				TAX
A_02C5:			INY            
				LDA (VAR_X),Y   
				JSR ECHO        
				DEX             
				BNE A_02C5    
				INY             
				TYA             
				CLC             
				ADC VAR_X ;zp      
				STA VAR_X ;zp        
				LDA #$00        
				ADC VAR_Y ;zp      
				STA VAR_Y ;zp      
				LDA #$10        
				JSR FUNC_WAIT   
				JSR ECHO_CR
				LDY #$00        
				LDA (VAR_X),Y   
				BEQ A_0286    
				BNE A_028R    

FUNC_WAIT:		PHA   
				TXA             
				PHA
				TYA             
				PHA
				LDY #$FF
A_02F2: 		LDX #$FF
A_02F4: 		LDA KBDCR
				BPL A_0302   
				PLA
				TAY            
				PLA
				TAX            
				PLA            
				LDA KBD        
				RTS            

A_0302:			DEX
				BNE A_02F4   
				DEY
				BNE A_02F2   
				PLA
				TAY            
				PLA
				TAX            
				PLA
				SEC            
				SBC #$01       
				BNE FUNC_WAIT  
				LDA #$00       
				RTS            

ECHO_CR: 		PHA
				LDA #$8D       
				JSR ECHO
				PLA
				RTS

SYMBOLS: 
	.BYTE $A0      
	.BYTE $AE      
	.BYTE $BA      
	.BYTE $AC      
	.BYTE $BB      
	.BYTE $A1      
	.BYTE $AD      
	.BYTE $DE      
	.BYTE $AB      
	.BYTE $BD      
	.BYTE $BF      
	.BYTE $A6      
	.BYTE $AA      
	.BYTE $A5      
	.BYTE $A3      
	.BYTE $C0      

INSTRUCTIONS: 
	.BYTE $FF
	.BYTE $1F
	.BYTE $1B
	.BYTE $17      
	.BYTE $16
	.BYTE $14      
	.BYTE $13      
	.BYTE $14      
	.BYTE $17      
	.BYTE $1B      
	.BYTE $1E
	.BYTE $FF
	.BYTE $CF
	.BYTE $1E
	.BYTE $2C
	.BYTE $18
	.BYTE $50
	.BYTE $21      
	.BYTE $12         
	.BYTE $14         
	.BYTE $17         
	.BYTE $1C         
	.BYTE $FF         
	.BYTE $8F         
	.BYTE $1B         
	.BYTE $16 
	.BYTE $12      
	.BYTE $21 
	.BYTE $70      
	.BYTE $31 
	.BYTE $10      
	.BYTE $11
	.BYTE $18      
	.BYTE $FF         
	.BYTE $5F         
	.BYTE $1D 
	.BYTE $15 
	.BYTE $50   
	.BYTE $21 
	.BYTE $70      
	.BYTE $41 
	.BYTE $18      
	.BYTE $1D 
	.BYTE $FF 
	.BYTE $2F   
	.BYTE $1E 
	.BYTE $14 
	.BYTE $F0   
	.BYTE $30 
	.BYTE $11      
	.BYTE $10 
	.BYTE $12      
	.BYTE $17         
	.BYTE $1E 
	.BYTE $FF 
	.BYTE $19   
	.BYTE $E0 
	.BYTE $11      
	.BYTE $12         
	.BYTE $24 
	.BYTE $12      
	.BYTE $40         
	.BYTE $19 
	.BYTE $FF 
	.BYTE $14   
	.BYTE $50
	.BYTE $23      
	.BYTE $11 
	.BYTE $20      
	.BYTE $21 
	.BYTE $20      
	.BYTE $12         
	.BYTE $15
	.BYTE $18      
	.BYTE $19
	.BYTE $16 
	.BYTE $12   
	.BYTE $30 
	.BYTE $12      
	.BYTE $19 
	.BYTE $DF 
	.BYTE $1C   
	.BYTE $11 
	.BYTE $40      
	.BYTE $12         
	.BYTE $19 
	.BYTE $1A 
	.BYTE $17   
	.BYTE $25
	.BYTE $26      
	.BYTE $34         
	.BYTE $17         
	.BYTE $2A         
	.BYTE $19
	.BYTE $17 
	.BYTE $13   
	.BYTE $30 
	.BYTE $11      
	.BYTE $1B         
	.BYTE $CF         
	.BYTE $18         
	.BYTE $50 
	.BYTE $13      
	.BYTE $2A         
	.BYTE $19 
	.BYTE $38 
	.BYTE $19   
	.BYTE $18         
	.BYTE $27         
	.BYTE $28         
	.BYTE $27         
	.BYTE $18         
	.BYTE $17         
	.BYTE $12         
	.BYTE $30 
	.BYTE $18      
	.BYTE $CF         
	.BYTE $1A         
	.BYTE $50 
	.BYTE $15      
	.BYTE $19 
	.BYTE $17 
	.BYTE $14   
	.BYTE $13         
	.BYTE $22         
	.BYTE $13         
	.BYTE $16 
	.BYTE $17      
	.BYTE $16 
	.BYTE $13      
	.BYTE $21 
	.BYTE $12      
	.BYTE $14         
	.BYTE $17         
	.BYTE $15 
	.BYTE $20      
	.BYTE $13         
	.BYTE $1D 
	.BYTE $CF 
	.BYTE $1C   
	.BYTE $40         
	.BYTE $12         
	.BYTE $28         
	.BYTE $15 
	.BYTE $13      
	.BYTE $11 
	.BYTE $30      
	.BYTE $12         
	.BYTE $28         
	.BYTE $12         
	.BYTE $10 
	.BYTE $11      
	.BYTE $12         
	.BYTE $14         
	.BYTE $17         
	.BYTE $18         
	.BYTE $12         
	.BYTE $10 
	.BYTE $1A      
	.BYTE $DF         
	.BYTE $1D 
	.BYTE $12 
	.BYTE $30   
	.BYTE $14         
	.BYTE $1A         
	.BYTE $19 
	.BYTE $18 
	.BYTE $17   
	.BYTE $45 
	.BYTE $16      
	.BYTE $1B         
	.BYTE $1D 
	.BYTE $18 
	.BYTE $26   
	.BYTE $17         
	.BYTE $18         
	.BYTE $1A         
	.BYTE $1B         
	.BYTE $15 
	.BYTE $11      
	.BYTE $1C         
	.BYTE $EF         
	.BYTE $18         
	.BYTE $10 
	.BYTE $13      
	.BYTE $12         
	.BYTE $13         
	.BYTE $59 
	.BYTE $18 
	.BYTE $27   
	.BYTE $19 
	.BYTE $1B 
	.BYTE $2C   
	.BYTE $1A         
	.BYTE $27         
	.BYTE $19 
	.BYTE $2A 
	.BYTE $17   
	.BYTE $12         
	.BYTE $18         
	.BYTE $EF         
	.BYTE $1E 
	.BYTE $12 
	.BYTE $23   
	.BYTE $11 
	.BYTE $15      
	.BYTE $16 
	.BYTE $35      
	.BYTE $24 
	.BYTE $35      
	.BYTE $16 
	.BYTE $17      
	.BYTE $16 
	.BYTE $14      
	.BYTE $13         
	.BYTE $14         
	.BYTE $15 
	.BYTE $16      
	.BYTE $15 
	.BYTE $11      
	.BYTE $18         
	.BYTE $FF         
	.BYTE $17         
	.BYTE $30 
	.BYTE $12      
	.BYTE $24 
	.BYTE $13      
	.BYTE $21 
	.BYTE $23      
	.BYTE $11 
	.BYTE $10      
	.BYTE $21 
	.BYTE $22      
	.BYTE $21 
	.BYTE $13      
	.BYTE $14         
	.BYTE $12         
	.BYTE $13         
	.BYTE $1D 
	.BYTE $FF 
	.BYTE $1D   
	.BYTE $16 
	.BYTE $11      
	.BYTE $10 
	.BYTE $21      
	.BYTE $22         
	.BYTE $11 
	.BYTE $22      
	.BYTE $13         
	.BYTE $24 
	.BYTE $25      
	.BYTE $14         
	.BYTE $23         
	.BYTE $41 
	.BYTE $1A      
	.BYTE $FF         
	.BYTE $2F         
	.BYTE $1D 
	.BYTE $16 
	.BYTE $15   
	.BYTE $20 
	.BYTE $31 
	.BYTE $13   
	.BYTE $24 
	.BYTE $15      
	.BYTE $16 
	.BYTE $47      
	.BYTE $13         
	.BYTE $11
	.BYTE $10      
	.BYTE $12         
	.BYTE $19 
	.BYTE $FF 
	.BYTE $2F   
	.BYTE $1D 
	.BYTE $1A 
	.BYTE $1C   
	.BYTE $19 
	.BYTE $13 
	.BYTE $11   
	.BYTE $20 
	.BYTE $21 
	.BYTE $13   
	.BYTE $24 
	.BYTE $33      
	.BYTE $24 
	.BYTE $21      
	.BYTE $13         
	.BYTE $1A         
	.BYTE $EF         
	.BYTE $2E 
	.BYTE $1D 
	.BYTE $1C   
	.BYTE $1B         
	.BYTE $1D 
	.BYTE $1E 
	.BYTE $1B   
	.BYTE $16 
	.BYTE $13      
	.BYTE $51 
	.BYTE $12      
	.BYTE $41 
	.BYTE $12      
	.BYTE $21 
	.BYTE $12      
	.BYTE $18         
	.BYTE $1A         
	.BYTE $1D 
	.BYTE $AF 
	.BYTE $1E   
	.BYTE $1D 
	.BYTE $3C 
	.BYTE $2D   
	.BYTE $4E 
	.BYTE $1A 
	.BYTE $14   
	.BYTE $22         
	.BYTE $11 
	.BYTE $20      
	.BYTE $71 
	.BYTE $13      
	.BYTE $15 
	.BYTE $17      
	.BYTE $2C 
	.BYTE $1D 
	.BYTE $1E   
	.BYTE $7F         
	.BYTE $4D 
	.BYTE $2E 
	.BYTE $2D   
	.BYTE $2E 
	.BYTE $1D
	.BYTE $2E   
	.BYTE $19
	.BYTE $23
	.BYTE $32   
	.BYTE $31
	.BYTE $22      
	.BYTE $13         
	.BYTE $15
	.BYTE $16      
	.BYTE $14         
	.BYTE $17         
	.BYTE $2E 
	.BYTE $3D 
	.BYTE $2E   
	.BYTE $4F         
	.BYTE $2E 
	.BYTE $7D 
	.BYTE $2E   
	.BYTE $1D 
	.BYTE $2E 
	.BYTE $1A   
	.BYTE $14         
	.BYTE $43         
	.BYTE $14         
	.BYTE $13         
	.BYTE $14         
	.BYTE $15 
	.BYTE $16      
	.BYTE $17         
	.BYTE $15 
	.BYTE $14      
	.BYTE $18         
	.BYTE $1D
	.BYTE $4E
	.BYTE $2D
	.BYTE $4E 
	.BYTE $9D 
	.BYTE $4E   
	.BYTE $1C         
	.BYTE $1A         
	.BYTE $18         
	.BYTE $15
	.BYTE $14      
	.BYTE $43         
	.BYTE $15
	.BYTE $26      
	.BYTE $15
	.BYTE $13      
	.BYTE $16 
	.BYTE $1A
	.BYTE $3E
	.BYTE $8D 
	.BYTE $00 
	.BYTE $04 
	.BYTE $57 
	.BYTE $4F 
	.BYTE $5A 
	.BYTE $20 
	.BYTE $00 

	.byte "Woz face program end", $0d, $00
