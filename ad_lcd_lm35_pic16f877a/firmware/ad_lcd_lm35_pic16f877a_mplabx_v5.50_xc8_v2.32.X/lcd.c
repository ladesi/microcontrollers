/*
 * LCD Library
 * Author: David Nascimento Coelho
 * Last Update: 2022/01/25
 */

// LIBRARIES INCLUDE

#include <xc.h>
#include "globals.h"
#include "lcd.h"
#include <stdint.h>

// DEFINES

#ifndef LCD_nbits
#define LCD_nbits 8
#endif

#ifndef LCD_dat
unsigned char data;
#define LCD_dat data
#endif

#ifndef LCD4
uint8_t var4;
#define LCD4 var4
#endif

#ifndef LCD5
uint8_t var5;
#define LCD5 var5
#endif

#ifndef LCD6
uint8_t var6;
#define LCD6 var6
#endif

#ifndef LCD7
uint8_t var7;
#define LCD7 var7
#endif

#ifndef LCD_RS
bit var8;
#define LCD_RS var8
#endif

#ifndef LCD_EN
bit var9;
#define LCD_EN var9
#endif


// FUNCTIONS

// Timing routines
void lcd_delay_1us(void)  {__delay_us(1);}
void lcd_delay_40us(void) {__delay_us(40);}
void lcd_delay_2ms(void)  {__delay_ms(2);}
void lcd_delay_40ms(void) {__delay_ms(40);}

void lcd_en_pulse(void)
{
    LCD_EN = 1;
    lcd_delay_1us();
    LCD_EN = 0;
    lcd_delay_1us();
}

void lcd_send_nibble(unsigned char data)
{
// least significative nibble

    if (data&0x01) LCD4 = 1;
	else LCD4 = 0;
	if (data&0x02) LCD5 = 1;
	else LCD5 = 0;
	if (data&0x04) LCD6 = 1;
	else LCD6 = 0;
	if (data&0x08) LCD7 = 1;
	else LCD7 = 0;

    lcd_en_pulse();    
}

void lcd_byte_4bits(unsigned char data)
{
    unsigned char nibble;
    
    // most significative nibble
    nibble = (data >> 4);
    lcd_send_nibble(nibble);
	
    // least significative nibble
    nibble = (data & 0x0F);
    lcd_send_nibble(nibble);
}

void lcd_byte_8bits(unsigned char data)
{
	LCD_dat = data;
    lcd_en_pulse();
}

void lcd_cmd(unsigned char data)
{
	LCD_RS = 0;
    
    if (LCD_nbits == 8)
        lcd_byte_8bits(data);
    else
        lcd_byte_4bits(data);
    
    lcd_delay_40us();
}

void lcd_char(unsigned char data)
{
    LCD_RS = 1;
    
    if (LCD_nbits == 8)
        lcd_byte_8bits(data);
    else
        lcd_byte_4bits(data);
    
    lcd_delay_40us();
}

void lcd_puts(unsigned char *vector, unsigned char LENGHT)
{
	unsigned char cnt;
	unsigned char x;

	LCD_RS = 1; //select data for LCD

	for (cnt=0; cnt<LENGHT; cnt++)
	{
        x = *(vector+cnt);
        lcd_char(x);
	}
}

void lcd_init_8bits(void)
{
    // wait 40 ms until LCD stabilize
    lcd_delay_40ms();
    // force LCD to 8bits configuration
	lcd_cmd(0x30);
    lcd_delay_2ms();
	lcd_cmd(0x30);
    lcd_delay_2ms();
	lcd_cmd(0x30);
    lcd_delay_2ms();
    // main configuration
	lcd_cmd(M8BITS_2);
	lcd_cmd(CURSOR_DIR);
	lcd_cmd(COM_CURSOR);
    lcd_clear();
}

void lcd_init_4bits(void)
{
    // wait 40 ms until LCD stabilize
    lcd_delay_40ms();
    // force LCD to 8bits configuration
    lcd_send_nibble(0x03);
    lcd_delay_2ms();
    lcd_send_nibble(0x03);
    lcd_delay_2ms();
    lcd_send_nibble(0x03);
    lcd_delay_2ms();
    // force LCD to 4bits configuration
    lcd_send_nibble(0x02);
    lcd_delay_2ms();
    // main configuration
	lcd_cmd(M4BITS_1);
	lcd_cmd(CURSOR_DIR);
	lcd_cmd(COM_CURSOR);
    lcd_clear();
}

void lcd_init(void)
{
    if (LCD_nbits == 8)
        lcd_init_8bits();
    else
        lcd_init_4bits();
}

void lcd_clear(void)
{
    lcd_cmd(0x01);
    lcd_delay_2ms();
}

void lcd_shutdown()
{
    lcd_clear();
    lcd_cmd(0x08);
}

void lcd_goto(unsigned char lin, unsigned char col)
{
    switch(lin)
    {
        case 1:
        {
            lcd_cmd(0x80+col);
            break;
        }
        case 2:
        {
            lcd_cmd(0xc0+col);
            break;
        }
        case 3:
        {
            lcd_cmd(0x90+col);
            break;
        }
        case 4:
        {
            lcd_cmd(0xd0+col);
            break;
        }
    }
}

/************************** SEE THESE FUNCTIONS!!! ************************/
 /*
 
 void lcd_puts(unsigned char * s)
{
    while(*s)
    	lcd_char(*s++);
}

void lcd_puts(unsigned char * s)
{
    while(*s!='\0')
    {
        lcd_char(*s);
        s++;
    }
}

//Build a new letter at LCD
void lcd_write_cgram(unsigned char pos, const char * a) 
{
	LCD_RS = 0;
	char i = pos << 3;
	lcd_write_cmd(0x40 + i);	
	LCD_RS = 1;
	for ( char c = 0; c < 8; c++ ) 
		lcd_write_cmd(a[c]);
}

// Write an integer to lcd
void lcd_write_int(int val, unsigned int field_length)
{
	// Variables
	char str[5] = {0,0,0,0,0};
	int i = 4;
	int j = 0;

	while(val)
	{
		str[i] = val%10;
		val = val/10;
		i--;
	}

	if(field_length==-1)
		while(str[j] == 0) j++;
	else
		j = 5 - field_length;

	if(val < 0)
		lcd_char('-');

	for(i=j; i<5; i++)
		lcd_char(48+str[i]);
}
  
*/
