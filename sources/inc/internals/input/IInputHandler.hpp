#pragma once

namespace Icyus
{
    namespace Input
    {
        class IInputHandler abstract
        {
        public:
            ~IInputHandler() = default;

            virtual void chooseFile() = 0;
        };
    }
}