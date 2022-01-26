/*
 * PIC16F877A Samples
 * Sample 05: PORTB Interrupt on Change
 * Author: David Nascimento Coelho
 * Last Update: 2022/01/25
 */

// LIBRARIES INCLUDE

#include "main.h"
#include <xc.h>

// FUNCTIONS

void __interrupt() myIsr() 
{  
    if(INTCONbits.INTE && INTCONbits.INTF)
    {
        INTCONbits.INTF = 0;
        led1 = !led1;
    }
    if(INTCONbits.RBIE && INTCONbits.RBIF)
    {
        INTCONbits.RBIF = 0;
        if(!testbit(PORTB,4))
        {
            leds = 0b00000001;
        }
        else if(!testbit(PORTB,5))
        {
            leds = 0b00000010;
        }
        else if(!testbit(PORTB,6))
        {
            leds = 0b00000100;
        }
        else if(!testbit(PORTB,7))
        {
            leds = 0b00001000;
        }
        else
        {
            leds = leds;
        }
    }
}

/* Set all Needed registers */
void init(void)
{
    // IO
    TRISA = 0b00000000;
    TRISB = 0b11110001;
    TRISC = 0b00000000;
    TRISD = 0b00000000;
    TRISE = 0b00000000;
    
    PORTA = 0b00000000;
    PORTB = 0b00000000;
    PORTC = 0b00000000;
    PORTD = 0b00000000;
    PORTE = 0b00000000;
    
    // INT EXT & TMR0
    OPTION_REG = 0b10000011;
/*	   			   ||||||||
	   			   |||||||ps0 -> preescaler 1:4
	   			   ||||||ps1 -^
	   			   |||||ps2 -^
	  			   ||||PSA   (=0 pre-escaler for timer0)
	   			   |||TMR0SE (when using as counter)
	   			   ||TMR0CS  (=0 timer)
	  			   |INTEDG   (int ext / =0 falling edge)
	   			   !PORTB    Pull-up enable (=1 disabled)
*/
    INTCON = 0b00011000;
/*	   		   ||||||||
	   		   |||||||RBIF
	   		   ||||||INTF
	   		   |||||TMR0IF
	  		   ||||RBIE
	   		   |||INTE
	   		   ||TMR0IE
	  		   |PEIE		//TIMER 1 e 2, AD, Serial... 
	   		   GIE			//are considered peripherals
*/ 

}

void main(void) 
{
    // disable all interrupts
    INTCONbits.GIE = 0;
    
    // Initialization routine
    init();
    
    // enable all interrupts
    INTCONbits.GIE = 1;

    // Main loop
    while(1)
    {
        
    }
    
    return;
}