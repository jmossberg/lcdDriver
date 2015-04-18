#include <stdint.h>

uint8_t lcdDriver_create();
uint8_t lcdDriver_destroy();
uint8_t lcdDriver_displayCharacter(uint8_t * characterToDisplay_p);
uint8_t lcdDriver_displayString(uint8_t * stringToDisplay_p);
