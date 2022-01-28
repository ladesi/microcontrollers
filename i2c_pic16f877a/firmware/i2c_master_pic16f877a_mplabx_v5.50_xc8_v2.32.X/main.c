/*
 * PIC16F877A Samples
 * Sample 18: I2C Protocol Master
 * Author: David Nascimento Coelho
 * Last Update: 2022/01/25
 */

#include <xc.h>

#define _XTAL_FREQ 20000000

// CONFIG

#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

void I2C_Master_Init(const unsigned long c)
{
    SSPADD =  (unsigned char)((_XTAL_FREQ/(4*c))-1);
    SSPCON =  0b00101000;
    SSPCON2 = 0b00000000;
    SSPSTAT = 0b00000000;
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
}

void I2C_Master_Wait()
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void I2C_Master_Start()
{
    I2C_Master_Wait();
    SSPCON2bits.SEN = 1;
}

void I2C_Master_RepeatedStart()
{
    I2C_Master_Wait();
    SSPCON2bits.RSEN = 1;
}

void I2C_Master_Stop()
{
    I2C_Master_Wait();
    SSPCON2bits.PEN = 1;
}

void I2C_Master_Write(unsigned char d)
{
    I2C_Master_Wait();
    SSPBUF = d;
}

unsigned char I2C_Master_Read(unsigned short a)
{
    unsigned char temp;
    I2C_Master_Wait();
    SSPCON2bits.RCEN = 1;
    I2C_Master_Wait();
    temp = SSPBUF;
    I2C_Master_Wait();
    SSPCON2bits.ACKDT = (a)?0:1;
    SSPCON2bits.ACKEN = 1;
    return temp;
}

void init()
{
// I/O
    
    PORTA = 0b00000000;
    PORTB = 0b00000000;
    PORTC = 0b00000000;
    TRISD = 0b00000000;
    PORTE = 0b00000000;

    TRISA = 0b00000000;
    TRISB = 0b11111111;
    TRISC = 0b00000000;
    PORTD = 0b00000000;
    TRISE = 0b00000000;
    
// INT EXT & TMR0
    
    OPTION_REG = 0b00000000;
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
// I2C
    
    I2C_Master_Init(100000);
}

void main()
{
    // disable all interrupts
    INTCONbits.GIE = 0;
    
    // initialization routine
    init();
    
    // enable all interrupts
    INTCONbits.GIE = 1;

    while(1)
    {
        I2C_Master_Start();             //
        I2C_Master_Write(0x30);         // Address + Write
        I2C_Master_Write(PORTB);        //
        I2C_Master_Stop();              //
        __delay_ms(200);                //
        
        I2C_Master_Start();             //
        I2C_Master_Write(0x31);         // Address + Read
        PORTD = I2C_Master_Read(0);     //
        I2C_Master_Stop();              //
        __delay_ms(200);                //
    }
}