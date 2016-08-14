#include <program2internals/view/detail/QtWidgetManager.h>

using namespace P2::View::detail;

QtWidgetManager::QtWidgetManager(QWidget *parent, const QString &uiFilePath) :
    formWidget{ createWidget(parent, uiFilePath) }
{}

void QtWidgetManager::setLabelSum( const QString &newString )
{
    ui_labelSum->setText( newString );
}

void QtWidgetManager::updateLabel( const QString &str )
{
    ui_labelSum->setText( str );
}

void QtWidgetManager::connectWithInput( P2::Input::InputPropagator *input )
{
    formWidget->connect( ui_pushButtonMinus, 
                         &QPushButton::clicked, 
                         input->createDecrementSumCallback() );
}

QWidget* QtWidgetManager::loadUiFile( const QString &path, QWidget *parent ) const
{
    QUiLoader loader;
    QFile file{ path };

    file.open( QFile::ReadOnly );

    auto widget = loader.load( &file, parent );
    file.close();

    return widget;
}

QWidget* QtWidgetManager::createWidget( QWidget *parent, const QString &uiFilePath)
{
    auto widget = loadUiFile(uiFilePath);

    widget->setParent( parent );

    ui_labelSum = widget->findChild<QLabel*>( "labelSum" );
    ui_pushButtonMinus = widget->findChild<QPushButton*>( "pushButtonMinus" );

    return widget;
}