#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "physicalwindow.hpp"

class Application : public QObject {
    Q_OBJECT
public:
    Application();
    ~Application();

    void init(int argc, char** argv);

public slots:
    void update();
    void spawnStuff();

private:
    QSharedPointer<b2World> mWorld;

    QList<QSharedPointer<PhysicalWindow> > mPhysicalWindows;
};

#endif
