#include <REGX52.h>

sbit BUTTON = P3^2; 

// Global mode variable
unsigned char mode = 0; 

// Set to 2 modes (0 and 1) to save space
#define TOTAL_MODES 2 

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
				// Sweep Left (0 to 7)
				for(i = 0; i < 8; i++) {
					P1 = (0x01 << i); 
					delay_short();
					if(check_button()) break;
				}
				if(mode != 0) break; 

				// Sweep Right (6 down to 1)
				for(i = 6; i > 0; i--) {
					P1 = (0x01 << i);
					delay_short();
					if(check_button()) break;
				}
				break;

			// --- MODE 1: Odd-Even Pattern ---
			case 1:
				// 0, 2, 4, 6
				for(i = 0; i < 8; i+=2) 
				{
					P1 = (0x01 << i);
					delay_short();
					if(check_button()) break;
				}
				if(mode != 1) break;

				// 7, 5, 3
				for(i = 7; i > 1; i-=2) 
				{
					P1 = (0x01 << i);
					delay_short();
					if(check_button()) break;
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
			if(mode >= TOTAL_MODES) 
			{
				mode = 0; // Reset to start
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