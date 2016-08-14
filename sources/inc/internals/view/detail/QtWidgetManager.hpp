#pragma once

//#include <program2internals/input/InputHandler.h>
//#include <program2internals/input/Input.h>

#include <view/detail/QtViewControls.hpp>


#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QUiLoader>
#include <QFile>

#include <functional>

namespace Icyus
{
    namespace View
    {
        namespace detail
        {
            class QtWidgetManager final
            {
            public:
                explicit QtWidgetManager( QWidget *parent, const QString &uiFilePath = "uiforms/Program2Form.ui" );

                QString getReceiverIp() const noexcept
                {
                    return controls.
                }

                void connectWithInput( Input::InputPropagator *input );

                QWidget* getWidget()
                {
                    return formWidget;
                }

            private:
                QWidget* loadUiFile( const QString &path, QWidget *parent = nullptr ) const;
                QWidget* createWidget( QWidget *parent, const QString &uiFilePath );

                QtViewControls controls;
            };
        }
    }
}
