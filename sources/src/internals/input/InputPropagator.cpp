#include <internals/input/InputPropagator.hpp>

namespace Icyus
{
    namespace Input
    {
        InputPropagator::InputPropagator(IInputHandler &inputHandler) :
            inputHandler{ inputHandler }
        {}

        void InputPropagator::chooseFile()
        {
            inputHandler.chooseFile();
        }

        void InputPropagator::send()
        {
            inputHandler.send();
        }

        void InputPropagator::connect()
        {
            inputHandler.connect();
        }

        void InputPropagator::startListening()
        {
            inputHandler.receiverStartListening();
        }

        void InputPropagator::newReceiverAddress(const std::string &address)
        {
            inputHandler.newReceiverAddress(address);
        }

        InputCallbacks InputPropagator::getCallbacks()
        {
            return {
                [this](bool) { chooseFile(); },
                [this](bool) { send(); },
                [this](bool) { connect(); },
                [this](const std::string &address) { newReceiverAddress(address); },

                InputCallbacks::Receiver{
                    [this](bool) { startListening(); }
                }
            };
        }
    }
}