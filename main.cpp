#include <QtGui/QApplication>
#include <QtCore/QTimer>

#include "application.hpp"

int main (int argc, char **argv) {
    QApplication qapplication(argc, argv);

    Application application;
    application.init(argc, argv);

    QTimer timer;
    timer.start(20);

    QObject::connect(&timer,       SIGNAL(timeout()),
                     &application, SLOT(update()));


    return qapplication.exec();
}
