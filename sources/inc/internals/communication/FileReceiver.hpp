#pragma once

#include <zmq/zmq.hpp>

#include <functional>
#include <thread>
#include <fstream>

namespace Icyus
{
    namespace Communication
    {
        class FileReceiver
        {
        public:
            FileReceiver(zmq::context_t &ctx,
                         const std::string &address = "tcp://127.0.0.1:1666",
                         std::function<void(size_t)> callaback = {}) :
                context{ ctx },
                socket{ context, zmq::socket_type::pull },
                progressCallback{ callaback }
            {
                socket.bind(address);
            }

            void receiveFile()
            {
                size_t fileSize;
                size_t alreadyReceivedBytes{ 0 };
                size_t currentlyReceived;
                zmq::message_t msg;
                std::ofstream out("out", std::ios::binary);

                socket.recv(&msg);

                fileSize = std::stoul(msg.str());

                while (alreadyReceivedBytes < fileSize)
                {
                    socket.recv(&msg);

                    currentlyReceived = msg.size();

                    alreadyReceivedBytes += currentlyReceived;

                    if (progressCallback)
                        progressCallback(alreadyReceivedBytes);

                    out.write(static_cast<const char*>(msg.data()), msg.size());
                }
            }

            void startReceiving()
            {
                if (receivingThread.joinable())
                    receivingThread.join();

                receivingThread = std::thread{ [this] {receiveFile(); } };
            }

        private:
            zmq::context_t &context;
            zmq::socket_t socket;
            std::function<void(size_t)> progressCallback;
            std::thread receivingThread;
        };
    }
}
