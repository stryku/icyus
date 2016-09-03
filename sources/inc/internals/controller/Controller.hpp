#pragma once

#include <internals/utils/log.hpp>
#include <internals/input/IInputHandler.hpp>
#include <internals/input/IInputObserver.hpp>
#include <internals/model/IModelObserver.hpp>
#include <internals/view/IView.hpp>
#include <internals/system/ISystemInteractor.hpp>
#include <internals/model/Model.hpp>
#include <internals/communication/FileSender.hpp>
#include <internals/communication/FileReceiver.hpp>
#include <internals/utils/foreach.hpp>
#include <internals/utils/utils.hpp>

#include <vector>
#include <filesystem>

namespace Icyus
{
    namespace Controller
    {
        template <typename FileSender, typename FileReceiver>
        class Controller final : public Icyus::Input::IInputHandler,
                                 public Icyus::Model::IModelObserver
        {
        public:
            Controller(Icyus::Model::Model &model,
                       Icyus::Input::IInputObserver &inputObserver,
                       Icyus::System::ISystemInteractor &systemInteractor,
                       FileSender &sender,
                       FileReceiver &receiver) :
                model{ model },
                inputObserver{ inputObserver },
                systemInteractor{ systemInteractor },
                sender{ sender },
                receiver{ receiver }
            {}

            ~Controller() = default;

            void receiverStartListening() override
            {
                receiver.setProgressCallback([this](size_t progress)
                {
                    model.newReceiverProgress(progress);
                });

                model.newReceiverListeningStatus("listening");
                receiver.startListening();
            }
            void newReceiverListeningStatus(const std::string &status) override
            {
                LOG("New receiver listening status: " << status);
                myforeachptr(views, setReceiverListeningStatus, status);
            }
            void newModelReceiverAddress(const std::string &address) override
            {
                LOG("New model receiver address: " << address);
                myforeachptr(views, setReceiverAddress, address);
            }
            void newReceiverAddress(const std::string &address) override
            {
                inputObserver.newReceiverAddress(address);
            }

            void newReceiverProgress(size_t progress) override
            {
                myforeachptr(views, setReceiverProgressValue, progress);// todo update views progress when multithread gui update will be implemented
                LOG("receiver progress: " << progress << "%");
            }

            void chooseFile() override
            {
                auto path = systemInteractor.chooseFile();

                if (!path.empty())
                    inputObserver.newFileChoosed(path);
            }

            void send() override
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

                myforeachptr(views, setSenderProgressValue, 0);
                sender.sendAsync(path);
            }
            void connect() override
            {
                auto address = model.getReceiverAddress();
                auto connectedCallback = [this] {model.newSenderConnectionStatus("connected"); };
                model.newSenderConnectionStatus("connecting...");
                sender.connectAsync(address, connectedCallback);
            }


            void newSenderConnectionStatus(const std::string &status) override
            {
                LOG("New sender connection status: " << status);
                myforeachptr(views, setSenderConnectedStatus, status);
            }
            void newSenderProgress(size_t progress) override
            {
                myforeachptr(views, setSenderProgressValue, progress); // todo update views progress when multithread gui update will be implemented
                LOG("sender progress: " << progress << "%");
            }
            void newSenderTransferSpeed(uintmax_t progress) override
            {
                LOG("sender transfer speed: " << utils::formatSize(progress));
            }
            void senderFilePathChanged(const std::string &newPath) override
            {
                myforeachptr(views, setFileToSend, newPath);
            }
            void senderProgressValueChanged(int newValue) override
            {
                myforeachptr(views, setSenderProgressValue, newValue);
            }

            void receiverProgressValueChanged(int newValue) override
            {
                myforeachptr(views, setReceiverProgressValue, newValue);
            }
            void registerView(Icyus::View::IView *view)
            {
                views.push_back(view);
            }

        private:
            Icyus::Model::Model &model;
            Icyus::Input::IInputObserver &inputObserver;
            Icyus::System::ISystemInteractor &systemInteractor;
            std::vector<Icyus::View::IView*> views;
            FileSender &sender;
            FileReceiver &receiver;
        };
    }
}