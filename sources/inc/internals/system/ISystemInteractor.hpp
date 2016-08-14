#pragma once

#include <string>

namespace Icyus
{
    namespace System
    {
        class ISystemInteractor abstract
        {
        public:
            ~ISystemInteractor() = default;

            virtual std::string chooseFile(const std::string &startPath = {}) = 0;
        };
    }
}