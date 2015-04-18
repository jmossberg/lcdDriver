#include "gmock/gmock.h"

extern "C"
{
#include "add.h"
}

TEST(AddFunction, CanAdd)
{
    ASSERT_EQ(3, add(1,2));
}
