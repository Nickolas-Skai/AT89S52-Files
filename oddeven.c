#include <REGX52.h>

void delay_ms(void);

void main()
{
    unsigned char i; //to be used for loop
    while(1)
    {
        for(i = 0x01; i != 0x80; i <<= 1) //starts with LED 1 on and then shifts the '1' bit to left twice each loop changing the led
        {
            P1 = i;
            delay_ms();
            i <<= 1; //allow it to jump 1 led
        }

        for(i = 0x80; i != 0x01; i >>= 1) //starts with LED 8 on and then shifts the '1' bit to right twice each loop changing the led
        {
            P1 = i;
            delay_ms();
            i >>= 1; //allow it to jump 1 led

        }
    }
}

void delay_ms(void)
{
    unsigned int i, j;
    for(i = 0; i < 500; i++)     // Increase these numbers to slow down more
        for(j = 0; j < 500; j++);
}
