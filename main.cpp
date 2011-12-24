#include <QtGui/QApplication>
#include <QtCore/QTimer>

#include "application.hpp"

int main (int argc, char **argv) {
    Application application(argc, argv);
    application.init();

    QTimer tick_timer;
    tick_timer.start(20);
    QObject::connect(&tick_timer,  SIGNAL(timeout()),
                     &application, SLOT(update()));

    QTimer spawn_timer;
    spawn_timer.start(100);
    QObject::connect(&spawn_timer, SIGNAL(timeout()),
                     &application, SLOT(spawnStuff()));


    return application.exec();
}
