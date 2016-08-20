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
            InputPropagator(IInputHandler &inputHandler);

            void chooseFile();
            void send();
            void connect();
            void startListening();
            void newReceiverAddress(const std::string &address);
            InputCallbacks getCallbacks();

        private:
            IInputHandler &inputHandler;
        };
    }
}