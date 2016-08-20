#include <internals/view/QtView.hpp>

namespace Icyus
{
    namespace View
    {
        QtView::QtView(QWidget *widgetContainer) noexcept :
            widgetManager{ widgetContainer }
        {}

        void QtView::sendingStarted(size_t size)
        {
            //todo disable controls
        }

        void QtView::setReceiverAddress(const std::string &address)
        {
            widgetManager.setReceiverAddress(address);
        }

        void QtView::connectWithInputPropagator(Icyus::Input::InputPropagator &propagator)
        {
            widgetManager.connectInputWithCallbacks(propagator.getCallbacks());
        }

        void QtView::setFileToSend(const std::string &path)
        {
            widgetManager.setFileToSendLabel(QString::fromStdString(path));
        }

        void QtView::setSenderProgressBounds(int min, int max)
        {
            widgetManager.setSenderProgressBarBounds(min, max);
        }

        void QtView::setSenderProgressValue(int value)
        {
            widgetManager.setSenderProgressBarValue(value);
        }

        void QtView::setSenderConnectedStatus(const std::string &status)
        {
            widgetManager.setSenderConnectedStatus(QString::fromStdString(status));
        }


        void QtView::setReceiverListeningStatus(const std::string &status)
        {
            widgetManager.setReceiverListeningStatus(status);
        }

        void QtView::setReceivingFileName(const std::string &name)
        {
            widgetManager.setReceivingFileName(QString::fromStdString(name));
        }

        void QtView::setReceiverProgressBounds(int min, int max)
        {
            widgetManager.setReceiverProgressBarBounds(min, max);
        }

        void QtView::setReceiverProgressValue(int value)
        {
            widgetManager.setReceiverProgressBarValue(value);
        }
    }
}
