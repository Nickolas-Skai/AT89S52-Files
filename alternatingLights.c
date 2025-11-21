#include <REGX52.h>

sbit BUTTON = P3^2; 

// Change 'bit' to 'unsigned char' to hold numbers 0-255
unsigned char mode = 0; 

// Define how many modes we have so we can loop back to 0
#define TOTAL_MODES 4 

void delay_short(void);
bit check_button(void);

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
				if(mode != 0) break; // Exit if button changed mode
				for(i = 6; i > 0; i--) {
					P1 = (0x01 << i);
					delay_short();
					if(check_button()) break;
				}
				break;

			// --- MODE 1: Chase Light (Left to Right) ---
			case 1:
				for(i = 0; i < 8; i++) {
					P1 = (0x01 << i);
					delay_short();
					if(check_button()) break;
				}
				break;

			// --- MODE 2: Blink All LEDs ---
			case 2:
				P1 = 0xFF; // All ON
				delay_short();
				if(check_button()) break;
				
				P1 = 0x00; // All OFF
				delay_short();
				if(check_button()) break;
				break;

			// --- MODE 3: Binary Counter ---
			case 3:
				for(i = 0; i < 255; i++) {
					P1 = ~i; // 'Not' operator used because LEDs are usually active LOW
					         // Remove '~' if your LEDs are active HIGH
					delay_short();
					if(check_button()) break;
				}
				break;

			// --- Mode 4: odd-even lights ---
			case 4:
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
				break;
		}
	}
}

bit check_button(void)
{
	if(BUTTON == 0) 
	{
		delay_short(); 
		if(BUTTON == 0)
		{
			mode++; // Go to next mode
			if(mode >= TOTAL_MODES) // If we pass the last mode...
			{
				mode = 0; // ...reset to the start
			}
			
			while(BUTTON == 0); // Wait for release
			return 1; // Signal that mode changed
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