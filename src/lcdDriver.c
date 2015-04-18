#include <lcdDriver.h>
#include <lcdIO.h>

static uint8_t lcdDataBits;

static inline void lcdDriver_bumpEnable()
{
  lcdIO_setEnableHigh();
  lcdIO_delayMicroSeconds(1);
  lcdIO_setEnableLow();
}

static inline void lcdDriver_send8BitsToDisplay(uint8_t bitsToSend)
{
  lcdDataBits = bitsToSend & 0xF0;
  lcdIO_setDataBits(&lcdDataBits);
  lcdDriver_bumpEnable();
  lcdIO_delayMicroSeconds(100);

  lcdDataBits = (bitsToSend << 4);
  lcdIO_setDataBits(&lcdDataBits);
  lcdDriver_bumpEnable();
  lcdIO_delayMicroSeconds(100);
}

static void lcdDriver_clearDisplay()
{
  lcdDriver_send8BitsToDisplay(0x01);
}

static void lcdDriver_turnDisplayOn()
{
  //turn display on
  lcdDataBits = 0x00;
  lcdIO_setDataBits(&lcdDataBits);
  lcdDriver_bumpEnable();
  lcdIO_delayMicroSeconds(100);

  lcdDataBits = 0xf0;
  lcdIO_setDataBits(&lcdDataBits);
  lcdDriver_bumpEnable();
  lcdIO_delayMicroSeconds(100);
}

static void lcdDriver_set4BitMode()
{
  lcdDataBits = 0x20;
  lcdIO_setDataBits(&lcdDataBits);
  lcdDriver_bumpEnable();
  lcdIO_delayMicroSeconds(100);
}

static void lcdDriver_activateCommandMode()
{
  lcdIO_activateCommandMode();
  lcdIO_delayMicroSeconds(1);
}

static void lcdDriver_activateCharacterMode()
{
  lcdIO_activateCharacterMode();
  lcdIO_delayMicroSeconds(1);
}


static void lcdDriver_addCharacter(uint8_t * characterToDisplay_p)
{
  lcdDriver_send8BitsToDisplay(*characterToDisplay_p);
}

uint8_t lcdDriver_create()
{
  lcdDataBits = 0;
  return 0;
}

uint8_t lcdDriver_destroy()
{
  lcdDataBits = 0;
  return 0;
}

uint8_t lcdDriver_displayString(uint8_t * stringToDisplay_p)
{
  uint8_t i = 0;

  lcdDriver_activateCommandMode();

  lcdDriver_set4BitMode();

  lcdDriver_clearDisplay();

  lcdDriver_turnDisplayOn();

  lcdDriver_activateCharacterMode();

  for(i = 0; i<10; i++)
  {
    if('\0' == stringToDisplay_p[i])
    {
      break;
    }
    else
    {
      lcdDriver_addCharacter(stringToDisplay_p + i);
    }
  }

  return 0;
}

uint8_t lcdDriver_displayCharacter(uint8_t * characterToDisplay_p)
{

  lcdDriver_activateCommandMode();

  lcdDriver_set4BitMode();

  lcdDriver_clearDisplay();

  lcdDriver_turnDisplayOn();

  lcdDriver_activateCharacterMode();

  lcdDriver_addCharacter(characterToDisplay_p);

  return 0;
}
