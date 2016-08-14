#pragma once

#include <internals/input/IInputHandler.hpp>
#include <internals/model/IModelObserver.hpp>
#include <internals/view/IView.hpp>

#include <vector>

namespace Icyus
{
    namespace Controller
    {
        class Controller final : public Icyus::Input::IInputHandler, 
                                 public Icyus::Model::IModelObserver
        {
        public:
            Controller(Icyus::Input::IInputHandler &inputObserver) :
                inputObserver{ inputObserver }
            {}
            ~Controller() = default;

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
            Icyus::Input::IInputHandler& inputObserver;
            std::vector<Icyus::View::IView*> views;
        };
    }
}