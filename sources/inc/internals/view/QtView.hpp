#pragma once

#include <internals/view/IView.hpp>

namespace Icyus
{
    namespace View
    {
        class QtView final : public IView
        {
        public:
            ~QtView() = default;

            void setFileToSendLabel(const std::string &path) override
            {}

            void setSenderProgressBarBounds(int min, int max) override
            {}

            void setSenderProgressBarValue(int value) override
            {}

            void setSenderConnectedStatus(const std::string &status) override
            {}


            void setReceiverListeningStatus(bool status) override
            {}

            void setReceivingFileName(const std::string &name) override
            {}

            void setReceiverProgressBarBounds(int min, int max) override
            {}

            void setReceiverProgressBarValue(int value) override
            {}
        };
    }
}
