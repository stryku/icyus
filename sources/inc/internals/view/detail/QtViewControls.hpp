#pragma once

class QLabel;
class QPushButton;
class QEditText;
class QProgressBar;

namespace Icyus
{
    namespace View
    {
        namespace detail
        {
            struct QtViewControls
            {
                struct
                {
                    QEditText *textEditReceiverIp;
                    QLabel *labelFileToSend;
                    QLabel *labelConnectionStatus;
                    QProgressBar *progressBar;
                } sender;

                struct
                {
                    QLabel *labelListeningStatus;
                    QLabel *labelIp;
                    QLabel *labelReceivingFile;
                    QProgressBar *progressBar;
                } receiver;
            };
        }
    }
}
