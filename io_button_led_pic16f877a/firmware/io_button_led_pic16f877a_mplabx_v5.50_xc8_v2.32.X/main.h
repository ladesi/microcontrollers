/*
 * PIC16F877A Samples
 * Sample 03: IO ports
 * Author: David Nascimento Coelho
 * Review: Luan Gomes Magalh�es Lima
 * Last Update: 2022/01/25
 * Last review: 2023/09/13
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
#pragma config LVP = OFF         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// Another way: #pragma config WDTE = ON, FOSC = XT, CPD = ON, ...

// CONSTANTS

#define _XTAL_FREQ 20000000     // Processor frequency for delay functions

#define bot1 !PORTDbits.RD0     // button at RB0 pin
#define led1 PORTDbits.RD1      // led at RB1 pin

// FUNCTIONS

void init(void);
void main(void);
void blink_led(void);
void blink_if_button(void);
void button_trigger(void);