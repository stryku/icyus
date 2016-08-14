#pragma once

#include <stdint.h>
#include <string>

namespace Icyus
{
    namespace View
    {
        class IView
        {
        public:
            virtual ~IView() = default;

            virtual void setFileToSend(const std::string &path) = 0;
            virtual void setSenderProgressBounds(int min, int max) = 0;
            virtual void setSenderProgressValue(int value) = 0;
            virtual void setSenderConnectedStatus(const std::string &status) = 0;

            virtual void setReceiverListeningStatus(bool status) = 0;
            virtual void setReceivingFileName(const std::string &name) = 0;
            virtual void setReceiverProgressBounds(int min, int max) = 0;
            virtual void setReceiverProgressValue(int value) = 0;
        };
    }
}
