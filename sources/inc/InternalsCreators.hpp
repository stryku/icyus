#pragma once

#include <internals/Internals.hpp>
#include <internals/view/QtView.hpp>
#include <internals/input/InputPropagator.hpp>
#include <internals/system/QtSystemInteractor.hpp>
#include <internals/communication/FileSender.hpp>
#include <internals/communication/FileReceiver.hpp>
#include <internals/communication/details/ZmqSocket.hpp>
#include <internals/system/FileWrapper.hpp>

#include <QWidget>

namespace Icyus
{
    namespace InternalsCreators
    {
        auto createLocalQt(QWidget *qtViewWidgetParent)
        {
            using Socket = Communication::detail::ZmqSocket;
            using File = Icyus::System::FileWrapper;
            using Sender = Icyus::Communication::FileSender<Socket, File>;
            using ControllerType = Icyus::Controller::Controller<Sender,
                                                                 Icyus::Communication::FileReceiver<Socket>,
                                                                 File>;

            auto ctx = new zmq::context_t{ 1 };
            auto sender = new Sender{ Socket{ *ctx, zmq::socket_type::req } };
            auto receiver = new Icyus::Communication::FileReceiver<Socket>{ Socket{*ctx, zmq::socket_type::rep} };
            auto systemInteractor = new Icyus::System::QtSystemInteractor();
            auto model = new Icyus::Model::Model();
            auto controller = new ControllerType{ *model,
                                              *model, 
                                              *systemInteractor, 
                                              *sender, 
                                              *receiver };
            auto inputPropagator = new Icyus::Input::InputPropagator(*controller);
            auto view = new Icyus::View::QtView(qtViewWidgetParent);

            view->connectWithInputPropagator(*inputPropagator);
            model->registerObserver(controller);
            controller->registerView(view);

            Icyus::Internals<ControllerType> internals( controller );

            //internals.setController(controller);
            //internals.addInputPropagator(inputPropagator);
            internals.registerView(view);

            return internals;
        }
    }
}
