#include <mcs51/8052.h>

// SDCC definition for P3.2
#define BUTTON P3_2 

// Global mode variable
unsigned char mode = 0; 
#define TOTAL_MODES 2 

void delay_short(void);
unsigned char check_button(void); // Changed return type to match SDCC bool handling

void main()
{
    unsigned char i;
    BUTTON = 1; // Init input

    while(1)
    {
        switch(mode)
        {
            // --- MODE 0: Knight Rider ---
            case 0:
                for(i = 0; i < 8; i++) {
                    P1 = (0x01 << i); 
                    delay_short();
                    if(check_button()) break;
                }
                if(mode != 0) break; 

                for(i = 6; i > 0; i--) {
                    P1 = (0x01 << i);
                    delay_short();
                    if(check_button()) break;
                }
                break;

            // --- MODE 1: Odd-Even Pattern ---
            case 1:
                for(i = 0; i < 8; i+=2) {
                    P1 = (0x01 << i);
                    delay_short();
                    if(check_button()) break;
                }
                if(mode != 1) break;

                for(i = 7; i > 1; i-=2) {
                    P1 = (0x01 << i);
                    delay_short();
                    if(check_button()) break;
                }
                break;
        }
    }
}

unsigned char check_button(void)
{
    if(BUTTON == 0) 
    {
        delay_short(); 
        if(BUTTON == 0)
        {
            mode++;
            if(mode >= TOTAL_MODES) mode = 0;
            while(BUTTON == 0); 
            return 1; 
        }
    }
    return 0;
}

void delay_short(void)
{
    unsigned int i, j;
    for(i = 0; i < 100; i++) 
        for(j = 0; j < 300; j++);
}