/*
 * PIC16F877A Samples
 * Sample 13: Internal PWM
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

#define tm2_pin PORTDbits.RD1   // timer2 output

#define rec_tmr2 255            // number of tmr2 counts - 1

// VARIABLES

volatile unsigned int count2;   // timer 2 counter

unsigned char percent_pw1;      // percentage of pwm 1
unsigned char percent_pw2;      // percentage of pwm 2
