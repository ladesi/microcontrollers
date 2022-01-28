/*
 * PIC16F877A Samples
 * Sample 15: Servo Motor (PWM by software)
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
#define M1 PORTCbits.RC0        // Servo Motor 1
#define M2 PORTCbits.RC1        // Servo Motor 1
#define T0_pin  PORTBbits.RB1   // tmr0 temporization
#define T1_pin  PORTBbits.RB2   // tmr1 temporization
#define RB_pin  PORTBbits.RB3   // portb interrupts

#define but0    !PORTBbits.RB0   //
#define but1    !PORTBbits.RB4   //
#define but2    !PORTBbits.RB5   //
#define but3    !PORTBbits.RB6   //
#define but4    !PORTBbits.RB7   //

// Servomotor angle
/* 1000us ---- 180º
     50us ---- 9º */

#define max_duty 40             // Max Angle (40*50uS = 2ms = +90º)
#define min_duty 20             // Min Angle (20*50uS = 1ms = -90º)

#define rec_tmr0 125            // number of tmr0 counts
#define rec_tmr1 50000          // number of tmr1 counts

// VARIABLES

int cont = 0;                   // Duty Cycle Counter
unsigned int duty1;             // Current angle of servo 1
unsigned int duty2;             // Current angle of servo 2
