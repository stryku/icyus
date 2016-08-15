#pragma once

#include <internals/input/IInputHandler.hpp>
#include <internals/input/IInputObserver.hpp>
#include <internals/model/IModelObserver.hpp>
#include <internals/view/IView.hpp>
#include <internals/system/ISystemInteractor.hpp>
#include <internals/model/Model.hpp>
#include <internals/communication/FileSender.hpp>
#include <internals/communication/FileReceiver.hpp>
#include <internals/utils/foreach.hpp>

#include <vector>
#include <filesystem>

namespace Icyus
{
    namespace Controller
    {
        class Controller final : public Icyus::Input::IInputHandler, 
                                 public Icyus::Model::IModelObserver
        {
        public:
            Controller(Icyus::Model::Model &model,
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
            ~Controller() = default;

            void chooseFile() override
            {
                auto path = systemInteractor.chooseFile();

                if(!path.empty())
                    inputObserver.newFileChoosed(path);
            }

            void receiverStartListening() override
            {
                model.newReceiverListeningStatus("listening");
                receiver.startListening();
            }

            void newSenderConnectionStatus(const std::string &status) override
            {
                myforeachptr(views, setSenderConnectedStatus, status);
            }

            void newReceiverListeningStatus(const std::string &status) override
            {
                myforeachptr(views, setReceiverListeningStatus, status);
            }

            void newModelReceiverAddress(const std::string &address) override
            {
                myforeachptr(views, setReceiverAddress, address);
            }

            void send() override
            {
                auto path = model.getSenderFilePath();

                auto fileSize = std::experimental::filesystem::file_size(path);

                for (auto view : views)
                    view->sendingStarted(fileSize);

                sender.setUptadeProgressCallback([this](size_t progress)
                {
                    model.newSenderProgress(progress);
                });

                //sender.setGranularity(1024); //todo
                sender.sendAsync(path);
            }

            void newReceiverAddress(const std::string &address) override
            {
                inputObserver.newReceiverAddress(address);
            }

            void connect() override
            {
                auto address = model.getReceiverAddress();
                auto connectedCallback = [this] {model.newSenderConnectionStatus("connected"); };
                model.newSenderConnectionStatus("connecting...");
                sender.connectAsync(address, connectedCallback);
            }

            void newSenderProgress(size_t progress) override
            {
                myforeachptr(views, setSenderProgressValue, progress);
            }

            void newReceiverProgress(size_t progress) override
            {
                myforeachptr(views, setReceiverProgressValue, progress);
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
            Icyus::Communication::FileSender &sender;
            Icyus::Communication::FileReceiver &receiver;
        };
    }
}