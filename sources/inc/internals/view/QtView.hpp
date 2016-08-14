#pragma once

#include <internals/view/IView.hpp>
#include <internals/view/detail/QtWidgetManager.hpp>

#include <QString>

namespace Icyus
{
    namespace View
    {
        class QtView final : public IView
        {
        public:
            QtView(QWidget *widgetContainer) :
                widgetManager{ widgetContainer }
            {}

            ~QtView() = default;
            QtView(QtView&&) = default;
            QtView& operator=(QtView&&) = default;

            QtView(QtView&) = delete;
            QtView& operator=(QtView&) = delete;

            void setFileToSend(const std::string &path) override
            {
                widgetManager.setFileToSendLabel(QString::fromStdString(path));
            }

            void setSenderProgressBounds(int min, int max) override
            {
                widgetManager.setSenderProgressBarBounds(min, max);
            }

            void setSenderProgressValue(int value) override
            {
                widgetManager.setSenderProgressBarValue(value);
            }

            void setSenderConnectedStatus(const std::string &status) override
            {
                widgetManager.setSenderConnectedStatus(QString::fromStdString(status));
            }


            void setReceiverListeningStatus(bool status) override
            {
                widgetManager.setReceiverListeningStatus(status);
            }

            void setReceivingFileName(const std::string &name) override
            {
                widgetManager.setReceivingFileName(QString::fromStdString(name));
            }

            void setReceiverProgressBounds(int min, int max) override
            {
                widgetManager.setReceiverProgressBarBounds(min, max);
            }

            void setReceiverProgressValue(int value) override
            {
                widgetManager.setReceiverProgressBarValue(value);
            }

        private:
            detail::QtWidgetManager widgetManager;
        };
    }
}
