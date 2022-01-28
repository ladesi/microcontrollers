/*
 * PIC16F877A Samples
 * Sample 18: I2C Protocol Slave
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

short z;

void __interrupt() I2C_Slave_Read(void)
{ 
    if(PIR1bits.SSPIF == 1)
    {
        SSPCONbits.CKP = 0;
        
        // If overflow or collision
        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL))
        {
            
            z = SSPBUF;            // Read previous value to clear the buffer
            SSPCONbits.SSPOV = 0;  // Clear the overflow flag
            SSPCONbits.WCOL = 0;   // Clear the collision flag
            SSPCONbits.CKP = 1;    // Release clock
        }
        
        // If last byte was Address + Write
        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW)
        {
            z = SSPBUF;             // Read previous value to clear the buffer
            while(!SSPSTATbits.BF); // 
            PORTD = SSPBUF;         // 
            SSPCONbits.CKP = 1;     // 
        }
        
        // If last byte was Address + Read
        else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW)
        {
            z = SSPBUF;             // Read previous value to clear the buffer
            SSPSTATbits.BF = 0;     // 
            SSPBUF = PORTB;         // 
            SSPCONbits.CKP = 1;     // 
            while(SSPSTATbits.BF);  // 
        }
       
        PIR1bits.SSPIF = 0;
    }
}

void I2C_Slave_Init(unsigned char address)
{
    SSPADD =  address;
    SSPCON =  0b00110110;
    SSPCON2 = 0b00000001;
    SSPSTAT = 0b10000000;
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;

    INTCONbits.PEIE = 1;
    PIE1bits.SSPIE = 1;
    PIR1bits.SSPIF = 0;
}

void init()
{
// I/O
    
    PORTA = 0b00000000;
    PORTB = 0b00000000;
    PORTC = 0b00000000;
    PORTD = 0b00000000;
    PORTE = 0b00000000;

    TRISA = 0b00000000;
    TRISB = 0b11111111;
    TRISC = 0b00000000;
    TRISD = 0b00000000;
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
    
    I2C_Slave_Init(0x30);
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
        
    }
}