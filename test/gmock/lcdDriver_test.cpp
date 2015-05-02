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

//TEST(lcdDriver, activateCommandMode)
//{
//    ASSERT_EQ(1,1);
//}
