#include <internals/communication/FileSender.hpp>

#include <details/SocketMock.hpp>
#include <details/FileMock.hpp>
#include <utils/utils.hpp>

#include <gtest/gtest/gtest.h>
#include <gtest/gmock/gmock.h>

using ::testing::Return;
using ::testing::AtLeast;
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

TEST(FileSenderTest, granularity_sendCount)
{
    using Socket = Icyus::Tests::Mocks::SocketMock;
    using File = Icyus::Tests::Mocks::FileMock;
    Socket socket;
    auto granularities = { 1, 2, 3 };
    auto filesizes = { 0, 1, 2, 3 };

    //socket.send times
    for (auto &size : filesizes)
    {
        for (auto &granularity : granularities)
        {
            int n = size / granularity + (size%granularity ? 1 : 0);
            EXPECT_CALL(socket, send(_))
                .RetiresOnSaturation(); //header
            EXPECT_CALL(socket, send(_,_))
                .Times(n)
                .RetiresOnSaturation(); //fileChunk send times
        }
    }

    Icyus::Communication::FileSender<Socket, File> sender{ std::move(socket), };

    for (auto &size : filesizes)
    {
        for (auto &granularity : granularities)
        {
            File file;
            uintmax_t alreadyRead;
            size_t fullBufferReads = size / granularity;
            size_t lastRead = size % granularity;

            FOR_TIMES_WILL_RETURN(2, size, file, size, );

            EXPECT_CALL(file, name()).
                WillRepeatedly(Return(""));

            FOR_TIMES_WILL_RETURN(fullBufferReads, granularity, file, lastReadCount, );

            if (lastRead > 0)
            {
                EXPECT_CALL(file, lastReadCount())
                    .WillOnce(Return(lastRead))
                    .RetiresOnSaturation();
            }

            sender.setGranularity(granularity);
            sender.send(file);
        }
    }
}

TEST(FileSenderTest, zeroGranularity_throw)
{
    using Socket = Icyus::Tests::Mocks::SocketMock;
    using File = Icyus::Tests::Mocks::FileMock;
    Socket socket;
    File file;
    Icyus::Communication::FileSender<Socket, File> sender{ std::move(socket) };

    ASSERT_THROW(sender.setGranularity(0), std::runtime_error);
}