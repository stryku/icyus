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

            virtual void setFileToSendLabel(const std::string &path) = 0;
            virtual void setSenderProgressBarBounds(int min, int max) = 0;
            virtual void setSenderProgressBarValue(int value) = 0;
            virtual void setSenderConnectedStatus(const std::string &status) = 0;

            virtual void setReceiverListeningStatus(bool status) = 0;
            virtual void setReceivingFileName(const std::string &name) = 0;
            virtual void setReceiverProgressBarBounds(int min, int max) = 0;
            virtual void setReceiverProgressBarValue(int value) = 0;
        };
    }
}
