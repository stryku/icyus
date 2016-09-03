#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#define FOR_TIMES_WILL_RETURN(times, returnValue, mock ,method, ...) \
{ \
    ::testing::InSequence dummy; \
    size_t t = times; \
    while (t --> 0) \
    { \
        EXPECT_CALL(mock, method(__VA_ARGS__)) \
            .WillOnce(Return(returnValue)) \
            .RetiresOnSaturation(); \
    } \
}
