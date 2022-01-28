/*
 * PIC16F877A Samples
 * Serial Communication Library
 * Author: David Nascimento Coelho
 * Last Update: 2022/01/25
 */

// LIBRARIES INCLUDE

#include <xc.h>
#include "usart.h"

// Send char
void putch(unsigned char byte)
{
    while(!PIR1bits.TXIF)
        continue;
    TXREG = byte;
}

// Send string
void send_str( const char * str)
{
	while(*str)
	{
		putch(*str++);
	}
}

// Receive char
unsigned char getch() 
{
	while(!RCIF)	
		continue;
	return RCREG;
}

// Receive char and send same
unsigned char getche(void)
{
	unsigned char c;
	putch(c = getch());
	return c;
}
