#pragma once

#include <internals/Internals.hpp>
#include <internals/view/QtView.hpp>

#include <QWidget>

namespace Icyus
{
    namespace InternalsCreators
    {
        Icyus::Internals createLocalQt(QWidget *qtViewWidgetParent)
        {
            auto model = new Icyus::Model::Model();
            auto controller = new Icyus::Controller::Controller(*model);
            //auto inputPropagator = new Icyus::Input::InputPropagator();
            auto view = new Icyus::View::QtView(qtViewWidgetParent);

            //view->connectWithInput(inputPropagator);
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
