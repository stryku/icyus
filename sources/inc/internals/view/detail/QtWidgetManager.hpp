#pragma once

#include <internals/view/detail/QtViewControls.hpp>

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QUiLoader>
#include <QFile>
#include <QProgressBar>

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
                explicit QtWidgetManager(QWidget *parent, const QString &uiFilePath = "uiforms/form.ui")
                {

                }

                QString getReceiverIp() const noexcept
                {
                    return controls.receiverTab.labelIp->text();
                }

                void setFileToSendLabel(const std::string &path)
                {
                    controls.senderTab.labelFileToSend->setText(QString("%1: %2").arg("File to send", 
                                                                                      QString::fromStdString(path)));
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

                void setSenderConnectedStatus(const std::string &status)
                {
                    controls.senderTab.labelConnectionStatus->setText(QString("%1: %2").arg("Connection status",
                                                                                            QString::fromStdString(status)));
                }


                void setReceiverListeningStatus(bool status)
                {
                    controls.receiverTab.labelListeningStatus->setText(QString("%1: %2").arg("Listening status",
                                                                                             status ? "connected" : "not connected"));
                }

                void setReceivingFileName(const std::string &name)
                {
                    controls.receiverTab.labelReceivingFile->setText(QString("%1: %2").arg("Receiving file",
                                                                                           QString::fromStdString(name)));
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

            private:
                QWidget* loadUiFile( const QString &path, QWidget *parent = nullptr ) const;
                QWidget* createWidget( QWidget *parent, const QString &uiFilePath );

                QWidget *formWidget;
                QtViewControls controls;
            };
        }
    }
}
