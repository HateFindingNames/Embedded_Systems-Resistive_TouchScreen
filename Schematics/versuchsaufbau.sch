EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:R R_yh
U 1 1 61BDF6AC
P 4100 2850
F 0 "R_yh" H 4170 2896 50  0000 L CNN
F 1 "R" H 4170 2805 50  0000 L CNN
F 2 "" V 4030 2850 50  0001 C CNN
F 3 "~" H 4100 2850 50  0001 C CNN
	1    4100 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R_yl
U 1 1 61BE4B4D
P 4100 3550
F 0 "R_yl" H 4170 3596 50  0000 L CNN
F 1 "R" H 4170 3505 50  0000 L CNN
F 2 "" V 4030 3550 50  0001 C CNN
F 3 "~" H 4100 3550 50  0001 C CNN
	1    4100 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R_xl
U 1 1 61BE503B
P 4450 3200
F 0 "R_xl" V 4243 3200 50  0000 C CNN
F 1 "R" V 4334 3200 50  0000 C CNN
F 2 "" V 4380 3200 50  0001 C CNN
F 3 "~" H 4450 3200 50  0001 C CNN
	1    4450 3200
	0    1    1    0   
$EndComp
$Comp
L Device:R R_xh
U 1 1 61BE5B18
P 3750 3200
F 0 "R_xh" V 3543 3200 50  0000 C CNN
F 1 "R" V 3634 3200 50  0000 C CNN
F 2 "" V 3680 3200 50  0001 C CNN
F 3 "~" H 3750 3200 50  0001 C CNN
	1    3750 3200
	0    1    1    0   
$EndComp
Wire Wire Line
	4100 3000 4100 3200
Wire Wire Line
	3900 3200 4100 3200
Connection ~ 4100 3200
Wire Wire Line
	4100 3200 4100 3400
Wire Wire Line
	4100 3200 4300 3200
Wire Notes Line
	3450 2600 4750 2600
Wire Notes Line
	4750 2600 4750 3800
Wire Notes Line
	4750 3800 3450 3800
Wire Notes Line
	3450 3800 3450 2600
Wire Wire Line
	4100 2700 4100 2500
Wire Wire Line
	4100 2500 4850 2500
Wire Wire Line
	4850 2500 4850 3100
Wire Wire Line
	4100 3700 4100 3850
Wire Wire Line
	4100 3850 4850 3850
Wire Wire Line
	3600 3200 3400 3200
Wire Wire Line
	3400 2350 4900 2350
$Comp
L power:GND #PWR?
U 1 1 61BEFB57
P 7550 2050
F 0 "#PWR?" H 7550 1800 50  0001 C CNN
F 1 "GND" H 7555 1877 50  0000 C CNN
F 2 "" H 7550 2050 50  0001 C CNN
F 3 "" H 7550 2050 50  0001 C CNN
	1    7550 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 2200 7300 2100
Wire Wire Line
	7300 2100 7200 2100
Wire Wire Line
	7100 2100 7100 2200
Wire Wire Line
	7200 2200 7200 2100
Connection ~ 7200 2100
Wire Wire Line
	7200 2100 7100 2100
Wire Wire Line
	7200 2100 7200 1900
Wire Wire Line
	7200 1900 7550 1900
Wire Wire Line
	7550 1900 7550 2050
Text Label 5100 3000 0    50   ~ 0
XH
Wire Wire Line
	3400 2350 3400 3200
Wire Wire Line
	4900 2350 4900 3000
Wire Wire Line
	4850 3300 4850 3850
Text Label 5100 3200 0    50   ~ 0
XL
Text Label 5100 3100 0    50   ~ 0
YH
Text Label 5100 3300 0    50   ~ 0
YL
NoConn ~ 6700 3500
NoConn ~ 6700 3700
NoConn ~ 6700 3900
NoConn ~ 7700 2600
NoConn ~ 7700 2700
NoConn ~ 7700 2800
NoConn ~ 7700 2900
NoConn ~ 7700 3000
NoConn ~ 7700 3100
NoConn ~ 7700 3200
NoConn ~ 7700 3300
NoConn ~ 7700 3400
NoConn ~ 7700 3500
NoConn ~ 7700 3700
NoConn ~ 7700 3800
NoConn ~ 7700 3900
NoConn ~ 7100 4300
NoConn ~ 7000 4300
$Comp
L Device:R R2
U 1 1 61C0417A
P 6250 2550
F 0 "R2" H 6320 2596 50  0000 L CNN
F 1 "10k" H 6320 2505 50  0000 L CNN
F 2 "" V 6180 2550 50  0001 C CNN
F 3 "~" H 6250 2550 50  0001 C CNN
	1    6250 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 61C05778
P 5850 2550
F 0 "R1" H 5920 2596 50  0000 L CNN
F 1 "10k" H 5920 2505 50  0000 L CNN
F 2 "" V 5780 2550 50  0001 C CNN
F 3 "~" H 5850 2550 50  0001 C CNN
	1    5850 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 2400 5850 2250
Wire Wire Line
	5850 2250 6050 2250
Wire Wire Line
	6250 2250 6250 2400
Wire Wire Line
	6050 2250 6050 2100
Wire Wire Line
	6050 2250 6250 2250
Connection ~ 6050 2250
$Comp
L power:+5V #PWR?
U 1 1 61C0905D
P 6050 2100
F 0 "#PWR?" H 6050 1950 50  0001 C CNN
F 1 "+5V" H 6065 2273 50  0000 C CNN
F 2 "" H 6050 2100 50  0001 C CNN
F 3 "" H 6050 2100 50  0001 C CNN
	1    6050 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 2700 6250 3100
Connection ~ 6250 3100
Wire Wire Line
	6250 3100 6700 3100
Wire Wire Line
	7300 4300 7300 4650
$Comp
L power:+5V #PWR?
U 1 1 61C0C59F
P 7600 4650
F 0 "#PWR?" H 7600 4500 50  0001 C CNN
F 1 "+5V" H 7615 4823 50  0000 C CNN
F 2 "" H 7600 4650 50  0001 C CNN
F 3 "" H 7600 4650 50  0001 C CNN
	1    7600 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 4650 7600 4650
Text Notes 3500 4600 0    50   ~ 0
XH\nXL\nYH\nYL\n
Text Notes 3800 4600 0    50   ~ 0
HIGH\nLOW\nADC\nHiZ
Text Notes 3500 4200 0    50   ~ 0
X Read
Text Notes 5050 4600 0    50   ~ 0
XH\nXL\nYH\nYL\n
Text Notes 5350 4600 0    50   ~ 0
ADC\nHiZ\nHIGH\nLOW
Text Notes 5050 4200 0    50   ~ 0
Y Read
$Comp
L MCU_Module:Arduino_Leonardo U1
U 1 1 61C2137C
P 7200 3300
F 0 "U1" H 7200 1700 50  0000 C CNN
F 1 "Arduino_Leonardo" H 7200 1800 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 7200 3300 50  0001 C CIN
F 3 "https://www.arduino.cc/en/Main/ArduinoBoardLeonardo" H 7200 3300 50  0001 C CNN
	1    7200 3300
	-1   0    0    1   
$EndComp
NoConn ~ 6700 2500
NoConn ~ 6700 2600
NoConn ~ 6700 2800
NoConn ~ 6700 2900
Text Notes 4350 3800 2    50   ~ 0
Resistive Touch Screen
Wire Notes Line
	3450 4100 6500 4100
Wire Notes Line
	3450 4200 6500 4200
Wire Notes Line
	3450 4650 6500 4650
Wire Wire Line
	4900 3000 5850 3000
Wire Wire Line
	5850 2700 5850 3000
Connection ~ 5850 3000
Wire Wire Line
	5850 3000 6700 3000
Wire Wire Line
	4850 3100 6250 3100
Wire Wire Line
	4600 3200 6700 3200
Wire Wire Line
	4850 3300 6700 3300
Text Notes 3500 5300 0    50   ~ 0
R1, R2 internal pullup
Text Notes 3500 5150 0    50   ~ 0
XH\nXL\nYH\nYL\n
Text Notes 3800 5150 0    50   ~ 0
HiZ\nLOW\nHiZ\nADC
Text Notes 3500 4750 0    50   ~ 0
Check fingered state
Wire Notes Line
	3450 4750 6500 4750
Wire Notes Line
	3450 5200 6500 5200
$Comp
L Switch:SW_SPST SW1
U 1 1 61D9FDC8
P 8400 3600
F 0 "SW1" H 8400 3835 50  0000 C CNN
F 1 "Jumper Wire" H 8400 3744 50  0000 C CNN
F 2 "" H 8400 3600 50  0001 C CNN
F 3 "~" H 8400 3600 50  0001 C CNN
	1    8400 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 3600 8200 3600
Wire Wire Line
	8600 3600 8800 3600
Wire Wire Line
	8800 3600 8800 3800
$Comp
L power:GND #PWR?
U 1 1 61DA5BB7
P 8800 3800
F 0 "#PWR?" H 8800 3550 50  0001 C CNN
F 1 "GND" H 8805 3627 50  0000 C CNN
F 2 "" H 8800 3800 50  0001 C CNN
F 3 "" H 8800 3800 50  0001 C CNN
	1    8800 3800
	1    0    0    -1  
$EndComp
$EndSCHEMATC
