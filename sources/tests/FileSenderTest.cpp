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

TEST(FileSenderTest, emptyFile_exactHeader)
{
    using Socket = Icyus::Tests::Mocks::SocketMock;
    using File = Icyus::Tests::Mocks::FileMock;
    File fileMock;
    Socket socket;
    std::string filename = "file name.txt";

    std::string expectedHeaderStr{ "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<header><filename>" + filename + "</filename><filesize>0</filesize></header>" };
    auto expectedHeaderMsg = Socket::MessageType{ std::begin(expectedHeaderStr),
        std::end(expectedHeaderStr) };

    std::cout << expectedHeaderStr << "\n";

    EXPECT_CALL(socket, send(expectedHeaderMsg));
    EXPECT_CALL(socket, recvDummy());

    EXPECT_CALL(fileMock, size()).
        WillRepeatedly(Return(0));

    EXPECT_CALL(fileMock, name()).
        WillRepeatedly(Return(filename));

    Icyus::Communication::FileSender<Socket, File> sender{ std::move(socket) };

    sender.send(fileMock);
}

TEST(FileSenderTest, zeroGranularity_throw)
{
    using Socket = Icyus::Tests::Mocks::SocketMock;
    using File = Icyus::Tests::Mocks::FileMock;
    Socket socket;
    File file;
    Icyus::Communication::FileSender<Socket, File> sender{ std::move(socket), };

    EXPECT_THROW(sender.setGranularity(0), std::runtime_error);
}
