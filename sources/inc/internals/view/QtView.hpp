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

            void setFileToSend(const std::string &path) override
            {}

            void setSenderProgressBounds(int min, int max) override
            {}

            void setSenderProgressValue(int value) override
            {}

            void setSenderConnectedStatus(const std::string &status) override
            {}


            void setReceiverListeningStatus(bool status) override
            {}

            void setReceivingFileName(const std::string &name) override
            {}

            void setReceiverProgressBounds(int min, int max) override
            {}

            void setReceiverProgressValue(int value) override
            {}
        };
    }
}
