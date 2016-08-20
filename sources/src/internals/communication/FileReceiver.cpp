#include <internals/communication/FileReceiver.hpp>

#include <internals/utils/log.hpp>
#include <internals/communication/utils/helpers.hpp>

namespace Icyus
{
    namespace Communication
    {
        FileReceiver::FileReceiver(zmq::context_t &ctx,
                                   std::function<void(size_t)> callaback) :
            context{ ctx },
            socket{ context, zmq::socket_type::rep },
            progressCallback{ callaback }
        {}

        void FileReceiver::receiveFile()
        {
            constexpr auto ok{ "ok" };
            auto fileSize{ 0ull };
            auto alreadyReceivedBytes{ 0ull };
            auto currentlyReceived{ 0ull };
            zmq::message_t msg;
            zmq::message_t okMsg{ 1 };
            auto fileName{ "out" };
            std::ofstream out(fileName, std::ios::binary);
            LOG("receiveFile. File will be written to " << fileName);

            socket.recv(&msg);
            LOG("received file size: " << fileSize);
            socket.send(okMsg);
            LOG("send ok msg");

            fileSize = std::stoull(msg.str());

            while (alreadyReceivedBytes < fileSize)
            {
                socket.recv(&msg);
                socket.send(okMsg);

                currentlyReceived = msg.size();

                alreadyReceivedBytes += currentlyReceived;
                LOG("received file chunk of size: " << currentlyReceived);

                if (progressCallback)
                    progressCallback(alreadyReceivedBytes);

                LOG("Received " << alreadyReceivedBytes << "/" << fileSize << "b (" << 100 * alreadyReceivedBytes / fileSize << "%)");

                out.write(static_cast<const char*>(msg.data()), msg.size());
            }

            LOG("receiving finished. Received " << alreadyReceivedBytes << "/" << fileSize << "bytes");
        }

        void FileReceiver::startListening(const std::string &address)
        {
            LOG("Receiver start listening");

            if (receivingThread.joinable())
            {
                LOG("receiving thread joinable. Joining.");
                receivingThread.join();
                LOG("Joining successfull");
            }

            LOG("Binding");
            socket.bind(address);

            LOG("Starting receiving thread");
            receivingThread = std::thread{ [this] { receiveFile(); } };
        }
    }
}