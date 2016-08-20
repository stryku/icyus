#pragma once

#include <string>

namespace Icyus
{
    namespace Model
    {
        class IModelObserver abstract
        {
        public:
            ~IModelObserver() = default;
            
            virtual void newSenderConnectionStatus(const std::string &status) = 0;
            virtual void newSenderProgress(size_t progress) = 0;
            virtual void newSenderTransferSpeed(uintmax_t progress) = 0;
            virtual void newModelReceiverAddress(const std::string &address) = 0;
            virtual void senderFilePathChanged(const std::string &newPath) = 0;
            virtual void senderProgressValueChanged(int newValue) = 0;

            virtual void newReceiverListeningStatus(const std::string &status) = 0;
            virtual void newReceiverProgress(size_t progress) = 0;
            virtual void receiverProgressValueChanged(int newValue) = 0;
        };
    }
}