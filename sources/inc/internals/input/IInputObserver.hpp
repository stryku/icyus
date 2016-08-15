#pragma once

#include <string>

namespace Icyus
{
    namespace Input
    {
        class IInputObserver abstract
        {
        public:
            ~IInputObserver() = default;

            virtual void newFileChoosed(const std::string &path, void *notifier) = 0;
            virtual void newReceiverAddress(const std::string &address, void *notifier) = 0;
        };
    }
}
