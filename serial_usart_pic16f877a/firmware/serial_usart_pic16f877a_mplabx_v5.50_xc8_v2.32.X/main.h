/*
 * PIC16F877A Samples
 * Sample 11: Serial Communication
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
void init(void);
void main(void);