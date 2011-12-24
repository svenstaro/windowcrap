#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <QtGui/QApplication>

#include "physicalwindow.hpp"

class Application : public QApplication {
    Q_OBJECT
public:
    Application(int argc, char** argv);
    ~Application();

    void init();

public slots:
    void update();
    void spawnStuff();

private:
    QSharedPointer<b2World> mWorld;

    QList<QSharedPointer<PhysicalWindow> > mPhysicalWindows;
};

#endif
