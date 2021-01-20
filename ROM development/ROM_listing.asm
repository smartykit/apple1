ca65 V2.19 - Git 0f4cb443
Main file   : SmartyKit1_ROM.asm
Current file: SmartyKit1_ROM.asm

000000r 1                         .setcpu "6502"
000000r 1                         .feature c_comments
000000r 1                         .segment "PICTURE"
000000r 1  00                     .byte          %00000000
000001r 1  66                     .byte          %01100110
000002r 1  FF                     .byte          %11111111
000003r 1  FF                     .byte          %11111111
000004r 1  FF                     .byte          %11111111
000005r 1  7E                     .byte          %01111110
000006r 1  3C                     .byte          %00111100
000007r 1  18                     .byte          %00011000
000008r 1  00                     .byte 00
000009r 1  00                     .byte 00
00000Ar 1  3C 42 A5 81  Smiley:   .byte $3c, $42, $a5, $81, $a5, $99, $42, $3c
00000Er 1  A5 99 42 3C  
000012r 1  88 A8 50 07  Woz:      .byte $88, $a8, $50, $07, $61, $92, $94, $67
000016r 1  61 92 94 67  
00001Ar 1                       ;  .byte "8*8 Pixel Art picture end", $0d, $00
00001Ar 1               
00001Ar 1                         .code
000000r 1  A9 12        loop:     lda #$12
000002r 1  4C rr rr               jmp loop
000005r 1               
000005r 1                         .segment "C000"
000000r 1  EA                     nop
000001r 1                         .segment "E000"
000000r 1  20 rr rr               JSR COPY_HEART
000003r 1  4C 00 FC               JMP $FC00
000006r 1  EA                     nop
000007r 1                         .segment "F000"
000000r 1                         ;Woz face
000000r 1                         .include "Apple30th_Woz.asm"
000000r 2               ;SYMBOLS_TABLE = $031D
000000r 2               ;INSTRUCTIONS_TABLE = $032D
000000r 2               
000000r 2               VAR_X = $0006
000000r 2               VAR_Y = $0007
000000r 2               
000000r 2               ;addresses from Woz Monitor
000000r 2               ;ECHO = $FFEF
000000r 2               ;KBD = $D010
000000r 2               ;KBDCR = $D011
000000r 2               
000000r 2               SCREEN_WIDTH = $28
000000r 2               
000000r 2  A9 FF        				LDA #$FF
000002r 2  48           				PHA
000003r 2  A9 00        				LDA #$00
000005r 2  48           				PHA
000006r 2  A9 rr        A_0286: 		LDA #<INSTRUCTIONS
000008r 2  85 06        				STA VAR_X ;zp
00000Ar 2  A9 rr        				LDA #>INSTRUCTIONS
00000Cr 2  85 07        				STA VAR_Y ;zp
00000Er 2  20 rr rr     A_028R:			JSR ECHO_CR
000011r 2               
000011r 2  A0 00        A_0291:			LDY #$00
000013r 2  B1 06        				LDA (VAR_X),Y
000015r 2  F0 1B        				BEQ A_02B2
000017r 2  4A           				LSR A
000018r 2  4A           				LSR A
000019r 2  4A           				LSR A
00001Ar 2  4A           				LSR A
00001Br 2  AA           				TAX
00001Cr 2  B1 06        				LDA (VAR_X),Y
00001Er 2  29 0F        				AND #$0F
000020r 2  A8           				TAY
000021r 2  B9 rr rr     				LDA SYMBOLS,Y
000024r 2  20 EF FF     A_02A4: 		JSR ECHO
000027r 2  CA           				DEX
000028r 2  D0 FA        				BNE A_02A4
00002Ar 2  E6 06        				INC VAR_X ;zp
00002Cr 2  D0 E3        				BNE A_0291
00002Er 2  E6 07        				INC VAR_Y ;zp
000030r 2  D0 DF        				BNE A_0291
000032r 2  C8           A_02B2:			INY
000033r 2  38           				SEC
000034r 2  A9 28        				LDA #SCREEN_WIDTH
000036r 2  F1 06        				SBC (VAR_X),Y
000038r 2  4A           				LSR A
000039r 2  AA           				TAX
00003Ar 2  A9 A0        				LDA #$A0
00003Cr 2  20 EF FF     A_02BC:			JSR ECHO
00003Fr 2  CA           				DEX
000040r 2  D0 FA        				BNE A_02BC
000042r 2  B1 06        				LDA (VAR_X),Y
000044r 2  AA           				TAX
000045r 2  C8           A_02C5:			INY
000046r 2  B1 06        				LDA (VAR_X),Y
000048r 2  20 EF FF     				JSR ECHO
00004Br 2  CA           				DEX
00004Cr 2  D0 F7        				BNE A_02C5
00004Er 2  C8           				INY
00004Fr 2  98           				TYA
000050r 2  18           				CLC
000051r 2  65 06        				ADC VAR_X ;zp
000053r 2  85 06        				STA VAR_X ;zp
000055r 2  A9 00        				LDA #$00
000057r 2  65 07        				ADC VAR_Y ;zp
000059r 2  85 07        				STA VAR_Y ;zp
00005Br 2  A9 10        				LDA #$10
00005Dr 2  20 rr rr     				JSR FUNC_WAIT
000060r 2  20 rr rr     				JSR ECHO_CR
000063r 2  A0 00        				LDY #$00
000065r 2  B1 06        				LDA (VAR_X),Y
000067r 2  F0 9D        				BEQ A_0286
000069r 2  D0 A3        				BNE A_028R
00006Br 2               
00006Br 2  48           FUNC_WAIT:		PHA
00006Cr 2  8A           				TXA
00006Dr 2  48           				PHA
00006Er 2  98           				TYA
00006Fr 2  48           				PHA
000070r 2  A0 FF        				LDY #$FF
000072r 2  A2 FF        A_02F2: 		LDX #$FF
000074r 2  AD 11 D0     A_02F4: 		LDA KBDCR
000077r 2  10 09        				BPL A_0302
000079r 2  68           				PLA
00007Ar 2  A8           				TAY
00007Br 2  68           				PLA
00007Cr 2  AA           				TAX
00007Dr 2  68           				PLA
00007Er 2  AD 10 D0     				LDA KBD
000081r 2  60           				RTS
000082r 2               
000082r 2  CA           A_0302:			DEX
000083r 2  D0 EF        				BNE A_02F4
000085r 2  88           				DEY
000086r 2  D0 EA        				BNE A_02F2
000088r 2  68           				PLA
000089r 2  A8           				TAY
00008Ar 2  68           				PLA
00008Br 2  AA           				TAX
00008Cr 2  68           				PLA
00008Dr 2  38           				SEC
00008Er 2  E9 01        				SBC #$01
000090r 2  D0 D9        				BNE FUNC_WAIT
000092r 2  A9 00        				LDA #$00
000094r 2  60           				RTS
000095r 2               
000095r 2  48           ECHO_CR: 		PHA
000096r 2  A9 8D        				LDA #$8D
000098r 2  20 EF FF     				JSR ECHO
00009Br 2  68           				PLA
00009Cr 2  60           				RTS
00009Dr 2               
00009Dr 2               SYMBOLS:
00009Dr 2  A0           	.BYTE $A0
00009Er 2  AE           	.BYTE $AE
00009Fr 2  BA           	.BYTE $BA
0000A0r 2  AC           	.BYTE $AC
0000A1r 2  BB           	.BYTE $BB
0000A2r 2  A1           	.BYTE $A1
0000A3r 2  AD           	.BYTE $AD
0000A4r 2  DE           	.BYTE $DE
0000A5r 2  AB           	.BYTE $AB
0000A6r 2  BD           	.BYTE $BD
0000A7r 2  BF           	.BYTE $BF
0000A8r 2  A6           	.BYTE $A6
0000A9r 2  AA           	.BYTE $AA
0000AAr 2  A5           	.BYTE $A5
0000ABr 2  A3           	.BYTE $A3
0000ACr 2  C0           	.BYTE $C0
0000ADr 2               
0000ADr 2               INSTRUCTIONS:
0000ADr 2  FF           	.BYTE $FF
0000AEr 2  1F           	.BYTE $1F
0000AFr 2  1B           	.BYTE $1B
0000B0r 2  17           	.BYTE $17
0000B1r 2  16           	.BYTE $16
0000B2r 2  14           	.BYTE $14
0000B3r 2  13           	.BYTE $13
0000B4r 2  14           	.BYTE $14
0000B5r 2  17           	.BYTE $17
0000B6r 2  1B           	.BYTE $1B
0000B7r 2  1E           	.BYTE $1E
0000B8r 2  FF           	.BYTE $FF
0000B9r 2  CF           	.BYTE $CF
0000BAr 2  1E           	.BYTE $1E
0000BBr 2  2C           	.BYTE $2C
0000BCr 2  18           	.BYTE $18
0000BDr 2  50           	.BYTE $50
0000BEr 2  21           	.BYTE $21
0000BFr 2  12           	.BYTE $12
0000C0r 2  14           	.BYTE $14
0000C1r 2  17           	.BYTE $17
0000C2r 2  1C           	.BYTE $1C
0000C3r 2  FF           	.BYTE $FF
0000C4r 2  8F           	.BYTE $8F
0000C5r 2  1B           	.BYTE $1B
0000C6r 2  16           	.BYTE $16
0000C7r 2  12           	.BYTE $12
0000C8r 2  21           	.BYTE $21
0000C9r 2  70           	.BYTE $70
0000CAr 2  31           	.BYTE $31
0000CBr 2  10           	.BYTE $10
0000CCr 2  11           	.BYTE $11
0000CDr 2  18           	.BYTE $18
0000CEr 2  FF           	.BYTE $FF
0000CFr 2  5F           	.BYTE $5F
0000D0r 2  1D           	.BYTE $1D
0000D1r 2  15           	.BYTE $15
0000D2r 2  50           	.BYTE $50
0000D3r 2  21           	.BYTE $21
0000D4r 2  70           	.BYTE $70
0000D5r 2  41           	.BYTE $41
0000D6r 2  18           	.BYTE $18
0000D7r 2  1D           	.BYTE $1D
0000D8r 2  FF           	.BYTE $FF
0000D9r 2  2F           	.BYTE $2F
0000DAr 2  1E           	.BYTE $1E
0000DBr 2  14           	.BYTE $14
0000DCr 2  F0           	.BYTE $F0
0000DDr 2  30           	.BYTE $30
0000DEr 2  11           	.BYTE $11
0000DFr 2  10           	.BYTE $10
0000E0r 2  12           	.BYTE $12
0000E1r 2  17           	.BYTE $17
0000E2r 2  1E           	.BYTE $1E
0000E3r 2  FF           	.BYTE $FF
0000E4r 2  19           	.BYTE $19
0000E5r 2  E0           	.BYTE $E0
0000E6r 2  11           	.BYTE $11
0000E7r 2  12           	.BYTE $12
0000E8r 2  24           	.BYTE $24
0000E9r 2  12           	.BYTE $12
0000EAr 2  40           	.BYTE $40
0000EBr 2  19           	.BYTE $19
0000ECr 2  FF           	.BYTE $FF
0000EDr 2  14           	.BYTE $14
0000EEr 2  50           	.BYTE $50
0000EFr 2  23           	.BYTE $23
0000F0r 2  11           	.BYTE $11
0000F1r 2  20           	.BYTE $20
0000F2r 2  21           	.BYTE $21
0000F3r 2  20           	.BYTE $20
0000F4r 2  12           	.BYTE $12
0000F5r 2  15           	.BYTE $15
0000F6r 2  18           	.BYTE $18
0000F7r 2  19           	.BYTE $19
0000F8r 2  16           	.BYTE $16
0000F9r 2  12           	.BYTE $12
0000FAr 2  30           	.BYTE $30
0000FBr 2  12           	.BYTE $12
0000FCr 2  19           	.BYTE $19
0000FDr 2  DF           	.BYTE $DF
0000FEr 2  1C           	.BYTE $1C
0000FFr 2  11           	.BYTE $11
000100r 2  40           	.BYTE $40
000101r 2  12           	.BYTE $12
000102r 2  19           	.BYTE $19
000103r 2  1A           	.BYTE $1A
000104r 2  17           	.BYTE $17
000105r 2  25           	.BYTE $25
000106r 2  26           	.BYTE $26
000107r 2  34           	.BYTE $34
000108r 2  17           	.BYTE $17
000109r 2  2A           	.BYTE $2A
00010Ar 2  19           	.BYTE $19
00010Br 2  17           	.BYTE $17
00010Cr 2  13           	.BYTE $13
00010Dr 2  30           	.BYTE $30
00010Er 2  11           	.BYTE $11
00010Fr 2  1B           	.BYTE $1B
000110r 2  CF           	.BYTE $CF
000111r 2  18           	.BYTE $18
000112r 2  50           	.BYTE $50
000113r 2  13           	.BYTE $13
000114r 2  2A           	.BYTE $2A
000115r 2  19           	.BYTE $19
000116r 2  38           	.BYTE $38
000117r 2  19           	.BYTE $19
000118r 2  18           	.BYTE $18
000119r 2  27           	.BYTE $27
00011Ar 2  28           	.BYTE $28
00011Br 2  27           	.BYTE $27
00011Cr 2  18           	.BYTE $18
00011Dr 2  17           	.BYTE $17
00011Er 2  12           	.BYTE $12
00011Fr 2  30           	.BYTE $30
000120r 2  18           	.BYTE $18
000121r 2  CF           	.BYTE $CF
000122r 2  1A           	.BYTE $1A
000123r 2  50           	.BYTE $50
000124r 2  15           	.BYTE $15
000125r 2  19           	.BYTE $19
000126r 2  17           	.BYTE $17
000127r 2  14           	.BYTE $14
000128r 2  13           	.BYTE $13
000129r 2  22           	.BYTE $22
00012Ar 2  13           	.BYTE $13
00012Br 2  16           	.BYTE $16
00012Cr 2  17           	.BYTE $17
00012Dr 2  16           	.BYTE $16
00012Er 2  13           	.BYTE $13
00012Fr 2  21           	.BYTE $21
000130r 2  12           	.BYTE $12
000131r 2  14           	.BYTE $14
000132r 2  17           	.BYTE $17
000133r 2  15           	.BYTE $15
000134r 2  20           	.BYTE $20
000135r 2  13           	.BYTE $13
000136r 2  1D           	.BYTE $1D
000137r 2  CF           	.BYTE $CF
000138r 2  1C           	.BYTE $1C
000139r 2  40           	.BYTE $40
00013Ar 2  12           	.BYTE $12
00013Br 2  28           	.BYTE $28
00013Cr 2  15           	.BYTE $15
00013Dr 2  13           	.BYTE $13
00013Er 2  11           	.BYTE $11
00013Fr 2  30           	.BYTE $30
000140r 2  12           	.BYTE $12
000141r 2  28           	.BYTE $28
000142r 2  12           	.BYTE $12
000143r 2  10           	.BYTE $10
000144r 2  11           	.BYTE $11
000145r 2  12           	.BYTE $12
000146r 2  14           	.BYTE $14
000147r 2  17           	.BYTE $17
000148r 2  18           	.BYTE $18
000149r 2  12           	.BYTE $12
00014Ar 2  10           	.BYTE $10
00014Br 2  1A           	.BYTE $1A
00014Cr 2  DF           	.BYTE $DF
00014Dr 2  1D           	.BYTE $1D
00014Er 2  12           	.BYTE $12
00014Fr 2  30           	.BYTE $30
000150r 2  14           	.BYTE $14
000151r 2  1A           	.BYTE $1A
000152r 2  19           	.BYTE $19
000153r 2  18           	.BYTE $18
000154r 2  17           	.BYTE $17
000155r 2  45           	.BYTE $45
000156r 2  16           	.BYTE $16
000157r 2  1B           	.BYTE $1B
000158r 2  1D           	.BYTE $1D
000159r 2  18           	.BYTE $18
00015Ar 2  26           	.BYTE $26
00015Br 2  17           	.BYTE $17
00015Cr 2  18           	.BYTE $18
00015Dr 2  1A           	.BYTE $1A
00015Er 2  1B           	.BYTE $1B
00015Fr 2  15           	.BYTE $15
000160r 2  11           	.BYTE $11
000161r 2  1C           	.BYTE $1C
000162r 2  EF           	.BYTE $EF
000163r 2  18           	.BYTE $18
000164r 2  10           	.BYTE $10
000165r 2  13           	.BYTE $13
000166r 2  12           	.BYTE $12
000167r 2  13           	.BYTE $13
000168r 2  59           	.BYTE $59
000169r 2  18           	.BYTE $18
00016Ar 2  27           	.BYTE $27
00016Br 2  19           	.BYTE $19
00016Cr 2  1B           	.BYTE $1B
00016Dr 2  2C           	.BYTE $2C
00016Er 2  1A           	.BYTE $1A
00016Fr 2  27           	.BYTE $27
000170r 2  19           	.BYTE $19
000171r 2  2A           	.BYTE $2A
000172r 2  17           	.BYTE $17
000173r 2  12           	.BYTE $12
000174r 2  18           	.BYTE $18
000175r 2  EF           	.BYTE $EF
000176r 2  1E           	.BYTE $1E
000177r 2  12           	.BYTE $12
000178r 2  23           	.BYTE $23
000179r 2  11           	.BYTE $11
00017Ar 2  15           	.BYTE $15
00017Br 2  16           	.BYTE $16
00017Cr 2  35           	.BYTE $35
00017Dr 2  24           	.BYTE $24
00017Er 2  35           	.BYTE $35
00017Fr 2  16           	.BYTE $16
000180r 2  17           	.BYTE $17
000181r 2  16           	.BYTE $16
000182r 2  14           	.BYTE $14
000183r 2  13           	.BYTE $13
000184r 2  14           	.BYTE $14
000185r 2  15           	.BYTE $15
000186r 2  16           	.BYTE $16
000187r 2  15           	.BYTE $15
000188r 2  11           	.BYTE $11
000189r 2  18           	.BYTE $18
00018Ar 2  FF           	.BYTE $FF
00018Br 2  17           	.BYTE $17
00018Cr 2  30           	.BYTE $30
00018Dr 2  12           	.BYTE $12
00018Er 2  24           	.BYTE $24
00018Fr 2  13           	.BYTE $13
000190r 2  21           	.BYTE $21
000191r 2  23           	.BYTE $23
000192r 2  11           	.BYTE $11
000193r 2  10           	.BYTE $10
000194r 2  21           	.BYTE $21
000195r 2  22           	.BYTE $22
000196r 2  21           	.BYTE $21
000197r 2  13           	.BYTE $13
000198r 2  14           	.BYTE $14
000199r 2  12           	.BYTE $12
00019Ar 2  13           	.BYTE $13
00019Br 2  1D           	.BYTE $1D
00019Cr 2  FF           	.BYTE $FF
00019Dr 2  1D           	.BYTE $1D
00019Er 2  16           	.BYTE $16
00019Fr 2  11           	.BYTE $11
0001A0r 2  10           	.BYTE $10
0001A1r 2  21           	.BYTE $21
0001A2r 2  22           	.BYTE $22
0001A3r 2  11           	.BYTE $11
0001A4r 2  22           	.BYTE $22
0001A5r 2  13           	.BYTE $13
0001A6r 2  24           	.BYTE $24
0001A7r 2  25           	.BYTE $25
0001A8r 2  14           	.BYTE $14
0001A9r 2  23           	.BYTE $23
0001AAr 2  41           	.BYTE $41
0001ABr 2  1A           	.BYTE $1A
0001ACr 2  FF           	.BYTE $FF
0001ADr 2  2F           	.BYTE $2F
0001AEr 2  1D           	.BYTE $1D
0001AFr 2  16           	.BYTE $16
0001B0r 2  15           	.BYTE $15
0001B1r 2  20           	.BYTE $20
0001B2r 2  31           	.BYTE $31
0001B3r 2  13           	.BYTE $13
0001B4r 2  24           	.BYTE $24
0001B5r 2  15           	.BYTE $15
0001B6r 2  16           	.BYTE $16
0001B7r 2  47           	.BYTE $47
0001B8r 2  13           	.BYTE $13
0001B9r 2  11           	.BYTE $11
0001BAr 2  10           	.BYTE $10
0001BBr 2  12           	.BYTE $12
0001BCr 2  19           	.BYTE $19
0001BDr 2  FF           	.BYTE $FF
0001BEr 2  2F           	.BYTE $2F
0001BFr 2  1D           	.BYTE $1D
0001C0r 2  1A           	.BYTE $1A
0001C1r 2  1C           	.BYTE $1C
0001C2r 2  19           	.BYTE $19
0001C3r 2  13           	.BYTE $13
0001C4r 2  11           	.BYTE $11
0001C5r 2  20           	.BYTE $20
0001C6r 2  21           	.BYTE $21
0001C7r 2  13           	.BYTE $13
0001C8r 2  24           	.BYTE $24
0001C9r 2  33           	.BYTE $33
0001CAr 2  24           	.BYTE $24
0001CBr 2  21           	.BYTE $21
0001CCr 2  13           	.BYTE $13
0001CDr 2  1A           	.BYTE $1A
0001CEr 2  EF           	.BYTE $EF
0001CFr 2  2E           	.BYTE $2E
0001D0r 2  1D           	.BYTE $1D
0001D1r 2  1C           	.BYTE $1C
0001D2r 2  1B           	.BYTE $1B
0001D3r 2  1D           	.BYTE $1D
0001D4r 2  1E           	.BYTE $1E
0001D5r 2  1B           	.BYTE $1B
0001D6r 2  16           	.BYTE $16
0001D7r 2  13           	.BYTE $13
0001D8r 2  51           	.BYTE $51
0001D9r 2  12           	.BYTE $12
0001DAr 2  41           	.BYTE $41
0001DBr 2  12           	.BYTE $12
0001DCr 2  21           	.BYTE $21
0001DDr 2  12           	.BYTE $12
0001DEr 2  18           	.BYTE $18
0001DFr 2  1A           	.BYTE $1A
0001E0r 2  1D           	.BYTE $1D
0001E1r 2  AF           	.BYTE $AF
0001E2r 2  1E           	.BYTE $1E
0001E3r 2  1D           	.BYTE $1D
0001E4r 2  3C           	.BYTE $3C
0001E5r 2  2D           	.BYTE $2D
0001E6r 2  4E           	.BYTE $4E
0001E7r 2  1A           	.BYTE $1A
0001E8r 2  14           	.BYTE $14
0001E9r 2  22           	.BYTE $22
0001EAr 2  11           	.BYTE $11
0001EBr 2  20           	.BYTE $20
0001ECr 2  71           	.BYTE $71
0001EDr 2  13           	.BYTE $13
0001EEr 2  15           	.BYTE $15
0001EFr 2  17           	.BYTE $17
0001F0r 2  2C           	.BYTE $2C
0001F1r 2  1D           	.BYTE $1D
0001F2r 2  1E           	.BYTE $1E
0001F3r 2  7F           	.BYTE $7F
0001F4r 2  4D           	.BYTE $4D
0001F5r 2  2E           	.BYTE $2E
0001F6r 2  2D           	.BYTE $2D
0001F7r 2  2E           	.BYTE $2E
0001F8r 2  1D           	.BYTE $1D
0001F9r 2  2E           	.BYTE $2E
0001FAr 2  19           	.BYTE $19
0001FBr 2  23           	.BYTE $23
0001FCr 2  32           	.BYTE $32
0001FDr 2  31           	.BYTE $31
0001FEr 2  22           	.BYTE $22
0001FFr 2  13           	.BYTE $13
000200r 2  15           	.BYTE $15
000201r 2  16           	.BYTE $16
000202r 2  14           	.BYTE $14
000203r 2  17           	.BYTE $17
000204r 2  2E           	.BYTE $2E
000205r 2  3D           	.BYTE $3D
000206r 2  2E           	.BYTE $2E
000207r 2  4F           	.BYTE $4F
000208r 2  2E           	.BYTE $2E
000209r 2  7D           	.BYTE $7D
00020Ar 2  2E           	.BYTE $2E
00020Br 2  1D           	.BYTE $1D
00020Cr 2  2E           	.BYTE $2E
00020Dr 2  1A           	.BYTE $1A
00020Er 2  14           	.BYTE $14
00020Fr 2  43           	.BYTE $43
000210r 2  14           	.BYTE $14
000211r 2  13           	.BYTE $13
000212r 2  14           	.BYTE $14
000213r 2  15           	.BYTE $15
000214r 2  16           	.BYTE $16
000215r 2  17           	.BYTE $17
000216r 2  15           	.BYTE $15
000217r 2  14           	.BYTE $14
000218r 2  18           	.BYTE $18
000219r 2  1D           	.BYTE $1D
00021Ar 2  4E           	.BYTE $4E
00021Br 2  2D           	.BYTE $2D
00021Cr 2  4E           	.BYTE $4E
00021Dr 2  9D           	.BYTE $9D
00021Er 2  4E           	.BYTE $4E
00021Fr 2  1C           	.BYTE $1C
000220r 2  1A           	.BYTE $1A
000221r 2  18           	.BYTE $18
000222r 2  15           	.BYTE $15
000223r 2  14           	.BYTE $14
000224r 2  43           	.BYTE $43
000225r 2  15           	.BYTE $15
000226r 2  26           	.BYTE $26
000227r 2  15           	.BYTE $15
000228r 2  13           	.BYTE $13
000229r 2  16           	.BYTE $16
00022Ar 2  1A           	.BYTE $1A
00022Br 2  3E           	.BYTE $3E
00022Cr 2  8D           	.BYTE $8D
00022Dr 2  00           	.BYTE $00
00022Er 2  04           	.BYTE $04
00022Fr 2  57           	.BYTE $57
000230r 2  4F           	.BYTE $4F
000231r 2  5A           	.BYTE $5A
000232r 2  20           	.BYTE $20
000233r 2  00           	.BYTE $00
000234r 2               
000234r 2  57 6F 7A 20  	.byte "Woz face program end", $0d, $00
000238r 2  66 61 63 65  
00023Cr 2  20 70 72 6F  
00024Ar 2               
00024Ar 1               
00024Ar 1               
00024Ar 1                         .segment "F800"
000000r 1                         ;Test from Apple-1 Operation Manual â€“ printing all ASCII symbols in a loop
000000r 1                         .include "TestFromManual.asm"
000000r 2               ;Test from Apple-1 Operation Manual â€“ printing all ASCII symbols in a loop
000000r 2  A9 00        			LDA #$00
000002r 2  AA           TEST_LOOP: 	TAX
000003r 2  20 EF FF     			JSR ECHO
000006r 2  E8           			INX
000007r 2  8A           			TXA
000008r 2  4C rr rr     			JMP TEST_LOOP
00000Br 2               
00000Br 1               
00000Br 1                         .segment "FA00"
000000r 1                         ;Power-On Self Test (POST)
000000r 1                         .include "POST.asm"
000000r 2               ;KBD             = $D010
000000r 2               ;KBDCR           = $D011
000000r 2               ;DSP             = $D012
000000r 2               ;DSPCR           = $D013
000000r 2               START_TEST = $EA
000000r 2               END_TEST = $EB
000000r 2               
000000r 2               
000000r 2               LED_BLINKS = 5
000000r 2               TEST1_REPEATS = 4
000000r 2               TEST2_REPEATS = 16
000000r 2               TEST61_REPEATS = 8
000000r 2               TEST62_REPEATS = 8
000000r 2               TEST7_REPEATS = 16
000000r 2               POSTOK_REPEATS = 4
000000r 2               
000000r 2               /*
000000r 2               LED_BLINKS = 1
000000r 2               TEST1_REPEATS = 1
000000r 2               TEST2_REPEATS = 1
000000r 2               TEST61_REPEATS = 1
000000r 2               TEST62_REPEATS = 1
000000r 2               TEST7_REPEATS = 1
000000r 2               POSTOK_REPEATS = 1
000000r 2               */
000000r 2               
000000r 2               
000000r 2  EA           POST_START:		NOP
000001r 2  A9 EA        				LDA #START_TEST
000003r 2  8D 12 D0     			    STA DSP
000006r 2               
000006r 2  A9 01        				LDA #%00000001
000008r 2  20 rr rr     				JSR BLINK
00000Br 2               ;Test 1. Memory addresses decoder (blinking in cycle)
00000Br 2  A2 04        MEM_DECODER: 	LDX #TEST1_REPEATS
00000Dr 2  AD 00 FF     LOOPADDR:	 	LDA $FF00
000010r 2  AD 00 E0     			    LDA $E000
000013r 2  AD 00 D0     			    LDA $D000
000016r 2  AD 00 C0     			    LDA $C000
000019r 2  CA           			    DEX
00001Ar 2  D0 F1        			    BNE LOOPADDR
00001Cr 2               
00001Cr 2  A9 02        			    LDA #%00000010
00001Er 2  20 rr rr     				JSR BLINK
000021r 2               ;Test 2. Ports decoder (blinking in cycle)
000021r 2  A9 10        				LDA #TEST2_REPEATS
000023r 2  AA           PORTS_DECODER:  TAX
000024r 2  AC 10 D0     		        LDY KBD
000027r 2  AC 11 D0     		        LDY KBDCR
00002Ar 2  8E 12 D0     		        STX DSP
00002Dr 2  2C 12 D0     		        BIT DSP
000030r 2  CA           		        DEX
000031r 2  8A           		        TXA
000032r 2  D0 EF        		        BNE PORTS_DECODER
000034r 2               
000034r 2  A9 04        		        LDA #%00000100
000036r 2  20 rr rr     				JSR BLINK
000039r 2               ;Test 3. Testing writing to Video port (1->2->4->8->16->32->64->128->256->0)
000039r 2  A9 01                		LDA #%00000001
00003Br 2  8D 12 D0     VIDEO_PORT: 	STA DSP
00003Er 2  0A                   		ASL A ;shifting 1 to the left
00003Fr 2  D0 FA               			BNE VIDEO_PORT
000041r 2               
000041r 2  A9 08               			LDA #%00001000
000043r 2  20 rr rr     				JSR BLINK
000046r 2               ;Test 4. Testing writing to Video port via function call (256->128->64->32->16->8->4->2->1->0)
000046r 2  20 rr rr     				JSR VIDEO_PORT2
000049r 2               
000049r 2               
000049r 2  A9 10        				LDA #%00010000
00004Br 2  20 rr rr     				JSR BLINK
00004Er 2               ;Test 5. Testing RAM with write&read (writing TEST_SYMBOL and testing read for every 4Kb block in 32Kb RAM)
00004Er 2               ;Total blocks tested is 8 (4*8 = 32)
00004Er 2               TEST_SYMBOL = $3E
00004Er 2               
00004Er 2               /*
00004Er 2               RAMTEST: 		CLD
00004Er 2               		        LDX #$00
00004Er 2               		        LDY #$00
00004Er 2               
00004Er 2               		        LDA #$FF
00004Er 2               		        STA $00
00004Er 2               		        LDA #$0F
00004Er 2               		        STA $01
00004Er 2               
00004Er 2               RAMLOOP: 		LDA #TEST_SYMBOL
00004Er 2               		        STA ($00),Y
00004Er 2               		        LDA ($00),Y
00004Er 2               		        CMP #TEST_SYMBOL
00004Er 2               		        BNE ENDTEST
00004Er 2               		        TXA
00004Er 2               		        ASL A
00004Er 2               		        ADC #$01
00004Er 2               		        STA DSP
00004Er 2               		        TAX
00004Er 2               		        LDA $01
00004Er 2               		        ADC #$10
00004Er 2               		        STA $01
00004Er 2               		        JMP RAMLOOP
00004Er 2               
00004Er 2               		        */
00004Er 2               
00004Er 2  A9 20        		        LDA #%00100000
000050r 2  20 rr rr     				JSR BLINK
000053r 2               ;Test 6. Testing BIT7 ports - keyboard and video
000053r 2               BIT7MASK     = %10000000
000053r 2               KBD7MASK     = %00000111
000053r 2               DSP7MASK     = %00111111
000053r 2               ;Test 6.1. Testing keyboard BIT7 port read (turn on 3 LEDs on the left and show BIT7 in the last LED)
000053r 2               
000053r 2  A2 08        KBDBIT7: 		LDX #TEST61_REPEATS
000055r 2  A9 07        		        LDA #KBD7MASK
000057r 2  8D 12 D0     		        STA DSP
00005Ar 2               KBD7LOOP:
00005Ar 2  AD 11 D0     		        LDA KBDCR
00005Dr 2  29 80        		        AND #BIT7MASK
00005Fr 2  09 07        		        ORA #KBD7MASK
000061r 2  8D 12 D0     		        STA DSP
000064r 2  CA           		        DEX
000065r 2  D0 F3        		        BNE KBD7LOOP
000067r 2               ;Test 6.2. Testing video BIT7 port read (turn on 6 LEDs on the left and show BIT7 in the last LED)
000067r 2               
000067r 2  A2 08        DSPBIT7: 		LDX #TEST62_REPEATS
000069r 2  A9 3F        		        LDA #DSP7MASK
00006Br 2  8D 12 D0     		        STA DSP
00006Er 2               DSP7LOOP:
00006Er 2  AD 12 D0     		        LDA DSP
000071r 2  29 80        		        AND #BIT7MASK
000073r 2  09 3F        		        ORA #DSP7MASK
000075r 2  8D 12 D0     		        STA DSP
000078r 2  CA           		        DEX
000079r 2  D0 F3        		        BNE DSP7LOOP
00007Br 2               
00007Br 2               
00007Br 2  A9 40        		        LDA #%01000000
00007Dr 2  20 rr rr     				JSR BLINK
000080r 2               ;Test 7. Testing keyboard port read and write to Video port
000080r 2  A2 10        KBDTODSP: 		LDX #TEST7_REPEATS
000082r 2  A9 00        		        LDA #$00
000084r 2  8D 12 D0     		        STA DSP
000087r 2               KBDDSPLOOP:
000087r 2  AD 10 D0     		        LDA KBD
00008Ar 2  8D 12 D0     		        STA DSP
00008Dr 2  CA           		        DEX
00008Er 2  D0 F7        		        BNE KBDDSPLOOP
000090r 2               
000090r 2               ;POST success and end
000090r 2               
000090r 2  A2 04        ENDPOST: 		LDX #POSTOK_REPEATS
000092r 2               ENDLOOP:
000092r 2  A9 55               			LDA #%01010101
000094r 2  8D 12 D0     		        STA DSP
000097r 2  EA           		        NOP
000098r 2  EA           		        NOP
000099r 2  A9 AA        		        LDA #%10101010
00009Br 2  8D 12 D0     		        STA DSP
00009Er 2  EA           		        NOP
00009Fr 2  EA           		        NOP
0000A0r 2  CA           		        DEX
0000A1r 2  D0 EF        		        BNE ENDLOOP
0000A3r 2               
0000A3r 2  EA           		        NOP
0000A4r 2  EA           		        NOP
0000A5r 2               
0000A5r 2               ;printing ASCII table
0000A5r 2  20 rr rr     		        JSR ASCII_ECHO
0000A8r 2               
0000A8r 2  EA           ENDTEST: 		NOP
0000A9r 2  EA                   		NOP
0000AAr 2  A9 EB                		LDA #END_TEST
0000ACr 2  20 EF FF             		JSR ECHO 	;writing END_TEST to let video driver know that tests are over
0000AFr 2               
0000AFr 2  A2 00                		LDX #$00
0000B1r 2               PRINT_MSG:
0000B1r 2  BD rr rr     				LDA POSTCompletedText, X
0000B4r 2  F0 07        				BEQ TO_WOZ_MON	;end printing at the end of the string (\n=0)
0000B6r 2  20 EF FF     				JSR ECHO
0000B9r 2  E8           				INX
0000BAr 2  4C rr rr     				JMP PRINT_MSG
0000BDr 2               
0000BDr 2  4C 00 FF      TO_WOZ_MON:	JMP RESET	;start Woz Monitor (operating system)
0000C0r 2               
0000C0r 2               ;------------------------------------------------------
0000C0r 2               ; POST subroutines
0000C0r 2               ;------------------------------------------------------
0000C0r 2               ;blinking LEDs in Video port
0000C0r 2  A9 80        VIDEO_PORT2: 	LDA #%10000000
0000C2r 2  8D 12 D0     TEST2:   		STA DSP
0000C5r 2  4A                   		LSR A
0000C6r 2  D0 FA                		BNE TEST2
0000C8r 2  60                  			RTS
0000C9r 2               
0000C9r 2               ;blink with a LED in a position from A register
0000C9r 2               TURN_OFF = %00000000
0000C9r 2  A2 05        BLINK:			LDX #LED_BLINKS
0000CBr 2  A8           				TAY	;save A
0000CCr 2  98           NEXT_BLINK:		TYA ;restore A
0000CDr 2  8D 12 D0     				STA DSP
0000D0r 2  EA           				NOP
0000D1r 2  EA           				NOP
0000D2r 2  A9 00        				LDA #TURN_OFF
0000D4r 2  8D 12 D0     				STA DSP
0000D7r 2  EA           				NOP
0000D8r 2  EA           				NOP
0000D9r 2  CA           				DEX
0000DAr 2  D0 F0        				BNE NEXT_BLINK
0000DCr 2  60           				RTS
0000DDr 2               
0000DDr 2               ;printing visible symbols of ACSII table via ECHO function from Woz Monitor
0000DDr 2               PRINT_ASCII:
0000DDr 2  A0 20        			    LDY #32
0000DFr 2  A2 5F        			    LDX #95 ;80 in hex = 127 in decimal
0000E1r 2               ASCII_ECHO:
0000E1r 2  2C 12 D0     			    BIT DSP
0000E4r 2  30 FB        			    BMI ASCII_ECHO
0000E6r 2  8C 12 D0     			    STY DSP
0000E9r 2  C8           			    INY
0000EAr 2  CA           			    DEX
0000EBr 2  D0 F4        			    BNE ASCII_ECHO
0000EDr 2  60           			    RTS
0000EEr 2               
0000EEr 2  2C 12 D0     CHAR_ECHO:	   	BIT DSP
0000F1r 2  30 FB        			    BMI CHAR_ECHO
0000F3r 2  8D 12 D0     			    STA DSP
0000F6r 2  60           			    RTS
0000F7r 2               
0000F7r 2               POSTCompletedText:
0000F7r 2  0D 0D 50 4F  	.byte $0d, $0d, "POST ok (v.1.0). SmartyKit 1 is ready.", $0d, $0d, $00
0000FBr 2  53 54 20 6F  
0000FFr 2  6B 20 28 76  
000122r 2               
000122r 1               
000122r 1                          .segment "FC00"
000000r 1                         ;printing 8x8 picture in the center with '*'
000000r 1                         .include "8x8art.asm"
000000r 2               ;printing 8x8 picture in the center with '*'
000000r 2               PIC_WIDTH = 8
000000r 2               PIC_HEIGHT = 8
000000r 2               OFFSET_X = (40 - PIC_WIDTH)/2
000000r 2               PIC_ADDRESS = $1111
000000r 2               ROW_ADDRESS = PIC_ADDRESS + PIC_HEIGHT
000000r 2               
000000r 2               
000000r 2               ; Y - row number
000000r 2               ; X - column (pixel) number
000000r 2  20 rr rr     				JSR NEXT_ROW
000003r 2  A9 00        				LDA #$0
000005r 2  8D 19 11     				STA ROW_ADDRESS	;initialize row counter with 0
000008r 2  A0 08        				LDY #PIC_HEIGHT
00000Ar 2               
00000Ar 2  20 rr rr     ROWS_LOOP:		JSR PRINT_OFFSET
00000Dr 2  AD 19 11     				LDA ROW_ADDRESS
000010r 2  AA           				TAX
000011r 2  BD 11 11     				LDA PIC_ADDRESS, X
000014r 2  A2 08        				LDX #PIC_WIDTH
000016r 2  0A           NEXT_PIXEL:		ASL
000017r 2  90 06        				BCC NO_PIXEL
000019r 2  20 rr rr     				JSR PRINT_STAR
00001Cr 2  4C rr rr     				JMP AFTER_PIXEL
00001Fr 2  20 rr rr     NO_PIXEL:		JSR PRINT_BLANK
000022r 2  CA           AFTER_PIXEL:	DEX
000023r 2  D0 F1        				BNE NEXT_PIXEL
000025r 2  20 rr rr     				JSR NEXT_ROW
000028r 2  EE 19 11     				INC ROW_ADDRESS
00002Br 2  88           				DEY
00002Cr 2  D0 DC        				BNE ROWS_LOOP
00002Er 2  20 rr rr     				JSR NEXT_ROW
000031r 2  4C 00 FF     				JMP RESET
000034r 2               
000034r 2               ;printing offset subroutine (optional: save registers A and X)
000034r 2  48           PRINT_OFFSET:	PHA ;save A
000035r 2  8A           				TXA ;X->A
000036r 2  48           				PHA	;save X
000037r 2  A2 10        				LDX #OFFSET_X
000039r 2  A9 20        OFFSET_LOOP:	LDA #' '
00003Br 2  20 EF FF     				JSR ECHO
00003Er 2  CA           			    DEX
00003Fr 2  D0 F8        			    BNE OFFSET_LOOP
000041r 2               
000041r 2  68           			    PLA ;restore X
000042r 2  AA           			    TAX ;A->X
000043r 2  68           			    PLA	;restore A
000044r 2  60           			    RTS
000045r 2               
000045r 2  48           PRINT_STAR:		PHA
000046r 2  A9 2A        				LDA #'*'
000048r 2  20 EF FF     				JSR ECHO
00004Br 2  68           				PLA
00004Cr 2  60           				RTS
00004Dr 2  48           PRINT_BLANK:	PHA
00004Er 2  A9 20        				LDA #' '
000050r 2  20 EF FF     				JSR ECHO
000053r 2  68           				PLA
000054r 2  60           				RTS
000055r 2  48           NEXT_ROW:		PHA
000056r 2  A9 0D        				LDA #$0d
000058r 2  20 EF FF     				JSR ECHO
00005Br 2  68           				PLA
00005Cr 2  60           				RTS
00005Dr 2               ;from HeartPicture
00005Dr 2               ;to PIC_ADDRESS ($88)
00005Dr 2  48           COPY_HEART:		PHA
00005Er 2  8A           				TXA
00005Fr 2  48           				PHA
000060r 2               
000060r 2  A2 08        				LDX #PIC_HEIGHT
000062r 2  BD rr rr     COPY_LOOP:		LDA HeartPicture, X
000065r 2  9D 11 11     				STA PIC_ADDRESS, X
000068r 2  CA           				DEX
000069r 2  10 F7        				BPL COPY_LOOP
00006Br 2               
00006Br 2  68           				PLA
00006Cr 2  AA           				TAX
00006Dr 2  68           				PLA
00006Er 2  60           				RTS
00006Fr 2               
00006Fr 2               
00006Fr 2               HeartPicture:
00006Fr 2  00                     .byte          %00000000
000070r 2  66                     .byte          %01100110
000071r 2  FF                     .byte          %11111111
000072r 2  FF                     .byte          %11111111
000073r 2  FF                     .byte          %11111111
000074r 2  7E                     .byte          %01111110
000075r 2  3C                     .byte          %00111100
000076r 2  18                     .byte          %00011000
000077r 2  3C 42 A5 81  SmileyPicture:   .byte $3c, $42, $a5, $81, $a5, $99, $42, $3c
00007Br 2  A5 99 42 3C  
00007Fr 2  88 A8 50 07  WozPicture:      .byte $88, $a8, $50, $07, $61, $92, $94, $67
000083r 2  61 92 94 67  
000087r 2  FF 81 BD BD  SmartyLogo:		 .byte $ff, $81, $bd, $bd, $bd, $bd, $81, $ff
00008Br 2  BD BD 81 FF  
00008Fr 2  18 24 24 24  RocketPicture:	 .byte $18, $24, $24, $24, $7e, $a5, $FF, $a5
000093r 2  7E A5 FF A5  
000097r 2  38 2A 38 20  	.byte "8*8 Pixel Art program end", $0d, $00
00009Br 2  50 69 78 65  
00009Fr 2  6C 20 41 72  
0000B2r 2               
0000B2r 1               
0000B2r 1                         .segment "FD00"
000000r 1                         ;Printing 'Hello, World!'
000000r 1                         .include "HelloWorld.asm"
000000r 2               ;printing 'Hello, World!'
000000r 2               ;More about 'Hello, World!' program: https://en.wikipedia.org/wiki/%22Hello,_World!%22_program
000000r 2  A2 00        	LDX #00
000002r 2               PRINT_CHAR:
000002r 2  BD rr rr     	LDA HelloWorldText, X
000005r 2  F0 07        	BEQ END_PRINT	;end printing at the end of the string (\n=0)
000007r 2  20 EF FF     	JSR ECHO
00000Ar 2  E8           	INX
00000Br 2  4C rr rr     	JMP PRINT_CHAR
00000Er 2               END_PRINT:
00000Er 2  4C 00 FF     	JMP RESET	;return to Woz Monitor
000011r 2               
000011r 2               HelloWorldText:
000011r 2  0D 48 65 6C  	.byte $0d, "Hello, World!", $0d, "This is SmartyKit 1.", $0d, $0d, $00
000015r 2  6C 6F 2C 20  
000019r 2  57 6F 72 6C  
000037r 2               
000037r 1               
000037r 1                         .segment "FF00"
000000r 1                         .include "Woz_Monitor.asm"
000000r 2               ;  The WOZ Monitor for the Apple 1
000000r 2               ;  Written by Steve Wozniak in 1976
000000r 2               
000000r 2               
000000r 2               ; Page 0 Variables
000000r 2               
000000r 2               XAML            = $24           ;  Last "opened" location Low
000000r 2               XAMH            = $25           ;  Last "opened" location High
000000r 2               STL             = $26           ;  Store address Low
000000r 2               STH             = $27           ;  Store address High
000000r 2               L               = $28           ;  Hex value parsing Low
000000r 2               H               = $29           ;  Hex value parsing High
000000r 2               YSAV            = $2A           ;  Used to see if hex value is given
000000r 2               MODE            = $2B           ;  $00=XAM, $7F=STOR, $AE=BLOCK XAM
000000r 2               
000000r 2               
000000r 2               ; Other Variables
000000r 2               
000000r 2               IN              = $0200         ;  Input buffer to $027F
000000r 2               KBD             = $D010         ;  PIA.A keyboard input
000000r 2               KBDCR           = $D011         ;  PIA.A keyboard control register
000000r 2               DSP             = $D012         ;  PIA.B display output register
000000r 2               DSPCR           = $D013         ;  PIA.B display control register
000000r 2               
000000r 2                              .org $FF00
00FF00  2                              .export RESET
00FF00  2               
00FF00  2  D8           RESET:          CLD             ; Clear decimal arithmetic mode.
00FF01  2  58                           CLI
00FF02  2  A0 7F                        LDY #$7F        ; Mask for DSP data direction register.
00FF04  2  8C 12 D0                     STY DSP         ; Set it up.
00FF07  2  A9 A7                        LDA #$A7        ; KBD and DSP control register mask.
00FF09  2  8D 11 D0                     STA KBDCR       ; Enable interrupts, set CA1, CB1, for
00FF0C  2  8D 13 D0                     STA DSPCR       ; positive edge sense/output mode.
00FF0F  2  C9 DF        NOTCR:          CMP #'_'+$80    ; "_"?
00FF11  2  F0 13                        BEQ BACKSPACE   ; Yes.
00FF13  2  C9 9B                        CMP #$9B        ; ESC?
00FF15  2  F0 03                        BEQ ESCAPE      ; Yes.
00FF17  2  C8                           INY             ; Advance text index.
00FF18  2  10 0F                        BPL NEXTCHAR    ; Auto ESC if > 127.
00FF1A  2  A9 DC        ESCAPE:         LDA #'\'+$80    ; "\".
00FF1C  2  20 EF FF                     JSR ECHO        ; Output it.
00FF1F  2  A9 8D        GETLINE:        LDA #$8D        ; CR.
00FF21  2  20 EF FF                     JSR ECHO        ; Output it.
00FF24  2  A0 01                        LDY #$01        ; Initialize text index.
00FF26  2  88           BACKSPACE:      DEY             ; Back up text index.
00FF27  2  30 F6                        BMI GETLINE     ; Beyond start of line, reinitialize.
00FF29  2  AD 11 D0     NEXTCHAR:       LDA KBDCR       ; Key ready?
00FF2C  2  10 FB                        BPL NEXTCHAR    ; Loop until ready.
00FF2E  2  AD 10 D0                     LDA KBD         ; Load character. B7 should be ‘1’.
00FF31  2  99 00 02                     STA IN,Y        ; Add to text buffer.
00FF34  2  20 EF FF                     JSR ECHO        ; Display character.
00FF37  2  C9 8D                        CMP #$8D        ; CR?
00FF39  2  D0 D4                        BNE NOTCR       ; No.
00FF3B  2  A0 FF                        LDY #$FF        ; Reset text index.
00FF3D  2  A9 00                        LDA #$00        ; For XAM mode.
00FF3F  2  AA                           TAX             ; 0->X.
00FF40  2  0A           SETSTOR:        ASL             ; Leaves $7B if setting STOR mode.
00FF41  2  85 2B        SETMODE:        STA MODE        ; $00=XAM $7B=STOR $AE=BLOK XAM
00FF43  2  C8           BLSKIP:         INY             ; Advance text index.
00FF44  2  B9 00 02     NEXTITEM:       LDA IN,Y        ; Get character.
00FF47  2  C9 8D                        CMP #$8D        ; CR?
00FF49  2  F0 D4                        BEQ GETLINE     ; Yes, done this line.
00FF4B  2  C9 AE                        CMP #'.'+$80    ; "."?
00FF4D  2  90 F4                        BCC BLSKIP      ; Skip delimiter.
00FF4F  2  F0 F0                        BEQ SETMODE     ; Yes. Set STOR mode.
00FF51  2  C9 BA                        CMP #':'+$80    ; ":"?
00FF53  2  F0 EB                        BEQ SETSTOR     ; Yes. Set STOR mode.
00FF55  2  C9 D2                        CMP #'R'+$80    ; "R"?
00FF57  2  F0 3B                        BEQ RUN         ; Yes. Run user program.
00FF59  2  86 28                        STX L           ; $00-> L.
00FF5B  2  86 29                        STX H           ; and H.
00FF5D  2  84 2A                        STY YSAV        ; Save Y for comparison.
00FF5F  2  B9 00 02     NEXTHEX:        LDA IN,Y        ; Get character for hex test.
00FF62  2  49 B0                        EOR #$B0        ; Map digits to $0-9.
00FF64  2  C9 0A                        CMP #$0A        ; Digit?
00FF66  2  90 06                        BCC DIG         ; Yes.
00FF68  2  69 88                        ADC #$88        ; Map letter "A"-"F" to $FA-FF.
00FF6A  2  C9 FA                        CMP #$FA        ; Hex letter?
00FF6C  2  90 11                        BCC NOTHEX      ; No, character not hex.
00FF6E  2  0A           DIG:            ASL
00FF6F  2  0A                           ASL             ; Hex digit to MSD of A.
00FF70  2  0A                           ASL
00FF71  2  0A                           ASL
00FF72  2  A2 04                        LDX #$04        ; Shift count.
00FF74  2  0A           HEXSHIFT:       ASL             ; Hex digit left, MSB to carry.
00FF75  2  26 28                        ROL L           ; Rotate into LSD.
00FF77  2  26 29                        ROL H           ;  Rotate into MSD’s.
00FF79  2  CA                           DEX             ; Done 4 shifts?
00FF7A  2  D0 F8                        BNE HEXSHIFT    ; No, loop.
00FF7C  2  C8                           INY             ; Advance text index.
00FF7D  2  D0 E0                        BNE NEXTHEX     ; Always taken. Check next char for hex.
00FF7F  2  C4 2A        NOTHEX:         CPY YSAV        ; Check if L, H empty (no hex digits).
00FF81  2  F0 97                        BEQ ESCAPE      ; Yes, generate ESC sequence.
00FF83  2  24 2B                        BIT MODE        ; Test MODE byte.
00FF85  2  50 10                        BVC NOTSTOR     ;  B6=0 STOR 1 for XAM & BLOCK XAM
00FF87  2  A5 28                        LDA L           ; LSD’s of hex data.
00FF89  2  81 26                        STA (STL,X)     ; Store at current ‘store index’.
00FF8B  2  E6 26                        INC STL         ; Increment store index.
00FF8D  2  D0 B5                        BNE NEXTITEM    ; Get next item. (no carry).
00FF8F  2  E6 27                        INC STH         ; Add carry to ‘store index’ high order.
00FF91  2  4C 44 FF     TONEXTITEM:     JMP NEXTITEM    ; Get next command item.
00FF94  2  6C 24 00     RUN:            JMP (XAML)      ; Run at current XAM index.
00FF97  2  30 2B        NOTSTOR:        BMI XAMNEXT     ; B7=0 for XAM, 1 for BLOCK XAM.
00FF99  2  A2 02                        LDX #$02        ; Byte count.
00FF9B  2  B5 27        SETADR:         LDA L-1,X       ; Copy hex data to
00FF9D  2  95 25                        STA STL-1,X     ; ‘store index’.
00FF9F  2  95 23                        STA XAML-1,X    ; And to ‘XAM index’.
00FFA1  2  CA                           DEX             ; Next of 2 bytes.
00FFA2  2  D0 F7                        BNE SETADR      ; Loop unless X=0.
00FFA4  2  D0 14        NXTPRNT:        BNE PRDATA      ; NE means no address to print.
00FFA6  2  A9 8D                        LDA #$8D        ; CR.
00FFA8  2  20 EF FF                     JSR ECHO        ; Output it.
00FFAB  2  A5 25                        LDA XAMH        ; ‘Examine index’ high-order byte.
00FFAD  2  20 DC FF                     JSR PRBYTE      ; Output it in hex format.
00FFB0  2  A5 24                        LDA XAML        ; Low-order ‘examine index’ byte.
00FFB2  2  20 DC FF                     JSR PRBYTE      ; Output it in hex format.
00FFB5  2  A9 BA                        LDA #':'+$80    ; ":".
00FFB7  2  20 EF FF                     JSR ECHO        ; Output it.
00FFBA  2  A9 A0        PRDATA:         LDA #$A0        ; Blank.
00FFBC  2  20 EF FF                     JSR ECHO        ; Output it.
00FFBF  2  A1 24                        LDA (XAML,X)    ; Get data byte at ‘examine index’.
00FFC1  2  20 DC FF                     JSR PRBYTE      ; Output it in hex format.
00FFC4  2  86 2B        XAMNEXT:        STX MODE        ; 0->MODE (XAM mode).
00FFC6  2  A5 24                        LDA XAML
00FFC8  2  C5 28                        CMP L           ; Compare ‘examine index’ to hex data.
00FFCA  2  A5 25                        LDA XAMH
00FFCC  2  E5 29                        SBC H
00FFCE  2  B0 C1                        BCS TONEXTITEM  ; Not less, so no more data to output.
00FFD0  2  E6 24                        INC XAML
00FFD2  2  D0 02                        BNE MOD8CHK     ; Increment ‘examine index’.
00FFD4  2  E6 25                        INC XAMH
00FFD6  2  A5 24        MOD8CHK:        LDA XAML        ; Check low-order ‘examine index’ byte
00FFD8  2  29 07                        AND #$07        ; For MOD 8=0
00FFDA  2  10 C8                        BPL NXTPRNT     ; Always taken.
00FFDC  2  48           PRBYTE:         PHA             ; Save A for LSD.
00FFDD  2  4A                           LSR
00FFDE  2  4A                           LSR
00FFDF  2  4A                           LSR             ; MSD to LSD position.
00FFE0  2  4A                           LSR
00FFE1  2  20 E5 FF                     JSR PRHEX       ; Output hex digit.
00FFE4  2  68                           PLA             ; Restore A.
00FFE5  2  29 0F        PRHEX:          AND #$0F        ; Mask LSD for hex print.
00FFE7  2  09 B0                        ORA #'0'+$80    ; Add "0".
00FFE9  2  C9 BA                        CMP #$BA        ; Digit?
00FFEB  2  90 02                        BCC ECHO        ; Yes, output it.
00FFED  2  69 06                        ADC #$06        ; Add offset for letter.
00FFEF  2  2C 12 D0     ECHO:           BIT DSP         ; bit (B7) cleared yet?
00FFF2  2  30 FB                        BMI ECHO        ; No, wait for display.
00FFF4  2  8D 12 D0                     STA DSP         ; Output character. Sets DA.
00FFF7  2  60                           RTS             ; Return.
00FFF8  2               
00FFF8  2  40            NMI:           RTI             ; simple Interrupt Service Routine(ISR)
00FFF9  2  40            IRQ:           RTI             ; simple Interrupt Service Routine(ISR)
00FFFA  2               
00FFFA  1               
00FFFA  1                         .segment "VECTORS"
00FFFA  1                         ; Interrupt Vectors
00FFFA  1  F8 FF                  .WORD NMI            ; NMI
00FFFC  1  rr rr                  .WORD POST_START     ; RESET (starting point in Woz Monitor) or POST (test)
00FFFE  1  F9 FF                  .WORD IRQ            ; BRK/IRQ
010000  1               
010000  1               
010000  1               
