#pragma once

#include <zmq/zmq.hpp>

#include <string>

namespace Icyus
{
    namespace Communication
    {
        namespace detail
        {
            class ZmqSocket
            {
            public:
                using MessageType = zmq::message_t;

                ZmqSocket(zmq::context_t &ctx,
                          zmq::socket_type socketType) :
                    context{ ctx },
                    socket{ ctx, socketType }
                {}

                void connect(const std::string &address)
                {
                    socket.connect(address);
                }

                void bind(const std::string &address)
                {
                    socket.bind(address);
                }

                size_t send(const void *data, size_t size)
                {
                    return socket.send(data, size);
                }

                size_t send(zmq::message_t &msg)
                {
                    return socket.send(msg);
                }

                bool recv(zmq::message_t &msg)
                {
                    return socket.recv(&msg);
                }

                void recvDummy()
                {
                    socket.recv();
                }

                void sendDummy()
                {
                    socket.send();
                }

            private:
                zmq::context_t &context;
                zmq::socket_t socket;
            };
        }
    }
}