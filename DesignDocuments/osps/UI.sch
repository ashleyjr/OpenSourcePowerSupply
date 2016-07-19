EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:CRCW060310K0FKEA
LIBS:STM32F302R8T6
LIBS:C0603C221J5GACTU
LIBS:wurth_742792651
LIBS:ABLS2-8.000MHZ-D4Y-T
LIBS:header-7x1-254
LIBS:header-3x1-254
LIBS:header-8x1-254
LIBS:header-6x1-254
LIBS:header-10x1-254
LIBS:header-8x2-254
LIBS:osps-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
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
L Header,8x2,2.54mm CN?
U 1 1 579013CE
P 2800 1150
F 0 "CN?" H 3400 1200 60  0000 C CNN
F 1 "Header,8x2,2.54mm" H 3200 2200 60  0000 C CNN
F 2 "" H 2800 1150 60  0000 C CNN
F 3 "" H 2800 1150 60  0000 C CNN
	1    2800 1150
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR?
U 1 1 579014F3
P 2950 2350
F 0 "#PWR?" H 2950 2100 50  0001 C CNN
F 1 "GND" H 2950 2200 50  0000 C CNN
F 2 "" H 2950 2350 50  0000 C CNN
F 3 "" H 2950 2350 50  0000 C CNN
	1    2950 2350
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR?
U 1 1 57901511
P 1300 1150
F 0 "#PWR?" H 1300 1000 50  0001 C CNN
F 1 "+3.3V" H 1300 1290 50  0000 C CNN
F 2 "" H 1300 1150 50  0000 C CNN
F 3 "" H 1300 1150 50  0000 C CNN
	1    1300 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 2050 1300 2050
Wire Wire Line
	1300 2050 1300 1150
NoConn ~ 1950 1350
NoConn ~ 2800 1350
NoConn ~ 2800 1950
NoConn ~ 2800 1750
NoConn ~ 1950 1750
NoConn ~ 2800 1650
NoConn ~ 1950 1650
Wire Wire Line
	1950 1950 1650 1950
Wire Wire Line
	1950 1850 1650 1850
Wire Wire Line
	2800 2050 2950 2050
Wire Wire Line
	2950 2050 2950 2350
Wire Wire Line
	2800 1850 3150 1850
Wire Wire Line
	2800 1550 3150 1550
Wire Wire Line
	2800 1450 3150 1450
Wire Wire Line
	1950 1550 1650 1550
Wire Wire Line
	1950 1450 1650 1450
Text Label 1700 1950 0    60   ~ 0
RS
Text Label 1700 1850 0    60   ~ 0
E
Text Label 1700 1450 0    60   ~ 0
DB7
Text Label 2900 1450 0    60   ~ 0
DB6
Text Label 1700 1550 0    60   ~ 0
DB5
Text Label 2900 1550 0    60   ~ 0
DB4
Text Label 2900 1850 0    60   ~ 0
RW
Text HLabel 1650 1450 0    60   BiDi ~ 0
DB7
Text HLabel 1650 1550 0    60   BiDi ~ 0
DB5
Text HLabel 1650 1850 0    60   Input ~ 0
E
Text HLabel 1650 1950 0    60   BiDi ~ 0
RS
Text HLabel 3150 1850 2    60   BiDi ~ 0
RW
Text HLabel 3150 1550 2    60   BiDi ~ 0
DB4
Text HLabel 3150 1450 2    60   BiDi ~ 0
DB6
$EndSCHEMATC
