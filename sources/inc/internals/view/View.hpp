#pragma once

#include <stdint.h>

namespace Icyus
{
    namespace View
    {
        class IView
        {
        public:
            virtual ~IView() = default;

            void setFileToSendLabel(const std::string &path) = 0;
            void setSenderProgressBarBounds(int min, int max) = 0;
            void setSenderProgressBarValue(int value) = 0;
            void setSenderConnectedStatus(const std::string &status) = 0;

            void setReceiverListeningStatus(bool status) = 0;
            void setReceivingFileName(const std::string &name) = 0;
            void setReceiverProgressBarBounds(int min, int max) = 0;
            void setReceiverProgressBarValue(int value) = 0;
        };
    }
}
