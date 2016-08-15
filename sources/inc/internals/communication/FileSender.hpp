#pragma once

#include <zmq/zmq.hpp>

#include <functional>
#include <fstream>
#include <thread>

namespace Icyus
{
    namespace Communication
    {
        class FileSender
        {
        public:
            FileSender(zmq::context_t &ctx,
                       size_t granularity = 1024 * 1024 * 32,
                       std::function<void(size_t)> callaback = {}) :
                context{ ctx },
                socket{ context, zmq::socket_type::push },
                progressCallback{ callaback },
                granularity{ granularity }
            {}

            void setGranularity(size_t newGranularity)
            {
                granularity = newGranularity;
            }

            void setUptadeProgressCallback(std::function<void(size_t)> newCallaback)
            {
                progressCallback = newCallaback;
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
                asyncThread = std::thread{ [this, 
                                            address, 
                                            doneCallback] {connect(address, 
                                                                   doneCallback); } };
            }

            void send(const std::string &path)
            {
                std::vector<char> buffer(granularity);
                char *buffPtr = &buffer[0];
                std::ifstream file{ path, std::ios::binary };
                size_t alreadySendBytes{ 0 };
                size_t currentRead;

                if (!file.is_open())
                    return;
                
                while ((currentRead = file.readsome(buffPtr, granularity) != 0))
                {
                    socket.send(buffPtr, currentRead);
                    alreadySendBytes += currentRead;
                    progressCallback(alreadySendBytes);
                }
            }

            void sendAsync(const std::string &path)
            {
                asyncThread = std::thread{ [this, &path] { send(path); } };
            }

        private:
            zmq::context_t &context;
            zmq::socket_t socket;
            std::function<void(size_t)> progressCallback;
            size_t granularity;
            std::thread asyncThread;
        };
    }
}
