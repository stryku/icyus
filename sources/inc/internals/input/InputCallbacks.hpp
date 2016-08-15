#pragma once

#include <functional>

namespace Icyus
{
    namespace Input
    {
        struct InputCallbacks
        {
            std::function<void(bool)> chooseFile;
            std::function<void(bool)> send;
            std::function<void(bool)> connect;
            std::function<void(const std::string&)> newReceiverAddress;
        };
    }
}