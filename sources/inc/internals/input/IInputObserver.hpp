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

            virtual void newFileChoosed(const std::string &path) = 0;
        };
    }
}