#pragma once

class QLabel;
class QPushButton;
class QLineEdit;
class QProgressBar;

namespace Icyus
{
    namespace View
    {
        namespace detail
        {
            struct QtViewControls
            {
                struct SenderTabControls
                {
                    QLineEdit *lineEditReceiverIp;
                    QLabel *labelFileToSend;
                    QLabel *labelConnectionStatus;
                    QProgressBar *progressBar;
                } senderTab;

                struct ReceiverTabControls
                {
                    QLabel *labelListeningStatus;
                    QLabel *labelIp;
                    QLabel *labelReceivingFile;
                    QProgressBar *progressBar;
                } receiverTab;
            };
        }
    }
}
