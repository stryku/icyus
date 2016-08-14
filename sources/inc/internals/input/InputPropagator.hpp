#pragma once

#include <internals/input/IInputHandler.hpp>
#include <internals/input/InputCallbacks.hpp>

namespace Icyus
{
    namespace Input
    {
        class InputPropagator
        {
        public:
            InputPropagator(IInputHandler &inputHandler) :
                inputHandler{ inputHandler }
            {}

            void chooseFile()
            {
                inputHandler.chooseFile();
            }

            InputCallbacks getCallbacks()
            {
                return { 
                    [this] (bool) { chooseFile(); } 
                };
            }

        private:
            IInputHandler &inputHandler;
        };
    }
}