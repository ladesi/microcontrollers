/*
 * PIC16F877A Samples
 * Sample 04: External Interrupt
 * Author: David Nascimento Coelho
 * Last Update: 2022/01/25
 */

// DEFINE ".h" JUST ONE TIME

#ifndef MAIN_H
#define	MAIN_H
#endif	/* MAIN_H */

// CONFIGURATION BITS

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// Another way: #pragma config WDTE = ON, FOSC = XT, CPD = ON, ...

// CONSTANTS

#define _XTAL_FREQ 20000000     // Processor frequency for delay functions

#define bot1 !PORTBbits.RB0     // button at RB0 pin
#define led1 PORTBbits.RB1      // led at RB1 pin

// FUNCTIONS

void __interrupt() myIsr(void);
void init(void);
void main(void);
