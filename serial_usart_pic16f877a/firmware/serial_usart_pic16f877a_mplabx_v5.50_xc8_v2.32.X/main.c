/*
 * PIC16F877A Samples
 * Sample 11: Serial Communication
 * Author: David Nascimento Coelho
 * Last Update: 2022/01/25
 */

// LIBRARIES INCLUDE

#include <xc.h>
#include <stdint.h>
#include "globals.h"
#include "usart.h"

// FUNCTIONS

/* Interruption Service Routine */
void __interrupt() myIsr(void)
{
    // External Interruption
    if(INTCONbits.INTE && INTCONbits.INTF)
    {
        INTCONbits.INTF = 0;
        led1 = ~led1;
    }
    // Serial Rx
    if(PIE1bits.RCIE && PIR1bits.RCIF)
    {
        letra = RCREG;
        flag_rx = 1;
    }
}

/* Set all Needed registers */
void init(void)
{
// I/O
    PORTA = 0b00000000;
    PORTB = 0b00000000;
    PORTC = 0b00000000;
    TRISD = 0b00000000;
    PORTE = 0b00000000;

    TRISA = 0b00000001;
    TRISB = 0b00000001;
    TRISC = 0b10000000;
    PORTD = 0b00000000;
    TRISE = 0b00000000;
    
// INT EXT & TMR0
    OPTION_REG = 0b10000001;
 /*	   			   ||||||||
	   			   |||||||ps0 -> preescaler 1:4
	   			   ||||||ps1 -^
	   			   |||||ps2 -^
	  			   ||||PSA (=0 pre-escaler para timer0)
	   			   |||TMR0SE (qdo como contador)
	   			   ||TMR0CS (=0 timer)
	  			   |INTEDG (int ext / =0 falling edge)
	   			   !PORTB Pull-up enable (=1 disabled)
*/
    INTCON = 0b01010000;
/*	   		   ||||||||
	   		   |||||TMR0IF
	   		   |||||||RBIF
	   		   ||||||INTF
	  		   ||||RBIE
	   		   |||INTE
	   		   ||TMR0IE
	  		   |PEIE		//TIMER 1 e 2, AD, Serial... 
	   		   GIE			//sao considerados perifericos
*/    

// USART
	TXSTA = 0b00100100;		//datasheet pg. 118
/*	   		  ||||||||
	   		  |||||||TX9D	(9o bit - can be parity)
	   		  ||||||TRMT	TSR status (=1 TSR empty)
	   		  |||||BRGH		(baud rate -> =1 high)
	  		  ||||(n)		(not implemented)
	   		  |||SYNC		(=0 Assynchronous)
	   		  ||TXEN		(enable Tx)
	  		  |TX9			(enable 9 bits Tx)
	   		  CSRC			(sinc: master/slave)
*/

	RCSTA = 0b10010000;		//datasheet pg. 120
/*	   		  ||||||||
	   		  |||||||RX9D	(9o bit - can be parity)
	   		  ||||||OERR	(overrun error - |see file of)
	   		  |||||FERR		(framing error - |USART => ERROS)
	  		  ||||ADDEN		(for 9 bits. =0 disable)
	   		  |||CREN		(continous receive, =1 enable)
	   		  ||SREN		(dont care)
	  		  |RX9			(habilita 9 bits Rx)
	   		  SPEN			(serial enable)
*/

	SPBRG = 129;	// BR = 9600 (pg. 116 datasheet)
    flag_rx = 0;    // Indicates that a char was received

// INTERRUPT PERIPHERALS

	PIE1 = 0b00100000;
/*	   		 ||||||||
	   		 |||||||TMR1IE	(TIMER 1)
	   		 ||||||TMR2IE	(TIMER 2)
	   		 |||||CCP1IE	(Modulo Comparador 1)
	  		 ||||SSPIE		(Synchronous Serial Port)
	   		 |||TXIE		(Tx Serial)
	   		 ||RCIE			(Rx Serial)
	  		 |ADIE			(AD)
	   		 PSPIE			(Parallel Slave Port)
*/

// CCP
    CMCON = 0x07;   // desabilita modulos comparadores
}

void main(void) 
{
    // disable all interrupts
    INTCONbits.GIE = 0;
    
    // initialization routine
    init();
    
    // enable all interrupts
    INTCONbits.GIE = 1;
    
    // infinity loop
    while(1)
    {
    // serial communication
        if(flag_rx)
        {
            putch(letra);
            putch('\n');
            if(letra == 'l')
                led2 = 1;
            if(letra == 'd')
                led2 = 0;
            flag_rx = 0;
        }
    }
    
    return;
}
