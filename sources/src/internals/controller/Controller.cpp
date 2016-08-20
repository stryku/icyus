#include <internals/controller/Controller.hpp>
#include <internals/utils/utils.hpp>

namespace Icyus
{
    namespace Controller
    {

        Controller::Controller(Icyus::Model::Model &model,
                               Icyus::Input::IInputObserver &inputObserver,
                               Icyus::System::ISystemInteractor &systemInteractor,
                               Icyus::Communication::FileSender &sender,
                               Icyus::Communication::FileReceiver &receiver) :
            model{ model },
            inputObserver{ inputObserver },
            systemInteractor{ systemInteractor },
            sender{ sender },
            receiver{ receiver }
        {}

        void Controller::chooseFile()
        {
            auto path = systemInteractor.chooseFile();

            if (!path.empty())
                inputObserver.newFileChoosed(path);
        }

        void Controller::receiverStartListening()
        {
            model.newReceiverListeningStatus("listening");
            receiver.startListening();
        }

        void Controller::newSenderConnectionStatus(const std::string &status)
        {
            LOG("New sender connection status: " << status);
            myforeachptr(views, setSenderConnectedStatus, status);
        }

        void Controller::newReceiverListeningStatus(const std::string &status)
        {
            LOG("New receiver listening status: " << status);
            myforeachptr(views, setReceiverListeningStatus, status);
        }

        void Controller::newModelReceiverAddress(const std::string &address)
        {
            LOG("New model receiver address: " << address);
            myforeachptr(views, setReceiverAddress, address);
        }

        void Controller::send()
        {
            auto path = model.getSenderFilePath();

            auto fileSize = std::experimental::filesystem::file_size(path);

            LOG("Sending started. \nFile: " << path << " \nsize: " << fileSize);
            for (auto view : views)
                view->sendingStarted(fileSize);

            sender.setUptadeProgressCallback([this](size_t progress)
            {
                model.newSenderProgress(progress);
            });

            sender.setUptadeTransferSpeedCallback([this](uintmax_t speed)
            {
                model.newSenderTransferSpeed(speed);
            });

            myforeachptr(views, setSenderProgressValue, 35);
            sender.sendAsync(path);
            myforeachptr(views, setSenderProgressValue, 100);
        }

        void Controller::newReceiverAddress(const std::string &address)
        {
            inputObserver.newReceiverAddress(address);
        }

        void Controller::connect()
        {
            auto address = model.getReceiverAddress();
            auto connectedCallback = [this] {model.newSenderConnectionStatus("connected"); };
            model.newSenderConnectionStatus("connecting...");
            sender.connectAsync(address, connectedCallback);
        }

        void Controller::newSenderProgress(size_t progress)
        {
            //myforeachptr(views, setSenderProgressValue, progress); // todo update views progress when multithread gui update will be implemented
            LOG("sender progress: " << progress << "%");
        }

        void Controller::newSenderTransferSpeed(uintmax_t progress)
        {
            LOG("sender transfer speed: " << utils::formatSize(progress));
        }

        void Controller::newReceiverProgress(size_t progress)
        {
            //myforeachptr(views, setReceiverProgressValue, progress);// todo update views progress when multithread gui update will be implemented
            LOG("receiver progress: " << progress << "%");
        }

        void Controller::senderFilePathChanged(const std::string &newPath)
        {
            myforeachptr(views, setFileToSend, newPath);
        }

        void Controller::senderProgressValueChanged(int newValue)
        {
            myforeachptr(views, setSenderProgressValue, newValue);
        }

        void Controller::receiverProgressValueChanged(int newValue)
        {
            myforeachptr(views, setReceiverProgressValue, newValue);
        }

        void Controller::registerView(Icyus::View::IView *view)
        {
            views.push_back(view);
        }
    }
}