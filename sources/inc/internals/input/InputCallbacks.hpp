#pragma once

#include <functional>

namespace Icyus
{
    namespace Input
    {
        struct InputCallbacks
        {
            std::function<void(bool)> chooseFile;
        };
    }
}