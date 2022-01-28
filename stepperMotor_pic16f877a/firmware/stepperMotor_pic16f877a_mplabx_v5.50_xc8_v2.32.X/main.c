/*
 * PIC16F877A Samples
 * Sample 16: Stepper Motor
 * Author: David Nascimento Coelho
 * Last Update: 2022/25/01
 */

// LIBRARIES INCLUDE

#include <xc.h>
#include "globals.h"

// FUNCTIONS

/* Interruption Service Routine */
void __interrupt() myIsr(void)
{

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
// STEPPER MOTOR
    IN1 = 0; 
    IN2 = 0; 
    IN3 = 0; 
    IN4 = 0;
    EN1 = 1;
    EN2 = 1;
}

void complete_step_unipolar_anticlock(void)
{
    // Pos1
    IN1 = 1; IN2 = 0; IN3 = 0; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos2
    IN1 = 0; IN2 = 1; IN3 = 0; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos3
    IN1 = 0; IN2 = 0; IN3 = 1; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos4
    IN1 = 0; IN2 = 0; IN3 = 0; IN4 = 1;
    __delay_ms(delay_quantity);
}
void complete_step_unipolar_clockwise(void)
{
    // Pos1
    IN1 = 0; IN2 = 0; IN3 = 0; IN4 = 1;
    __delay_ms(delay_quantity);
    // Pos2
    IN1 = 0; IN2 = 0; IN3 = 1; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos3
    IN1 = 0; IN2 = 1; IN3 = 0; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos4
    IN1 = 1; IN2 = 0; IN3 = 0; IN4 = 0;
    __delay_ms(delay_quantity);
}
void half_step_unipolar_clockwise(void)
{
    // Pos1
    IN1 = 1; IN2 = 0; IN3 = 0; IN4 = 1;
    __delay_ms(delay_quantity);
    // Pos2
    IN1 = 0; IN2 = 0; IN3 = 0; IN4 = 1;
    __delay_ms(delay_quantity);
    // Pos3
    IN1 = 0; IN2 = 0; IN3 = 1; IN4 = 1;
    __delay_ms(delay_quantity);
    // Pos4
    IN1 = 0; IN2 = 0; IN3 = 1; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos5
    IN1 = 0; IN2 = 1; IN3 = 1; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos6
    IN1 = 0; IN2 = 1; IN3 = 0; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos7
    IN1 = 1; IN2 = 1; IN3 = 0; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos8
    IN1 = 1; IN2 = 0; IN3 = 0; IN4 = 0;
    __delay_ms(delay_quantity);
}
void half_step_unipolar_anticlock(void)
{
    // Pos1
    IN1 = 1; IN2 = 0; IN3 = 0; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos2
    IN1 = 1; IN2 = 1; IN3 = 0; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos3
    IN1 = 0; IN2 = 1; IN3 = 0; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos4
    IN1 = 0; IN2 = 1; IN3 = 1; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos5
    IN1 = 0; IN2 = 0; IN3 = 1; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos6
    IN1 = 0; IN2 = 0; IN3 = 1; IN4 = 1;
    __delay_ms(delay_quantity);
    // Pos7
    IN1 = 0; IN2 = 0; IN3 = 0; IN4 = 1;
    __delay_ms(delay_quantity);
    // Pos8
    IN1 = 1; IN2 = 0; IN3 = 0; IN4 = 1;
    __delay_ms(delay_quantity);
}
void complete_step_bipolar_anticlock(void)
{
    // Pos1
    IN1 = 1; IN2 = 0; IN3 = 1; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos2
    IN1 = 0; IN2 = 1; IN3 = 1; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos3
    IN1 = 0; IN2 = 1; IN3 = 0; IN4 = 1;
    __delay_ms(delay_quantity);
    // Pos4
    IN1 = 1; IN2 = 0; IN3 = 0; IN4 = 1;
    __delay_ms(delay_quantity);
}
void complete_step_bipolar_clockwise(void)
{
    // Pos1
    IN1 = 1; IN2 = 0; IN3 = 0; IN4 = 1;
    __delay_ms(delay_quantity);
    // Pos2
    IN1 = 0; IN2 = 1; IN3 = 0; IN4 = 1;
    __delay_ms(delay_quantity);
    // Pos3
    IN1 = 0; IN2 = 1; IN3 = 1; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos4
    IN1 = 1; IN2 = 0; IN3 = 1; IN4 = 0;
    __delay_ms(delay_quantity);
}
void half_step_bipolar_anticlock(void)
{
    // Pos1
    IN1 = 1; IN2 = 0; IN3 = 1; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos2
    IN1 = 0; IN2 = 0; IN3 = 1; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos3
    IN1 = 0; IN2 = 1; IN3 = 1; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos4
    IN1 = 0; IN2 = 1; IN3 = 0; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos5
    IN1 = 0; IN2 = 1; IN3 = 0; IN4 = 1;
    __delay_ms(delay_quantity);
    // Pos6
    IN1 = 0; IN2 = 0; IN3 = 0; IN4 = 1;
    __delay_ms(delay_quantity);
    // Pos7
    IN1 = 1; IN2 = 0; IN3 = 0; IN4 = 1;
    __delay_ms(delay_quantity);
    // Pos8
    IN1 = 1; IN2 = 0; IN3 = 0; IN4 = 0;
    __delay_ms(delay_quantity);    
}
void half_step_bipolar_clockwise(void)
{
    // Pos1
    IN1 = 1; IN2 = 0; IN3 = 0; IN4 = 0;
    __delay_ms(delay_quantity);    
    // Pos2
    IN1 = 1; IN2 = 0; IN3 = 0; IN4 = 1;
    __delay_ms(delay_quantity);
    // Pos3
    IN1 = 0; IN2 = 0; IN3 = 0; IN4 = 1;
    __delay_ms(delay_quantity);
    // Pos4
    IN1 = 0; IN2 = 1; IN3 = 0; IN4 = 1;
    __delay_ms(delay_quantity);
    // Pos5
    IN1 = 0; IN2 = 1; IN3 = 0; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos6
    IN1 = 0; IN2 = 1; IN3 = 1; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos7
    IN1 = 0; IN2 = 0; IN3 = 1; IN4 = 0;
    __delay_ms(delay_quantity);
    // Pos8
    IN1 = 1; IN2 = 0; IN3 = 1; IN4 = 0;
    __delay_ms(delay_quantity);
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
        complete_step_unipolar_clockwise();
        //complete_step_unipolar_anticlock();
        //half_step_unipolar_clockwise();
        //half_step_unipolar_anticlock();
        //complete_step_bipolar_anticlock();
        //complete_step_bipolar_clockwise();
        //half_step_bipolar_anticlock();
        //half_step_bipolar_clockwise();
    }
    return;
}
