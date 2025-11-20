#include <REGX52.h>

// Function Prototype
void delay(unsigned int count);

void main()
{
    unsigned char i;

    while(1)
    {
        // 1. Move Left (0 to 7)
        // Shift 1 to the left 'i' times: 0x01, 0x02, 0x04... 0x80
        for(i = 0; i < 8; i++)
        {
            P1 = (0x01 << i); 
            delay(100); // Adjust this value to change speed
        }

        // 2. Move Right (6 to 1)
        // We start at 6 and end at 1 to avoid repeating the end LEDs twice,
        // making the animation look smoother at the edges.
        for(i = 6; i > 0; i--)
        {
            P1 = (0x01 << i);
            delay(100); // Adjust this value to change speed
        }
    }
}

// Simple software delay function
void delay(unsigned int count)
{
    unsigned int i, j;
    for(i = 0; i < count; i++)
    {
        // Loop adjusted for a responsive scanning speed
        for(j = 0; j < 120; j++); 
    }
}