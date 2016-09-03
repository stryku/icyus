#pragma once

#include <internals/utils/utils.hpp>

#include <gtest/gtest/gtest.h>
#include <gtest/gmock/gmock.h>

#include <vector>

namespace Icyus
{
    namespace Tests
    {
        namespace Mocks
        {
            struct SocketMock : public Icyus::Tests::TestClass
            {
                using MessageType = std::vector<char>;

                MOVABLE_MOCK_METHOD1(connect, void(const std::string &address));
                MOVABLE_MOCK_METHOD1(bind, void(const std::string &address));
                MOVABLE_MOCK_METHOD2(send, size_t(const void *data, size_t size));
                MOVABLE_MOCK_METHOD1(send, size_t(MessageType &msg));
                MOVABLE_MOCK_METHOD1(recv, bool(MessageType &msg));
                MOVABLE_MOCK_METHOD0(recvDummy, void());
                MOVABLE_MOCK_METHOD0(sendDummy, void());
            };
        }
    }
}