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
#include <QThread>

#include <functional>

namespace Icyus
{
    namespace View
    {
        namespace detail
        {

            

            class QtWidgetManager final : public QObject
            {
                Q_OBJECT

            public Q_SLOTS:
                void setReceiverAddress(const QString &address);
                void setFileToSendLabel(const QString &path);
                void setSenderProgressBarBounds(int min, int max);
                void setSenderProgressBarValue(int value);
                void setSenderConnectedStatus(const QString &status);

                void setReceiverListeningStatus(const QString &status);
                void setReceivingFileName(const QString &name);
                void setReceiverProgressBarBounds(int min, int max);
                void setReceiverProgressBarValue(int value);

            public:
                explicit QtWidgetManager(QWidget *parent, const QString &uiFilePath = "uiforms/form.ui");

                QString getReceiverIp() const noexcept;

                /*void setReceiverAddress(const std::string &address);
                void setFileToSendLabel(const QString &path);
                void setSenderProgressBarBounds(int min, int max);
                void setSenderProgressBarValue(int value);
                void setSenderConnectedStatus(const QString &status);

                void setReceiverListeningStatus(const std::string &status);
                void setReceivingFileName(const QString &name);
                void setReceiverProgressBarBounds(int min, int max);
                void setReceiverProgressBarValue(int value);*/

                QWidget* getWidget();

                void connectInputWithCallbacks(Icyus::Input::InputCallbacks &callbacks);

            private:
                QWidget* loadUiFile(const QString &path, QWidget *parent = nullptr) const;
                QWidget* createWidget(QWidget *parent, const QString &uiFilePath) const;

                QtViewControls extractControls(QWidget *widget) const noexcept;
                QtViewControls::SenderTabControls extractSenderTabControls(QWidget *widget) const noexcept;
                QtViewControls::ReceiverTabControls extractReceiverTabControls(QWidget *widget) const noexcept;

                QWidget *formWidget;
                QtViewControls controls;
            };
        }
    }
}
