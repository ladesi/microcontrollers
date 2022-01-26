/*
 * PIC16F877A Samples
 * Sample 06: 7-segment display
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
    
    disp1_val = disp1_val+1;
	if (disp1_val == 10)
	{
		disp1_val = 0;
		disp2_val = disp2_val+1;
		if (disp2_val == 10)
		{
			disp2_val = 0;
			disp3_val = disp3_val+1;
			if (disp3_val == 10)
			{
				disp3_val = 0;
				disp4_val = disp4_val+1;
				if (disp4_val == 10)
				{
					disp4_val = 0;
				}
			}
		}
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

    TRISA = 0b00000000;
    TRISB = 0b00000001;
    TRISC = 0b00000000;
    PORTD = 0b00000000;
    TRISE = 0b00000000;
    
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
    INTCON = 0b00010000;
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
    
    // initialization routine
    init();
    
    // enable all interrupts
    INTCONbits.GIE = 1;
    
    // Infinity loop
    while(1)
    {
        // display multiplexing
        disp7seg = tab1[disp1_val];
        ac_disp1 = 1;
        __delay_ms(50);
        ac_disp1 = 0;
        disp7seg = tab1[disp2_val];
        ac_disp2 = 1;
        __delay_ms(50);
        ac_disp2 = 0;
        disp7seg = tab1[disp3_val];
        ac_disp3 = 1;
        __delay_ms(50);
        ac_disp3 = 0;
        disp7seg = tab1[disp4_val];
        ac_disp4 = 1;
        __delay_ms(50);
        ac_disp4 = 0;
    }    
    
    return;
}
