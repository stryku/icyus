#pragma once

#include <internals/communication/details/TransferHeaderMsgFactory.hpp>

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
                       uintmax_t granularity = 1024 * 1024 * 10,
                       std::function<void(size_t)> callaback = {});

            void setGranularity(uintmax_t newGranularity) noexcept;
            void setUptadeProgressCallback(std::function<void(size_t)> newCallaback) noexcept;

            void connect(const std::string &address, std::function<void()> doneCallback = {});
            void connectAsync(const std::string &address, std::function<void()> doneCallback);

            void send(const std::experimental::filesystem::path &path);
            void sendAsync(const std::string &path);

        private:
            void sendHeader(const std::experimental::filesystem::path &path);

            zmq::context_t &context;
            zmq::socket_t socket;
            std::function<void(size_t)> progressCallback;
            uintmax_t granularity;
            std::thread asyncThread;
        };
    }
}
