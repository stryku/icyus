#pragma once

#include <internals/view/IView.hpp>
#include <internals/controller/Controller.hpp>
#include <internals/model/Model.hpp>
#include <internals/input/IInputHandler.hpp>

#include <vector>

namespace Icyus
{
    class Internals
    {
    public:
        Internals(Icyus::Controller::Controller *controller) :
            controller{ controller }
        {}

        void registerView(Icyus::View::IView *view)
        {
            controller->registerView(view);
        }

        /*void addInputPropagator(Icyus::Input::InputPropagator *input)
        {
            inputs.push_back(input);
            input->setInputHandler(controller);
        }*/

    private:
        //std::vector <Icyus::Input::InputPropagator*> inputs;
        Icyus::Controller::Controller *controller;
    };
}
