/*
 * PIC16F877A Samples
 * Sample 03: IO ports
 * Author: David Nascimento Coelho
 * Review: Luan Gomes Magalh�es Lima
 * Last Update: 2022/01/25
 * Last review: 2023/09/13
 */

// LIBRARIES INCLUDE

#include <xc.h>
#include "main.h"

// FUNCTIONS

/* Set all Needed registers */
void init(void)
{
// I/O
    PORTA = 0b00000000;
    PORTB = 0b00000000;
    PORTC = 0b00000000;
    TRISD = 0b00000001; // set RD0 as input and RD1 as output
    PORTE = 0b00000000;

    TRISA = 0b00000000;
    TRISB = 0b00000000;
    TRISC = 0b00000000;
    PORTD = 0b00000000;
    TRISE = 0b00000000;
}

void blink_led(void)
{
    led1 = 1;
    __delay_ms(500);
    led1 = 0;
    __delay_ms(500);         
}

void blink_if_button(void)
{
    if(bot1)
    {
        led1 = 1;
        __delay_ms(500);
        led1 = 0;
        __delay_ms(500);
    }
    else
    {
        led1 = 0;
    }
}

void button_trigger(void)
{
    if(bot1)
    {
        led1 = 1;
        __delay_ms(2000);
        led1 = 0;
    }
}

void main(void) 
{
    // initialization routine
    init();
    
    // Infinity loop
    while(1)
    {
        /* Choose one of the functions below*/
        blink_led();
        //blink_if_button();
        //button_trigger();
    }
    
    return;
}
