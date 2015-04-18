#include <stdint.h>

#ifndef LCDIO_H
#define LCDIO_H

void lcdIO_create();
void lcdIO_destroy();
void lcdIO_activateWriteMode();
void lcdIO_activateCommandMode();
void lcdIO_activateCharacterMode();
void lcdIO_setDataBits(uint8_t * lcdDataBits_p);
void lcdIO_setEnableHigh();
void lcdIO_setEnableLow();
void lcdIO_waitForEnableToRegisterInLcd();
void lcdIO_delayMicroSeconds(uint8_t microSeconds);

//for testing
void lcdIO_setDS1High();
void lcdIO_setDS1Low();

#endif
