#ifndef PHYSICALWINDOW_HPP
#define PHYSICALWINDOW_HPP

#include <Box2D/Box2D.h>

#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtCore/QSharedPointer>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPainter>

#undef signals // Collides with GTK symbols
#include <libwnck/libwnck.h>

class PhysicalWindow : public QObject {
    Q_OBJECT
public:
    // Constructor for the dynamic actors
    PhysicalWindow(int x, int y, int width, int height,
                   QSharedPointer<b2World> physics_world);

    // Mapping to a certain window (static)
    PhysicalWindow(WnckWindow* window, QSharedPointer<b2World> physics_world);

    ~PhysicalWindow();

    void update();

private:
    QString mType;
    QMainWindow mWindow;
    QLabel mLabel;
    QPixmap mPixmap;
    b2Body* mPhysicsBody;
};

#endif
