#include <internals/communication/FileReceiver.hpp>
#include <internals/communication/details/TransferHeaderParser.hpp>

#include <internals/utils/log.hpp>

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
            auto alreadyReceivedBytes{ 0ull };
            auto currentlyReceived{ 0ull };
            zmq::message_t msg;

            auto header = receiveHeader();
            LOG("received file header: " << header.fileName << ", " << header.fileSize);

            std::ofstream out(header.fileName, std::ios::binary);
            LOG("File will be written to " << header.fileName);

            while (alreadyReceivedBytes < header.fileSize)
            {
                socket.recv(&msg);
                socket.send();

                currentlyReceived = msg.size();

                alreadyReceivedBytes += currentlyReceived;
                LOG("received file chunk of size: " << currentlyReceived);

                if (progressCallback)
                    progressCallback(100 * alreadyReceivedBytes / header.fileSize);

                LOG("Received " << alreadyReceivedBytes << "/" << header.fileSize << "b (" << 100 * alreadyReceivedBytes / header.fileSize << "%)");

                out.write(static_cast<const char*>(msg.data()), msg.size());
            }

            LOG("receiving finished. Received " << alreadyReceivedBytes << "/" << header.fileSize << "bytes");
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

        detail::TransferHeader::Header FileReceiver::receiveHeader()
        {
            zmq::message_t msg;

            socket.recv(&msg);
            socket.send();

            return detail::TransferHeader::Parser<detail::TransferHeader::Formats::Xml>::parse(msg.cbegin(), msg.cend());
        }


    }
}