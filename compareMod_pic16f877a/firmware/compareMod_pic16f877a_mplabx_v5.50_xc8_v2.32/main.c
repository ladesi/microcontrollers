/*
 * PIC16F877A Samples
 * Sample 21: Compare Module
 * Author: David Nascimento Coelho
 * Last Update: 2022/01/10
 */

// LIBRARIES INCLUDE

#include <xc.h>
#include "main.h"
#include "globals.h"

// FUNCTIONS

void __interrupt() myIsr(void) {
    
    // Extern Interruption
    if (INTCONbits.INTE && INTCONbits.INTF) {
        INTCONbits.INTF = 0;
        led1 = ~led1;
    }
}

/* Set all Needed registers */
void init(void) {
    // I/O
    PORTA = 0b00000000;
    PORTB = 0b00000000;
    PORTC = 0b00000000;
    TRISD = 0b00000000;
    PORTE = 0b00000000;
    
    TRISA = 0b00000001;
    TRISB = 0b00000001;
    TRISC = 0b00000000; 
    PORTD = 0b00000000;
    TRISE = 0b00000000;
    
    // INT EXT & TMR0
    OPTION_REG = 0b10000001;
    /*             ||||||||
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
    /*	   	   ||||||||
               |||||||RBIF
               ||||||INTF
               |||||TMR0IF
               ||||RBIE
               |||INTE
               ||TMR0IE
               |PEIE		//TIMER 1 e 2, AD, Serial, CCPs... 
               GIE			//sao considerados perifericos
    */
    
    // TIMER 1
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
    TMR1 = 0;
    
    PIR1bits.TMR1IF = 0;
    
    // CCP
    
    CCPR1 = 2000;
    
    CCP1CON = 0b00001001;
/*	 	       ||||||||
	    	   |||||||CCP1M0 -> Mode Select bits
	  		   ||||||CCP1M1 -^  (1001 => Compare)
		       |||||CCP1M2 -^   (clear ccp pin)
	 	       ||||CCP1M3 -^    
		       |||CCP1Y ->      least LSBs of PWM duty-cicle
		       ||CCP1X -^       (not used for comparator)
		       |0               (not implemented)
               0                (not implemented)
*/
    PIR1bits.CCP1IF = 0;
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
    while(1){
        while(PIR1bits.CCP1IF == 0); // wait flag to be set
        TMR1 = 0;
        PIR1bits.CCP1IF = 0;
        CCP1CON = 0b00001000;
        CCPR1 = 3000;
        while(PIR1bits.CCP1IF == 0); // wait flag to be set
        TMR1 = 0;
        PIR1bits.CCP1IF = 0;
        CCP1CON = 0b00001001;
        CCPR1 = 2000;
    }
    return;
}
