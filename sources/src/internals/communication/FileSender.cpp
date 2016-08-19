#include <internals/communication/FileSender.hpp>

namespace Icyus
{
    namespace Communication
    {
        FileSender::FileSender(zmq::context_t &ctx,
                               size_t granularity,
                               std::function<void(size_t)> callaback) :
            context{ ctx },
            socket{ context, zmq::socket_type::push },
            progressCallback{ callaback },
            granularity{ granularity }
        {}

        void FileSender::setGranularity(size_t newGranularity)
        {
            granularity = newGranularity;
        }

        void FileSender::setUptadeProgressCallback(std::function<void(size_t)> newCallaback)
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

        void FileSender::send(const std::string &path)
        {
            std::vector<char> buffer(granularity);
            char *buffPtr = &buffer[0];
            std::ifstream file{ path, std::ios::binary };
            auto alreadySendBytes{ 0ull };
            auto currentRead{ 0ull };

            if (!file.is_open())
                return;

            auto fileSize = std::experimental::filesystem::file_size(path);
            auto strSize = std::to_string(fileSize);

            socket.send(strSize.begin(), strSize.end());

            while (file.read(buffPtr, granularity))
            {
                currentRead = file.gcount();
                socket.send(buffPtr, currentRead);
                alreadySendBytes += currentRead;
                progressCallback((alreadySendBytes * 100) / fileSize);
            }

            if ((currentRead = file.gcount()) > 0)
                socket.send(buffPtr, currentRead);

            progressCallback(100);
        }

        void FileSender::sendAsync(const std::string &path)
        {
            if (asyncThread.joinable())
                asyncThread.join();

            asyncThread = std::thread{ [this, path] { send(path); } };
        }
    }
}