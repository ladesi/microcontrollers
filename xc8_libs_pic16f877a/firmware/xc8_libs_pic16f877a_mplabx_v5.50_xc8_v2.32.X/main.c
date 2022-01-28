/*
 * PIC16F877A Samples
 * Sample 20: XC8 native libraries
 * Author: David Nascimento Coelho
 * Last Update: 2022/01/25
 */

// LIBRARIES INCLUDE

#include <xc.h>

#include <stdlib.h>     // Conversion between numbers and strings
#include <math.h>       // Mathematical functions
#include <ctype.h>      // Character testing
#include <string.h>     // Tring manipulating
#include <stdio.h>      // Printf function

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

/* Function used by printf */
void putch(char dado) 
{
    lcd_char(dado);
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
    TRISC = 0b00000000;
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

void show_ad(void)
{
    // choose between the next two functions
    amost1(&ad_value);  //ad_value = amost2();
    // Temperature = conversion/2
    ad_value = ad_value/2;
    // convert int value for string
    itoa(ad_char_val, ad_value, 10);
    // print char value at lcd
    lcd_goto(1,1);
    printf("A/D CONVERSION");
    lcd_goto(2,2);
    printf("AD value: %s",ad_char_val);
    // wait 3s
    __delay_ms(3000);
    lcd_clear();
}

void stdlib_testing(void)
{
    //Initial
    lcd_goto(1,0);
    printf("XC8 LIBS TESTING");
    lcd_goto(2,5);
    printf("STDLIB");
    __delay_ms(3000);
    lcd_clear();
/*
    //itoa
    itoa(str_dec1, int_value, 10);
    lcd_goto(1,0);
    printf("itoa: %s", str_dec1);
    itoa(str_hex1, int_value, 16);
    lcd_goto(2,0);
    printf("itoa: %s", str_hex1);
    __delay_ms(3000);
    lcd_clear();
    
    //ltoa
    ltoa(str_dec2, long_value1, 10);
    lcd_goto(1,0);
    printf("ltoa: %s", str_dec2);
    ltoa(str_hex2, long_value1, 16);
    lcd_goto(2,0);
    printf("ltoa: %s", str_hex2);
    __delay_ms(3000);
    lcd_clear();
    
    //utoa and xtoi
    str_unsigned = utoa(str_unsigned, (unsigned) unsigned_value, 2);
    lcd_goto(1,0);
    printf("utoa: %s", str_unsigned);
    lcd_goto(2,0);
    printf("xtoi: %i",xtoi(str_unsigned));
    __delay_ms(3000);
    lcd_clear();
    
    //ftoa
    str_float = ftoa(float_value, status);
    lcd_goto(1,0);
    printf("ftoa: %s",str_float);
    __delay_ms(3000);
    lcd_clear();

    float z = 123.456;
    char *status;
    char c = ftoa(z, status);
    printf("CHAR %s", c);
    
    //atoi and atol
    int_char = "1234";
    lcd_goto(1,0);
    printf("atoi: %i", atoi(int_char));
    long_char1 = "123456789";
    lcd_goto(2,0);
    printf("atol: %ld", atol(long_char1));
    __delay_ms(3000);
    lcd_clear();
    
    //strtol
    long_char2 = "975215";
    long_value2 = strtol(long_char2, NULL, 0);
    lcd_goto(1,0);
    printf("long_str: %s", long_char2);
    lcd_goto(2,0);
    printf("long_val: %ld", long_value2);
    __delay_ms(3000);
    lcd_clear();
    
    //rand and srand
    srand(20);              // the seed can be the timer1 value (unsigned int)
    random_num = rand();    // integer value
    lcd_goto(1,0);
    printf("random: %d",random_num);
    __delay_ms(3000);
    lcd_clear();
    
    //abs, labs, fabs
    // absolute values
*/
}

void math_testing(void)
{
    //Initial
    lcd_goto(1,0);
    printf("XC8 LIBS TESTING");
    lcd_goto(2,4);
    printf("MATH LIB");
    __delay_ms(3000);
    lcd_clear();
/*
    lcd_goto(1,0);
    printf("sin(90): %.2f", sin(3.14/2));
    lcd_goto(2,0);
    printf("asin(1): %.2f", asin(1));
    __delay_ms(3000);
    lcd_clear();
    
    lcd_goto(1,0);
    printf("cos(90): %.2f", cos(3.14/2));
    lcd_goto(2,0);
    printf("acos(1): %.2f", acos(1));
    __delay_ms(3000);
    lcd_clear();
    
    lcd_goto(1,0);
    printf("tan(2pi): %.2f", tan(6.28));
    lcd_goto(2,0);
    printf("atan(1): %.2f", atan(1));
    __delay_ms(3000);
    lcd_clear();
    
    lcd_goto(1,0);
    printf("atan2(0,180): %.2f", atan2(0,180));
    lcd_goto(2,0);
    printf("exp(10): %.2f", exp(10));
    __delay_ms(3000);
    lcd_clear();
    
    lcd_goto(1,0);
    printf("log(2): %.2f", log(2));
    lcd_goto(2,0);
    printf("log10(10): %.2f",log10(10));
    __delay_ms(3000);
    lcd_clear();
    
    lcd_goto(1,0);
    printf("sinh(1): %.2f", sinh(1));
    lcd_goto(2,0);
    printf("cosh(1): %.2f", cosh(1));
    __delay_ms(3000);
    lcd_clear();

    lcd_goto(1,0);
    printf("tanh(1): %.2f", tanh(1));
    __delay_ms(3000);
    lcd_clear();
    
    lcd_goto(1,0);
    printf("ceil(4.67): %.2f", ceil(4.67));
    lcd_goto(2,0);
    printf("floor(4.67): %.2f", floor(4.67));
    __delay_ms(3000);
    lcd_clear();
    
    lcd_goto(1,0);
    printf("round(4.356): %.2f", round(4.356));
    lcd_goto(2,0);
    printf("trunc(13/3): %.2f", trunc(13/3));
    __delay_ms(3000);
    lcd_clear();

    lcd_goto(1,0);
    printf("sqrt(4): %.2f", sqrt(4));
    lcd_goto(2,0);
    printf("pow(4,2): %.2f", pow(4,2);
    __delay_ms(3000);
    lcd_clear();
*/
}

void ctype_testing(void)
{
    //Initial
    lcd_goto(1,0);
    printf("XC8 LIBS TESTING");
    lcd_goto(2,3);
    printf("CTYPE LIB");
    __delay_ms(3000);
    lcd_clear();    
    
    lcd_goto(1,0);
    printf("isgraph(c)? %d", isgraph('t'));
    lcd_goto(2,0);
    printf("ispunct(c)? %d", ispunct('.'));
    __delay_ms(3000);
    lcd_clear();

    lcd_goto(1,0);
    printf("isspace(c)? %d", isspace(' '));
    lcd_goto(2,0);
    printf("isupper(c)? %d", isupper('t'));
    __delay_ms(3000);
    lcd_clear();

    lcd_goto(1,0);
    printf("isxdigit(c)? %d", isxdigit('4'));
    lcd_goto(2,0);
    printf("iscntrl(c)? %d", iscntrl('\t'));
    __delay_ms(3000);
    lcd_clear();

    lcd_goto(1,0);
    printf("isdigit(c)? %d", isxdigit('3'));
    lcd_goto(2,0);
    printf("islower(c)? %d", islower('C'));
    __delay_ms(3000);
    lcd_clear();

    lcd_goto(1,0);
    printf("isprint(c)? %d", isprint('3'));
    lcd_goto(2,0);
    printf("isalnum(c)? %d", isalnum('*'));
    __delay_ms(3000);
    lcd_clear();

    lcd_goto(1,0);
    printf("isalpha(c)? %d", isalpha('3'));
    lcd_goto(2,0);
    printf("isascii(c)? %d", isascii('f'));
    __delay_ms(3000);
    lcd_clear();

    lcd_goto(1,0);
    printf("A to lower: %c", tolower('A'));
    lcd_goto(2,0);
    printf("a to upper: %c", toupper('a'));
    __delay_ms(3000);
    lcd_clear();

    lcd_goto(1,0);
    printf("a to ascii %d", toascii('a'));
    __delay_ms(3000);
    lcd_clear();
}

void string_testing(void)
{
    //Initial
    lcd_goto(1,0);
    printf("XC8 LIBS TESTING");
    lcd_goto(2,3);
    printf("STRING LIB");
    __delay_ms(3000);
    lcd_clear();
    
    char string[10] = "abc";
    char str[10] = "def";

    //strcat();         // Concatena "string1" com "string2"
    strcat(string,str); // strcmp(string1, string2);
    lcd_goto(1,0);
    printf("strcat");
    lcd_goto(2,0);
    printf("%s",string);
    __delay_ms(3000);
    lcd_clear();
    
    //strchr();       // Primeira ocorrencia do caractere 'c' em "string".   
    lcd_goto(1,0);    // strchr(string,c);
    printf("strchr");
    lcd_goto(2,0);
    printf("%s",strchr(string,'d'));
    __delay_ms(3000);
    lcd_clear();
    
    //memchr();       // Posição de memória do caractere 'c' na "string"   
    lcd_goto(1,0);    // de tamanho 'm' -> memchr(string,c,m);
    printf("memchr");
    lcd_goto(2,0);
    printf("%s",memchr(string,'e',6));
    __delay_ms(3000);
    lcd_clear();
    
    //strlen();       // Retorna o tamanho de "string" -> strlen(string);
    lcd_goto(1,0);
    printf("strlen");
    lcd_goto(2,0);
    printf("length: %d",strlen(string));
    __delay_ms(3000);
    lcd_clear();
    
    //strcmp();      // Compara o primeiro caractere não coincidente de "string1" 
    lcd_goto(1,0);   // com "string2" retornando um valor 'i' inteiro
    printf("strcmp");
    lcd_goto(2,0);
    printf("%d",strcmp(string,"abcd"));
    __delay_ms(3000);
    lcd_clear();
    
    //memcmp();       // Similar à função strcmp(), porém, as strings são comparadas 
    lcd_goto(1,0);    // a um número 'n' de bytes. memcmp(string1,string2,n)
    printf("memcmp");
    lcd_goto(2,0);
    printf("%d",memcmp(string,"ab",5));
    __delay_ms(3000);
    lcd_clear();
    
    //strcpy();    // Copia uma "copy" para "string" -> strcpy(string,"copy");
    lcd_goto(1,0);
    printf("strcpy");
    lcd_goto(2,0);
    printf("%s",strcpy(string,"teste"));
    __delay_ms(3000);
    lcd_clear();
    
    //memcpy();       // Copia uma "memcpy" para "string" até a posição 'i' de 
    lcd_goto(1,0);    // "string1" ->  memcpy(string,"memcpy",i);
    printf("memcpy");
    lcd_goto(2,0);
    printf("%s",memcpy(string,"teste",5));
    __delay_ms(3000);
    lcd_clear();
    
    //memmove();      // Similar à função memcpy();
    lcd_goto(1,0);  
    printf("memmove");
    lcd_goto(2,0);
    printf("%s",memmove(string,"teste2",6));
    __delay_ms(3000);
    lcd_clear();
    
    //memset();     // Substitui os 'i' primeiros caracteres de "string" por 'x' 
    lcd_goto(1,0);  // memset(string,'x',i);
    printf("memset");
    lcd_goto(2,0);
    printf("%s",memset(string,'a',5));
    __delay_ms(3000);
    lcd_clear();
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
    
    // Infinity loop
    while(1)
    {
        // AD VALUE
        show_ad();
        
        // STDLIB FUNCTIONS
        stdlib_testing();
        
        // MATH FUNCTIONS
        math_testing();
        
        // CTYPE FUNCTIONS
        ctype_testing();
        
        // STRING FUNCTIONS
        string_testing();
        
    }
    return;
}
