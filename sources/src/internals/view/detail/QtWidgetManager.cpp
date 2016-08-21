#include <internals/view/detail/QtWidgetManager.hpp>

namespace Icyus
{
    namespace View
    {
        namespace detail
        {
            QtWidgetManager::QtWidgetManager(QWidget *parent, const QString &uiFilePath) :
                formWidget{ createWidget(parent, uiFilePath) },
                controls{ extractControls(formWidget) }
            {

            }

            QString QtWidgetManager::getReceiverIp() const noexcept
            {
                return controls.receiverTab.labelIp->text();
            }

            void QtWidgetManager::setReceiverAddress(const QString &address)
            {
                if (controls.senderTab.lineEditReceiverIp->text() != address)
                    controls.senderTab.lineEditReceiverIp->setText(address);
            }

            void QtWidgetManager::setFileToSendLabel(const QString &path)
            {
                controls.senderTab.labelFileToSend->setText(QString("%1: %2").arg("File to send",
                                                            path));
            }

            void QtWidgetManager::setSenderProgressBarBounds(int min, int max)
            {
                controls.senderTab.progressBar->setMinimum(min);
                controls.senderTab.progressBar->setMaximum(max);
            }


            void QtWidgetManager::setSenderProgressBarValue(int value)
            {
                controls.senderTab.progressBar->setValue(value);
            }

            void QtWidgetManager::setSenderConnectedStatus(const QString &status)
            {
                controls.senderTab.labelConnectionStatus->setText(QString("%1: %2").arg("Connection status",
                                                                  status));
            }


            void QtWidgetManager::setReceiverListeningStatus(const QString &status)
            {
                controls.receiverTab.labelListeningStatus->setText(QString("%1: %2").arg("Listening status",
                                                                   status));
            }

            void QtWidgetManager::setReceivingFileName(const QString &name)
            {
                controls.receiverTab.labelReceivingFile->setText(QString("%1: %2").arg("Receiving file",
                                                                 name));
            }

            void QtWidgetManager::setReceiverProgressBarBounds(int min, int max)
            {
                controls.receiverTab.progressBar->setMinimum(min);
                controls.receiverTab.progressBar->setMaximum(max);
            }

            void QtWidgetManager::setReceiverProgressBarValue(int value)
            {
                controls.receiverTab.progressBar->setValue(value);
            }

            QWidget* QtWidgetManager::getWidget()
            {
                return formWidget;
            }

            void QtWidgetManager::connectInputWithCallbacks(Icyus::Input::InputCallbacks &callbacks)
            {
                formWidget->connect(controls.senderTab.buttonChooseFile,
                                    &QPushButton::clicked,
                                    callbacks.chooseFile);

                formWidget->connect(controls.senderTab.buttonSend,
                                    &QPushButton::clicked,
                                    callbacks.send);

                formWidget->connect(controls.senderTab.buttonConnect,
                                    &QPushButton::clicked,
                                    callbacks.connect);

                formWidget->connect(controls.senderTab.lineEditReceiverIp,
                                    &QLineEdit::editingFinished,
                                    [this, callbacks]
                {
                    callbacks.newReceiverAddress(controls.senderTab.lineEditReceiverIp->text().toStdString());
                });

                formWidget->connect(controls.receiverTab.buttonStartReceiving,
                                    &QPushButton::clicked,
                                    callbacks.receiver.startListening);
            }

            QWidget* QtWidgetManager::loadUiFile(const QString &path, QWidget *parent) const //todo noexcept?
            {
                QUiLoader loader;
                QFile file{ path };

                file.open(QFile::ReadOnly);

                auto widget = loader.load(&file, parent);
                file.close();

                return widget;
            }

            QWidget* QtWidgetManager::createWidget(QWidget *parent, const QString &uiFilePath) const //todo noexcept?
            {
                auto widget = loadUiFile(uiFilePath);

                widget->setParent(parent);

                return widget;
            }

            QtViewControls QtWidgetManager::extractControls(QWidget *widget) const noexcept
            {
                return{
                    extractSenderTabControls(widget),
                    extractReceiverTabControls(widget)
                };
            }

            QtViewControls::SenderTabControls QtWidgetManager::extractSenderTabControls(QWidget *widget) const noexcept
            {
                QtViewControls::SenderTabControls controls;

                controls.labelConnectionStatus = widget->findChild<QLabel*>("labelConnectionStatus");
                controls.labelFileToSend = widget->findChild<QLabel*>("labelFileToSend");
                controls.progressBar = widget->findChild<QProgressBar*>("progressBarSender");
                controls.lineEditReceiverIp = widget->findChild<QLineEdit*>("lineEditReceiverIp");
                controls.buttonChooseFile = widget->findChild<QPushButton*>("pushButtonChooseFileToSend");
                controls.buttonSend = widget->findChild<QPushButton*>("pushButtonSend");
                controls.buttonConnect = widget->findChild<QPushButton*>("pushButtonConnect");

                return controls;
            }

            QtViewControls::ReceiverTabControls QtWidgetManager::extractReceiverTabControls(QWidget *widget) const noexcept
            {
                QtViewControls::ReceiverTabControls controls;

                controls.labelIp = widget->findChild<QLabel*>("labelReceiverIp");
                controls.labelListeningStatus = widget->findChild<QLabel*>("labelListeningStatus");
                controls.progressBar = widget->findChild<QProgressBar*>("progressBarReceiver");
                controls.labelReceivingFile = widget->findChild<QLabel*>("labelReceivinFile");
                controls.buttonStartReceiving = widget->findChild<QPushButton*>("pushButtonStartListening");

                return controls;
            }
        }
    }
}