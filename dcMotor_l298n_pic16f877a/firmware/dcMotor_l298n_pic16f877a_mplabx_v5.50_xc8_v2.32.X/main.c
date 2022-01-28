/*
 * PIC16F877A Samples
 * Sample 14: H Bridge L298N
 * Author: David Nascimento Coelho
 * Last Update: 2022/01/25
 */

// LIBRARIES INCLUDE

#include <xc.h>
#include "globals.h"

// FUNCTIONS

void set_pwm1_duty(unsigned char percent)
{
    float var = 10.23 * percent;
    int value = (int) var;
    CCPR1L = value >> 2;
    CCP1CONbits.CCP1X = value&0b0000000010;
    CCP1CONbits.CCP1Y = value&0b0000000001;
}

void set_pwm2_duty(unsigned char percent)
{
    float var = 10.23 * percent;
    int value = (int) var;
    CCPR2L = value >> 2;
    CCP2CONbits.CCP2X = value&0b0000000010;
    CCP2CONbits.CCP2Y = value&0b0000000001;
}

/* Interruption Service Routine */
void __interrupt() myIsr(void)
{
    // Extern Interruption
    if(INTCONbits.INTE && INTCONbits.INTF)
    {
        // Reset external interruption flag
        INTCONbits.INTF = 0;
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
    INTCON = 0b00010000;
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
    CCPR1L = 0b10000000;        // MSBs of PWM duty-cicle
    
    CCP1CON = 0b00001111;
/*	 	       ||||||||
	    	   |||||||CCP1M0 -> Mode Select bits
	  		   ||||||CCP1M1 -^  (11xx => PWM)
		       |||||CCP1M2 -^   
	 	       ||||CCP1M3 -^    
		       |||CCP1Y ->      least LSBs of PWM duty-cicle
		       ||CCP1X -^       
		       |0               (not implemented)
               0                (not implemented)
*/
    CCPR2L = 0b10000000;        // MSBs of PWM duty-cicle
    
    CCP2CON = 0b00001111;
/*	 	       ||||||||
	    	   |||||||CCP2M0 -> Mode Select bits
	  		   ||||||CCP2M1 -^  (11xx => PWM)
		       |||||CCP2M2 -^   
	 	       ||||CCP2M3 -^    
		       |||CCP2Y ->      least LSBs of PWM duty-cicle
		       ||CCP2X -^       
		       |0               (not implemented)
               0                (not implemented)
*/
    percent_pw1 = 50;
    percent_pw2 = 50;
    
}

void main(void) 
{
    // disable all interrupts
    INTCONbits.GIE = 0;
    
    // initialization routine
    init();
    
    // enable all interrupts
    INTCONbits.GIE = 1;
    
    // Turn On Motors
    IN1 = 1;
    IN2 = 0;
    IN3 = 1;
    IN4 = 0;
    
    // infinity loop
    while(1)
    {
        set_pwm1_duty(percent_pw1);
        set_pwm2_duty(percent_pw2);

        __delay_ms(250);

        percent_pw1++;
        percent_pw2++;

        if(percent_pw1 == 90)
        {
            IN1 = ~IN1;
            IN2 = ~IN2;
            IN3 = ~IN3;
            IN4 = ~IN4;
            percent_pw1 = 50;
            percent_pw2 = 50;
        }
    }
    
    return;
}
