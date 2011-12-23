#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <Box2D/Box2D.h>

#include <QtGui/QMainWindow>
#include <QtGui/QLabel>
#include <QtCore/QObject>
#include <QtCore/QSharedPointer>

class Application : public QObject {
    Q_OBJECT
public:
    Application();
    ~Application();

    void init(int argc, char** argv);

public slots:
    void tick();

private:
    QSharedPointer<b2World> mWorld;
    QMainWindow mBallWindow;
    QLabel mBallLabel;
    QPixmap mBallPixmap;
    b2Body* mBallBody;
};

#endif
