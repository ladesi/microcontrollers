/*
 * PIC16F877A Samples
 * Sample 05: PORTB Interrupt on Change
 * Author: David Nascimento Coelho
 * Last Update: 2022/01/25
 */

// Guard condition: contents of this file
// are not included more than once.

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

#define _XTAL_FREQ 20000000

#define botao1 !PORTBbits.RB0
#define led1    PORTBbits.RB1
#define botao2 !PORTBbits.RB4
#define botao3 !PORTBbits.RB5
#define botao4 !PORTBbits.RB6
#define botao5 !PORTBbits.RB7

#define leds PORTC

#define testbit(var,bit) ((var) & (1 <<(bit)))
#define setbit(var,bit)  ((var) |= (1 << (bit)))
#define clrbit(var,bit)  ((var) &= ~(1 << (bit)))
#define invbit(var,bit)  ((var) ^= (1<<(bit)))

// FUNCTIONS

void __interrupt() myIsr();
void init(void);
void main(void);