#pragma once

#include <internals/communication/details/TransferHeaderMsgFactory.hpp>

#include <zmq/zmq.hpp>

#include <functional>
#include <fstream>
#include <thread>
#include <filesystem>
#include <chrono>

namespace Icyus
{
    namespace Communication
    {
        class FileSender
        {
        public:
            FileSender(zmq::context_t &ctx,
                       uintmax_t granularity = 1024 * 1024 * 10,
                       std::function<void(size_t)> progressCallback = {},
                       std::function<void(uintmax_t)> transferSpeedCallback = {});

            void setGranularity(uintmax_t newGranularity) noexcept;
            void setUptadeProgressCallback(std::function<void(size_t)> newCallaback) noexcept;
            void setUptadeTransferSpeedCallback(std::function<void(uintmax_t)> newCallback) noexcept;

            void connect(const std::string &address, std::function<void()> doneCallback = {});
            void connectAsync(const std::string &address, std::function<void()> doneCallback);

            void send(const std::experimental::filesystem::path &path);
            void sendAsync(const std::string &path);

        private:
            using Clock = std::chrono::system_clock;
            void sendHeader(const std::experimental::filesystem::path &path);
            void updateTransferSpeed(const std::chrono::time_point<Clock> &start);

            zmq::context_t &context;
            zmq::socket_t socket;
            std::function<void(size_t)> progressCallback;
            std::function<void(uintmax_t)> transferSpeedCallback;
            uintmax_t granularity;
            std::thread asyncThread;
        };
    }
}
