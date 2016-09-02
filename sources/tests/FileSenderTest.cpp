#include <internals/communication/FileSender.hpp>

#include <SocketMock.hpp>
#include <FileMock.hpp>

#include <gtest/gtest/gtest.h>
#include <gtest/gmock/gmock.h>

using ::testing::Return;
using ::testing::_;

TEST(FileSenderTest, emptyFile_onlyHeaderSend)
{
    using Socket = Icyus::Tests::Mocks::SocketMock;
    using File = Icyus::Tests::Mocks::FileMock;
    File fileMock;
    Socket socket;

    EXPECT_CALL(socket, send(_));
    EXPECT_CALL(socket, recvDummy());

    EXPECT_CALL(fileMock, size()).
        WillRepeatedly(Return(0));

    EXPECT_CALL(fileMock, name()).
        WillRepeatedly(Return(""));

    Icyus::Communication::FileSender<Socket, File> sender{ std::move(socket) };

    sender.send(fileMock);
}
