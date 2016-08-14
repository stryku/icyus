#pragma once

namespace Icyus
{
    namespace Model
    {
        class IModelObserver abstract
        {
        public:
            ~IModelObserver() = default;

            virtual void senderFilePathChanged(const std::string &newPath) = 0;
            virtual void senderProgressValueChanged(int newValue) = 0;

            virtual void receiverProgressValueChanged(int newValue) = 0;
        };
    }
}