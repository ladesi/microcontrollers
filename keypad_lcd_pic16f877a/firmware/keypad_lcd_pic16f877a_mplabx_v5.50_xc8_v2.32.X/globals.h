/*
 * PIC16F877A Samples
 * Sample 19: 4x4 Keypad
 * Author: David Nascimento Coelho
 * Last Update: 2022/01/25
 */

// Guard condition: contents of this file
// are not included more than once.

#ifndef GLOBALS_H
#define	GLOBALS_H
#endif	/* GLOBALS_H */

// CONFIGURATION BITS

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// CONSTANTS

#define _XTAL_FREQ 20000000     // Processor frequency for delay functions

#define bot1     !PORTBbits.RB0 // button at RB0 pin
#define led1     PORTBbits.RB1  // led at RB1 pin

#define lin1    PORTCbits.RC0   // lin1 of keypad
#define lin2    PORTCbits.RC1   // lin2 of keypad
#define lin3    PORTCbits.RC2   // lin3 of keypad
#define lin4    PORTCbits.RC3   // lin4 of keypad
#define col1    PORTCbits.RC4   // col1 of keypad
#define col2    PORTCbits.RC5   // col2 of keypad
#define col3    PORTCbits.RC6   // col3 of keypad
#define col4    PORTCbits.RC7   // col4 of keypad

/* LCD: Always define: */
#define LCD_nbits 8             // number of LCD data bits
#define LCD_RS	PORTEbits.RE0   // LCD command/character selection
#define LCD_EN	PORTEbits.RE1   // LCD enable pin

/* LCD: define on 8 bits mode: */
#define LCD_dat PORTD           // LCD byte for command and character

/* LCD: define on 4 bits mode: */
//#define LCD4	PORTDbits.RD4   // bit 4 of lcd
//#define LCD5	PORTDbits.RD5   // bit 5 of lcd
//#define LCD6	PORTDbits.RD6   // bit 6 of lcd
//#define LCD7	PORTDbits.RD7   // bit 7 of lcd

// VARIABLES

volatile unsigned int ad_value; // get value of conversion
unsigned char ad_char_val[5];   // receive char value