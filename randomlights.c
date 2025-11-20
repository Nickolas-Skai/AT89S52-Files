#include <REGX52.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void delay_ms(void);
//random lights
void main()
{
    srand(time(NULL));

    unsigned char i; //to be used for loop
    int max_val = 8; //total leds
    while(1)
    {
        // Generate a random number within 0 and total leds
        int random_number = 0 + rand() % (max_val - 0 + 1);

        P1 = (0x01 << random_number);
        delay_ms();
        
     
    }
}

void delay_ms(void)
{
    unsigned int i, j;
    for(i = 0; i < 500; i++)     // Increase these numbers to slow down more
        for(j = 0; j < 500; j++);
}
