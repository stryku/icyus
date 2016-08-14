#pragma once

#include <internals/input/IInputHandler.hpp>
#include <internals/input/IInputObserver.hpp>
#include <internals/model/IModelObserver.hpp>
#include <internals/view/IView.hpp>
#include <internals/system/ISystemInteractor.hpp>

#include <vector>

namespace Icyus
{
    namespace Controller
    {
        class Controller final : public Icyus::Input::IInputHandler, 
                                 public Icyus::Model::IModelObserver
        {
        public:
            Controller(Icyus::Input::IInputObserver &inputObserver,
                       Icyus::System::ISystemInteractor &systemInteractor) :
                inputObserver{ inputObserver },
                systemInteractor{ systemInteractor }
            {}
            ~Controller() = default;

            void chooseFile() override
            {
                auto path = systemInteractor.chooseFile();

                if(!path.empty())
                    inputObserver.newFileChoosed(path);
            }

            void senderFilePathChanged(const std::string &newPath) override
            {
                for (auto view : views)
                    view->setFileToSend(newPath);
            }

            void senderProgressValueChanged(int newValue) override
            {
                for (auto view : views)
                    view->setSenderProgressValue(newValue);
            }

            void receiverProgressValueChanged(int newValue) override
            {
                for (auto view : views)
                    view->setReceiverProgressValue(newValue);
            }

            void registerView(Icyus::View::IView *view)
            {
                views.push_back(view);
            }

        private:
            Icyus::Input::IInputObserver &inputObserver;
            Icyus::System::ISystemInteractor &systemInteractor;
            std::vector<Icyus::View::IView*> views;
        };
    }
}