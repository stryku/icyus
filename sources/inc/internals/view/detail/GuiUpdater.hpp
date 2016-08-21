#pragma once

#include <QString>
#include <QObject>

namespace Icyus
{
    namespace View
    {
        namespace detail
        {
            class GuiUpdater : public QObject
            {
                Q_OBJECT
            public:
                void setFileToSend(const std::string &path)
                {
                    emit signalSetFileToSend(QString::fromStdString(path));
                }
                void setSenderProgressValue(int value)
                {
                    emit signalSetSenderProgressValue(value);
                }
                void setSenderConnectedStatus(const std::string &path)
                {
                    emit signalSetSenderConnectedStatus(QString::fromStdString(path));
                }

                void setReceiverAddress(const std::string &path)
                {
                    emit signalSetReceiverAddress(QString::fromStdString(path));
                }
                void setReceiverListeningStatus(const std::string &path)
                {
                    emit signalSetReceiverListeningStatus(QString::fromStdString(path));
                }
                void setReceivingFileName(const std::string &path)
                {
                    emit signalSetReceivingFileName(QString::fromStdString(path));
                }
                void setReceiverProgressValue(int value)
                {
                    emit signalSetReceiverProgressValue(value);
                }

            Q_SIGNALS:
                void signalSetFileToSend(const QString &);
                void signalSetSenderProgressBounds(int min, int max);
                void signalSetSenderProgressValue(int value);
                void signalSetSenderConnectedStatus(const QString &);

                void signalSetReceiverAddress(const QString &);
                void signalSetReceiverListeningStatus(const QString &);
                void signalSetReceivingFileName(const QString &);
                void signalSetReceiverProgressValue(int value);
            };
        }
    }
}