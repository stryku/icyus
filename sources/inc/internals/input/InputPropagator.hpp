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

            void send()
            {
                inputHandler.send();
            }

            void connect()
            {
                inputHandler.connect();
            }

            void startListening()
            {
                inputHandler.receiverStartListening();
            }

            void newReceiverAddress(const std::string &address)
            {
                inputHandler.newReceiverAddress(address);
            }

            InputCallbacks getCallbacks()
            {
                return {
                    [this](bool) { chooseFile(); },
                    [this](bool) { send(); },
                    [this](bool) { connect(); },
                    [this](const std::string &address) { newReceiverAddress(address); },

                    {
                        [this](bool) { startListening(); }
                    }
                };
            }

        private:
            IInputHandler &inputHandler;
        };
    }
}