#pragma once

#include <string>

namespace Icyus
{
    namespace Input
    {
        class IInputHandler abstract
        {
        public:
            ~IInputHandler() = default;

            virtual void chooseFile() = 0;
            virtual void send() = 0;
            virtual void connect() = 0;
            virtual void newReceiverAddress(const std::string &address) = 0;
        };
    }
}