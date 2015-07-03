#include "lcdDriver.h"
#include <stm32.h>

int main()
{
	lcdDriver_create(); /* Will call stm32_create() */
	uint8_t test_string[] = "TEST";
	lcdDriver_displayString(test_string);	
	
	while(1) {
		//Set LED on
		stm32_setPortC(12, LOW);
	
		//Delay 3 seconds
		stm32_delay(3000);
	
		//Set LED off
		stm32_setPortC(12, HIGH);
	
		//Delay 3 seconds
		stm32_delay(3000);
	}
}
