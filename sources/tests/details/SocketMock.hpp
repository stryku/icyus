#pragma once

#include <gtest/gtest/gtest.h>
#include <gtest/gmock/gmock.h>

#include <vector>

namespace Icyus
{
    namespace Tests
    {
        namespace Mocks
        {
            class SocketMock
            {
                using MsgType = std::vector<char>;

                MOCK_METHOD1(connect, void(const std::string &address));
                MOCK_METHOD1(bind, void(const std::string &address));
                MOCK_METHOD2(send, size_t(const void *data, size_t size));
                MOCK_METHOD1(send, size_t(MsgType &msg));
                MOCK_METHOD1(recv, bool(MsgType &msg));
                MOCK_METHOD0(recvDummy, void());
                MOCK_METHOD0(sendDummy, void());
            };
        }
    }
}