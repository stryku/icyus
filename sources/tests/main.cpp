#include <gtest/gtest/gtest.h>
#include <gtest/gmock/gmock.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}