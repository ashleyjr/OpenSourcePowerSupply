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
Sheet 1 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 1150 1050 1400 950 
U 5785F670
F0 "Processor" 60
F1 "processor.sch" 60
F2 "PA8_DISP_RS" B R 2550 1400 60 
F3 "PB14_DISP_DB4" B R 2550 1600 60 
F4 "PB15_DISP_DB5" B R 2550 1700 60 
F5 "PC6_DISP_DB6" B R 2550 1800 60 
F6 "PC7_DISP_DB7" B R 2550 1900 60 
F7 "PC8_DISP_E" O R 2550 1300 60 
F8 "PC9_DISP_RW" B R 2550 1500 60 
$EndSheet
$Sheet
S 3000 1050 1200 950 
U 578E9575
F0 "UI" 60
F1 "UI.sch" 60
F2 "DB7" B L 3000 1900 60 
F3 "DB5" B L 3000 1700 60 
F4 "E" I L 3000 1300 60 
F5 "RS" B L 3000 1400 60 
F6 "RW" B L 3000 1500 60 
F7 "DB4" B L 3000 1600 60 
F8 "DB6" B L 3000 1800 60 
$EndSheet
Wire Wire Line
	3000 1300 2550 1300
Wire Wire Line
	2550 1400 3000 1400
Wire Wire Line
	3000 1500 2550 1500
Wire Wire Line
	2550 1600 3000 1600
Wire Wire Line
	3000 1700 2550 1700
Wire Wire Line
	2550 1800 3000 1800
Wire Wire Line
	3000 1900 2550 1900
$EndSCHEMATC
