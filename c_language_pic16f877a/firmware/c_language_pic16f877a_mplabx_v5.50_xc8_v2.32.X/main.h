/*
 * PIC16F877A Samples
 * Sample 02: C coding
 * Author: David Nascimento Coelho
 * Last Update: 2022/01/25
 */

// DEFINE ".h" JUST ONE TIME

#ifndef MAIN_H
#define	MAIN_H
#endif	/* MAIN_H */

// LIBRARIES INCLUDE

#include <stdint.h>

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

#define count_min 0b00110011    // binary base
#define count_max 65            // decimal base
#define level_min 025           // octal base
#define level_max 0xFD          // hexadecimal base
#define letter 'A'              // ASCII coding

// VARIABLES

/* Access bits and bytes of the same variable - Definition */
typedef union
{
	struct
	{
		unsigned bit0 : 1;
		unsigned bit1 : 1;
		unsigned bit2 : 1;
		unsigned bit3 : 1;
		unsigned bit4 : 1;
		unsigned bit5 : 1;
		unsigned bit6 : 1;
		unsigned bit7 : 1;
	}bits;
	char byte;
}generic_byte;

/* Access bit and bytes of the same variable - create variable */
generic_byte var1;

/* Standard variables */
//bit flag1 = 0;            // 01 bit  - cannot be initialized with "1"
uint8_t flag1 = 0;          // 08 bit  - from <stdint> library
unsigned char letra = 'a';  // 08 bits - from 0 to 255 (ASCII coding)
signed char num1 = 8;       // 08 bits - from -128 to 127
unsigned int acc1 = 300;    // 16 bits - from 0 to 65.535
signed int sum1 = 5000;     // 16 bits - from -32.768 to 32.767
float divisao = 1.3;        // 24 bits - floating point number

/* especial modifiers */
__bank(2) int logEntry;   // indicates in which bank the variable will be stored
__eeprom char title[20];  // indicates that variable will be stored at eeprom
volatile int ad_read;     // variable can be modified several times
const char tabela[] = {0x34,0x56}; // variable will not be modified

// FUNCTIONS

void main(void);
void functions_c_coding(void);
void binary_logic(void);
void assembly_instructions(void);