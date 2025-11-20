#include <REGX52.h>

void delay_ms(void);
//odd even lights
void main()
{
    unsigned char i; //to be used for loop
    while(1)
    {
        for(i = 0; i != 8; i+2) //starts with LED 1 on and then shifts the '1' bit to left twice each loop changing the led
        {
            P1 = (0x01 << i);
            delay_ms();
        }

        for(i = 7; i != 1; i-2) //starts with LED 8 on and then shifts the '1' bit to right twice each loop changing the led
        {
            P1 = (0x01 << i);
            delay_ms();

        }
    }
}

void delay_ms(void)
{
    unsigned int i, j;
    for(i = 0; i < 500; i++)     // Increase these numbers to slow down more
        for(j = 0; j < 500; j++);
}
