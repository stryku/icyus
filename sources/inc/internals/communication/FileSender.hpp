#pragma once

#include <zmq/zmq.hpp>

#include <functional>
#include <fstream>
#include <thread>
#include <filesystem>

namespace Icyus
{
    namespace Communication
    {
        class FileSender
        {
        public:
            FileSender(zmq::context_t &ctx,
                       size_t granularity = 1024 * 1024 * 32,
                       std::function<void(size_t)> callaback = {});

            void setGranularity(size_t newGranularity);
            void setUptadeProgressCallback(std::function<void(size_t)> newCallaback);

            void connect(const std::string &address, std::function<void()> doneCallback = {});
            void connectAsync(const std::string &address, std::function<void()> doneCallback);

            void send(const std::string &path);
            void sendAsync(const std::string &path);

        private:
            zmq::context_t &context;
            zmq::socket_t socket;
            std::function<void(size_t)> progressCallback;
            size_t granularity;
            std::thread asyncThread;
        };
    }
}
