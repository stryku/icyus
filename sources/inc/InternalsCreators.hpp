#pragma once

#include <internals/Internals.hpp>
#include <internals/view/QtView.hpp>
#include <internals/input/InputPropagator.hpp>
#include <internals/system/QtSystemInteractor.hpp>
#include <internals/communication/FileSender.hpp>

#include <QWidget>

namespace Icyus
{
    namespace InternalsCreators
    {
        Icyus::Internals createLocalQt(QWidget *qtViewWidgetParent)
        {
            auto ctx = new zmq::context_t{ 1 };
            auto sender = new Icyus::Communication::FileSender{ *ctx };
            auto systemInteractor = new Icyus::System::QtSystemInteractor();
            auto model = new Icyus::Model::Model();
            auto controller = new Icyus::Controller::Controller(*model, *model, *systemInteractor, *sender);
            auto inputPropagator = new Icyus::Input::InputPropagator(*controller);
            auto view = new Icyus::View::QtView(qtViewWidgetParent);

            view->connectWithInputPropagator(*inputPropagator);
            model->registerObserver(controller);
            controller->registerView(view);

            auto internals = Icyus::Internals(controller);

            //internals.setController(controller);
            //internals.addInputPropagator(inputPropagator);
            internals.registerView(view);

            return internals;
        }
    }
}
