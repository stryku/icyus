#pragma once

#include <internals/view/IView.hpp>
#include <internals/view/detail/QtWidgetManager.hpp>
#include <internals/view/detail/GuiUpdater.hpp>

#include <QString>

namespace Icyus
{
    namespace View
    {
        class QtView final : public IView
        {
        public:
            QtView(QWidget *widgetContainer) noexcept;

            ~QtView() = default;
            QtView(QtView&&) = default;
            QtView& operator=(QtView&&) = default;

            QtView(QtView&) = delete;
            QtView& operator=(QtView&) = delete;

            void connectWithInputPropagator(Icyus::Input::InputPropagator &propagator) override;

            void sendingStarted(size_t size) override;
            void setFileToSend(const std::string &path) override;
            void setSenderProgressValue(int value) override;
            void setSenderConnectedStatus(const std::string &status) override;

            void setReceiverAddress(const std::string &address) override;
            void setReceiverListeningStatus(const std::string &status) override;
            void setReceivingFileName(const std::string &name) override;
            void setReceiverProgressValue(int value) override;

        private:
            detail::QtWidgetManager widgetManager;
            detail::GuiUpdater updater;
        };
    }
}
