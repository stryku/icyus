#include <internals/communication/FileReceiver.hpp>

namespace Icyus
{
    namespace Communication
    {
        FileReceiver::FileReceiver(zmq::context_t &ctx,
                                   std::function<void(size_t)> callaback) :
            context{ ctx },
            socket{ context, zmq::socket_type::pull },
            progressCallback{ callaback }
        {}

        void FileReceiver::receiveFile()
        {
            auto fileSize{ 0ull };
            auto alreadyReceivedBytes{ 0ull };
            auto currentlyReceived{ 0ull };
            zmq::message_t msg;
            auto fileName{ "out" };
            std::ofstream out(fileName, std::ios::binary);

            LOG("receiveFile. File will be written to " << fileName);

            socket.recv(&msg);

            fileSize = std::stoull(msg.str());

            LOG("received file size: " << fileSize);

            while (alreadyReceivedBytes < fileSize)
            {
                socket.recv(&msg);

                currentlyReceived = msg.size();

                alreadyReceivedBytes += currentlyReceived;
                LOG("received file chunk of size: " << currentlyReceived);

                if (progressCallback)
                    progressCallback(alreadyReceivedBytes);

                LOG("received file chunk. Received " << alreadyReceivedBytes << "/" << fileSize << "b (" << 100 * alreadyReceivedBytes / fileSize << "%)");

                out.write(static_cast<const char*>(msg.data()), msg.size());
            }

            LOG("receiving finished. Received " << alreadyReceivedBytes << "/" << fileSize << "bytes");
        }

        void FileReceiver::startListening(const std::string &address)
        {
            if (receivingThread.joinable())
                receivingThread.join();

            socket.bind(address);

            receivingThread = std::thread{ [this] { receiveFile(); } };
        }
    }
}