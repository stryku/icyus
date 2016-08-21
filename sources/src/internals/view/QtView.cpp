#include <internals/view/QtView.hpp>

namespace Icyus
{
    namespace View
    {
        QtView::QtView(QWidget *widgetContainer) noexcept :
            widgetManager{ widgetContainer }
        {
            QObject::connect(&updater, SIGNAL(signalSetFileToSend(const QString &)), &widgetManager, SLOT(setFileToSendLabel(const QString &)));
            QObject::connect(&updater, SIGNAL(signalSetReceiverAddress(const QString &)), &widgetManager, SLOT(setReceiverAddress(const QString &)));
            QObject::connect(&updater, SIGNAL(signalSetSenderProgressValue(int)), &widgetManager, SLOT(setSenderProgressBarValue(int)));
            QObject::connect(&updater, SIGNAL(signalSetSenderConnectedStatus(const QString &)), &widgetManager, SLOT(setSenderConnectedStatus(const QString &)));
            QObject::connect(&updater, SIGNAL(signalSetReceiverListeningStatus(const QString &)), &widgetManager, SLOT(setReceiverListeningStatus(const QString &)));
            QObject::connect(&updater, SIGNAL(signalSetReceivingFileName(const QString &)), &widgetManager, SLOT(setReceivingFileName(const QString &)));
            QObject::connect(&updater, SIGNAL(signalSetReceiverProgressValue(int)), &widgetManager, SLOT(setReceiverProgressBarValue(int)));
        }

        void QtView::sendingStarted(size_t size)
        {
            //todo disable controls
        }

        void QtView::setReceiverAddress(const std::string &address)
        {
            updater.setReceiverAddress(address);
            //widgetManager.setReceiverAddress(address);
        }

        void QtView::connectWithInputPropagator(Icyus::Input::InputPropagator &propagator)
        {
            widgetManager.connectInputWithCallbacks(propagator.getCallbacks());
        }

        void QtView::setFileToSend(const std::string &path)
        {
            updater.setFileToSend(path);
            //widgetManager.setFileToSendLabel(QString::fromStdString(path));
        }

        void QtView::setSenderProgressValue(int value)
        {
            updater.setSenderProgressValue(value);
            //widgetManager.setSenderProgressBarValue(value);
        }

        void QtView::setSenderConnectedStatus(const std::string &status)
        {
            updater.setSenderConnectedStatus(status);
            //widgetManager.setSenderConnectedStatus(QString::fromStdString(status));
        }


        void QtView::setReceiverListeningStatus(const std::string &status)
        {
            updater.setReceiverListeningStatus(status);
            //widgetManager.setReceiverListeningStatus(status);
        }

        void QtView::setReceivingFileName(const std::string &name)
        {
            updater.setReceivingFileName(name);
            //widgetManager.setReceivingFileName(QString::fromStdString(name));
        }

        void QtView::setReceiverProgressValue(int value)
        {
            updater.setReceiverProgressValue(value);
            //widgetManager.setReceiverProgressBarValue(value);
        }
    }
}
