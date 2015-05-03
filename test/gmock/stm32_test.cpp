#include "gmock/gmock.h"
#include <stm32.h>

TEST(stm32, passingTest)
{
    ASSERT_EQ(1,1);
}

TEST(stm32, waitButtonDown)
{
    stm32_waitButtonDown();
    ASSERT_EQ(1,1); //will only be executed if stm32_waitButtonDown exit
}
