#include "gmock/gmock.h"

extern "C"
{
#include <lcdDriver.h>
#include <mock_lcdIO.h>
}

TEST(lcdDriver, createLcdDriver)
{
  ASSERT_EQ(0, lcdDriver_create());
}

TEST(lcdDriver, destroyLcdDriver)
{
  ASSERT_EQ(0, lcdDriver_destroy());
}

TEST(lcdDriver, activateCommandMode)
{
  //Setup
  uint8_t test_character = 'A';
  ASSERT_EQ(0, lcdDriver_create());

  //Execute
  ASSERT_EQ(0, lcdDriver_displayCharacter(&test_character));

  //Verify
  ASSERT_EQ(1, mock_lcdIO_getCountActivateCommandMode());

  //Teardown
  ASSERT_EQ(0, lcdDriver_destroy());
}

TEST(lcdDriver, requestCharacterA)
{
  //Setup
  uint8_t test_character = 'A';
  ASSERT_EQ(0, lcdDriver_create());

  //set expectations
  //expect lcd data bits to set lcd to 4 bit mode
  //that is code 0x20 (0b00100000)
  mock_lcdIO_addExpectedLcdCommand(0x20, COMMAND_MODE);
  //expect lcd clear, that is code 0x01
  mock_lcdIO_addExpectedLcdCommand(0x00, COMMAND_MODE); // first nibble
  mock_lcdIO_addExpectedLcdCommand(0x10, COMMAND_MODE); // second nibble
  //expect lcd display on, that is code 0x0f
  mock_lcdIO_addExpectedLcdCommand(0x00, COMMAND_MODE); // first nibble
  mock_lcdIO_addExpectedLcdCommand(0xf0, COMMAND_MODE); // second nibble
  //expect lcd to receive character A, that is code 0x41
  mock_lcdIO_addExpectedLcdCommand(0x40, CHARACTER_MODE); // first nibble
  mock_lcdIO_addExpectedLcdCommand(0x10, CHARACTER_MODE); // second nibble
 
  //Execute
  ASSERT_EQ(0, lcdDriver_displayCharacter(&test_character));

  //Verify
  ASSERT_EQ(1, mock_lcdIO_lcdCommandsEqualExpected());

  //Teardown
  ASSERT_EQ(0, lcdDriver_destroy());
}

