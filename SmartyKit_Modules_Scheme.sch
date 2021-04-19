EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "SmartyKit 1: modules connections"
Date "2020-11-26"
Rev "1.0"
Comp "Sergey Panarin (SmartyKit)"
Comment1 "sergey@smartykit.io"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_01x06 J44
U 1 1 5FC30E7B
P 6900 5900
F 0 "J44" H 6975 6225 50  0000 R CNN
F 1 "Conn_01x06" V 7025 6125 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical_SMD_Pin1Left" H 6900 5900 50  0001 C CNN
F 3 "~" H 6900 5900 50  0001 C CNN
	1    6900 5900
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J45
U 1 1 5FC31E9C
P 7450 5900
F 0 "J45" H 7525 6000 50  0000 R CNN
F 1 "Conn_01x02" V 7575 6000 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical_SMD_Pin1Left" H 7450 5900 50  0001 C CNN
F 3 "~" H 7450 5900 50  0001 C CNN
	1    7450 5900
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR054
U 1 1 5FC3240D
P 7550 6175
F 0 "#PWR054" H 7550 5925 50  0001 C CNN
F 1 "GND" H 7555 6002 50  0000 C CNN
F 2 "" H 7550 6175 50  0001 C CNN
F 3 "" H 7550 6175 50  0001 C CNN
	1    7550 6175
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR053
U 1 1 5FC32876
P 7450 6100
F 0 "#PWR053" H 7450 5950 50  0001 C CNN
F 1 "VCC" H 7465 6273 50  0000 C CNN
F 2 "" H 7450 6100 50  0001 C CNN
F 3 "" H 7450 6100 50  0001 C CNN
	1    7450 6100
	-1   0    0    1   
$EndComp
Text Notes 6450 6425 0    50   ~ 0
MOD5. NAND (R/W)
NoConn ~ 7200 6100
NoConn ~ 7100 6100
NoConn ~ 7000 6100
NoConn ~ 6900 6100
NoConn ~ 6800 6100
NoConn ~ 6700 6100
Text GLabel 7450 5225 1    50   Output ~ 0
W_
Text GLabel 7150 5225 1    50   Output ~ 0
R_
Text GLabel 6950 5250 1    50   Input ~ 0
RW
Wire Wire Line
	6950 5525 6950 5475
Wire Wire Line
	7050 5525 7050 5475
Wire Wire Line
	7050 5475 6950 5475
Connection ~ 6950 5475
Text GLabel 7350 5225 1    50   Input ~ 0
F2
$Comp
L Connector_Generic:Conn_01x06 J39
U 1 1 5FC30B8D
P 7150 5725
F 0 "J39" H 7200 6050 50  0000 R CNN
F 1 "Conn_01x06" V 7275 5950 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical_SMD_Pin1Left" H 7150 5725 50  0001 C CNN
F 3 "~" H 7150 5725 50  0001 C CNN
	1    7150 5725
	0    -1   1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J51
U 1 1 5FC2F020
P 5075 7200
F 0 "J51" H 5125 7400 50  0000 R CNN
F 1 "Conn_01x03" V 5200 7425 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical_SMD_Pin1Left" H 5075 7200 50  0001 C CNN
F 3 "~" H 5075 7200 50  0001 C CNN
	1    5075 7200
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J52
U 1 1 5FC2FAAE
P 5375 7200
F 0 "J52" H 5425 7300 50  0000 R CNN
F 1 "Conn_01x02" V 5500 7350 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical_SMD_Pin1Left" H 5375 7200 50  0001 C CNN
F 3 "~" H 5375 7200 50  0001 C CNN
	1    5375 7200
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J49
U 1 1 5FC2FEBB
P 4975 7025
F 0 "J49" H 5050 7425 50  0000 R CNN
F 1 "Conn_01x08" V 5075 7275 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical_SMD_Pin1Left" H 4975 7025 50  0001 C CNN
F 3 "~" H 4975 7025 50  0001 C CNN
	1    4975 7025
	0    -1   1    0   
$EndComp
Text Notes 4450 7725 0    50   ~ 0
MOD2. Memory decoder
NoConn ~ 4975 6825
NoConn ~ 4875 6825
NoConn ~ 4775 6825
NoConn ~ 4675 6825
$Comp
L power:GND #PWR060
U 1 1 5FC34139
P 5475 7475
F 0 "#PWR060" H 5475 7225 50  0001 C CNN
F 1 "GND" H 5480 7302 50  0000 C CNN
F 2 "" H 5475 7475 50  0001 C CNN
F 3 "" H 5475 7475 50  0001 C CNN
	1    5475 7475
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR059
U 1 1 5FC34341
P 5375 7400
F 0 "#PWR059" H 5375 7250 50  0001 C CNN
F 1 "VCC" H 5390 7573 50  0000 C CNN
F 2 "" H 5375 7400 50  0001 C CNN
F 3 "" H 5375 7400 50  0001 C CNN
	1    5375 7400
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J50
U 1 1 5FC346CD
P 4675 7200
F 0 "J50" H 4725 7400 50  0000 R CNN
F 1 "Conn_01x03" V 4800 7425 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical_SMD_Pin1Left" H 4675 7200 50  0001 C CNN
F 3 "~" H 4675 7200 50  0001 C CNN
	1    4675 7200
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR061
U 1 1 5FC35C79
P 5175 7425
F 0 "#PWR061" H 5175 7175 50  0001 C CNN
F 1 "GND" H 5180 7252 50  0000 C CNN
F 2 "" H 5175 7425 50  0001 C CNN
F 3 "" H 5175 7425 50  0001 C CNN
	1    5175 7425
	1    0    0    -1  
$EndComp
Text Notes 2300 6425 0    50   ~ 0
MOD4. CPU 6502
$Comp
L Connector_Generic:Conn_01x16 J40
U 1 1 5FC46E24
P 3150 5900
F 0 "J40" H 3225 6700 50  0000 R CNN
F 1 "Conn_01x16" V 3275 6125 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x16_P2.54mm_Vertical_SMD_Pin1Left" H 3150 5900 50  0001 C CNN
F 3 "~" H 3150 5900 50  0001 C CNN
	1    3150 5900
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J41
U 1 1 5FC48A29
P 4475 5900
F 0 "J41" H 4550 6300 50  0000 R CNN
F 1 "Conn_01x08" V 4600 6100 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical_SMD_Pin1Left" H 4475 5900 50  0001 C CNN
F 3 "~" H 4475 5900 50  0001 C CNN
	1    4475 5900
	0    -1   -1   0   
$EndComp
Text GLabel 2450 6150 3    50   Output ~ 0
A0
Text GLabel 2550 6150 3    50   Output ~ 0
A1
Text GLabel 2650 6150 3    50   Output ~ 0
A2
Text GLabel 2750 6150 3    50   Output ~ 0
A3
Text GLabel 2850 6150 3    50   Output ~ 0
A4
Text GLabel 2950 6150 3    50   Output ~ 0
A5
Text GLabel 3050 6150 3    50   Output ~ 0
A6
Text GLabel 3150 6150 3    50   Output ~ 0
A7
Text GLabel 3250 6150 3    50   Output ~ 0
A8
Text GLabel 3350 6150 3    50   Output ~ 0
A9
Text GLabel 3450 6150 3    50   Output ~ 0
A10
Text GLabel 3550 6150 3    50   Output ~ 0
A11
Text GLabel 3650 6150 3    50   Output ~ 0
A12
Text GLabel 3750 6150 3    50   Output ~ 0
A13
Text GLabel 3850 6150 3    50   Output ~ 0
A14
Text GLabel 3950 6150 3    50   Output ~ 0
A15
Text GLabel 4175 6150 3    50   Output ~ 0
D0
Text GLabel 4275 6150 3    50   Output ~ 0
D1
Text GLabel 4375 6150 3    50   Output ~ 0
D2
Text GLabel 4475 6150 3    50   Output ~ 0
D3
Text GLabel 4575 6150 3    50   Output ~ 0
D4
Text GLabel 4675 6150 3    50   Output ~ 0
D5
Text GLabel 4775 6150 3    50   Output ~ 0
D6
Text GLabel 4875 6150 3    50   Output ~ 0
D7
Wire Wire Line
	2450 6100 2450 6150
Wire Wire Line
	2550 6100 2550 6150
Wire Wire Line
	2650 6100 2650 6150
Wire Wire Line
	2750 6100 2750 6150
Wire Wire Line
	2850 6100 2850 6150
Wire Wire Line
	2950 6100 2950 6150
Wire Wire Line
	3050 6100 3050 6150
Wire Wire Line
	3150 6100 3150 6150
Wire Wire Line
	3250 6100 3250 6150
Wire Wire Line
	3350 6100 3350 6150
Wire Wire Line
	3450 6100 3450 6150
Wire Wire Line
	3550 6100 3550 6150
Wire Wire Line
	3650 6100 3650 6150
Wire Wire Line
	3750 6100 3750 6150
Wire Wire Line
	3850 6100 3850 6150
Wire Wire Line
	3950 6100 3950 6150
Wire Wire Line
	4175 6100 4175 6150
Wire Wire Line
	4275 6100 4275 6150
Wire Wire Line
	4375 6100 4375 6150
Wire Wire Line
	4475 6100 4475 6150
Wire Wire Line
	4575 6100 4575 6150
Wire Wire Line
	4675 6100 4675 6150
Wire Wire Line
	4775 6100 4775 6150
Wire Wire Line
	4875 6100 4875 6150
Text Notes 750  7725 0    50   ~ 0
MOD1. Memory (ROM+RAM)
$Comp
L Connector_Generic:Conn_01x08 J54
U 1 1 5FCCB6F5
P 2850 7550
F 0 "J54" H 2900 7950 50  0000 R CNN
F 1 "Conn_01x08" V 2975 7750 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical_SMD_Pin1Left" H 2850 7550 50  0001 C CNN
F 3 "~" H 2850 7550 50  0001 C CNN
	1    2850 7550
	0    -1   1    0   
$EndComp
Text GLabel 3250 7300 1    50   Output ~ 0
D7
Text GLabel 3150 7300 1    50   Output ~ 0
D6
Text GLabel 3050 7300 1    50   Output ~ 0
D5
Text GLabel 2950 7300 1    50   Output ~ 0
D4
Text GLabel 2850 7300 1    50   Output ~ 0
D3
Text GLabel 2750 7300 1    50   Output ~ 0
D2
Text GLabel 2650 7300 1    50   Output ~ 0
D1
Text GLabel 2550 7300 1    50   Output ~ 0
D0
Wire Wire Line
	2350 7350 2350 7325
Wire Wire Line
	2250 7350 2250 7300
Wire Wire Line
	2150 7350 2150 7300
Wire Wire Line
	2050 7350 2050 7300
Wire Wire Line
	1950 7350 1950 7300
Wire Wire Line
	1850 7350 1850 7300
Wire Wire Line
	1750 7350 1750 7300
Wire Wire Line
	1650 7350 1650 7300
Wire Wire Line
	1550 7350 1550 7300
Wire Wire Line
	1450 7350 1450 7300
Wire Wire Line
	1350 7350 1350 7300
Wire Wire Line
	1250 7350 1250 7300
Wire Wire Line
	1150 7350 1150 7300
Wire Wire Line
	1050 7350 1050 7300
Wire Wire Line
	950  7350 950  7300
Wire Wire Line
	850  7350 850  7300
Wire Wire Line
	3250 7350 3250 7300
Wire Wire Line
	3150 7350 3150 7300
Wire Wire Line
	3050 7350 3050 7300
Wire Wire Line
	2950 7350 2950 7300
Wire Wire Line
	2850 7350 2850 7300
Wire Wire Line
	2750 7350 2750 7300
Wire Wire Line
	2650 7350 2650 7300
Wire Wire Line
	2550 7350 2550 7300
$Comp
L Connector_Generic:Conn_01x16 J53
U 1 1 5FCCB6EF
P 1550 7550
F 0 "J53" H 1600 8350 50  0000 R CNN
F 1 "Conn_01x16" V 1675 7775 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x16_P2.54mm_Vertical_SMD_Pin1Left" H 1550 7550 50  0001 C CNN
F 3 "~" H 1550 7550 50  0001 C CNN
	1    1550 7550
	0    -1   1    0   
$EndComp
Text GLabel 850  7300 1    50   Input ~ 0
A0
Text GLabel 950  7300 1    50   Input ~ 0
A1
Text GLabel 1050 7300 1    50   Input ~ 0
A2
Text GLabel 1150 7300 1    50   Input ~ 0
A3
Text GLabel 1250 7300 1    50   Input ~ 0
A4
Text GLabel 1350 7300 1    50   Input ~ 0
A5
Text GLabel 1450 7300 1    50   Input ~ 0
A6
Text GLabel 1550 7300 1    50   Input ~ 0
A7
Text GLabel 1650 7300 1    50   Input ~ 0
A8
Text GLabel 1750 7300 1    50   Input ~ 0
A9
Text GLabel 1850 7300 1    50   Input ~ 0
A10
Text GLabel 1950 7300 1    50   Input ~ 0
A11
Text GLabel 2050 7300 1    50   Input ~ 0
A12
Text GLabel 2150 7300 1    50   Input ~ 0
A13
Text GLabel 2250 7300 1    50   Input ~ 0
A14
Text GLabel 2350 7300 1    50   Input ~ 0
A15
$Comp
L Connector_Generic:Conn_01x02 J55
U 1 1 5FD0C6FE
P 3450 7550
F 0 "J55" H 3500 7650 50  0000 R CNN
F 1 "Conn_01x02" V 3575 7700 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical_SMD_Pin1Left" H 3450 7550 50  0001 C CNN
F 3 "~" H 3450 7550 50  0001 C CNN
	1    3450 7550
	0    -1   1    0   
$EndComp
$Comp
L power:GND #PWR058
U 1 1 5FD0C704
P 3550 7350
F 0 "#PWR058" H 3550 7100 50  0001 C CNN
F 1 "GND" H 3550 7225 50  0000 C CNN
F 2 "" H 3550 7350 50  0001 C CNN
F 3 "" H 3550 7350 50  0001 C CNN
	1    3550 7350
	-1   0    0    1   
$EndComp
$Comp
L power:VCC #PWR057
U 1 1 5FD0C70A
P 3450 7225
F 0 "#PWR057" H 3450 7075 50  0001 C CNN
F 1 "VCC" H 3465 7398 50  0000 C CNN
F 2 "" H 3450 7225 50  0001 C CNN
F 3 "" H 3450 7225 50  0001 C CNN
	1    3450 7225
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J56
U 1 1 5FD28451
P 3750 7550
F 0 "J56" H 3800 7650 50  0000 R CNN
F 1 "Conn_01x02" V 3875 7700 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical_SMD_Pin1Left" H 3750 7550 50  0001 C CNN
F 3 "~" H 3750 7550 50  0001 C CNN
	1    3750 7550
	0    -1   1    0   
$EndComp
Wire Wire Line
	3850 7350 3850 7300
Wire Wire Line
	3850 7300 3750 7300
Wire Wire Line
	3750 7300 3750 7350
Connection ~ 3850 7300
$Comp
L Connector_Generic:Conn_01x03 J57
U 1 1 5FD3111A
P 4150 7550
F 0 "J57" H 4200 7750 50  0000 R CNN
F 1 "Conn_01x03" V 4275 7775 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical_SMD_Pin1Left" H 4150 7550 50  0001 C CNN
F 3 "~" H 4150 7550 50  0001 C CNN
	1    4150 7550
	0    -1   1    0   
$EndComp
Wire Wire Line
	4150 7350 4150 7300
Wire Wire Line
	4150 7300 4050 7300
Wire Wire Line
	4050 7300 4050 7350
Text GLabel 4150 7250 1    50   Input ~ 0
A15
Wire Wire Line
	4150 7250 4150 7300
Connection ~ 4150 7300
Text GLabel 4250 7250 1    50   Input ~ 0
W_
Wire Wire Line
	4250 7250 4250 7350
$Comp
L Connector_Generic:Conn_01x02 J42
U 1 1 5FD6BFBC
P 5100 5900
F 0 "J42" H 5175 6000 50  0000 R CNN
F 1 "Conn_01x02" V 5225 6050 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical_SMD_Pin1Left" H 5100 5900 50  0001 C CNN
F 3 "~" H 5100 5900 50  0001 C CNN
	1    5100 5900
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR052
U 1 1 5FD6BFC2
P 5200 6175
F 0 "#PWR052" H 5200 5925 50  0001 C CNN
F 1 "GND" H 5205 6002 50  0000 C CNN
F 2 "" H 5200 6175 50  0001 C CNN
F 3 "" H 5200 6175 50  0001 C CNN
	1    5200 6175
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR051
U 1 1 5FD6BFC8
P 5100 6100
F 0 "#PWR051" H 5100 5950 50  0001 C CNN
F 1 "VCC" H 5115 6273 50  0000 C CNN
F 2 "" H 5100 6100 50  0001 C CNN
F 3 "" H 5100 6100 50  0001 C CNN
	1    5100 6100
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J43
U 1 1 5FD72026
P 5725 5900
F 0 "J43" H 5800 6100 50  0000 R CNN
F 1 "Conn_01x04" V 5850 6125 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical_SMD_Pin1Left" H 5725 5900 50  0001 C CNN
F 3 "~" H 5725 5900 50  0001 C CNN
	1    5725 5900
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x06 J47
U 1 1 5FDA1FC7
P 6100 7200
F 0 "J47" H 6175 7500 50  0000 R CNN
F 1 "Conn_01x06" V 6225 7425 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical_SMD_Pin1Left" H 6100 7200 50  0001 C CNN
F 3 "~" H 6100 7200 50  0001 C CNN
	1    6100 7200
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J48
U 1 1 5FDA1FCD
P 6625 7200
F 0 "J48" H 6700 7300 50  0000 R CNN
F 1 "Conn_01x02" V 6750 7300 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical_SMD_Pin1Left" H 6625 7200 50  0001 C CNN
F 3 "~" H 6625 7200 50  0001 C CNN
	1    6625 7200
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR056
U 1 1 5FDA1FD3
P 6725 7475
F 0 "#PWR056" H 6725 7225 50  0001 C CNN
F 1 "GND" H 6725 7300 50  0000 C CNN
F 2 "" H 6725 7475 50  0001 C CNN
F 3 "" H 6725 7475 50  0001 C CNN
	1    6725 7475
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR055
U 1 1 5FDA1FD9
P 6625 7400
F 0 "#PWR055" H 6625 7250 50  0001 C CNN
F 1 "VCC" H 6625 7575 50  0000 C CNN
F 2 "" H 6625 7400 50  0001 C CNN
F 3 "" H 6625 7400 50  0001 C CNN
	1    6625 7400
	-1   0    0    1   
$EndComp
Text Notes 5750 7725 0    50   ~ 0
MOD3. AND (ROM select)
NoConn ~ 6400 7400
NoConn ~ 6300 7400
NoConn ~ 6200 7400
NoConn ~ 6100 7400
NoConn ~ 6000 7400
NoConn ~ 5900 7400
$Comp
L Connector_Generic:Conn_01x06 J46
U 1 1 5FDA1FF6
P 6325 7025
F 0 "J46" H 6375 7325 50  0000 R CNN
F 1 "Conn_01x06" V 6450 7250 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical_SMD_Pin1Left" H 6325 7025 50  0001 C CNN
F 3 "~" H 6325 7025 50  0001 C CNN
	1    6325 7025
	0    -1   1    0   
$EndComp
NoConn ~ 6425 6825
NoConn ~ 6525 6825
NoConn ~ 6625 6825
Text Notes 625  7425 1    100  ~ 20
Board 1
Text Notes 625  6100 1    100  ~ 20
Board 2\n
$Comp
L Connector_Generic:Conn_01x04 J38
U 1 1 5FE58FCA
P 5725 5725
F 0 "J38" H 5775 5925 50  0000 R CNN
F 1 "Conn_01x04" V 5850 5900 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical_SMD_Pin1Left" H 5725 5725 50  0001 C CNN
F 3 "~" H 5725 5725 50  0001 C CNN
	1    5725 5725
	0    -1   1    0   
$EndComp
Text GLabel 5925 5450 1    50   Output ~ 0
RW
Text GLabel 5625 5450 1    50   Output ~ 0
F2
$Comp
L Connector_Generic:Conn_01x05 J37
U 1 1 5FE842AF
P 5200 5725
F 0 "J37" H 5250 6025 50  0000 R CNN
F 1 "Conn_01x05" V 5325 5900 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical_SMD_Pin1Left" H 5200 5725 50  0001 C CNN
F 3 "~" H 5200 5725 50  0001 C CNN
	1    5200 5725
	0    -1   1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J36
U 1 1 5FEAAE6B
P 4375 5725
F 0 "J36" H 4425 6125 50  0000 R CNN
F 1 "Conn_01x08" V 4500 5900 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical_SMD_Pin1Left" H 4375 5725 50  0001 C CNN
F 3 "~" H 4375 5725 50  0001 C CNN
	1    4375 5725
	0    -1   1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J35
U 1 1 5FF08AD1
P 3475 5725
F 0 "J35" H 3525 6125 50  0000 R CNN
F 1 "Conn_01x08" V 3600 5900 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical_SMD_Pin1Left" H 3475 5725 50  0001 C CNN
F 3 "~" H 3475 5725 50  0001 C CNN
	1    3475 5725
	0    -1   1    0   
$EndComp
Wire Wire Line
	3175 5425 3175 5525
Wire Wire Line
	3275 5425 3275 5525
Wire Wire Line
	3375 5425 3375 5525
Wire Wire Line
	3475 5425 3475 5525
Wire Wire Line
	3575 5425 3575 5525
Wire Wire Line
	3675 5425 3675 5525
Wire Wire Line
	3775 5425 3775 5525
$Comp
L Connector_Generic:Conn_01x06 J34
U 1 1 5FF12C07
P 2650 5725
F 0 "J34" H 2700 6025 50  0000 R CNN
F 1 "Conn_01x06" V 2775 5950 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical_SMD_Pin1Left" H 2650 5725 50  0001 C CNN
F 3 "~" H 2650 5725 50  0001 C CNN
	1    2650 5725
	0    -1   1    0   
$EndComp
$Comp
L power:VCC #PWR046
U 1 1 6000EC0C
P 2100 5900
F 0 "#PWR046" H 2100 5750 50  0001 C CNN
F 1 "VCC" H 2115 6073 50  0000 C CNN
F 2 "" H 2100 5900 50  0001 C CNN
F 3 "" H 2100 5900 50  0001 C CNN
	1    2100 5900
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R11
U 1 1 6001A940
P 2850 5275
F 0 "R11" H 2909 5321 50  0001 L CNN
F 1 "3k3" V 2850 5200 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 2850 5275 50  0001 C CNN
F 3 "~" H 2850 5275 50  0001 C CNN
	1    2850 5275
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R10
U 1 1 60043500
P 2750 5275
F 0 "R10" H 2809 5321 50  0001 L CNN
F 1 "3k3" V 2750 5200 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 2750 5275 50  0001 C CNN
F 3 "~" H 2750 5275 50  0001 C CNN
	1    2750 5275
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R9
U 1 1 600437F5
P 2650 5275
F 0 "R9" H 2709 5321 50  0001 L CNN
F 1 "3k3" V 2650 5200 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 2650 5275 50  0001 C CNN
F 3 "~" H 2650 5275 50  0001 C CNN
	1    2650 5275
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R8
U 1 1 60081616
P 2100 5800
F 0 "R8" H 2159 5846 50  0001 L CNN
F 1 "3k3" V 2100 5725 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 2100 5800 50  0001 C CNN
F 3 "~" H 2100 5800 50  0001 C CNN
	1    2100 5800
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push_Dual_x2 SW1
U 1 1 600AA3B8
P 1900 5700
F 0 "SW1" H 1900 5985 50  0000 C CNN
F 1 "SW_MEC_5E" H 1900 5894 50  0001 C CNN
F 2 "Button_Switch_SMD:SW_Push_1P1T_NO_CK_KSC7xxJ" H 1900 6000 50  0001 C CNN
F 3 "http://www.apem.com/int/index.php?controller=attachment&id_attachment=1371" H 1900 6000 50  0001 C CNN
	1    1900 5700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR049
U 1 1 600FD4E1
P 1700 5900
F 0 "#PWR049" H 1700 5650 50  0001 C CNN
F 1 "GND" H 1705 5727 50  0000 C CNN
F 2 "" H 1700 5900 50  0001 C CNN
F 3 "" H 1700 5900 50  0001 C CNN
	1    1700 5900
	1    0    0    -1  
$EndComp
$Comp
L Oscillator:TXC-7C X1
U 1 1 60121B7C
P 1100 5700
F 0 "X1" H 950 5575 50  0000 L CNN
F 1 "TXC-7C" H 1150 5425 50  0000 L CNN
F 2 "Oscillator:Oscillator_SMD_TXC_7C-4Pin_5.0x3.2mm" H 1800 5350 50  0001 C CNN
F 3 "http://www.txccorp.com/download/products/osc/7C_o.pdf" H 1000 5700 50  0001 C CNN
	1    1100 5700
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR048
U 1 1 60122448
P 800 5625
F 0 "#PWR048" H 800 5475 50  0001 C CNN
F 1 "VCC" H 815 5798 50  0000 C CNN
F 2 "" H 800 5625 50  0001 C CNN
F 3 "" H 800 5625 50  0001 C CNN
	1    800  5625
	1    0    0    -1  
$EndComp
Wire Wire Line
	800  5625 800  5700
$Comp
L power:VCC #PWR047
U 1 1 60130D61
P 1100 5400
F 0 "#PWR047" H 1100 5250 50  0001 C CNN
F 1 "VCC" H 1115 5573 50  0000 C CNN
F 2 "" H 1100 5400 50  0001 C CNN
F 3 "" H 1100 5400 50  0001 C CNN
	1    1100 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR050
U 1 1 60131032
P 1100 6000
F 0 "#PWR050" H 1100 5750 50  0001 C CNN
F 1 "GND" H 1105 5827 50  0000 C CNN
F 2 "" H 1100 6000 50  0001 C CNN
F 3 "" H 1100 6000 50  0001 C CNN
	1    1100 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1525 5700 1400 5700
$Comp
L Connector_Generic:Conn_01x02 J16
U 1 1 602F14E5
P 8250 3150
F 0 "J16" H 8300 3250 50  0000 R CNN
F 1 "Conn_01x02" V 8375 3250 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical_SMD_Pin1Left" H 8250 3150 50  0001 C CNN
F 3 "~" H 8250 3150 50  0001 C CNN
	1    8250 3150
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR027
U 1 1 602F14EB
P 8350 3425
F 0 "#PWR027" H 8350 3175 50  0001 C CNN
F 1 "GND" H 8355 3252 50  0000 C CNN
F 2 "" H 8350 3425 50  0001 C CNN
F 3 "" H 8350 3425 50  0001 C CNN
	1    8350 3425
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR026
U 1 1 602F14F1
P 8250 3350
F 0 "#PWR026" H 8250 3200 50  0001 C CNN
F 1 "VCC" H 8265 3523 50  0000 C CNN
F 2 "" H 8250 3350 50  0001 C CNN
F 3 "" H 8250 3350 50  0001 C CNN
	1    8250 3350
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J9
U 1 1 60345B9E
P 8250 2825
F 0 "J9" H 8250 2925 50  0000 R CNN
F 1 "Conn_01x02" V 8375 2950 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical_SMD_Pin1Left" H 8250 2825 50  0001 C CNN
F 3 "~" H 8250 2825 50  0001 C CNN
	1    8250 2825
	0    -1   1    0   
$EndComp
Text Notes 8100 3675 1    50   ~ 0
MOD16. Keyboard connector (PS/2)
$Comp
L Connector_Generic:Conn_01x14 J15
U 1 1 604703EF
P 6900 2850
F 0 "J15" H 6975 3550 50  0000 R CNN
F 1 "Conn_01x14" V 7025 3075 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x14_P2.54mm_Vertical_SMD_Pin1Left" H 6900 2850 50  0001 C CNN
F 3 "~" H 6900 2850 50  0001 C CNN
	1    6900 2850
	0    -1   -1   0   
$EndComp
Text GLabel 6800 3225 3    50   Output ~ 0
KBIT7
NoConn ~ 6400 3050
NoConn ~ 6300 3050
$Comp
L Connector_Generic:Conn_01x06 J8
U 1 1 606E656E
P 7300 2700
F 0 "J8" H 7325 3000 50  0000 R CNN
F 1 "Conn_01x06" V 7425 2925 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical_SMD_Pin1Left" H 7300 2700 50  0001 C CNN
F 3 "~" H 7300 2700 50  0001 C CNN
	1    7300 2700
	0    -1   1    0   
$EndComp
Text GLabel 7600 2500 1    50   Output ~ 0
LOWRATE
Text Notes 5175 3675 1    50   ~ 0
MOD11. Keyboard controller
$Comp
L Connector_Generic:Conn_01x14 J14
U 1 1 60B7DB76
P 2875 2850
F 0 "J14" H 2950 3550 50  0000 R CNN
F 1 "Conn_01x14" V 3000 3075 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x14_P2.54mm_Vertical_SMD_Pin1Left" H 2875 2850 50  0001 C CNN
F 3 "~" H 2875 2850 50  0001 C CNN
	1    2875 2850
	0    -1   -1   0   
$EndComp
Text GLabel 2775 3225 3    50   Output ~ 0
VBIT7
NoConn ~ 2375 3050
NoConn ~ 2275 3050
$Comp
L Connector_Generic:Conn_01x06 J7
U 1 1 60B7DB96
P 3275 2700
F 0 "J7" H 3300 3000 50  0000 R CNN
F 1 "Conn_01x06" V 3400 2925 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical_SMD_Pin1Left" H 3275 2700 50  0001 C CNN
F 3 "~" H 3275 2700 50  0001 C CNN
	1    3275 2700
	0    -1   1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x07 J11
U 1 1 60B7DBA8
P 1750 2850
F 0 "J11" H 1825 3250 50  0000 R CNN
F 1 "Conn_01x07" V 1875 3050 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x07_P2.54mm_Vertical_SMD_Pin1Left" H 1750 2850 50  0001 C CNN
F 3 "~" H 1750 2850 50  0001 C CNN
	1    1750 2850
	0    -1   -1   0   
$EndComp
$Comp
L power:VCC #PWR020
U 1 1 60B7DBAE
P 2050 3050
F 0 "#PWR020" H 2050 2900 50  0001 C CNN
F 1 "VCC" V 2050 3250 50  0000 C CNN
F 2 "" H 2050 3050 50  0001 C CNN
F 3 "" H 2050 3050 50  0001 C CNN
	1    2050 3050
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR019
U 1 1 60B7DBB8
P 1850 3050
F 0 "#PWR019" H 1850 2800 50  0001 C CNN
F 1 "GND" V 1850 2850 50  0000 C CNN
F 2 "" H 1850 3050 50  0001 C CNN
F 3 "" H 1850 3050 50  0001 C CNN
	1    1850 3050
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR018
U 1 1 60B7DBBE
P 1750 3050
F 0 "#PWR018" H 1750 2900 50  0001 C CNN
F 1 "VCC" V 1750 3250 50  0000 C CNN
F 2 "" H 1750 3050 50  0001 C CNN
F 3 "" H 1750 3050 50  0001 C CNN
	1    1750 3050
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R6
U 1 1 60B7DBC6
P 1300 3200
F 0 "R6" V 1225 3150 50  0000 L CNN
F 1 "10k" V 1300 3125 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 1300 3200 50  0001 C CNN
F 3 "~" H 1300 3200 50  0001 C CNN
	1    1300 3200
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR024
U 1 1 60B7DBCC
P 1300 3325
F 0 "#PWR024" H 1300 3175 50  0001 C CNN
F 1 "VCC" H 1315 3498 50  0000 C CNN
F 2 "" H 1300 3325 50  0001 C CNN
F 3 "" H 1300 3325 50  0001 C CNN
	1    1300 3325
	-1   0    0    1   
$EndComp
Wire Wire Line
	1300 3325 1300 3300
$Comp
L Device:C_Small C3
U 1 1 60B7DBD6
P 1450 3425
F 0 "C3" H 1542 3471 50  0001 L CNN
F 1 "22pF" V 1550 3300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1450 3425 50  0001 C CNN
F 3 "~" H 1450 3425 50  0001 C CNN
	1    1450 3425
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C4
U 1 1 60B7DBDC
P 1650 3425
F 0 "C4" H 1742 3471 50  0001 L CNN
F 1 "22pF" V 1750 3300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1650 3425 50  0001 C CNN
F 3 "~" H 1650 3425 50  0001 C CNN
	1    1650 3425
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR028
U 1 1 60B7DBE2
P 1650 3550
F 0 "#PWR028" H 1650 3300 50  0001 C CNN
F 1 "GND" H 1800 3500 50  0000 C CNN
F 2 "" H 1650 3550 50  0001 C CNN
F 3 "" H 1650 3550 50  0001 C CNN
	1    1650 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal_Small Y2
U 1 1 60B7DBEC
P 1550 3200
F 0 "Y2" H 1550 3425 50  0001 C CNN
F 1 "16Mhz" V 1550 3200 50  0000 C CNN
F 2 "Crystal:Crystal_SMD_0603-2Pin_6.0x3.5mm" H 1550 3200 50  0001 C CNN
F 3 "~" H 1550 3200 50  0001 C CNN
	1    1550 3200
	1    0    0    -1  
$EndComp
Text Notes 800  3650 1    50   ~ 0
MOD10. Video controller
NoConn ~ 2675 3050
NoConn ~ 2475 3050
$Comp
L Switch:SW_Push_Dual_x2 SW2
U 1 1 60CAD328
P 1100 3050
F 0 "SW2" H 1100 3225 50  0000 C CNN
F 1 "SW_MEC_5E" H 1100 3244 50  0001 C CNN
F 2 "Button_Switch_SMD:SW_Push_1P1T_NO_CK_KSC7xxJ" H 1100 3350 50  0001 C CNN
F 3 "http://www.apem.com/int/index.php?controller=attachment&id_attachment=1371" H 1100 3350 50  0001 C CNN
	1    1100 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 60CE035B
P 900 3050
F 0 "#PWR014" H 900 2800 50  0001 C CNN
F 1 "GND" H 905 2877 50  0000 C CNN
F 2 "" H 900 3050 50  0001 C CNN
F 3 "" H 900 3050 50  0001 C CNN
	1    900  3050
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x14 J13
U 1 1 5FEBC4FC
P 2875 1325
F 0 "J13" H 2950 2025 50  0000 R CNN
F 1 "Conn_01x14" V 3000 1550 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x14_P2.54mm_Vertical_SMD_Pin1Left" H 2875 1325 50  0001 C CNN
F 3 "~" H 2875 1325 50  0001 C CNN
	1    2875 1325
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x06 J6
U 1 1 5FEBC51C
P 3275 1175
F 0 "J6" H 3300 1475 50  0000 R CNN
F 1 "Conn_01x06" V 3400 1400 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical_SMD_Pin1Left" H 3275 1175 50  0001 C CNN
F 3 "~" H 3275 1175 50  0001 C CNN
	1    3275 1175
	0    -1   1    0   
$EndComp
Text Notes 800  2125 1    50   ~ 0
MOD12. TV controller
Text GLabel 1300 2725 1    50   Output ~ 0
VideoRST
Text GLabel 1300 1525 3    50   Input ~ 0
VideoRST
NoConn ~ 3275 975 
NoConn ~ 3175 975 
NoConn ~ 3075 975 
$Comp
L Device:R_Small R3
U 1 1 6078F018
P 3375 750
F 0 "R3" H 3434 796 50  0001 L CNN
F 1 "2k2" V 3375 675 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 3375 750 50  0001 C CNN
F 3 "~" H 3375 750 50  0001 C CNN
	1    3375 750 
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R4
U 1 1 6078F863
P 3425 650
F 0 "R4" H 3484 696 50  0001 L CNN
F 1 "2k2" V 3425 575 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 3425 650 50  0001 C CNN
F 3 "~" H 3425 650 50  0001 C CNN
	1    3425 650 
	0    1    1    0   
$EndComp
$Comp
L power:VCC #PWR012
U 1 1 607903E7
P 3150 750
F 0 "#PWR012" H 3150 600 50  0001 C CNN
F 1 "VCC" H 3025 825 50  0000 C CNN
F 2 "" H 3150 750 50  0001 C CNN
F 3 "" H 3150 750 50  0001 C CNN
	1    3150 750 
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x14 J3
U 1 1 6094B7A7
P 6475 1200
F 0 "J3" H 6525 1900 50  0000 R CNN
F 1 "Conn_01x14" V 6600 1425 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x14_P2.54mm_Vertical_SMD_Pin1Left" H 6475 1200 50  0001 C CNN
F 3 "~" H 6475 1200 50  0001 C CNN
	1    6475 1200
	0    -1   -1   0   
$EndComp
Text Notes 5725 2125 0    50   ~ 0
MOD14. Shift register
NoConn ~ 6675 1400
$Comp
L power:GND #PWR06
U 1 1 609E2E35
P 6775 1900
F 0 "#PWR06" H 6775 1650 50  0001 C CNN
F 1 "GND" H 6900 1825 50  0000 C CNN
F 2 "" H 6775 1900 50  0001 C CNN
F 3 "" H 6775 1900 50  0001 C CNN
	1    6775 1900
	1    0    0    -1  
$EndComp
Text GLabel 6875 1550 3    50   Input ~ 0
TV_CLK
$Comp
L Device:R_Small R2
U 1 1 60C3B49E
P 6400 1825
F 0 "R2" H 6459 1871 50  0001 L CNN
F 1 "10k" V 6400 1750 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 6400 1825 50  0001 C CNN
F 3 "~" H 6400 1825 50  0001 C CNN
	1    6400 1825
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR010
U 1 1 60CD5E9E
P 6450 1925
F 0 "#PWR010" H 6450 1775 50  0001 C CNN
F 1 "VCC" V 6450 2100 50  0000 C CNN
F 2 "" H 6450 1925 50  0001 C CNN
F 3 "" H 6450 1925 50  0001 C CNN
	1    6450 1925
	0    1    1    0   
$EndComp
Text GLabel 2150 1925 2    50   Output ~ 0
TV_CLK
NoConn ~ 3175 1525
NoConn ~ 3275 1525
NoConn ~ 3375 1525
NoConn ~ 3475 1525
NoConn ~ 3575 1525
$Comp
L Connector_Generic:Conn_01x08 J2
U 1 1 612E9F8D
P 6775 1050
F 0 "J2" H 6825 1450 50  0000 R CNN
F 1 "Conn_01x08" V 6900 1225 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical_SMD_Pin1Left" H 6775 1050 50  0001 C CNN
F 3 "~" H 6775 1050 50  0001 C CNN
	1    6775 1050
	0    -1   1    0   
$EndComp
$Comp
L power:VCC #PWR03
U 1 1 612EAAD7
P 7075 850
F 0 "#PWR03" H 7075 700 50  0001 C CNN
F 1 "VCC" H 7075 1000 50  0000 C CNN
F 2 "" H 7075 850 50  0001 C CNN
F 3 "" H 7075 850 50  0001 C CNN
	1    7075 850 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 612EADF2
P 7250 850
F 0 "#PWR04" H 7250 600 50  0001 C CNN
F 1 "GND" H 7250 700 50  0000 C CNN
F 2 "" H 7250 850 50  0001 C CNN
F 3 "" H 7250 850 50  0001 C CNN
	1    7250 850 
	-1   0    0    1   
$EndComp
Wire Wire Line
	7250 850  7175 850 
NoConn ~ 6975 850 
NoConn ~ 6875 850 
NoConn ~ 6775 850 
NoConn ~ 6675 850 
NoConn ~ 6575 850 
$Comp
L Connector_Generic:Conn_01x02 J5
U 1 1 614FC12F
P 8050 1275
F 0 "J5" H 8100 1375 50  0000 R CNN
F 1 "Conn_01x02" V 8175 1375 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical_SMD_Pin1Left" H 8050 1275 50  0001 C CNN
F 3 "~" H 8050 1275 50  0001 C CNN
	1    8050 1275
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR09
U 1 1 614FC135
P 8050 1475
F 0 "#PWR09" H 8050 1225 50  0001 C CNN
F 1 "GND" H 8050 1325 50  0000 C CNN
F 2 "" H 8050 1475 50  0001 C CNN
F 3 "" H 8050 1475 50  0001 C CNN
	1    8050 1475
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J4
U 1 1 614FC150
P 8050 1100
F 0 "J4" H 8050 1200 50  0000 R CNN
F 1 "Conn_01x02" V 8175 1225 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical_SMD_Pin1Left" H 8050 1100 50  0001 C CNN
F 3 "~" H 8050 1100 50  0001 C CNN
	1    8050 1100
	0    -1   1    0   
$EndComp
Text Notes 7875 1625 1    50   ~ 0
MOD17. Video connector
$Comp
L power:GND #PWR05
U 1 1 6154813C
P 8050 900
F 0 "#PWR05" H 8050 650 50  0001 C CNN
F 1 "GND" H 8050 750 50  0000 C CNN
F 2 "" H 8050 900 50  0001 C CNN
F 3 "" H 8050 900 50  0001 C CNN
	1    8050 900 
	-1   0    0    1   
$EndComp
$Comp
L Device:LED_Small D3
U 1 1 61689F9A
P 5825 5250
F 0 "D3" V 5772 5330 50  0000 L CNN
F 1 "Green" V 5863 5330 50  0000 L CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 5825 5250 50  0001 C CNN
F 3 "~" H 5825 5250 50  0001 C CNN
F 4 "CPU SYNC LED" V 5825 5250 50  0001 C CNN "SmartyKit Module"
	1    5825 5250
	0    -1   1    0   
$EndComp
$Comp
L Device:R_Small R5
U 1 1 620BD7B9
P 7100 2350
F 0 "R5" H 7159 2396 50  0001 L CNN
F 1 "1k" V 7100 2300 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 7100 2350 50  0001 C CNN
F 3 "~" H 7100 2350 50  0001 C CNN
	1    7100 2350
	0    1    1    0   
$EndComp
$Comp
L Device:LED_Small D2
U 1 1 620BD7C0
P 7300 2350
F 0 "D2" V 7247 2430 50  0001 L CNN
F 1 "Green" H 7200 2450 50  0000 L CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 7300 2350 50  0001 C CNN
F 3 "~" H 7300 2350 50  0001 C CNN
F 4 "Low-rate clock LED" V 7300 2350 50  0001 C CNN "SmartyKit Module"
	1    7300 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR013
U 1 1 620BD7C6
P 6925 2350
F 0 "#PWR013" H 6925 2100 50  0001 C CNN
F 1 "GND" H 7025 2250 50  0000 C CNN
F 2 "" H 6925 2350 50  0001 C CNN
F 3 "" H 6925 2350 50  0001 C CNN
	1    6925 2350
	-1   0    0    1   
$EndComp
Text Notes 625  3325 1    100  ~ 20
Board 4\n
Text Notes 625  1725 1    100  ~ 20
Board 5\n
$Comp
L power:GND #PWR02
U 1 1 6210BEEA
P 10300 1550
F 0 "#PWR02" H 10300 1300 50  0001 C CNN
F 1 "GND" H 10305 1377 50  0000 C CNN
F 2 "" H 10300 1550 50  0001 C CNN
F 3 "" H 10300 1550 50  0001 C CNN
	1    10300 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	10300 1500 10300 1525
$Comp
L Device:R_Small R1
U 1 1 6210BEF1
P 10300 1400
F 0 "R1" H 10359 1446 50  0001 L CNN
F 1 "1k" V 10300 1350 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 10300 1400 50  0001 C CNN
F 3 "~" H 10300 1400 50  0001 C CNN
	1    10300 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:LED_Small D1
U 1 1 6210BEF8
P 10300 1100
F 0 "D1" V 10247 1180 50  0000 L CNN
F 1 "Green" H 10338 1180 50  0000 L CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 10300 1100 50  0001 C CNN
F 3 "~" H 10300 1100 50  0001 C CNN
F 4 "Power-On LED indicator" H 10300 1100 50  0001 C CNN "SmartyKit Module"
	1    10300 1100
	0    -1   -1   0   
$EndComp
Text Notes 10050 1950 1    50   ~ 0
Power connector
$Comp
L power:VCC #PWR01
U 1 1 621F6546
P 10300 875
F 0 "#PWR01" H 10300 725 50  0001 C CNN
F 1 "VCC" H 10315 1048 50  0000 C CNN
F 2 "" H 10300 875 50  0001 C CNN
F 3 "" H 10300 875 50  0001 C CNN
	1    10300 875 
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 622459BA
P 10475 1200
F 0 "J1" H 10475 1300 50  0000 R CNN
F 1 "Conn_01x02" V 10600 1325 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical_SMD_Pin1Left" H 10475 1200 50  0001 C CNN
F 3 "~" H 10475 1200 50  0001 C CNN
	1    10475 1200
	-1   0    0    -1  
$EndComp
Connection ~ 10300 925 
Wire Wire Line
	10300 925  10300 875 
Connection ~ 10300 1525
Wire Wire Line
	10300 1525 10300 1550
Text Notes 625  4725 1    100  ~ 20
Board 3\n
NoConn ~ 5075 925 
NoConn ~ 5175 925 
NoConn ~ 5275 925 
NoConn ~ 5375 925 
NoConn ~ 5475 925 
Wire Wire Line
	4775 1000 4775 925 
$Comp
L power:GND #PWR036
U 1 1 602F5BD9
P 4875 1075
F 0 "#PWR036" H 4875 825 50  0001 C CNN
F 1 "GND" H 4880 902 50  0000 C CNN
F 2 "" H 4875 1075 50  0001 C CNN
F 3 "" H 4875 1075 50  0001 C CNN
	1    4875 1075
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR035
U 1 1 602F55BA
P 4775 1000
F 0 "#PWR035" H 4775 850 50  0001 C CNN
F 1 "VCC" H 4790 1173 50  0000 C CNN
F 2 "" H 4775 1000 50  0001 C CNN
F 3 "" H 4775 1000 50  0001 C CNN
	1    4775 1000
	-1   0    0    1   
$EndComp
NoConn ~ 4975 925 
NoConn ~ 4675 925 
$Comp
L power:GND #PWR037
U 1 1 60062077
P 4075 1200
F 0 "#PWR037" H 4075 950 50  0001 C CNN
F 1 "GND" H 4080 1027 50  0000 C CNN
F 2 "" H 4075 1200 50  0001 C CNN
F 3 "" H 4075 1200 50  0001 C CNN
	1    4075 1200
	1    0    0    -1  
$EndComp
Text Notes 3925 1500 0    50   ~ 0
MOD13. Display module
$Comp
L Connector_Generic:Conn_01x15 J25
U 1 1 5FEFFC8E
P 4775 725
F 0 "J25" H 4825 1525 50  0000 R CNN
F 1 "Conn_01x15" V 4900 950 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x15_P2.54mm_Vertical_SMD_Pin1Left" H 4775 725 50  0001 C CNN
F 3 "~" H 4775 725 50  0001 C CNN
	1    4775 725 
	0    -1   -1   0   
$EndComp
NoConn ~ 3125 4725
NoConn ~ 3225 4725
NoConn ~ 3325 4725
NoConn ~ 3425 4725
$Comp
L power:GND #PWR032
U 1 1 602A886A
P 2275 4025
F 0 "#PWR032" H 2275 3775 50  0001 C CNN
F 1 "GND" H 2200 3900 50  0000 C CNN
F 2 "" H 2275 4025 50  0001 C CNN
F 3 "" H 2275 4025 50  0001 C CNN
	1    2275 4025
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J21
U 1 1 6028CC20
P 2175 4350
F 0 "J21" H 2200 4450 50  0000 R CNN
F 1 "Conn_01x02" V 2300 4475 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical_SMD_Pin1Left" H 2175 4350 50  0001 C CNN
F 3 "~" H 2175 4350 50  0001 C CNN
	1    2175 4350
	0    -1   1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J20
U 1 1 60270BFE
P 1575 4350
F 0 "J20" H 1600 4750 50  0000 R CNN
F 1 "Conn_01x08" V 1700 4525 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical_SMD_Pin1Left" H 1575 4350 50  0001 C CNN
F 3 "~" H 1575 4350 50  0001 C CNN
	1    1575 4350
	0    -1   1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J26
U 1 1 6023D4D4
P 1575 4500
F 0 "J26" H 1625 4900 50  0000 R CNN
F 1 "Conn_01x08" V 1700 4700 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical_SMD_Pin1Left" H 1575 4500 50  0001 C CNN
F 3 "~" H 1575 4500 50  0001 C CNN
	1    1575 4500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2325 4700 2275 4700
$Comp
L power:VCC #PWR038
U 1 1 6023D4CD
P 2175 4700
F 0 "#PWR038" H 2175 4550 50  0001 C CNN
F 1 "VCC" H 2190 4873 50  0000 C CNN
F 2 "" H 2175 4700 50  0001 C CNN
F 3 "" H 2175 4700 50  0001 C CNN
	1    2175 4700
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR039
U 1 1 6023D4C7
P 2325 4700
F 0 "#PWR039" H 2325 4450 50  0001 C CNN
F 1 "GND" H 2330 4527 50  0000 C CNN
F 2 "" H 2325 4700 50  0001 C CNN
F 3 "" H 2325 4700 50  0001 C CNN
	1    2325 4700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J27
U 1 1 6023D4C1
P 2175 4500
F 0 "J27" H 2225 4600 50  0000 R CNN
F 1 "Conn_01x02" V 2300 4600 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical_SMD_Pin1Left" H 2175 4500 50  0001 C CNN
F 3 "~" H 2175 4500 50  0001 C CNN
	1    2175 4500
	0    -1   -1   0   
$EndComp
Text Notes 800  4950 1    50   ~ 0
MOD6. Video port
$Comp
L Connector_Generic:Conn_01x06 J28
U 1 1 601F1E05
P 3225 4525
F 0 "J28" H 3300 4825 50  0000 R CNN
F 1 "Conn_01x06" V 3350 4750 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical_SMD_Pin1Left" H 3225 4525 50  0001 C CNN
F 3 "~" H 3225 4525 50  0001 C CNN
	1    3225 4525
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J22
U 1 1 60163CBA
P 2775 4350
F 0 "J22" H 2800 4450 50  0000 R CNN
F 1 "Conn_01x02" V 2900 4475 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical_SMD_Pin1Left" H 2775 4350 50  0001 C CNN
F 3 "~" H 2775 4350 50  0001 C CNN
	1    2775 4350
	0    -1   1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J24
U 1 1 60163849
P 3650 4350
F 0 "J24" H 3675 4450 50  0000 R CNN
F 1 "Conn_01x02" V 3775 4475 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical_SMD_Pin1Left" H 3650 4350 50  0001 C CNN
F 3 "~" H 3650 4350 50  0001 C CNN
	1    3650 4350
	0    -1   1    0   
$EndComp
$Comp
L power:VCC #PWR033
U 1 1 6012285B
P 3225 4150
F 0 "#PWR033" H 3225 4000 50  0001 C CNN
F 1 "VCC" H 3200 4300 50  0000 C CNN
F 2 "" H 3225 4150 50  0001 C CNN
F 3 "" H 3225 4150 50  0001 C CNN
	1    3225 4150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR034
U 1 1 60122855
P 3325 4100
F 0 "#PWR034" H 3325 3850 50  0001 C CNN
F 1 "GND" H 3300 3950 50  0000 C CNN
F 2 "" H 3325 4100 50  0001 C CNN
F 3 "" H 3325 4100 50  0001 C CNN
	1    3325 4100
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J23
U 1 1 6012284F
P 3225 4350
F 0 "J23" H 3275 4450 50  0000 R CNN
F 1 "Conn_01x02" V 3350 4500 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical_SMD_Pin1Left" H 3225 4350 50  0001 C CNN
F 3 "~" H 3225 4350 50  0001 C CNN
	1    3225 4350
	0    -1   1    0   
$EndComp
Wire Wire Line
	3025 4775 3025 4725
Text GLabel 3025 4775 3    50   Output ~ 0
D7
Wire Wire Line
	3525 4775 3525 4725
Text GLabel 3525 4775 3    50   Output ~ 0
D7
Text Notes 2625 4950 1    50   ~ 0
MOD7. BIT7 ports
$Comp
L power:VCC #PWR031
U 1 1 5FEF4B04
P 5175 4025
F 0 "#PWR031" H 5175 3875 50  0001 C CNN
F 1 "VCC" H 5075 4150 50  0000 C CNN
F 2 "" H 5175 4025 50  0001 C CNN
F 3 "" H 5175 4025 50  0001 C CNN
	1    5175 4025
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J18
U 1 1 5FEE2FC8
P 5175 4350
F 0 "J18" H 5200 4450 50  0000 R CNN
F 1 "Conn_01x02" V 5300 4475 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical_SMD_Pin1Left" H 5175 4350 50  0001 C CNN
F 3 "~" H 5175 4350 50  0001 C CNN
	1    5175 4350
	0    -1   1    0   
$EndComp
Wire Wire Line
	5325 4700 5275 4700
$Comp
L power:VCC #PWR040
U 1 1 5FE9E848
P 5175 4700
F 0 "#PWR040" H 5175 4550 50  0001 C CNN
F 1 "VCC" H 5190 4873 50  0000 C CNN
F 2 "" H 5175 4700 50  0001 C CNN
F 3 "" H 5175 4700 50  0001 C CNN
	1    5175 4700
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR041
U 1 1 5FE9E842
P 5325 4700
F 0 "#PWR041" H 5325 4450 50  0001 C CNN
F 1 "GND" H 5330 4527 50  0000 C CNN
F 2 "" H 5325 4700 50  0001 C CNN
F 3 "" H 5325 4700 50  0001 C CNN
	1    5325 4700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J30
U 1 1 5FE9E83C
P 5175 4500
F 0 "J30" H 5225 4600 50  0000 R CNN
F 1 "Conn_01x02" V 5300 4600 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical_SMD_Pin1Left" H 5175 4500 50  0001 C CNN
F 3 "~" H 5175 4500 50  0001 C CNN
	1    5175 4500
	0    -1   -1   0   
$EndComp
Text Notes 4025 4950 1    50   ~ 0
MOD8. Keyboard port
NoConn ~ 6100 4100
NoConn ~ 6200 4100
NoConn ~ 6400 4100
NoConn ~ 6500 4100
NoConn ~ 6600 4100
NoConn ~ 6800 4100
NoConn ~ 6900 4100
NoConn ~ 7200 4100
NoConn ~ 7300 4100
NoConn ~ 7400 4100
NoConn ~ 7500 4100
NoConn ~ 7600 4100
$Comp
L Connector_Generic:Conn_01x16 J19
U 1 1 5FCF9812
P 6800 4300
F 0 "J19" H 6850 5100 50  0000 R CNN
F 1 "Conn_01x16" V 6925 4475 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x16_P2.54mm_Vertical_SMD_Pin1Left" H 6800 4300 50  0001 C CNN
F 3 "~" H 6800 4300 50  0001 C CNN
	1    6800 4300
	0    -1   1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J31
U 1 1 5FCBCE10
P 6200 4450
F 0 "J31" H 6275 4650 50  0000 R CNN
F 1 "Conn_01x04" V 6325 4675 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical_SMD_Pin1Left" H 6200 4450 50  0001 C CNN
F 3 "~" H 6200 4450 50  0001 C CNN
	1    6200 4450
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J32
U 1 1 5FC9E813
P 6700 4450
F 0 "J32" H 6775 4550 50  0000 R CNN
F 1 "Conn_01x02" V 6825 4550 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical_SMD_Pin1Left" H 6700 4450 50  0001 C CNN
F 3 "~" H 6700 4450 50  0001 C CNN
	1    6700 4450
	0    -1   -1   0   
$EndComp
$Comp
L power:VCC #PWR043
U 1 1 5FC9017F
P 7500 4650
F 0 "#PWR043" H 7500 4500 50  0001 C CNN
F 1 "VCC" H 7515 4823 50  0000 C CNN
F 2 "" H 7500 4650 50  0001 C CNN
F 3 "" H 7500 4650 50  0001 C CNN
	1    7500 4650
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR044
U 1 1 5FC90179
P 7600 4725
F 0 "#PWR044" H 7600 4475 50  0001 C CNN
F 1 "GND" H 7605 4552 50  0000 C CNN
F 2 "" H 7600 4725 50  0001 C CNN
F 3 "" H 7600 4725 50  0001 C CNN
	1    7600 4725
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J33
U 1 1 5FC90173
P 7500 4450
F 0 "J33" H 7600 4550 50  0000 R CNN
F 1 "Conn_01x02" V 7625 4550 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical_SMD_Pin1Left" H 7500 4450 50  0001 C CNN
F 3 "~" H 7500 4450 50  0001 C CNN
	1    7500 4450
	0    -1   -1   0   
$EndComp
Text Notes 5850 4950 1    50   ~ 0
MOD9. Ports decoder
Wire Notes Line
	3300 7050 3300 6600
Wire Notes Line
	3300 6600 800  6600
Wire Notes Line
	800  6600 800  7050
Wire Notes Line
	800  7050 3300 7050
Text Notes 850  7025 0    50   ~ 0
MOD15. Address&data bus connector (CPU<->Memory)
Wire Notes Line
	700  7750 4350 7750
Wire Notes Line
	5675 7750 4425 7750
Wire Notes Line
	6925 7750 5725 7750
Wire Notes Line
	8500 2200 8000 2200
Wire Notes Line
	6375 6450 6375 5025
Wire Notes Line
	6375 5025 2275 5025
Wire Notes Line
	2275 5025 2275 6450
Wire Notes Line
	6375 6450 2275 6450
Wire Notes Line
	2200 6450 2200 5025
Wire Notes Line
	6425 6450 7750 6450
Wire Notes Line
	7750 6450 7750 5025
Wire Notes Line
	7750 5025 6425 5025
Wire Notes Line
	6425 5025 6425 6450
NoConn ~ 7400 2500
NoConn ~ 7300 2500
NoConn ~ 7200 2500
NoConn ~ 7100 2500
Text Label 4075 925  3    50   ~ 0
D_A0
Text Label 2450 5525 1    50   ~ 0
RES_
Text Label 5825 5525 1    50   ~ 0
SYNC
Text Label 5725 5525 1    50   ~ 0
F1
NoConn ~ 5725 5400
Text Label 2550 5525 1    50   ~ 0
CLK
Wire Wire Line
	2650 5175 2650 5100
Wire Wire Line
	2650 5100 2750 5100
Wire Wire Line
	2750 5100 2750 5175
Wire Wire Line
	2750 5100 2850 5100
Wire Wire Line
	2850 5100 2850 5175
Connection ~ 2750 5100
Wire Wire Line
	2850 5375 2850 5525
Wire Wire Line
	2750 5375 2750 5525
Wire Wire Line
	2650 5375 2650 5525
Wire Wire Line
	2950 5100 2850 5100
Wire Wire Line
	2950 5100 2950 5525
Connection ~ 2850 5100
Text Label 2650 5525 1    50   ~ 0
RDY
Text Label 2750 5525 1    50   ~ 0
IRQ_
Text Label 2850 5525 1    50   ~ 0
NMI_
Text Label 2950 5525 1    50   ~ 0
SO
Wire Wire Line
	5725 5400 5725 5525
Wire Wire Line
	2100 5700 2100 5300
Wire Wire Line
	2100 5300 2450 5300
Connection ~ 2100 5700
Wire Wire Line
	2450 5300 2450 5525
Wire Wire Line
	1700 5700 1700 5900
Text Notes 875  6275 0    30   ~ 0
1MHz clock generator
Text Notes 1675 6275 0    30   ~ 0
CPU RESET button
Text Notes 725  6425 0    50   ~ 0
CPU Clock & Reset
Wire Notes Line
	2200 6450 700  6450
Wire Notes Line
	2200 5025 700  5025
Text Label 2100 5525 1    50   ~ 0
RES_
Text Label 1525 5525 1    50   ~ 0
CLK
Wire Wire Line
	5825 5350 5825 5525
Wire Wire Line
	5625 5450 5625 5525
Wire Wire Line
	5925 5450 5925 5525
Wire Wire Line
	5175 7425 5175 7400
Wire Wire Line
	5175 7425 5075 7425
Wire Wire Line
	5075 7425 5075 7400
Connection ~ 5175 7425
Wire Notes Line
	7375 575  5700 575 
Wire Wire Line
	4075 925  4075 1200
Wire Notes Line
	3900 1525 3900 575 
Wire Notes Line
	3900 575  5600 575 
Wire Notes Line
	5600 575  5600 1525
Wire Notes Line
	5600 1525 3900 1525
Text Label 3175 5525 1    50   ~ 0
D0
Text Label 3275 5525 1    50   ~ 0
D1
Text Label 3375 5525 1    50   ~ 0
D2
Text Label 3475 5525 1    50   ~ 0
D3
Text Label 3575 5525 1    50   ~ 0
D4
Text Label 3675 5525 1    50   ~ 0
D5
Text Label 3775 5525 1    50   ~ 0
D6
Text Label 3875 5525 1    50   ~ 0
D7
Text Label 1275 4700 3    50   ~ 0
D0
Text Label 1375 4700 3    50   ~ 0
D1
Text Label 1475 4700 3    50   ~ 0
D2
Text Label 1575 4700 3    50   ~ 0
D3
Text Label 1675 4700 3    50   ~ 0
D4
Text Label 1775 4700 3    50   ~ 0
D5
Text Label 1875 4700 3    50   ~ 0
D6
Text Label 1975 4700 3    50   ~ 0
D7
Wire Wire Line
	1275 4700 1275 4800
Wire Wire Line
	1375 4700 1375 4800
Wire Wire Line
	1475 4700 1475 4800
Wire Wire Line
	1575 4700 1575 4800
Wire Wire Line
	1675 4700 1675 4800
Wire Wire Line
	1775 4700 1775 4800
Wire Wire Line
	1875 4700 1875 4800
Wire Wire Line
	1975 4700 1975 4800
Entry Wire Line
	1275 4800 1375 4900
Entry Wire Line
	1375 4800 1475 4900
Entry Wire Line
	1475 4800 1575 4900
Entry Wire Line
	1575 4800 1675 4900
Entry Wire Line
	1675 4800 1775 4900
Entry Wire Line
	1775 4800 1875 4900
Entry Wire Line
	1875 4800 1975 4900
Entry Wire Line
	1975 4800 2075 4900
Entry Wire Line
	3075 5325 3175 5425
Entry Wire Line
	3175 5325 3275 5425
Entry Wire Line
	3275 5325 3375 5425
Entry Wire Line
	3375 5325 3475 5425
Entry Wire Line
	3475 5325 3575 5425
Entry Wire Line
	3575 5325 3675 5425
Entry Wire Line
	3675 5325 3775 5425
Entry Wire Line
	3775 5325 3875 5425
$Comp
L power:VCC #PWR062
U 1 1 61893817
P 2650 5100
F 0 "#PWR062" H 2650 4950 50  0001 C CNN
F 1 "VCC" V 2650 5275 50  0000 C CNN
F 2 "" H 2650 5100 50  0001 C CNN
F 3 "" H 2650 5100 50  0001 C CNN
	1    2650 5100
	0    -1   -1   0   
$EndComp
Connection ~ 2650 5100
Wire Bus Line
	3075 5325 3075 5000
Wire Wire Line
	2550 5525 2550 5200
Wire Wire Line
	2550 5200 1525 5200
Wire Wire Line
	1525 5200 1525 5700
Text Label 1275 4150 1    50   ~ 0
VD0
Wire Wire Line
	1275 4000 1275 4150
Wire Wire Line
	1375 4000 1375 4150
Wire Wire Line
	1475 4000 1475 4150
Wire Wire Line
	1575 4000 1575 4150
Wire Wire Line
	1675 4000 1675 4150
Wire Wire Line
	1775 4000 1775 4150
Wire Wire Line
	1875 4000 1875 4150
Wire Wire Line
	1975 4000 1975 4150
Text Label 1375 4150 1    50   ~ 0
VD1
Text Label 1475 4150 1    50   ~ 0
VD2
Text Label 1575 4150 1    50   ~ 0
VD3
Text Label 1675 4150 1    50   ~ 0
VD4
Text Label 1775 4150 1    50   ~ 0
VD5
Text Label 1875 4150 1    50   ~ 0
VD6
Text Label 1975 4150 1    50   ~ 0
VD7
Entry Wire Line
	1175 3900 1275 4000
Entry Wire Line
	1275 3900 1375 4000
Entry Wire Line
	1375 3900 1475 4000
Entry Wire Line
	1475 3900 1575 4000
Entry Wire Line
	1575 3900 1675 4000
Entry Wire Line
	1675 3900 1775 4000
Entry Wire Line
	1775 3900 1875 4000
Entry Wire Line
	1875 3900 1975 4000
Text Label 2875 3050 3    50   ~ 0
VD0
Wire Wire Line
	2875 3050 2875 3200
Wire Wire Line
	2975 3050 2975 3200
Wire Wire Line
	3075 3050 3075 3200
Wire Wire Line
	3175 3050 3175 3200
Wire Wire Line
	3275 3050 3275 3200
Wire Wire Line
	3375 3050 3375 3200
Wire Wire Line
	3475 3050 3475 3200
Wire Wire Line
	3575 3050 3575 3200
Text Label 2975 3050 3    50   ~ 0
VD1
Text Label 3075 3050 3    50   ~ 0
VD2
Text Label 3175 3050 3    50   ~ 0
VD3
Text Label 3275 3050 3    50   ~ 0
VD4
Text Label 3375 3050 3    50   ~ 0
VD5
Text Label 3475 3050 3    50   ~ 0
VD6
Text Label 3575 3050 3    50   ~ 0
VD7
Entry Wire Line
	2875 3200 2975 3300
Entry Wire Line
	2975 3200 3075 3300
Entry Wire Line
	3075 3200 3175 3300
Entry Wire Line
	3175 3200 3275 3300
Entry Wire Line
	3275 3200 3375 3300
Entry Wire Line
	3375 3200 3475 3300
Entry Wire Line
	3475 3200 3575 3300
Entry Wire Line
	3575 3200 3675 3300
Wire Notes Line
	700  4975 700  3825
Wire Notes Line
	700  3825 2475 3825
Wire Notes Line
	2475 3825 2475 4975
Wire Notes Line
	700  4975 2475 4975
Wire Notes Line
	2525 4975 2525 3825
Text GLabel 3875 5275 1    50   Input ~ 0
D7
Wire Wire Line
	1300 3050 1450 3050
Connection ~ 1300 3050
Wire Wire Line
	1300 3050 1300 3100
Wire Wire Line
	1300 2725 1300 3050
Wire Wire Line
	1550 3050 1550 3075
Wire Wire Line
	1550 3075 1450 3075
Wire Wire Line
	1450 3075 1450 3200
Connection ~ 1450 3200
Wire Wire Line
	1650 3050 1650 3200
Connection ~ 1650 3200
Wire Wire Line
	2050 3050 1950 3050
Connection ~ 2050 3050
Wire Wire Line
	1650 3200 1650 3325
Wire Wire Line
	1450 3200 1450 3325
Wire Wire Line
	1650 3550 1650 3525
Wire Wire Line
	1650 3550 1450 3550
Wire Wire Line
	1450 3550 1450 3525
Connection ~ 1650 3550
Wire Notes Line
	700  3700 3800 3700
$Comp
L Connector_Generic:Conn_01x07 J10
U 1 1 6265DA02
P 1750 1325
F 0 "J10" H 1825 1725 50  0000 R CNN
F 1 "Conn_01x07" V 1875 1525 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x07_P2.54mm_Vertical_SMD_Pin1Left" H 1750 1325 50  0001 C CNN
F 3 "~" H 1750 1325 50  0001 C CNN
	1    1750 1325
	0    -1   -1   0   
$EndComp
$Comp
L power:VCC #PWR017
U 1 1 6265DA08
P 2050 1525
F 0 "#PWR017" H 2050 1375 50  0001 C CNN
F 1 "VCC" V 2050 1725 50  0000 C CNN
F 2 "" H 2050 1525 50  0001 C CNN
F 3 "" H 2050 1525 50  0001 C CNN
	1    2050 1525
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR016
U 1 1 6265DA0E
P 1850 1525
F 0 "#PWR016" H 1850 1275 50  0001 C CNN
F 1 "GND" V 1850 1325 50  0000 C CNN
F 2 "" H 1850 1525 50  0001 C CNN
F 3 "" H 1850 1525 50  0001 C CNN
	1    1850 1525
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR015
U 1 1 6265DA14
P 1750 1525
F 0 "#PWR015" H 1750 1375 50  0001 C CNN
F 1 "VCC" V 1750 1725 50  0000 C CNN
F 2 "" H 1750 1525 50  0001 C CNN
F 3 "" H 1750 1525 50  0001 C CNN
	1    1750 1525
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C1
U 1 1 6265DA27
P 1450 1900
F 0 "C1" H 1542 1946 50  0001 L CNN
F 1 "22pF" V 1550 1775 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1450 1900 50  0001 C CNN
F 3 "~" H 1450 1900 50  0001 C CNN
	1    1450 1900
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C2
U 1 1 6265DA2D
P 1650 1900
F 0 "C2" H 1742 1946 50  0001 L CNN
F 1 "22pF" V 1750 1775 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1650 1900 50  0001 C CNN
F 3 "~" H 1650 1900 50  0001 C CNN
	1    1650 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR030
U 1 1 6265DA33
P 1650 2025
F 0 "#PWR030" H 1650 1775 50  0001 C CNN
F 1 "GND" H 1800 1975 50  0000 C CNN
F 2 "" H 1650 2025 50  0001 C CNN
F 3 "" H 1650 2025 50  0001 C CNN
	1    1650 2025
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal_Small Y1
U 1 1 6265DA39
P 1550 1675
F 0 "Y1" H 1550 1900 50  0001 C CNN
F 1 "16Mhz" V 1550 1675 50  0000 C CNN
F 2 "Crystal:Crystal_SMD_0603-2Pin_6.0x3.5mm" H 1550 1675 50  0001 C CNN
F 3 "~" H 1550 1675 50  0001 C CNN
	1    1550 1675
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 1525 1550 1550
Wire Wire Line
	1550 1550 1450 1550
Wire Wire Line
	1450 1550 1450 1675
Connection ~ 1450 1675
Wire Wire Line
	1650 1525 1650 1675
Connection ~ 1650 1675
Wire Wire Line
	2050 1525 1950 1525
Connection ~ 2050 1525
Wire Wire Line
	1650 1675 1650 1800
Wire Wire Line
	1450 1675 1450 1800
Wire Wire Line
	1650 2025 1650 2000
Wire Wire Line
	1650 2025 1450 2025
Wire Wire Line
	1450 2025 1450 2000
Connection ~ 1650 2025
Wire Wire Line
	1300 1525 1450 1525
Wire Wire Line
	1650 1800 1950 1800
Wire Wire Line
	1950 1800 1950 1925
Connection ~ 1650 1800
Entry Wire Line
	3475 2375 3575 2275
Wire Wire Line
	3475 2375 3475 2500
Wire Wire Line
	3575 2500 3575 2375
Entry Wire Line
	3575 2375 3675 2275
Text Label 3475 2500 1    50   ~ 0
V_A4
Text Label 3575 2500 1    50   ~ 0
V_A5
Text Label 3475 975  1    50   ~ 0
V_A4
Text Label 3575 975  1    50   ~ 0
V_A5
Entry Wire Line
	3475 800  3575 700 
Entry Wire Line
	3600 800  3700 700 
Wire Wire Line
	3575 800  3600 800 
Wire Wire Line
	3575 800  3575 975 
Wire Wire Line
	3525 650  3600 650 
Wire Wire Line
	3600 650  3600 800 
Wire Wire Line
	3275 650  3325 650 
Wire Wire Line
	3275 650  3275 750 
Wire Bus Line
	3575 700  3700 700 
Text Label 8150 1500 0    50   ~ 0
TV_SYNC
Wire Wire Line
	6775 1400 6775 1900
Wire Wire Line
	6975 1400 6975 1900
Wire Wire Line
	7175 1400 7175 1600
Text Label 6775 1400 3    50   ~ 0
DIn
Text Label 6875 1400 3    50   ~ 0
CLK
Text Label 6975 1400 3    50   ~ 0
CE_
Text Label 7075 1400 3    50   ~ 0
SH-LD_
Wire Wire Line
	7075 1400 7075 1700
Text Label 7175 1400 3    50   ~ 0
CLR_
$Comp
L power:VCC #PWR0101
U 1 1 62FCB5B5
P 7175 1600
F 0 "#PWR0101" H 7175 1450 50  0001 C CNN
F 1 "VCC" V 7100 1700 50  0000 C CNN
F 2 "" H 7175 1600 50  0001 C CNN
F 3 "" H 7175 1600 50  0001 C CNN
	1    7175 1600
	0    1    1    0   
$EndComp
Entry Wire Line
	7075 1700 7175 1800
Wire Bus Line
	7175 1800 7425 1800
Entry Wire Line
	2825 800  2925 900 
Text Label 3050 900  0    50   ~ 0
SH-LD_
Wire Wire Line
	6875 1400 6875 1575
Text Label 6475 850  1    50   ~ 0
Dout
Wire Wire Line
	6475 650  6475 850 
Wire Wire Line
	5200 6175 5200 6100
Text Label 5075 6825 1    50   ~ 0
$C0
Wire Wire Line
	5075 6650 5075 6825
NoConn ~ 5075 6650
Text Label 2275 1525 3    50   ~ 0
TVD0
Text Label 2375 1525 3    50   ~ 0
TVD1
Text Label 2475 1525 3    50   ~ 0
TVD2
Text Label 2575 1525 3    50   ~ 0
TVD3
Text Label 2675 1525 3    50   ~ 0
TVD4
Text Label 2775 1525 3    50   ~ 0
TVD5
Text Label 2875 1525 3    50   ~ 0
TVD6
Text Label 2975 1525 3    50   ~ 0
TVD7
Entry Wire Line
	2275 1700 2375 1800
Entry Wire Line
	2375 1700 2475 1800
Entry Wire Line
	2475 1700 2575 1800
Entry Wire Line
	2575 1700 2675 1800
Entry Wire Line
	2675 1700 2775 1800
Entry Wire Line
	2775 1700 2875 1800
Entry Wire Line
	2875 1700 2975 1800
Entry Wire Line
	2975 1700 3075 1800
Wire Wire Line
	2275 1700 2275 1525
Wire Wire Line
	2375 1525 2375 1700
Wire Wire Line
	2475 1525 2475 1700
Wire Wire Line
	2575 1525 2575 1700
Wire Wire Line
	2675 1525 2675 1700
Wire Wire Line
	2775 1525 2775 1700
Wire Wire Line
	2875 1525 2875 1700
Wire Wire Line
	2975 1525 2975 1700
Text Label 5875 1400 3    50   ~ 0
TVD0
Text Label 5975 1400 3    50   ~ 0
TVD1
Text Label 6075 1400 3    50   ~ 0
TVD2
Text Label 6175 1400 3    50   ~ 0
TVD3
Text Label 6275 1400 3    50   ~ 0
TVD4
Text Label 6375 1400 3    50   ~ 0
TVD5
Text Label 6475 1400 3    50   ~ 0
TVD6
Text Label 6575 1400 3    50   ~ 0
TVD7
Entry Wire Line
	5875 1575 5975 1675
Entry Wire Line
	5975 1575 6075 1675
Entry Wire Line
	6075 1575 6175 1675
Entry Wire Line
	6175 1575 6275 1675
Entry Wire Line
	6275 1575 6375 1675
Entry Wire Line
	6375 1575 6475 1675
Entry Wire Line
	6475 1575 6575 1675
Entry Wire Line
	6575 1575 6675 1675
Wire Wire Line
	5875 1575 5875 1400
Wire Wire Line
	5975 1400 5975 1575
Wire Wire Line
	6075 1400 6075 1575
Wire Wire Line
	6175 1400 6175 1575
Wire Wire Line
	6275 1400 6275 1575
Wire Wire Line
	6475 1400 6475 1575
Wire Wire Line
	6575 1400 6575 1575
Wire Wire Line
	6375 1625 6400 1625
Wire Wire Line
	6400 1625 6400 1725
Wire Wire Line
	6450 1925 6400 1925
Text Label 4175 925  3    50   ~ 0
D_A1
Text Label 4375 925  3    50   ~ 0
D_A3
Text Label 4475 925  3    50   ~ 0
D_A4
Wire Wire Line
	4175 925  4175 1200
Wire Wire Line
	4275 925  4275 1200
Wire Wire Line
	4375 925  4375 1200
Wire Wire Line
	4475 925  4475 1200
Wire Wire Line
	4875 925  4875 1075
Text Label 4575 925  3    50   ~ 0
D_A5
Wire Wire Line
	4575 925  4575 1200
NoConn ~ 4575 1200
Entry Wire Line
	4175 1200 4275 1300
Entry Wire Line
	4275 1200 4375 1300
Entry Wire Line
	4375 1200 4475 1300
Entry Wire Line
	4475 1200 4575 1300
Text Label 3075 2500 1    50   ~ 0
D_A1
Text Label 3175 2500 1    50   ~ 0
D_A2
Text Label 3275 2500 1    50   ~ 0
D_A3
Text Label 3375 2500 1    50   ~ 0
D_A4
Text Label 4275 925  3    50   ~ 0
D_A2
Wire Wire Line
	3075 2500 3075 2325
Entry Wire Line
	3075 2325 3175 2225
Entry Wire Line
	3175 2325 3275 2225
Wire Wire Line
	3175 2325 3175 2500
Wire Wire Line
	3275 2325 3275 2500
Wire Wire Line
	3375 2325 3375 2500
Entry Wire Line
	3275 2325 3375 2225
Entry Wire Line
	3375 2325 3475 2225
Wire Notes Line
	3800 2200 3800 3700
Wire Notes Line
	3800 2200 700  2200
Wire Notes Line
	700  2200 700  3700
Wire Wire Line
	2150 1925 1950 1925
Wire Wire Line
	3275 750  3150 750 
Connection ~ 3275 750 
Wire Notes Line
	3800 575  700  575 
Wire Bus Line
	2150 500  7475 500 
Wire Bus Line
	7425 550  7425 1800
Wire Wire Line
	6975 1900 6775 1900
Connection ~ 6775 1900
Wire Wire Line
	3375 900  2925 900 
Wire Wire Line
	3375 900  3375 975 
Wire Bus Line
	2825 800  2825 550 
Wire Notes Line
	5500 3825 5500 4975
Wire Notes Line
	7750 3825 7750 4975
Wire Notes Line
	3925 3825 3925 4975
Wire Notes Line
	3925 4975 5500 4975
Text Label 6625 650  0    50   ~ 0
TV_VIDEO
Text Label 3150 1700 0    50   ~ 0
TV_SYNC
Wire Wire Line
	8150 1475 8150 1700
NoConn ~ 5200 5525
NoConn ~ 5300 5525
NoConn ~ 5400 5525
Wire Bus Line
	4900 1300 4900 2225
Wire Notes Line
	7375 2150 7375 575 
Wire Notes Line
	5700 2150 5700 575 
Wire Bus Line
	2150 500  2150 1800
Wire Notes Line
	3800 2150 700  2150
Wire Notes Line
	700  2150 700  575 
Wire Notes Line
	3800 2150 3800 575 
Wire Bus Line
	3700 700  3700 2275
Wire Wire Line
	3075 1525 3075 1700
Wire Wire Line
	8150 650  8150 900 
Wire Notes Line
	7775 1750 7775 575 
Wire Bus Line
	2825 550  7425 550 
Wire Notes Line
	7375 2150 5700 2150
Wire Bus Line
	7475 500  7475 2025
Text Label 8150 900  0    50   ~ 0
TV_VIDEO
Wire Wire Line
	7500 1700 7500 2175
Wire Wire Line
	7500 2175 5675 2175
Wire Wire Line
	5675 1700 5675 2175
Wire Wire Line
	3075 1700 5675 1700
Wire Notes Line
	8500 1750 8500 575 
Wire Notes Line
	8500 1750 7775 1750
Wire Notes Line
	7775 575  8500 575 
Wire Notes Line
	5075 2200 5075 3700
Wire Wire Line
	2775 3050 2775 3225
Wire Wire Line
	3325 4150 3325 4100
Wire Wire Line
	7550 6100 7550 6175
Text Label 7450 5525 1    50   ~ 0
OUT_2
Wire Wire Line
	7450 5225 7450 5275
Wire Wire Line
	7350 5225 7350 5525
Wire Wire Line
	7150 5225 7150 5275
Text Label 7150 5525 1    50   ~ 0
OUT_1
Wire Wire Line
	7150 5275 7250 5275
Connection ~ 7150 5275
Wire Wire Line
	7150 5275 7150 5525
Wire Wire Line
	7250 5275 7250 5525
Wire Wire Line
	6950 5250 6950 5475
Wire Notes Line
	8000 3700 8500 3700
Wire Notes Line
	8500 2200 8500 3700
Wire Notes Line
	8000 3700 8000 2200
Wire Wire Line
	8350 3350 8350 3425
Wire Wire Line
	10300 925  10300 1000
Wire Wire Line
	10300 1200 10300 1300
Wire Wire Line
	10675 1200 10675 925 
Wire Wire Line
	10675 925  10300 925 
Wire Wire Line
	10675 1300 10675 1525
Wire Wire Line
	10675 1525 10300 1525
Wire Notes Line
	9950 2025 10800 2025
Wire Notes Line
	10800 2025 10800 600 
Wire Notes Line
	9950 600  9950 2025
Wire Notes Line
	10800 600  9950 600 
Text Label 7100 4100 1    50   ~ 0
Video7
Text Label 7000 4100 1    50   ~ 0
Video
Text Label 6700 4100 1    50   ~ 0
Kbd7
Text Label 6300 4100 1    50   ~ 0
Kbd
Entry Wire Line
	7000 3775 7100 3875
Entry Wire Line
	6900 3775 7000 3875
Entry Wire Line
	6600 3775 6700 3875
Entry Wire Line
	6200 3775 6300 3875
Wire Wire Line
	6300 3875 6300 4100
Wire Wire Line
	6700 3875 6700 4100
Wire Wire Line
	7000 3875 7000 4100
Wire Wire Line
	7100 3875 7100 4100
Text Label 6600 3675 0    50   ~ 0
Kbd
Entry Wire Line
	6500 3775 6600 3675
Entry Wire Line
	5175 3775 5275 3875
Text Label 5275 4150 1    50   ~ 0
Kbd
Entry Wire Line
	3650 3775 3750 3875
Wire Wire Line
	3750 3875 3750 4150
Text Label 3750 4150 1    50   ~ 0
Kbd7
Entry Wire Line
	2175 3875 2275 3775
Wire Wire Line
	2175 3875 2175 4150
Text Label 2175 4150 1    50   ~ 0
Video
Text Label 2775 4150 1    50   ~ 0
Video7
Wire Wire Line
	2775 4150 2775 3875
Entry Wire Line
	2775 3875 2875 3775
Text Label 2575 3675 0    50   ~ 0
Video
Entry Wire Line
	2575 3675 2675 3775
Wire Wire Line
	2575 3050 2575 3675
Wire Bus Line
	3675 3300 3675 2775
Wire Bus Line
	3675 2775 2125 2775
Wire Bus Line
	2125 2775 2125 3900
Entry Wire Line
	4875 3900 4975 4000
Entry Wire Line
	4775 3900 4875 4000
Entry Wire Line
	4675 3900 4775 4000
Entry Wire Line
	4575 3900 4675 4000
Entry Wire Line
	4475 3900 4575 4000
Entry Wire Line
	4375 3900 4475 4000
Entry Wire Line
	4275 3900 4375 4000
Entry Wire Line
	4175 3900 4275 4000
Text Label 4975 4150 1    50   ~ 0
KD7
Text Label 4875 4150 1    50   ~ 0
KD6
Text Label 4775 4150 1    50   ~ 0
KD5
Text Label 4675 4150 1    50   ~ 0
KD4
Text Label 4575 4150 1    50   ~ 0
KD3
Text Label 4475 4150 1    50   ~ 0
KD2
Text Label 4375 4150 1    50   ~ 0
KD1
Wire Wire Line
	4975 4000 4975 4150
Wire Wire Line
	4875 4000 4875 4150
Wire Wire Line
	4775 4000 4775 4150
Wire Wire Line
	4675 4000 4675 4150
Wire Wire Line
	4575 4000 4575 4150
Wire Wire Line
	4475 4000 4475 4150
Wire Wire Line
	4375 4000 4375 4150
Wire Wire Line
	4275 4000 4275 4150
Text Label 4275 4150 1    50   ~ 0
KD0
Wire Notes Line
	3925 3825 5500 3825
$Comp
L Connector_Generic:Conn_01x08 J17
U 1 1 5FF06C4F
P 4575 4350
F 0 "J17" H 4600 4750 50  0000 R CNN
F 1 "Conn_01x08" V 4700 4525 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical_SMD_Pin1Left" H 4575 4350 50  0001 C CNN
F 3 "~" H 4575 4350 50  0001 C CNN
	1    4575 4350
	0    -1   1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J29
U 1 1 5FF0799A
P 4575 4500
F 0 "J29" H 4625 4900 50  0000 R CNN
F 1 "Conn_01x08" V 4700 4700 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical_SMD_Pin1Left" H 4575 4500 50  0001 C CNN
F 3 "~" H 4575 4500 50  0001 C CNN
	1    4575 4500
	0    -1   -1   0   
$EndComp
Wire Bus Line
	4075 3900 4075 4425
Text GLabel 2875 4150 1    50   Input ~ 0
VBIT7
Text GLabel 3600 4150 1    50   Input ~ 0
KBIT7
Wire Wire Line
	3650 4150 3600 4150
Wire Wire Line
	5275 3875 5275 4150
Wire Bus Line
	4075 4425 5575 4425
Text Label 4275 4700 3    50   ~ 0
D0
Text Label 4375 4700 3    50   ~ 0
D1
Text Label 4475 4700 3    50   ~ 0
D2
Text Label 4575 4700 3    50   ~ 0
D3
Text Label 4675 4700 3    50   ~ 0
D4
Text Label 4775 4700 3    50   ~ 0
D5
Text Label 4875 4700 3    50   ~ 0
D6
Text Label 4975 4700 3    50   ~ 0
D7
Wire Wire Line
	4275 4700 4275 4800
Wire Wire Line
	4375 4700 4375 4800
Wire Wire Line
	4475 4700 4475 4800
Wire Wire Line
	4575 4700 4575 4800
Wire Wire Line
	4675 4700 4675 4800
Wire Wire Line
	4775 4700 4775 4800
Wire Wire Line
	4875 4700 4875 4800
Wire Wire Line
	4975 4700 4975 4800
Entry Wire Line
	4575 4800 4675 4900
Entry Wire Line
	4675 4800 4775 4900
Entry Wire Line
	4775 4800 4875 4900
Entry Wire Line
	4875 4800 4975 4900
Entry Wire Line
	4975 4800 5075 4900
Wire Wire Line
	4075 5425 4075 5525
Wire Wire Line
	4175 5425 4175 5525
Wire Wire Line
	4275 5425 4275 5525
Wire Wire Line
	4375 5425 4375 5525
Wire Wire Line
	4475 5425 4475 5525
Wire Wire Line
	4575 5425 4575 5525
Wire Wire Line
	4675 5425 4675 5525
Text Label 4075 5525 1    50   ~ 0
D0
Text Label 4175 5525 1    50   ~ 0
D1
Text Label 4275 5525 1    50   ~ 0
D2
Text Label 4375 5525 1    50   ~ 0
D3
Text Label 4475 5525 1    50   ~ 0
D4
Text Label 4575 5525 1    50   ~ 0
D5
Text Label 4675 5525 1    50   ~ 0
D6
Text Label 4775 5525 1    50   ~ 0
D7
Entry Wire Line
	3975 5325 4075 5425
Entry Wire Line
	4075 5325 4175 5425
Entry Wire Line
	4175 5325 4275 5425
Entry Wire Line
	4275 5325 4375 5425
Entry Wire Line
	4375 5325 4475 5425
Entry Wire Line
	4475 5325 4575 5425
Entry Wire Line
	4575 5325 4675 5425
Wire Notes Line
	3875 3825 3875 4975
Wire Notes Line
	3875 4975 2525 4975
Wire Notes Line
	2525 3825 3875 3825
Wire Bus Line
	3975 5325 3975 5000
Wire Bus Line
	3975 5000 4375 5000
Entry Wire Line
	4475 4800 4575 4900
Entry Wire Line
	4375 4800 4475 4900
Entry Wire Line
	4275 4800 4375 4900
Entry Wire Line
	4675 5325 4775 5425
Text GLabel 4775 5275 1    50   Input ~ 0
D7
Wire Wire Line
	7600 4650 7600 4725
Wire Wire Line
	5000 5050 5900 5050
Wire Wire Line
	5000 5050 5000 5525
Wire Notes Line
	5750 3825 5750 4975
Wire Notes Line
	5750 3825 7750 3825
Wire Notes Line
	5750 4975 7750 4975
Text Label 5000 5525 1    50   ~ 0
A0
Text Label 5100 5525 1    50   ~ 0
A1
Text Label 6300 4650 3    50   ~ 0
A0
Text Label 6400 4650 3    50   ~ 0
A1
Text Label 6200 4650 3    50   ~ 0
W_
Text Label 6100 4650 3    50   ~ 0
R_
Wire Wire Line
	7150 5275 7075 5275
Wire Wire Line
	7075 5275 7075 4925
Wire Wire Line
	7075 4925 6100 4925
Wire Wire Line
	6100 4650 6100 4925
Wire Wire Line
	7450 5275 7525 5275
Wire Wire Line
	7525 5275 7525 4900
Wire Wire Line
	7525 4900 6200 4900
Wire Wire Line
	6200 4650 6200 4900
Connection ~ 7450 5275
Wire Wire Line
	7450 5275 7450 5525
Text Label 6700 4650 3    50   ~ 0
$D0
$Comp
L power:GND #PWR042
U 1 1 5FC9EB1C
P 6800 4650
F 0 "#PWR042" H 6800 4400 50  0001 C CNN
F 1 "GND" H 6805 4477 50  0000 C CNN
F 2 "" H 6800 4650 50  0001 C CNN
F 3 "" H 6800 4650 50  0001 C CNN
	1    6800 4650
	1    0    0    -1  
$EndComp
Text Label 5175 6825 1    50   ~ 0
$D0
Wire Wire Line
	6300 4800 5900 4800
Wire Wire Line
	5900 4800 5900 5050
Wire Wire Line
	6300 4800 6300 4650
Wire Wire Line
	6400 4850 5950 4850
Wire Wire Line
	6400 4850 6400 4650
Wire Wire Line
	6700 4650 6700 4950
Wire Wire Line
	6700 4950 6400 4950
Wire Wire Line
	6400 4950 6400 6475
Wire Wire Line
	6400 6475 5175 6475
Wire Wire Line
	5175 6475 5175 6825
Wire Bus Line
	5575 5000 5575 4425
$Comp
L power:GND #PWR045
U 1 1 6206ADBA
P 6125 5150
F 0 "#PWR045" H 6125 4900 50  0001 C CNN
F 1 "GND" H 6130 4977 50  0000 C CNN
F 2 "" H 6125 5150 50  0001 C CNN
F 3 "" H 6125 5150 50  0001 C CNN
	1    6125 5150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6125 5150 5825 5150
Wire Notes Line
	5675 6500 4425 6500
Wire Notes Line
	4425 6500 4425 7750
Wire Notes Line
	5675 6500 5675 7750
Wire Notes Line
	5725 7750 5725 6500
Wire Notes Line
	5725 6500 6925 6500
Wire Notes Line
	6925 6500 6925 7750
Wire Notes Line
	4350 7750 4350 6500
Wire Notes Line
	4350 6500 700  6500
Wire Notes Line
	700  6500 700  7750
Wire Notes Line
	700  6450 700  5025
$Comp
L Device:C_Small C20
U 1 1 60A2820B
P 10350 6050
F 0 "C20" V 10121 6050 50  0001 C CNN
F 1 "0.1uF" V 10213 6050 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10350 6050 50  0001 C CNN
F 3 "~" H 10350 6050 50  0001 C CNN
	1    10350 6050
	0    1    1    0   
$EndComp
Text Notes 10050 6400 1    50   ~ 0
Decoupling capacitors
$Comp
L power:GND #PWR08
U 1 1 60A2D3B0
P 10450 6200
F 0 "#PWR08" H 10450 5950 50  0001 C CNN
F 1 "GND" H 10455 6027 50  0000 C CNN
F 2 "" H 10450 6200 50  0001 C CNN
F 3 "" H 10450 6200 50  0001 C CNN
	1    10450 6200
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR07
U 1 1 60A2DBD9
P 10250 2350
F 0 "#PWR07" H 10250 2200 50  0001 C CNN
F 1 "VCC" H 10265 2523 50  0000 C CNN
F 2 "" H 10250 2350 50  0001 C CNN
F 3 "" H 10250 2350 50  0001 C CNN
	1    10250 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	10450 6050 10450 6200
$Comp
L Device:C_Small C19
U 1 1 60AB8903
P 10350 5800
F 0 "C19" V 10121 5800 50  0001 C CNN
F 1 "0.1uF" V 10213 5800 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10350 5800 50  0001 C CNN
F 3 "~" H 10350 5800 50  0001 C CNN
	1    10350 5800
	0    1    1    0   
$EndComp
Connection ~ 10250 5800
Wire Wire Line
	10250 5800 10250 6050
$Comp
L Device:C_Small C18
U 1 1 60AB9150
P 10350 5550
F 0 "C18" V 10121 5550 50  0001 C CNN
F 1 "0.1uF" V 10213 5550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10350 5550 50  0001 C CNN
F 3 "~" H 10350 5550 50  0001 C CNN
	1    10350 5550
	0    1    1    0   
$EndComp
Connection ~ 10250 5550
Wire Wire Line
	10250 5550 10250 5800
$Comp
L Device:C_Small C17
U 1 1 60AB98F8
P 10350 5300
F 0 "C17" V 10121 5300 50  0001 C CNN
F 1 "0.1uF" V 10213 5300 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10350 5300 50  0001 C CNN
F 3 "~" H 10350 5300 50  0001 C CNN
	1    10350 5300
	0    1    1    0   
$EndComp
Connection ~ 10250 5300
Wire Wire Line
	10250 5300 10250 5550
$Comp
L Device:C_Small C16
U 1 1 60ABA150
P 10350 5025
F 0 "C16" V 10121 5025 50  0001 C CNN
F 1 "0.1uF" V 10213 5025 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10350 5025 50  0001 C CNN
F 3 "~" H 10350 5025 50  0001 C CNN
	1    10350 5025
	0    1    1    0   
$EndComp
Connection ~ 10250 5025
Wire Wire Line
	10250 5025 10250 5300
$Comp
L Device:C_Small C15
U 1 1 60ABA982
P 10350 4750
F 0 "C15" V 10121 4750 50  0001 C CNN
F 1 "0.1uF" V 10213 4750 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10350 4750 50  0001 C CNN
F 3 "~" H 10350 4750 50  0001 C CNN
	1    10350 4750
	0    1    1    0   
$EndComp
Connection ~ 10250 4750
Wire Wire Line
	10250 4750 10250 5025
$Comp
L Device:C_Small C14
U 1 1 60ABB1D1
P 10350 4500
F 0 "C14" V 10121 4500 50  0001 C CNN
F 1 "0.1uF" V 10213 4500 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10350 4500 50  0001 C CNN
F 3 "~" H 10350 4500 50  0001 C CNN
	1    10350 4500
	0    1    1    0   
$EndComp
Connection ~ 10250 4500
Wire Wire Line
	10250 4500 10250 4750
$Comp
L Device:C_Small C13
U 1 1 60AC314F
P 10350 4225
F 0 "C13" V 10121 4225 50  0001 C CNN
F 1 "0.1uF" V 10213 4225 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10350 4225 50  0001 C CNN
F 3 "~" H 10350 4225 50  0001 C CNN
	1    10350 4225
	0    1    1    0   
$EndComp
Connection ~ 10250 4225
Wire Wire Line
	10250 4225 10250 4500
$Comp
L Device:C_Small C12
U 1 1 60AF96EF
P 10350 3975
F 0 "C12" V 10121 3975 50  0001 C CNN
F 1 "0.1uF" V 10213 3975 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10350 3975 50  0001 C CNN
F 3 "~" H 10350 3975 50  0001 C CNN
	1    10350 3975
	0    1    1    0   
$EndComp
Connection ~ 10250 3975
Wire Wire Line
	10250 3975 10250 4225
$Comp
L Device:C_Small C11
U 1 1 60AF9BCA
P 10350 3700
F 0 "C11" V 10121 3700 50  0001 C CNN
F 1 "0.1uF" V 10213 3700 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10350 3700 50  0001 C CNN
F 3 "~" H 10350 3700 50  0001 C CNN
	1    10350 3700
	0    1    1    0   
$EndComp
Connection ~ 10250 3700
Wire Wire Line
	10250 3700 10250 3975
$Comp
L Device:C_Small C10
U 1 1 60AFB6C2
P 10350 3400
F 0 "C10" V 10121 3400 50  0001 C CNN
F 1 "0.1uF" V 10213 3400 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10350 3400 50  0001 C CNN
F 3 "~" H 10350 3400 50  0001 C CNN
	1    10350 3400
	0    1    1    0   
$EndComp
Connection ~ 10250 3400
Wire Wire Line
	10250 3400 10250 3700
$Comp
L Device:C_Small C9
U 1 1 60AFBCB5
P 10350 3125
F 0 "C9" V 10121 3125 50  0001 C CNN
F 1 "0.1uF" V 10213 3125 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10350 3125 50  0001 C CNN
F 3 "~" H 10350 3125 50  0001 C CNN
	1    10350 3125
	0    1    1    0   
$EndComp
Connection ~ 10250 3125
Wire Wire Line
	10250 3125 10250 3400
$Comp
L Device:C_Small C8
U 1 1 60AFC1AC
P 10350 2850
F 0 "C8" V 10121 2850 50  0001 C CNN
F 1 "0.1uF" V 10213 2850 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10350 2850 50  0001 C CNN
F 3 "~" H 10350 2850 50  0001 C CNN
	1    10350 2850
	0    1    1    0   
$EndComp
Connection ~ 10250 2850
Wire Wire Line
	10250 2850 10250 3125
$Comp
L Device:C_Small C7
U 1 1 60AFC713
P 10350 2600
F 0 "C7" V 10121 2600 50  0001 C CNN
F 1 "0.1uF" V 10213 2600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10350 2600 50  0001 C CNN
F 3 "~" H 10350 2600 50  0001 C CNN
	1    10350 2600
	0    1    1    0   
$EndComp
Connection ~ 10250 2600
Wire Wire Line
	10250 2600 10250 2850
Wire Wire Line
	10450 6050 10450 5800
Connection ~ 10450 6050
Connection ~ 10450 2850
Connection ~ 10450 3125
Wire Wire Line
	10450 3125 10450 2850
Connection ~ 10450 3400
Wire Wire Line
	10450 3400 10450 3125
Connection ~ 10450 3700
Wire Wire Line
	10450 3700 10450 3400
Connection ~ 10450 3975
Wire Wire Line
	10450 3975 10450 3700
Connection ~ 10450 4225
Wire Wire Line
	10450 4225 10450 3975
Connection ~ 10450 4500
Wire Wire Line
	10450 4500 10450 4225
Connection ~ 10450 4750
Wire Wire Line
	10450 4750 10450 4500
Connection ~ 10450 5025
Wire Wire Line
	10450 5025 10450 4750
Connection ~ 10450 5300
Wire Wire Line
	10450 5300 10450 5025
Connection ~ 10450 5550
Wire Wire Line
	10450 5550 10450 5300
Connection ~ 10450 5800
Wire Wire Line
	10450 5800 10450 5550
Wire Wire Line
	10450 2600 10450 2850
Wire Wire Line
	10250 2350 10250 2600
Wire Notes Line
	9950 6450 10575 6450
Wire Notes Line
	10575 6450 10575 2075
Wire Notes Line
	10575 2075 9950 2075
Wire Notes Line
	9950 2075 9950 6450
$Comp
L Device:LED_Small D18
U 1 1 60CE1C06
P 10925 6025
F 0 "D18" V 10872 6105 50  0001 L CNN
F 1 "Green" H 10825 5925 50  0000 L CNN
F 2 "LED_THT:LED_D3.0mm" H 10925 6025 50  0001 C CNN
F 3 "~" H 10925 6025 50  0001 C CNN
	1    10925 6025
	1    0    0    -1  
$EndComp
Text Notes 10750 6400 1    50   ~ 0
LEDs for tests
NoConn ~ 11025 6025
NoConn ~ 10825 6025
$Comp
L Device:LED_Small D19
U 1 1 60D97870
P 10925 6250
F 0 "D19" V 10872 6330 50  0001 L CNN
F 1 "Green" H 10825 6150 50  0000 L CNN
F 2 "LED_THT:LED_D3.0mm" H 10925 6250 50  0001 C CNN
F 3 "~" H 10925 6250 50  0001 C CNN
	1    10925 6250
	1    0    0    -1  
$EndComp
NoConn ~ 11025 6250
NoConn ~ 10825 6250
$Comp
L Device:LED_Small D16
U 1 1 60DD1E3D
P 10925 5575
F 0 "D16" V 10872 5655 50  0001 L CNN
F 1 "Green" H 10825 5475 50  0000 L CNN
F 2 "LED_THT:LED_D3.0mm" H 10925 5575 50  0001 C CNN
F 3 "~" H 10925 5575 50  0001 C CNN
	1    10925 5575
	1    0    0    -1  
$EndComp
NoConn ~ 11025 5575
NoConn ~ 10825 5575
$Comp
L Device:LED_Small D17
U 1 1 60DD1E45
P 10925 5800
F 0 "D17" V 10872 5880 50  0001 L CNN
F 1 "Green" H 10825 5700 50  0000 L CNN
F 2 "LED_THT:LED_D3.0mm" H 10925 5800 50  0001 C CNN
F 3 "~" H 10925 5800 50  0001 C CNN
	1    10925 5800
	1    0    0    -1  
$EndComp
NoConn ~ 11025 5800
NoConn ~ 10825 5800
$Comp
L Device:LED_Small D14
U 1 1 60E0D2AA
P 10925 5125
F 0 "D14" V 10872 5205 50  0001 L CNN
F 1 "Green" H 10825 5025 50  0000 L CNN
F 2 "LED_THT:LED_D3.0mm" H 10925 5125 50  0001 C CNN
F 3 "~" H 10925 5125 50  0001 C CNN
	1    10925 5125
	1    0    0    -1  
$EndComp
NoConn ~ 11025 5125
NoConn ~ 10825 5125
$Comp
L Device:LED_Small D15
U 1 1 60E0D2B2
P 10925 5350
F 0 "D15" V 10872 5430 50  0001 L CNN
F 1 "Green" H 10825 5250 50  0000 L CNN
F 2 "LED_THT:LED_D3.0mm" H 10925 5350 50  0001 C CNN
F 3 "~" H 10925 5350 50  0001 C CNN
	1    10925 5350
	1    0    0    -1  
$EndComp
NoConn ~ 11025 5350
NoConn ~ 10825 5350
$Comp
L Device:LED_Small D12
U 1 1 60E0D2BA
P 10925 4675
F 0 "D12" V 10872 4755 50  0001 L CNN
F 1 "Green" H 10825 4575 50  0000 L CNN
F 2 "LED_THT:LED_D3.0mm" H 10925 4675 50  0001 C CNN
F 3 "~" H 10925 4675 50  0001 C CNN
	1    10925 4675
	1    0    0    -1  
$EndComp
NoConn ~ 11025 4675
NoConn ~ 10825 4675
$Comp
L Device:LED_Small D13
U 1 1 60E0D2C2
P 10925 4900
F 0 "D13" V 10872 4980 50  0001 L CNN
F 1 "Green" H 10825 4800 50  0000 L CNN
F 2 "LED_THT:LED_D3.0mm" H 10925 4900 50  0001 C CNN
F 3 "~" H 10925 4900 50  0001 C CNN
	1    10925 4900
	1    0    0    -1  
$EndComp
NoConn ~ 11025 4900
NoConn ~ 10825 4900
$Comp
L Device:LED_Small D10
U 1 1 60E4B27D
P 10925 4200
F 0 "D10" V 10872 4280 50  0001 L CNN
F 1 "Green" H 10825 4100 50  0000 L CNN
F 2 "LED_THT:LED_D3.0mm" H 10925 4200 50  0001 C CNN
F 3 "~" H 10925 4200 50  0001 C CNN
	1    10925 4200
	1    0    0    -1  
$EndComp
NoConn ~ 11025 4200
NoConn ~ 10825 4200
$Comp
L Device:LED_Small D11
U 1 1 60E4B285
P 10925 4425
F 0 "D11" V 10872 4505 50  0001 L CNN
F 1 "Green" H 10825 4325 50  0000 L CNN
F 2 "LED_THT:LED_D3.0mm" H 10925 4425 50  0001 C CNN
F 3 "~" H 10925 4425 50  0001 C CNN
	1    10925 4425
	1    0    0    -1  
$EndComp
NoConn ~ 11025 4425
NoConn ~ 10825 4425
$Comp
L Device:LED_Small D8
U 1 1 60E4B28D
P 10925 3750
F 0 "D8" V 10872 3830 50  0001 L CNN
F 1 "Green" H 10825 3650 50  0000 L CNN
F 2 "LED_THT:LED_D3.0mm" H 10925 3750 50  0001 C CNN
F 3 "~" H 10925 3750 50  0001 C CNN
	1    10925 3750
	1    0    0    -1  
$EndComp
NoConn ~ 11025 3750
NoConn ~ 10825 3750
$Comp
L Device:LED_Small D9
U 1 1 60E4B295
P 10925 3975
F 0 "D9" V 10872 4055 50  0001 L CNN
F 1 "Green" H 10825 3875 50  0000 L CNN
F 2 "LED_THT:LED_D3.0mm" H 10925 3975 50  0001 C CNN
F 3 "~" H 10925 3975 50  0001 C CNN
	1    10925 3975
	1    0    0    -1  
$EndComp
NoConn ~ 11025 3975
NoConn ~ 10825 3975
$Comp
L Device:LED_Small D6
U 1 1 60E4B29D
P 10925 3300
F 0 "D6" V 10872 3380 50  0001 L CNN
F 1 "Green" H 10825 3200 50  0000 L CNN
F 2 "LED_THT:LED_D3.0mm" H 10925 3300 50  0001 C CNN
F 3 "~" H 10925 3300 50  0001 C CNN
	1    10925 3300
	1    0    0    -1  
$EndComp
NoConn ~ 11025 3300
NoConn ~ 10825 3300
$Comp
L Device:LED_Small D7
U 1 1 60E4B2A5
P 10925 3525
F 0 "D7" V 10872 3605 50  0001 L CNN
F 1 "Green" H 10825 3425 50  0000 L CNN
F 2 "LED_THT:LED_D3.0mm" H 10925 3525 50  0001 C CNN
F 3 "~" H 10925 3525 50  0001 C CNN
	1    10925 3525
	1    0    0    -1  
$EndComp
NoConn ~ 11025 3525
NoConn ~ 10825 3525
$Comp
L Device:LED_Small D4
U 1 1 60E4B2AD
P 10925 2850
F 0 "D4" V 10872 2930 50  0001 L CNN
F 1 "Green" H 10825 2750 50  0000 L CNN
F 2 "LED_THT:LED_D3.0mm" H 10925 2850 50  0001 C CNN
F 3 "~" H 10925 2850 50  0001 C CNN
	1    10925 2850
	1    0    0    -1  
$EndComp
NoConn ~ 11025 2850
NoConn ~ 10825 2850
$Comp
L Device:LED_Small D5
U 1 1 60E4B2B5
P 10925 3075
F 0 "D5" V 10872 3155 50  0001 L CNN
F 1 "Green" H 10825 2975 50  0000 L CNN
F 2 "LED_THT:LED_D3.0mm" H 10925 3075 50  0001 C CNN
F 3 "~" H 10925 3075 50  0001 C CNN
	1    10925 3075
	1    0    0    -1  
$EndComp
NoConn ~ 11025 3075
NoConn ~ 10825 3075
Wire Notes Line
	10650 6450 11125 6450
Wire Notes Line
	11125 6450 11125 2700
Wire Notes Line
	10650 2700 10650 6450
Wire Notes Line
	10650 2700 11125 2700
Text Label 7600 3050 3    50   ~ 0
KD7
Text Label 7500 3050 3    50   ~ 0
KD6
Text Label 7400 3050 3    50   ~ 0
KD5
Text Label 7300 3050 3    50   ~ 0
KD4
Text Label 7200 3050 3    50   ~ 0
KD3
Text Label 7100 3050 3    50   ~ 0
KD2
Text Label 7000 3050 3    50   ~ 0
KD1
Text Label 6900 3050 3    50   ~ 0
KD0
$Comp
L Connector_Generic:Conn_01x07 J12
U 1 1 61064133
P 5775 2850
F 0 "J12" H 5850 3250 50  0000 R CNN
F 1 "Conn_01x07" V 5900 3050 50  0001 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x07_P2.54mm_Vertical_SMD_Pin1Left" H 5775 2850 50  0001 C CNN
F 3 "~" H 5775 2850 50  0001 C CNN
	1    5775 2850
	0    -1   -1   0   
$EndComp
$Comp
L power:VCC #PWR0102
U 1 1 61064139
P 6075 3050
F 0 "#PWR0102" H 6075 2900 50  0001 C CNN
F 1 "VCC" V 6075 3250 50  0000 C CNN
F 2 "" H 6075 3050 50  0001 C CNN
F 3 "" H 6075 3050 50  0001 C CNN
	1    6075 3050
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 6106413F
P 5875 3050
F 0 "#PWR0103" H 5875 2800 50  0001 C CNN
F 1 "GND" V 5875 2850 50  0000 C CNN
F 2 "" H 5875 3050 50  0001 C CNN
F 3 "" H 5875 3050 50  0001 C CNN
	1    5875 3050
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0104
U 1 1 61064145
P 5775 3050
F 0 "#PWR0104" H 5775 2900 50  0001 C CNN
F 1 "VCC" V 5775 3250 50  0000 C CNN
F 2 "" H 5775 3050 50  0001 C CNN
F 3 "" H 5775 3050 50  0001 C CNN
	1    5775 3050
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R7
U 1 1 6106414B
P 5325 3200
F 0 "R7" V 5250 3150 50  0000 L CNN
F 1 "10k" V 5325 3125 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 5325 3200 50  0001 C CNN
F 3 "~" H 5325 3200 50  0001 C CNN
	1    5325 3200
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0105
U 1 1 61064151
P 5325 3325
F 0 "#PWR0105" H 5325 3175 50  0001 C CNN
F 1 "VCC" H 5340 3498 50  0000 C CNN
F 2 "" H 5325 3325 50  0001 C CNN
F 3 "" H 5325 3325 50  0001 C CNN
	1    5325 3325
	-1   0    0    1   
$EndComp
Wire Wire Line
	5325 3325 5325 3300
$Comp
L Device:C_Small C5
U 1 1 61064158
P 5475 3425
F 0 "C5" H 5567 3471 50  0001 L CNN
F 1 "22pF" V 5575 3300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5475 3425 50  0001 C CNN
F 3 "~" H 5475 3425 50  0001 C CNN
	1    5475 3425
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C6
U 1 1 6106415E
P 5675 3425
F 0 "C6" H 5767 3471 50  0001 L CNN
F 1 "22pF" V 5775 3300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5675 3425 50  0001 C CNN
F 3 "~" H 5675 3425 50  0001 C CNN
	1    5675 3425
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 61064164
P 5675 3550
F 0 "#PWR0106" H 5675 3300 50  0001 C CNN
F 1 "GND" H 5825 3500 50  0000 C CNN
F 2 "" H 5675 3550 50  0001 C CNN
F 3 "" H 5675 3550 50  0001 C CNN
	1    5675 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal_Small Y3
U 1 1 6106416A
P 5575 3200
F 0 "Y3" H 5575 3425 50  0001 C CNN
F 1 "16Mhz" V 5575 3200 50  0000 C CNN
F 2 "Crystal:Crystal_SMD_0603-2Pin_6.0x3.5mm" H 5575 3200 50  0001 C CNN
F 3 "~" H 5575 3200 50  0001 C CNN
	1    5575 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5325 3050 5475 3050
Wire Wire Line
	5325 3050 5325 3100
Wire Wire Line
	5575 3050 5575 3075
Wire Wire Line
	5575 3075 5475 3075
Wire Wire Line
	5475 3075 5475 3200
Connection ~ 5475 3200
Wire Wire Line
	5675 3050 5675 3200
Connection ~ 5675 3200
Wire Wire Line
	6075 3050 5975 3050
Connection ~ 6075 3050
Wire Wire Line
	5675 3200 5675 3325
Wire Wire Line
	5475 3200 5475 3325
Wire Wire Line
	5675 3550 5675 3525
Wire Wire Line
	5675 3550 5475 3550
Wire Wire Line
	5475 3550 5475 3525
Connection ~ 5675 3550
Wire Wire Line
	6600 3050 6600 3675
Wire Wire Line
	6800 3050 6800 3225
Wire Wire Line
	6900 3050 6900 3200
Wire Wire Line
	7000 3050 7000 3200
Wire Wire Line
	7100 3050 7100 3200
Wire Wire Line
	7200 3050 7200 3200
Wire Wire Line
	7300 3050 7300 3200
Wire Wire Line
	7400 3050 7400 3200
Wire Wire Line
	7500 3050 7500 3200
Wire Wire Line
	7600 3050 7600 3200
Entry Wire Line
	6900 3200 7000 3300
Entry Wire Line
	7000 3200 7100 3300
Entry Wire Line
	7100 3200 7200 3300
Entry Wire Line
	7200 3200 7300 3300
Entry Wire Line
	7300 3200 7400 3300
Entry Wire Line
	7400 3200 7500 3300
Entry Wire Line
	7500 3200 7600 3300
Entry Wire Line
	7600 3200 7700 3300
Wire Wire Line
	5950 5100 5100 5100
Wire Wire Line
	5100 5100 5100 5525
Wire Wire Line
	5950 4850 5950 5100
Wire Wire Line
	5175 4150 5175 4025
Text Label 5175 4150 1    50   ~ 0
C
Wire Wire Line
	2275 4025 2275 4150
Text Label 2275 4150 1    50   ~ 0
OE_
Wire Wire Line
	7500 2350 7400 2350
Wire Wire Line
	7500 2350 7500 2500
Wire Wire Line
	7000 2350 6925 2350
Wire Notes Line
	7525 2200 7525 2100
Wire Notes Line
	5075 2200 7525 2200
Wire Notes Line
	7750 3700 7750 2100
Wire Notes Line
	7525 2100 7750 2100
Wire Notes Line
	7750 3700 5075 3700
Text GLabel 1325 5125 0    50   Input ~ 0
LOWRATE
Wire Wire Line
	1325 5125 1525 5125
NoConn ~ 1525 5125
Wire Bus Line
	2075 4900 2075 5000
Wire Bus Line
	2075 5000 3075 5000
Wire Bus Line
	4375 4900 4375 5000
Wire Bus Line
	7800 5000 7800 3300
Wire Bus Line
	5575 5000 7800 5000
Wire Bus Line
	5975 1675 5975 2025
Wire Bus Line
	5975 2025 7475 2025
Text Label 5275 6825 1    50   ~ 0
$E0
Text Label 5375 6825 1    50   ~ 0
$F0
Wire Wire Line
	5275 6625 6225 6625
Wire Wire Line
	5275 6625 5275 6825
Wire Wire Line
	6225 6625 6225 6825
Text Label 6125 6825 1    50   ~ 0
$F0
Text Label 6225 6825 1    50   ~ 0
$E0
Wire Wire Line
	6125 6675 5375 6675
Wire Wire Line
	5375 6675 5375 6825
Wire Wire Line
	6125 6675 6125 6825
Wire Wire Line
	3850 6575 6325 6575
Wire Wire Line
	3850 6575 3850 7300
Text Label 3850 7250 1    50   ~ 0
ROM_SELECT_
Text Notes 3750 7675 0    30   ~ 0
ROM
Text Notes 4100 7675 0    30   ~ 0
RAM
Wire Wire Line
	3450 7225 3450 7350
Text Label 5625 6100 3    50   ~ 0
A12
Text Label 5725 6100 3    50   ~ 0
A13
Text Label 5825 6100 3    50   ~ 0
A14
Text Label 5925 6100 3    50   ~ 0
A15
Wire Wire Line
	5625 6100 5625 6250
Wire Wire Line
	5725 6100 5725 6250
Wire Wire Line
	5825 6100 5825 6250
Wire Wire Line
	5925 6100 5925 6250
Entry Wire Line
	5625 6250 5725 6350
Entry Wire Line
	5725 6250 5825 6350
Entry Wire Line
	5825 6250 5925 6350
Entry Wire Line
	5925 6250 6025 6350
Wire Bus Line
	5725 6350 5725 6425
Wire Bus Line
	5725 6425 4400 6425
Wire Bus Line
	4400 6425 4400 7650
Text Label 4575 7400 3    50   ~ 0
A12
Text Label 4675 7400 3    50   ~ 0
A13
Text Label 4775 7400 3    50   ~ 0
A14
Text Label 4975 7400 3    50   ~ 0
A15
Wire Wire Line
	4975 7400 4975 7550
Wire Wire Line
	4775 7400 4775 7550
Wire Wire Line
	4675 7400 4675 7550
Wire Wire Line
	4575 7400 4575 7550
Entry Wire Line
	4575 7550 4675 7650
Entry Wire Line
	4675 7550 4775 7650
Entry Wire Line
	4775 7550 4875 7650
Entry Wire Line
	4975 7550 5075 7650
Wire Wire Line
	5475 7475 5475 7400
Wire Wire Line
	6725 7400 6725 7475
Wire Wire Line
	6325 6575 6325 6825
Text Label 6325 6750 0    50   ~ 0
ROM_SELECT_
Connection ~ 2350 7325
Wire Wire Line
	2350 7325 2350 7300
Wire Wire Line
	2450 7325 2450 7100
Wire Wire Line
	2450 7100 3350 7100
Wire Wire Line
	3350 7100 3350 6725
Wire Wire Line
	3350 6725 4050 6725
Wire Wire Line
	4050 6725 4050 7300
Wire Wire Line
	2350 7325 2450 7325
Connection ~ 4050 7300
Wire Wire Line
	6150 2775 7900 2775
Wire Wire Line
	7900 2775 7900 2100
Text Label 8350 2625 1    50   ~ 0
PS2_DATA
Wire Wire Line
	8350 2100 8350 2625
Text Label 6500 3050 3    50   ~ 0
PS2_DATA
Wire Wire Line
	6700 3050 6700 3525
Text Label 8250 2625 1    50   ~ 0
PS2_CLK
Text Label 6700 3050 3    50   ~ 0
PS2_CLK
Wire Wire Line
	6500 3525 6150 3525
Wire Wire Line
	6150 2775 6150 3525
Wire Wire Line
	6500 3050 6500 3525
Wire Wire Line
	8250 2175 8250 2625
Wire Wire Line
	7500 1700 8150 1700
Wire Wire Line
	6475 650  8150 650 
Wire Wire Line
	8350 2100 7900 2100
Wire Wire Line
	8250 2175 7975 2175
Wire Wire Line
	7975 2175 7975 3525
Wire Wire Line
	7975 3525 6700 3525
Text Notes 8325 6350 0    40   ~ 0
1 – MOD1. Memory (ROM + RAM)\n2 – MOD2. Memory decoder\n3 – MOD3. AND gate (ROM select)\n4 – MOD4. CPU\n5 – MOD5. NAND gate (CPU R/W)\n6 – MOD6. Video port\n7 – MOD7. BIT7 ports (Kbd7 & Video7)\n8 – MOD8. Keyboard port\n9 – MOD9. Ports decoder\n10 - MOD10. Video controller\n11 - MOD11. Keyboard controller\n12 - MOD12. TV out (Hi-Res video) controller\n13 – MOD13. Display module (2.8" TFT 320x240)\n14 – MOD14. Shift register\n15 – MOD15. Address&bus connector\n16 – MOD16. Keyboard connector (PS/2)\n17 – MOD17. Video connector (RCA)
Text Notes 9275 5200 2    50   ~ 10
SmartyKit 1 molules list
Wire Notes Line
	9875 6450 9875 5025
Wire Notes Line
	9875 5025 8250 5025
Wire Notes Line
	8250 5025 8250 6450
Wire Notes Line
	8250 6450 9875 6450
Wire Wire Line
	4775 5275 4775 5525
Wire Wire Line
	6375 1400 6375 1625
Wire Wire Line
	3475 750  3475 975 
Wire Bus Line
	3575 2275 3700 2275
Wire Wire Line
	3875 5275 3875 5525
Wire Bus Line
	5725 6350 6025 6350
Wire Bus Line
	3175 2225 4900 2225
Wire Bus Line
	4275 1300 4900 1300
Wire Bus Line
	4400 7650 5075 7650
Wire Bus Line
	1375 4900 2075 4900
Wire Bus Line
	3075 5325 3775 5325
Wire Bus Line
	2975 3300 3675 3300
Wire Bus Line
	5975 1675 6675 1675
Wire Bus Line
	3975 5325 4675 5325
Wire Bus Line
	4375 4900 5075 4900
Wire Bus Line
	4075 3900 4875 3900
Wire Bus Line
	2150 1800 3075 1800
Wire Bus Line
	1175 3900 2125 3900
Wire Bus Line
	7000 3300 7800 3300
Wire Bus Line
	2275 3775 7000 3775
$EndSCHEMATC
