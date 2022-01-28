/*
 * PIC16F877A Samples
 * Sample 10: AD Conversion and LCD
 * Author: David Nascimento Coelho
 * Last Update: 2022/01/25
 */

// Guard condition: contents of this file
// are not included more than once.

#ifndef MAIN_H
#define	MAIN_H
#endif	/* MAIN_H */

// FUNCTIONS

void __interrupt() myIsr(void);
void amost1(unsigned int *value);
unsigned int amost2(void);
void init(void);
void main(void);