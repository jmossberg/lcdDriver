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
  lcdIO_create();
  ASSERT_EQ(0, lcdDriver_create());

  //Execute
  ASSERT_EQ(0, lcdDriver_displayCharacter(&test_character));

  //Verify
  ASSERT_EQ(1, mock_lcdIO_getCountActivateCommandMode());

  //Teardown
  ASSERT_EQ(0, lcdDriver_destroy());
  lcdIO_destroy();
}
