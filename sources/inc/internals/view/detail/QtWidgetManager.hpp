#pragma once

#include <internals/view/detail/QtViewControls.hpp>
#include <internals/input/InputCallbacks.hpp>

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QUiLoader>
#include <QFile>
#include <QProgressBar>
#include <QLineEdit>

#include <functional>

namespace Icyus
{
    namespace View
    {
        namespace detail
        {
            class QtWidgetManager final
            {
            public:
                explicit QtWidgetManager(QWidget *parent, const QString &uiFilePath = "uiforms/form.ui") :
                    formWidget{ createWidget(parent, uiFilePath) },
                    controls { extractControls(formWidget) }
                {}

                QString getReceiverIp() const noexcept
                {
                    return controls.receiverTab.labelIp->text();
                }

                void setReceiverAddress(const std::string &address)
                {
                    auto str = QString::fromStdString(address);

                    if (controls.senderTab.lineEditReceiverIp->text() != str)
                        controls.senderTab.lineEditReceiverIp->setText(str);
                }

                void setFileToSendLabel(const QString &path)
                {
                    controls.senderTab.labelFileToSend->setText(QString("%1: %2").arg("File to send", 
                                                                                      path));
                }

                void setSenderProgressBarBounds(int min, int max)
                {
                    controls.senderTab.progressBar->setMinimum(min);
                    controls.senderTab.progressBar->setMaximum(max);
                }


                void setSenderProgressBarValue(int value)
                {
                    controls.senderTab.progressBar->setValue(value);
                }

                void setSenderConnectedStatus(const QString &status)
                {
                    controls.senderTab.labelConnectionStatus->setText(QString("%1: %2").arg("Connection status",
                                                                                            status));
                }


                void setReceiverListeningStatus(bool status)
                {
                    controls.receiverTab.labelListeningStatus->setText(QString("%1: %2").arg("Listening status",
                                                                                             status ? "connected" : "not connected"));
                }

                void setReceivingFileName(const QString &name)
                {
                    controls.receiverTab.labelReceivingFile->setText(QString("%1: %2").arg("Receiving file",
                                                                                           name));
                }

                void setReceiverProgressBarBounds(int min, int max)
                {
                    controls.receiverTab.progressBar->setMinimum(min);
                    controls.receiverTab.progressBar->setMaximum(max);
                }

                void setReceiverProgressBarValue(int value)
                {
                    controls.receiverTab.progressBar->setValue(value);
                }

                //void connectWithInput( Input::InputPropagator *input );

                QWidget* getWidget()
                {
                    return formWidget;
                }

                void connectInputWithCallbacks(Icyus::Input::InputCallbacks &callbacks)
                {
                    formWidget->connect(controls.senderTab.buttonChooseFile,
                                        &QPushButton::clicked,
                                        callbacks.chooseFile);

                    formWidget->connect(controls.senderTab.buttonSend,
                                        &QPushButton::clicked,
                                        callbacks.send);

                    formWidget->connect(controls.senderTab.buttonConnect,
                                        &QPushButton::clicked,
                                        callbacks.send);

                    formWidget->connect(controls.senderTab.lineEditReceiverIp,
                                        &QLineEdit::editingFinished,
                                        [this, callbacks] 
                                        { 
                                            callbacks.newReceiverAddress(controls.senderTab.lineEditReceiverIp->text().toStdString()); 
                                        });
                }

            private:
                QWidget* loadUiFile(const QString &path, QWidget *parent = nullptr) const //todo noexcept?
                {
                    QUiLoader loader;
                    QFile file{ path };

                    file.open(QFile::ReadOnly);

                    auto widget = loader.load(&file, parent);
                    file.close();

                    return widget;
                }

                QWidget* createWidget(QWidget *parent, const QString &uiFilePath) const //todo noexcept?
                {
                    auto widget = loadUiFile(uiFilePath);

                    widget->setParent(parent);

                    return widget;
                }

                QtViewControls extractControls(QWidget *widget) const noexcept
                {
                    return {
                        extractSenderTabControls(widget),
                        extractReceiverTabControls(widget)
                    };
                }

                QtViewControls::SenderTabControls extractSenderTabControls(QWidget *widget) const noexcept
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

                QtViewControls::ReceiverTabControls extractReceiverTabControls(QWidget *widget) const noexcept
                {
                    QtViewControls::ReceiverTabControls controls;

                    controls.labelIp = widget->findChild<QLabel*>("labelReceiverIp");
                    controls.labelListeningStatus = widget->findChild<QLabel*>("labelListeningStatus");
                    controls.progressBar = widget->findChild<QProgressBar*>("progressBarReceiver");
                    controls.labelReceivingFile = widget->findChild<QLabel*>("labelReceivinFile");

                    return controls;
                }

                QWidget *formWidget;
                QtViewControls controls;
            };
        }
    }
}
