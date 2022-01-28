/*
 * PIC16F877A Samples
 * Sample 12: Timer 2
 * Author: David Nascimento Coelho
 * Last Update: 2022/01/25
 */

// LIBRARIES INCLUDE

#include <xc.h>
#include "globals.h"

// FUNCTIONS

/* Interruption Service Routine */
void __interrupt() myIsr(void)
{
    // Extern Interruption
    if(INTCONbits.INTE && INTCONbits.INTF)
    {
        INTCONbits.INTF = 0;
        led1 = ~led1;
    }
    
    // Timer 2
    if (PIE1bits.TMR2IE && PIR1bits.TMR2IF)
    {
        PIR1bits.TMR2IF = 0;
        count2 = count2 + 1;
        if(count2 == 100)
        {
            tm2_pin = ~tm2_pin;
            count2 = 0;
        }
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
	   		   |||||||RBIF
	   		   ||||||INTF
	   		   |||||TMR0IF
	  		   ||||RBIE
	   		   |||INTE
	   		   ||TMR0IE
	  		   |PEIE		//TIMER 1 e 2, AD, Serial... 
	   		   GIE			//sao considerados perifericos
*/    

// INTERRUPT PERIFERICOS

	PIE1 = 0b00000010;
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

	PIE2 = 0b00000000;
/*	   		 ||||||||
	   		 |||||||CCP2IE	(Modulo Comparador 2)
	   		 ||||||(n)		(nao implementado)
	   		 |||||(n)		(nao implementado)
	  		 ||||BCLIE		(Bus Colision)
	   		 |||EEIE		(EEPROM Write)
	   		 ||(n)			(nao implementado)		
	  		 |CMIE			(Comparador)
	   		 (n)			(nao implementado)
*/
    
// TIMER 2 & PWM
    PR2 = rec_tmr2;             // TMR2 counts from 0 to PR2

    T2CON = 0b01111111;
/*		      ||||||||
	    	  |||||||T2CKPS0	(Pre-Scaler)
	  		  ||||||T2CKPS1		(1:1, 1:4, 1:16, 1:16)
		      |||||TMR20N		(liga timer 2)
	 	      ||||TOUTPS0		(Post-Scale)
		      |||TOUTPS1		(de 1:1 a 1:16)
		      ||TOUTPS2
		      |TOUTPS3
	  		  0					(not implemented)
*/
    count2 = 0;
  
	CMCON = 0b00000111;			//Pg. 137 Datasheet
/*	   		  ||||||||
	   		  |||||||CM0 ->		Operation mode
	   		  ||||||CM1	-^		(disable comparator modules)
	   		  |||||CM2 -^		
	  		  ||||CIS			
	   		  |||C1INV			
	   		  ||C2INV			
	  		  |C1OUT			
	   		  C2OUT				
*/
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
        
    }
    
    return;
}