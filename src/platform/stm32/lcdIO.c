#include <lcdIO.h>


/* STM32 <--> LCD Pin connections
 *
 *  PORT | Bit | Extension board | LCD Pin
 *  -----|-----|-----------------|---------------------
 *  C    | 0   | EXT1-19         | Data bit 4
 *  C    | 1   | EXT1-20         | Data bit 5
 *  C    | 2   | EXT2-2          | Data bit 6
 *  C    | 3   | EXT2-9          | Data bit 7
 *  C    | 4   | EXT2-12         | RS (Register Select)
 *  C    | 5   | EXT2-13         | E (Enable)   
 */


void lcdIO_create()
{

}

void lcdIO_destroy()
{

}

void lcdIO_activateWriteMode();
{

}

void lcdIO_activateCommandMode()
{
	stm32_setPortC(4, LOW);
}

void lcdIO_activateCharacterMode();
{
	stm32_setPortC(4, HIGH);
}

void lcdIO_setEnableHigh()
{
	stm32_setPortC(5, HIGH);
}

void lcdIO_setEnableLow()
{
	stm32_setPortC(5, LOW);
}

void lcdIO_waitForEnableToRegisterInLcd()
{
	stm32_delay(4000);
}

void lcdIO_delayMicroSeconds(uint8_t microSeconds)
{
	stm32_delay(1);
}

void lcdIO_setDataBits(uint8_t * lcdDataBits_p)
{
	/* Bit 4-7 from *lcdDataBits_p shall be sent to display */

	uint8_t i = 0;

	for(i = 4; i <= 7; i++) {
		PINSTATE pinState = LOW;
		uint8_t bitValue = (*lcdDataBits_p >> i) & 0x01;
		if(1 == bitValue) { pinState = HIGH; }
		stm32_setPortC(i, pinState);
	}
}
