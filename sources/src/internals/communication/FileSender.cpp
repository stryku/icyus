#include <internals/communication/FileSender.hpp>
#include <internals/utils/log.hpp>

namespace Icyus
{
    namespace Communication
    {
        FileSender::FileSender(zmq::context_t &ctx,
                               uintmax_t granularity,
                               std::function<void(size_t)> callaback) :
            context{ ctx },
            socket{ context, zmq::socket_type::req },
            progressCallback{ callaback },
            granularity{ granularity }
        {}

        void FileSender::setGranularity(uintmax_t newGranularity) noexcept
        {
            granularity = newGranularity;
        }

        void FileSender::setUptadeProgressCallback(std::function<void(size_t)> newCallaback) noexcept
        {
            progressCallback = newCallaback;
        }

        void FileSender::connect(const std::string &address, std::function<void()> doneCallback)
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

        void FileSender::connectAsync(const std::string &address, std::function<void()> doneCallback)
        {
            if (asyncThread.joinable())
                asyncThread.join();

            asyncThread = std::thread{ [this,
                                        address,
                                        doneCallback] 
                                        {
                                            connect(address, doneCallback);
                                        }};
        }

        void FileSender::send(const std::experimental::filesystem::path &path)
        {
            std::vector<char> buffer(granularity);
            char *buffPtr = &buffer[0];
            std::ifstream file{ path, std::ios::binary };
            auto alreadySendBytes{ 0ull };
            auto currentRead{ 0ull };
            size_t lastProgress = -1;
            auto fileSize = std::experimental::filesystem::file_size(path);

            if (!file.is_open())
                return;

            sendHeader(path);

            while (file.read(buffPtr, granularity))
            {
                currentRead = file.gcount();

                socket.send(buffPtr, currentRead);
                socket.recv();

                alreadySendBytes += currentRead;
                size_t progress = (alreadySendBytes * 100) / fileSize;
                if (lastProgress != progress)
                {
                    progressCallback((alreadySendBytes * 100) / fileSize);
                    lastProgress = progress;
                }
            }

            if ((currentRead = file.gcount()) > 0)
                socket.send(buffPtr, currentRead);

            progressCallback(100);
        }

        void FileSender::sendHeader(const std::experimental::filesystem::path &path)
        {
            auto fileSize = std::experimental::filesystem::file_size(path);
            auto transferHeaderMsg = detail::TransferHeader::MsgFactory<zmq::message_t,
                                                                        detail::TransferHeader::Formats::Xml>::create(path.filename().string(), 
                                                                                                                      fileSize);

            socket.send(transferHeaderMsg);
            socket.recv();
        }

        void FileSender::sendAsync(const std::string &path)
        {
            if (asyncThread.joinable())
                asyncThread.join();

            asyncThread = std::thread{ [this, path] { send(path); } };
        }
    }
}