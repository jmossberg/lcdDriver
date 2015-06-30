#include <lcdIO.h>
#include <stm32.h>


/* STM32 <--> LCD Pins <--> Breadboard
 *
 *  PORT | Bit | Extension board | LCD Pin                 | Breadboard
 *  -----|-----|-----------------|-------------------------|-----------
 *       |     |                 | 1. VSS                  | Ground
 *       |     |                 | 2. VCC                  | +5V
 *       |     |                 | 3. Vee (LCD Contrast)   | Variable Resistor
 *  C    | 4   | EXT2-12         | 4. RS (Register Select) |
 *             |                 | 5. Read/Write           | Ground (Write)
 *  C    | 5   | EXT2-13         | 6. E (Enable)           | 
 *       |     |                 | 7. Data bit 0           | Ground
 *       |     |                 | 8. Data bit 1           | Ground
 *       |     |                 | 9. Data bit 2           | Ground
 *       |     |                 | 10.Data bit 3           | Ground
 *  C    | 0   | EXT1-19         | 11.Data bit 4           |
 *  C    | 1   | EXT1-20         | 12.Data bit 5           |
 *  C    | 2   | EXT2-2          | 13.Data bit 6           |
 *  C    | 3   | EXT2-9          | 14.Data bit 7           |
 */


void lcdIO_create()
{
	stm32_create();
	stm32_delay(50);
}

void lcdIO_destroy()
{

}

void lcdIO_activateWriteMode()
{

}

void lcdIO_activateCommandMode()
{
	stm32_setPortC(4, LOW);
}

void lcdIO_activateCharacterMode()
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
