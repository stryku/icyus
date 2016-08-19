#pragma once

#include <internals/utils/log.hpp>

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
                         std::function<void(size_t)> callaback = {});

            void receiveFile();

            void startListening(const std::string &address = "tcp://*:1666");

        private:
            zmq::context_t &context;
            zmq::socket_t socket;
            std::function<void(size_t)> progressCallback;
            std::thread receivingThread;
        };
    }
}
