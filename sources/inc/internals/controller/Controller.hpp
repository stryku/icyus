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
                       Icyus::Communication::FileReceiver &receiver);
            ~Controller() = default;

            void receiverStartListening() override;
            void newReceiverListeningStatus(const std::string &status) override;
            void newModelReceiverAddress(const std::string &address) override;
            void newReceiverAddress(const std::string &address) override;
            void newReceiverProgress(size_t progress) override;

            void chooseFile() override;

            void send() override;
            void connect() override;


            void newSenderConnectionStatus(const std::string &status) override;
            void newSenderProgress(size_t progress) override;
            void newSenderTransferSpeed(uintmax_t progress) override;
            void senderFilePathChanged(const std::string &newPath) override;
            void senderProgressValueChanged(int newValue) override;

            void receiverProgressValueChanged(int newValue) override;
            void registerView(Icyus::View::IView *view);

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