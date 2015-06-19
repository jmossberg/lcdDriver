#include "lcdDriver.h"

int main()
{
	lcdDriver_create();
	uint8_t test_character = 'A';
	lcdDriver_displayCharacter(&test_character);
	while(1){};
}
