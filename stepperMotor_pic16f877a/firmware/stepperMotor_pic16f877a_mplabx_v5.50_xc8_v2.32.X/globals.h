/*
 * PIC16F877A Samples
 * Sample 14: Stepper Motor
 * Author: David Nascimento Coelho
 * Last Update: 2018/05/11
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

#define _XTAL_FREQ 20000000         // Processor frequency for delay functions

#define EN1 PORTCbits.RC1       // Enable 1 of L298N or L293D
#define EN2 PORTCbits.RC2       // Enable 2 of L298N or L293D
#define IN1 PORTDbits.RD4       // IN1 of L298N or L293D
#define IN2 PORTDbits.RD5       // IN2 of L298N or L293D
#define IN3 PORTDbits.RD6       // IN3 of L298N or L293D
#define IN4 PORTDbits.RD7       // IN4 of L298N or L293D
#define delay_quantity 500      // how many ms stay at the same position
