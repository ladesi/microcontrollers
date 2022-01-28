/*
 * PIC16F877A Samples
 * Sample 15: Servo Motor (PWM by software)
 * Author: David Nascimento Coelho
 * Last Update: 2021/09/25
 */

// LIBRARIES INCLUDE

#include <xc.h>
#include "globals.h"

// FUNCTIONS

/* Interruption Service Routine */
void __interrupt() myIsr(void)
{
    if (PIR1bits.TMR1IF && PIE1bits.TMR1IE)
    {
        PIR1bits.TMR1IF = 0;
        T1_pin = !T1_pin;
        cont = 0;
        TMR1 = 65536 - rec_tmr1 + TMR1;
    }

    if (INTCONbits.TMR0IF && INTCONbits.TMR0IE)
    {
        INTCONbits.TMR0IF = 0;
        T0_pin = !T0_pin;
        cont = cont+1;
        
        // Motor 1
        if (cont <= duty1)
            M1 = 1;
        else
            M1 = 0;
        
        // Motor 2
        if (cont <= duty2)
            M2 = 1;
        else
            M2 = 0;
        
        // Recharge timer 0
        TMR0 = 256 - rec_tmr0 + TMR0;
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
    TRISB = 0b11110001;
    TRISC = 0b10000000;
    PORTD = 0b00000000;
    TRISE = 0b00000000;
    
// INT EXT & TMR0
    
    OPTION_REG = 0b10000000;
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
    INTCON = 0b01100000;
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
    TMR0 = 256 - rec_tmr0;
    // T_0 = Tm.PS.(rec_tmr0) = 0,2u.2.125 = 50us
    
// TMR1
    
    T1CON = 0b00010001;
/*	   		  ||||||||
	   		  |||||||TMR1ON (=1 enable timer1)
	   		  ||||||TMR1CS (=0 internal clock)
     		  |||||T1SYNC (ignored when TMR1CS = 0)
	  		  ||||T1OSCEN (=0 disabled)
	   		  |||T1CKPS0 -> preescaler 1:2 (1, 2, 4, 8)
	   		  ||T1CKPS1 -^
	  		  |unimplemented
	   		  unimplemented 
*/     
    TMR1 = 65536 - rec_tmr1;
    // T_1 = Tm.PS1.(rec_tmr1) = 0,2u.2.50000 = 20ms

    PIE1bits.TMR1IE = 1;
    
    cont = 0;
    duty1 = 20;
    duty2 = 40;
    
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
        // Motor 1
        if (but1 && duty1 < max_duty)
        {
            while(but1);
            duty1++;
        }
        if (but2 && duty1 > min_duty)
        {
            while(but2);
            duty1--;
        }
        
        //Motor2
        if (but3 && duty2 < max_duty)
        {
            while(but3);
            duty2++;
        }
        if (but4 && duty2 > min_duty)
        {
            while(but4);
            duty2--;
        }
    }

    return;
}
