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
        template <typename Socket>
        class FileSender
        {
        public:
            FileSender(Socket &&socket,
                       uintmax_t granularity = 1024 * 1024 * 10,
                       std::function<void(size_t)> progressCallback = {},
                       std::function<void(uintmax_t)> transferSpeedCallback = {}) :
                socket{ std::move(socket) },
                progressCallback{ progressCallback },
                transferSpeedCallback{ transferSpeedCallback },
                granularity{ granularity }
            {}


            void setGranularity(uintmax_t newGranularity) noexcept
            {
                granularity = newGranularity;
            }

            void setUptadeProgressCallback(std::function<void(size_t)> newCallaback) noexcept
            {
                progressCallback = newCallaback;
            }

            void setUptadeTransferSpeedCallback(std::function<void(uintmax_t)> newCallback) noexcept
            {
                transferSpeedCallback = newCallback;
            }


            void connect(const std::string &address, std::function<void()> doneCallback = {})
            {
                try
                {
                    socket.connect(address);

                    if (doneCallback)
                        doneCallback();
                }
                catch (std::exception &e)
                {
                    //todo handle
                }
            }

            void connectAsync(const std::string &address, std::function<void()> doneCallback)
            {
                if (asyncThread.joinable())
                    asyncThread.join();

                asyncThread = std::thread{ [this,
                    address,
                    doneCallback]
                {
                    connect(address, doneCallback);
                } };
            }


            void send(const std::experimental::filesystem::path &path) {
                std::vector<char> buffer(granularity);
                char *buffPtr = &buffer[0];
                std::ifstream file{ path, std::ios::binary };
                auto alreadySendBytes{ 0ull };
                auto currentRead{ 0ull };
                size_t lastProgress = -1;
                auto fileSize = std::experimental::filesystem::file_size(path);
                Clock::time_point chunkSendStart;

                if (!file.is_open())
                    return;

                sendHeader(path);

                while (file.read(buffPtr, granularity))
                {
                    currentRead = file.gcount();

                    chunkSendStart = Clock::now();
                    socket.send(buffPtr, currentRead);
                    socket.recvDummy();

                    alreadySendBytes += currentRead;

                    progressCallback((alreadySendBytes * 100) / fileSize);
                    updateTransferSpeed(chunkSendStart);
                }

                if ((currentRead = file.gcount()) > 0)
                    socket.send(buffPtr, currentRead);

                progressCallback(100);
            }

            void sendAsync(const std::string &path)
            {
                if (asyncThread.joinable())
                    asyncThread.join();

                asyncThread = std::thread{ [this, path] { send(path); } };
            }

        private:
            using Clock = std::chrono::system_clock;
            void sendHeader(const std::experimental::filesystem::path &path)
            {
                auto fileSize = std::experimental::filesystem::file_size(path);
                auto transferHeaderMsg = detail::TransferHeader::MsgFactory<zmq::message_t,
                    detail::TransferHeader::Formats::Xml>::create(path.filename().string(),
                                                                  fileSize);

                socket.send(transferHeaderMsg);
                socket.recvDummy();
            }
            void updateTransferSpeed(const std::chrono::time_point<Clock> &start)
            {
                using s = std::chrono::seconds;
                auto duration = Clock::now() - start;
                auto sec = std::chrono::duration_cast<s>(duration);

                transferSpeedCallback((sec.count() == 0) ?
                                      granularity :
                                      granularity / sec.count());
            }

            Socket socket;
            std::function<void(size_t)> progressCallback;
            std::function<void(uintmax_t)> transferSpeedCallback;
            uintmax_t granularity;
            std::thread asyncThread;
        };
    }
}
