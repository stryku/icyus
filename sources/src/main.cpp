#include <internals/view/QtView.hpp>
#include <InternalsCreators.hpp>

#include "mainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    auto internals = Icyus::InternalsCreators::createLocalQt(w.getWidget());

    w.show();

    return a.exec();
}
