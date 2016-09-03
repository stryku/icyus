#pragma once

#include <internals/communication/details/TransferHeaderMsgFactory.hpp>
#include <internals/utils/utils.hpp>
#include <internals/utils/log.hpp>

#include <zmq/zmq.hpp>

#include <functional>
#include <fstream>
#include <thread>
#include <filesystem>
#include <chrono>
#include <string>

namespace Icyus
{
    namespace Communication
    {
        template <typename Socket, typename File>
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
                if (newGranularity == 0)
                    throw std::runtime_error("FileSender granularity must be > 0");

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


            void send(File &file)
            {
                std::vector<char> buffer(granularity);
                char *buffPtr = &buffer[0];
                auto alreadySendBytes{ 0ull };
                auto currentRead{ 0ull };
                size_t lastProgress = -1;
                //auto fileSize = std::experimental::filesystem::file_size(path);
                auto fileSize = file.size();
                Clock::time_point chunkSendStart;

                sendHeader(file);

                while (alreadySendBytes < fileSize)
                {
                    file.read(buffPtr, granularity);
                    currentRead = file.lastReadCount();

                    chunkSendStart = Clock::now();
                    socket.send(buffPtr, currentRead);
                    socket.recvDummy();

                    alreadySendBytes += currentRead;

                    updateProgress((alreadySendBytes * 100) / fileSize);
                    updateTransferSpeed(chunkSendStart);
                }

                updateProgress(100);
            }

            void sendAsync(const std::string &path)
            {
                if (asyncThread.joinable())
                    asyncThread.join();

                asyncThread = std::thread{ [this, path] { send(path); } };
            }

            std::enable_if_t<Icyus::utils::isTestClass<Socket>, Socket&> getSocket()
            {
                return socket;
            }

        private:
            using Clock = std::chrono::system_clock;
            void sendHeader(const File &file)
            {
                auto transferHeaderMsg = detail::TransferHeader::MsgFactory<Socket::MessageType,
                    detail::TransferHeader::Formats::Xml>::create(file.name(),
                                                                  file.size());

                LOG("sending header: " << std::string(transferHeaderMsg.cbegin(), transferHeaderMsg.cend()));

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
            void updateProgress(size_t progress)
            {
                if (progressCallback)
                    progressCallback(100);
                else
                    LOG("FileSender::progressCallback is empty");
            }

            Socket socket;
            std::function<void(size_t)> progressCallback;
            std::function<void(uintmax_t)> transferSpeedCallback;
            uintmax_t granularity;
            std::thread asyncThread;
        };
    }
}
