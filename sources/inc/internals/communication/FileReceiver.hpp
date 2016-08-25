#pragma once

#include <internals/communication/details/TransferHeader.hpp>
#include <internals/utils/log.hpp>

#include <zmq/zmq.hpp>

#include <functional>
#include <thread>
#include <fstream>

namespace Icyus
{
    namespace Communication
    {
        template <typename Socket>
        class FileReceiver
        {
        public:
            FileReceiver(Socket &&socket,
                         std::function<void(size_t)> callaback = {}) :
                socket{ std::move(socket) }, 
                progressCallback{ callaback }
            {}

            void setProgressCallback(std::function<void(size_t)> callback)
            {
                progressCallback = callback;
            }

            void receiveFile()
            {
                constexpr auto ok{ "ok" };
                auto alreadyReceivedBytes{ 0ull };
                auto currentlyReceived{ 0ull };
                zmq::message_t msg;

                auto header = receiveHeader();
                LOG("received file header: " << header.fileName << ", " << header.fileSize);

                std::ofstream out(header.fileName, std::ios::binary);
                LOG("File will be written to " << header.fileName);

                while (alreadyReceivedBytes < header.fileSize)
                {
                    socket.recv(&msg);
                    socket.send();

                    currentlyReceived = msg.size();

                    alreadyReceivedBytes += currentlyReceived;
                    LOG("received file chunk of size: " << currentlyReceived);

                    if (progressCallback)
                        progressCallback(100 * alreadyReceivedBytes / header.fileSize);

                    LOG("Received " << alreadyReceivedBytes << "/" << header.fileSize << "b (" << 100 * alreadyReceivedBytes / header.fileSize << "%)");

                    out.write(static_cast<const char*>(msg.data()), msg.size());
                }

                LOG("receiving finished. Received " << alreadyReceivedBytes << "/" << header.fileSize << "bytes");
            }

            void startListening(const std::string &address = "tcp://*:1666")
            {
                LOG("Receiver start listening");

                if (receivingThread.joinable())
                {
                    LOG("receiving thread joinable. Joining.");
                    receivingThread.join();
                    LOG("Joining successfull");
                }

                LOG("Binding");
                socket.bind(address);

                LOG("Starting receiving thread");
                receivingThread = std::thread{ [this] { receiveFile(); } };
            }



        private:
            detail::TransferHeader::Header receiveHeader()
            {
                using ParseMethod = detail::TransferHeader::Parser<detail::TransferHeader::Formats::Xml>::parse;

                zmq::message_t msg;

                socket.recv(&msg);
                socket.send();

                return ParseMethod(msg.cbegin(), msg.cend());
            }

            Socket socket;
            std::function<void(size_t)> progressCallback;
            std::thread receivingThread;
        };
    }
}
