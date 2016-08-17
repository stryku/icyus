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
                         std::function<void(size_t)> callaback = {}) :
                context{ ctx },
                socket{ context, zmq::socket_type::pull },
                progressCallback{ callaback }
            {
            }

            void receiveFile()
            {
                auto fileSize{ 0ull };
                auto alreadyReceivedBytes{ 0ull };
                auto currentlyReceived{ 0ull };
                zmq::message_t msg;
                std::ofstream out("out2", std::ios::binary);

                socket.recv(&msg);

                fileSize = std::stoull(msg.str());

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


            void startListening(const std::string &address = "tcp://*:1666")
            {
                if (receivingThread.joinable())
                    receivingThread.join();

                socket.bind(address);

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
