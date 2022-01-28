/*
 * PIC16F877A Samples
 * Sample 19: 4x4 Keypad
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
void __interrupt() myIsr(void)
{
    // Extern Interruption
    if(INTCONbits.INTE && INTCONbits.INTF)
    {
        INTCONbits.INTF = 0;
        led1 = ~led1;
    }
}

// Sampling function 1
void amost1(unsigned int *value)
{
    __delay_us(100);                        // wait 100uS 
    ADCON0bits.GO_nDONE = 1;                // init AD
    while(ADCON0bits.GO_nDONE);             // wait ad conversion finish
    *value = (unsigned int)(ADRESH << 8) + (ADRESL); // get 10 bits value
}

// Sampling function 2
unsigned int amost2(void)
{
    unsigned int value;
    __delay_us(100);                        // wait 100uS 
    ADCON0bits.GO_nDONE = 1;                // init AD
    while(ADCON0bits.GO_nDONE);             // wait ad conversion finish
    value = (unsigned int)(ADRESH << 8) + (ADRESL); // get 10 bits value
    return value;
}

// Keypad 1 scanning
unsigned char keypad1_scan(unsigned int value)
{
    switch(value)
    {
        case 300:
            return '0';
        case 341:
            return '1';
        case 512:
            return '2';
        case 1023:
            return '3';
        case 295:
            return '4';
        case 414:
            return '5';
        case 696:
            return '6';
        case 260:
            return '7';
        case 348:
            return '8';
        case 527:
            return '9';
        case 232:
            return '*';
        case 425:
            return '#';
        default:
            return ' ';
    }
}

// Keypad 2 scanning
unsigned char keypad2_scan(void)
{
    col1 = 1; col2 = 0; col3 = 0;
    if (lin1 == 1) return '1';
    else if (lin2 == 1) return '4';
    else if (lin3 == 1) return '7';
    else if (lin4 == 1) return '*';
    
    col1 = 0; col2 = 1; col3 = 0;
    if (lin1 == 1) return '2';
    else if (lin2 == 1) return '5';
    else if (lin3 == 1) return '8';
    else if (lin4 == 1) return '0';
    
    col1 = 0; col2 = 0; col3 = 1;
    if (lin1 == 1) return '3';
    else if (lin2 == 1) return '6';
    else if (lin3 == 1) return '9';
    else if (lin4 == 1) return '#';
    
    return ' ';
    
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
    TRISC = 0b00001111;
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

// CCP
    CMCON = 0x07;   // desabilita modulos comparadores

// AD
    ADCON0 = 0b10000001;
/*             ||||||||
               |||||||ADON
               ||||||GO_nDONE
               ||||CHS0
               |||CHS1
               ||CHS2
               |ADCS0
               ADCS1
 */
    ADCON1 = 0b10001110;
 /*            ||||||||
               |||||||PCFG0
               ||||||PCFG1
               |||||PCFG2
               ||||PCFG3
               ||| nao imp
               ||nao imp
               |ADCS2
               ADFM (=1 - à direita)
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
    
    // initialize LCD
    lcd_init();
    
    // write LCD
    lcd_goto(1,1);
    lcd_puts("    KEYPAD    ",16);
    
    // Infinity loop
    while(1)
    {
        // get ad value (verify if key pressed)
        amost1(&ad_value);      
        // convert into char
        ad_char_val[0] = keypad1_scan(ad_value);
        // verify if no key was pressed at keypad1
        if (ad_char_val[0] == ' ')
        {
            // verify keypad2
            ad_char_val[0] = keypad2_scan();
        }
        // print char value at lcd
        lcd_goto(2,1);
        lcd_puts(ad_char_val,1);
        // wait 200ms
        __delay_ms(200);
    }
    return;
}