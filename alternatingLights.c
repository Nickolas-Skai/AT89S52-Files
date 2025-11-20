#include <REGX52.h>

// Define Button Pin. 
// Note: Standard AT89S52 does not have Port 4. 
// We are using P3.2 (standard input/interrupt pin) instead.
sbit BUTTON = P3^2; 

void delay_short(void);
bit check_button(void);

// Global mode variable: 0 = Knight Rider, 1 = Chase
bit mode = 0; 

void main()
{
	unsigned char i;
	
	// Initialize Button (Input)
	BUTTON = 1; 

	while(1)
	{
		if(mode == 0) // --- Mode 0: Knight Rider Pattern ---
		{
			// 1. Sweep Left
			for(i = 0; i < 8; i++)
			{
				P1 = (0x01 << i); 
				delay_short();
				if(check_button()) break; // Exit loop if mode changed
			}
			
			// 2. Sweep Right (only if mode hasn't changed)
			if(mode == 0) 
			{
				for(i = 6; i > 0; i--)
				{
					P1 = (0x01 << i);
					delay_short();
					if(check_button()) break;
				}
			}
		}
		else // --- Mode 1: Chase Light Pattern ---
		{
			// Continuous Left Shift (loops 0 to 7 then restarts at 0)
			for(i = 0; i < 8; i++)
			{
				P1 = (0x01 << i);
				delay_short();
				if(check_button()) break;
			}
		}
	}
}

// Checks button state, debounces, and toggles mode.
// Returns 1 if mode was changed, 0 otherwise.
bit check_button(void)
{
	if(BUTTON == 0) // Check if button pressed (Active Low)
	{
		delay_short(); // Simple debounce using existing delay
		if(BUTTON == 0)
		{
			mode = !mode; // Toggle the mode
			
			// Wait for button release to prevent rapid toggling
			while(BUTTON == 0); 
			
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