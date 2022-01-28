/*
 * PIC16F877A Samples
 * Sample 21: Capture Module
 * Author: David Nascimento Coelho
 * Last Update: 2022/01/25
 */

// LIBRARIES INCLUDE

#include <xc.h>
#include <stdlib.h>
#include "globals.h"
#include "lcd.h"

// FUNCTIONS

/* Interruption Service Routine */
void __interrupt() myIsr(void) {
    
    // Extern Interruption
    if (INTCONbits.INTE && INTCONbits.INTF) {
        INTCONbits.INTF = 0;
        led1 = ~led1;
    }
    // Timer1
    if(PIE1bits.TMR1IE && PIR1bits.TMR1IF)
    {
        //TMR1 = 65536 - rec_tmr1 + TMR1;
        //count1++;
        out_tmr1 = !out_tmr1;
        TMR1 = 0;
        if (number_of_edges == 1) {
            tm1_overflow_cont++;
        }
        else {
            tm1_overflow_cont = 0;
        }
        PIR1bits.TMR1IF = 0;
    }
    // Capture 1
    if (PIE1bits.CCP1IE && PIR1bits.CCP1IF)
    {
        if (number_of_edges == 0) {
            tmr1_counter1 = CCPR1;
            number_of_edges = 1;
        }
        else {
            out_ccp1 = !out_ccp1;
            tmr1_counter2 = CCPR1;
            number_of_edges = 0;
            two_edges_flag = 1;

            if(tm1_overflow_cont == 0) {
                total_cont = tmr1_counter2 - tmr1_counter1;
            }
            else {
                total_cont = rec_tmr1 - tmr1_counter1;
                total_cont += tmr1_counter2;
                //tm1_overflow_cont = tm1_overflow_cont - 1;
                //total_cont += (unsigned long)tm1_overflow_cont * rec_tmr1;
            }
        }
        PIR1bits.CCP1IF = 0;
    }
    // Capture 2
    if (PIE2bits.CCP2IE && PIR2bits.CCP2IF)
    {
        
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
    TRISC = 0b00000110; // Pins for capture 1 and 2 as inputs
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
    
    PIE1bits.TMR1IE = 1;    
    
    // CCP

    CCPR1H = 0b00000000;    // MSBs of CCPR1
    CCPR1L = 0b00000000;    // LSBs of CCPR1

    CCP1CON = 0b00000101;
/*	 	       ||||||||
	    	   |||||||CCP1M0 -> Mode Select bits
	  		   ||||||CCP1M1 -^  (0101 => Capture)
		       |||||CCP1M2 -^   (on rising edge)
	 	       ||||CCP1M3 -^    
		       |||CCP1Y ->      least LSBs of PWM duty-cicle
		       ||CCP1X -^       (not used for comparator)
		       |0               (not implemented)
               0                (not implemented)
*/
    PIE1bits.CCP1IE = 1;
    PIR1bits.CCP1IF = 0;
            
    CCPR2H = 0b00000000;    // MSBs of CCPR1
    CCPR2L = 0b00000000;    // LSBs of CCPR1
    
    CCP2CON = 0b00000101;
/*	 	       ||||||||
	    	   |||||||CCP2M0 -> Mode Select bits
	  		   ||||||CCP2M1 -^  (0101 => Comparator)
		       |||||CCP2M2 -^   (on rising edge)
	 	       ||||CCP2M3 -^    
		       |||CCP2Y ->      least LSBs of PWM duty-cicle
		       ||CCP2X -^       (not used for comparator)
		       |0               (not implemented)
               0                (not implemented)
*/
    PIE2bits.CCP2IE = 1;
    PIR2bits.CCP2IF = 0;
    
    // Comparator Modules
    CMCON = 0x07; // desabilita modulos comparadores
    
    // Init Variables
    number_of_edges = 0;
    tm1_overflow_cont = 0;
    tmr1_counter1 = 0;
    tmr1_counter2 = 0;
    two_edges_flag = 0;
    total_cont = 0;

}

void main(void) 
{
    // disable all interrupts
    INTCONbits.GIE = 0;

    // initialization routine
    init();

    // enable all interrupts
    INTCONbits.GIE = 1;

    // initialize LCD
    lcd_init();

    // write LCD
    lcd_goto(1,0);
    lcd_puts("NUMBER OF PULSES",16);

    // Infinity loop
    while (1) 
    {
        if (two_edges_flag == 1) {
            two_edges_flag = 0;
            itoa(pulses_char_val, total_cont, 10);
            lcd_goto(2,0);
            lcd_puts(pulses_char_val,10);
        }
        // wait 500ms
        __delay_ms(500);
    }
    return;
}
