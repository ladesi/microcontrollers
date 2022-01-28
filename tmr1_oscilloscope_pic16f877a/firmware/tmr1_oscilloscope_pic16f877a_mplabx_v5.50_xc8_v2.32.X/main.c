/*
 * PIC16F877A Samples
 * Sample 09: Timer1 and Oscilloscope
 * Author: David Nascimento Coelho
 * Last Update: 2022/01/25
 */

// LIBRARIES INCLUDE

#include <xc.h>
#include "main.h"

// FUNCTIONS

/* Interruption Service Routine */
void __interrupt() myIsr(void)
{
    // Extern Interruption
    if(INTCONbits.INTE && INTCONbits.INTF)
    {
        INTCONbits.INTF = 0;
        led1 = !led1;
    }
    
    // Timer0
    if(INTCONbits.TMR0IE && INTCONbits.TMR0IF)
    {
         TMR0 = 256 - rec_tmr0;
         count0++;
         INTCONbits.TMR0IF = 0;
    }
    
    // Timer1
    if(PIE1bits.TMR1IE && PIR1bits.TMR1IF)
    {
        TMR1 = 65536 - rec_tmr1;
        count1++;
        PIR1bits.TMR1IF = 0;
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

    TRISA = 0b00000000;
    TRISB = 0b00000001;
    TRISC = 0b00000000;
    PORTD = 0b00000000;
    TRISE = 0b00000000;
    
// INT EXT & TMR0
    OPTION_REG = 0b10000001;
 /*	   			   ||||||||
	   			   |||||||ps0 -> preescaler 1:4
	   			   ||||||ps1 -^
	   			   |||||ps2 -^
	  			   ||||PSA    (=0 pre-escaler para timer0)
	   			   |||TMR0SE  (qdo como contador)
	   			   ||TMR0CS   (=0 timer)
	  			   |INTEDG    (int ext / =0 falling edge)
	   			   !PORTB Pull-up enable (=1 disabled)
*/
    INTCON = 0b01110000;
/*	   		   ||||||||
	   		   |||||||RBIF
	   		   ||||||INTF
	   		   |||||TMR0IF
	  		   ||||RBIE
	   		   |||INTE
	   		   ||TMR0IE
	  		   |PEIE		// TIMER 1 e 2, AD, Serial... 
	   		   GIE			// are considered peripherals
*/    
    TMR0 = 256 - rec_tmr0;
    count0 = 0;

// TMR1
    T1CON = 0b00000001;
/*	   		  ||||||||
	   		  |||||||TMR1ON (=1 enable timer1)
	   		  ||||||TMR1CS (=0 internal clock)
     		  |||||T1SYNC (ignored when TMR1CS = 0)
	  		  ||||T1OSCEN (=0 disabled)
	   		  |||T1CKPS0 -> preescaler 1:1 (1, 2, 4, 8)
	   		  ||T1CKPS1 -^
	  		  |unimplemented
	   		  unimplemented 
*/     
    TMR1 = 65536 - rec_tmr1;
    count1 = 0;

    PIE1bits.TMR1IE = 1;

// CCP
    CMCON = 0x07;   // disable comparators
}

void main(void) 
{
    // disable all interrupts
    INTCONbits.GIE = 0;
    
    // initialization routine
    init();
    
    // enable all interrupts
    INTCONbits.GIE = 1;
    
    // Infinity loop
    while(1)
    {
        if(count0 == 5000)
        {
            rele1 = !rele1;
            count0 = 0;
        }
        if(count1 == 5000)
        {
            out_tmr1 = !out_tmr1;
            count1 = 0;
        }
        
    }
    
    return;
}
