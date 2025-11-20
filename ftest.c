#include <REGX52.h>

void delay_ms(void);

void main()
{
    while(1)
    {
        P1 = 0x01;   // Turn ON P1.0
        delay_ms();  // Delay
        P1 = 0x00;   // Turn OFF P1.0
        delay_ms();  // Delay
    }
}

void delay_ms(void)
{
    unsigned int i, j;
    for(i = 0; i < 500; i++)     // Increase these numbers to slow down more
        for(j = 0; j < 500; j++);
}
