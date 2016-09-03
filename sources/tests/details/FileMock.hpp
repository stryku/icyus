#pragma once

#include <gtest/gtest/gtest.h>
#include <gtest/gmock/gmock.h>

#include <experimental/filesystem>

namespace Icyus
{
    namespace Tests
    {
        namespace Mocks
        {
            struct FileMock
            {
                FileMock() {}

                MOCK_CONST_METHOD0(size, uintmax_t());
                MOCK_CONST_METHOD2(read, uintmax_t(void*, size_t));
                MOCK_CONST_METHOD0(lastReadCount, size_t());
                MOCK_CONST_METHOD0(is_open, bool());
                MOCK_CONST_METHOD0(name, std::experimental::filesystem::path());
            };
        }
    }
}