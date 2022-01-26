/*
 * PIC16F877A Samples
 * Sample 01: C coding
 * Author: David Nascimento Coelho
 * Last Update: 2021/09/25
 */

// LIBRARIES INCLUDE

#include <xc.h>
#include "main.h"

// FUNCTIONS

void functions_c_coding(void)
{
    // IF-ELSE
    if (flag1 == 1)
    {
        letra = 'd';
    }
    else
    {
        letra = 'e';
    }

   // SWITCH-CASE
    switch(letra)
    {
        case 'a':
            sum1 = 2;
            break;
        case 'b':
            sum1 = 3;
            break;
        default:
            sum1 = 0;
            break;
    }

     // FOR
    for(int i=1; i<=10; i++)
    {
        sum1 = sum1 + 1;
    }

    // WHILE
    while(sum1 < 20)
    {
        sum1 = sum1 + 1;
    }

    // DO-WHILE
    do
    {
        sum1 = sum1 + 1;
    }while(sum1 < 30);

    // Change generic byte variable value
    var1.byte = 0xA2;            // access its byte
    var1.bits.bit0 = 0;          // access its bits
}

void binary_logic(void)
{
    //SHIFT
    num1 = num1 << 1; // shift left (multiply by 2^1)
    num1 = num1 >> 2; // shift right (divide by by 2^2)
    
    // ROTATE
    num1 = (num1 << 1) | (num1 >> 7); // rotate left
    num1 = (num1 >> 1) | (num1 << 7); // rotate right
    
    // AND & (verify bit)
    if (num1 & 0b01000000) // verifies bit 6 of num1
    {        
    }
    if(testbit(num1,6))    // verifies bit 6 of num1
    {
    }
    
    // OR | (set bit)
    num1 = num1 | 0b00000001; // set bit 0 of num1
    num1 = setbit(num1,0);    // set bit 0 of num1
    
    // AND & (clear bit)
    num1 = num1 & 0b11111101; // clear bit 1 of num1
    num1 = clrbit(num1,1);    // clear bit 1 of num1
    
    // XOR ^ (reverse bit value)
    num1 = num1 ^ 0b00100000; // reverses bit 5 of num1
    num1 = invbit(num1,5);    // reverses bit 5 of num1
}

void assembly_instructions(void)
{
    // assembly commands (already implemented in the compiler)

    NOP();      // do nothing in 1 machine cycle
    //CLRWDT();   // restart watchdog counting
    //SLEEP();    // enter sleep mode
    //RESET();    // resets device

    // inline assembly instructions - examples

    asm("NOP");
    //asm("MOVLW 20");
    //asm("MOVWF _i");
    //asm("CLRF Ii+1");
}

// MAIN FUNCTION

void main(void) 
{
    // call functions
    functions_c_coding();
    binary_logic();
    assembly_instructions();

    // infinity loop
    while(1)
    {
        
    }

    return;
}
