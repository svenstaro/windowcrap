#include <libwnck/libwnck.h>

#include <QtGui/QPainter>
#include <QtGui/QMovie>
#include <QtCore/QDebug>

#include "application.hpp"

Application::Application() {}

Application::~Application() {}

void Application::init(int argc, char** argv) {
    b2Vec2 gravity(0.0f, 10.0f);
    mWorld = QSharedPointer<b2World>(new b2World(gravity));
    mWorld->SetAllowSleeping(false);

    // DEBUG
    /*
    QMainWindow window_debug;
    QPixmap pixmap_debug(100, 100);
    pixmap_debug.fill(QColor(0, 0, 0, 0));
    QPainter painter_debug(&pixmap_debug);
    QPainterPath path_debug;
    painter_debug.setRenderHint(QPainter::Antialiasing, true);
    painter_debug.setBrush(QBrush(Qt::green));
    path_debug.addRect(0, 0, 100, 100);
    painter_debug.drawPath(path_debug);
    QLabel label_debug(&window_debug);
    label_debug.setPixmap(pixmap_debug);

    label_debug.resize(100, 100);
    window_debug.setAttribute(Qt::WA_TranslucentBackground);
    window_debug.setWindowFlags(Qt::FramelessWindowHint);
    window_debug.setWindowFlags(Qt::X11BypassWindowManagerHint);

    window_debug.show();*/

    // BALL
    QPixmap pixmap(100, 100);
    mBallPixmap = pixmap;
    mBallPixmap.fill(QColor(0, 0, 0, 0));
    QPainter painter(&mBallPixmap);
    QPainterPath path;
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(Qt::green));
    path.addEllipse(0, 0, 100, 100);
    painter.drawPath(path);
    mBallLabel.setParent(&mBallWindow);
    mBallLabel.setPixmap(mBallPixmap);

    mBallLabel.resize(mBallPixmap.size().width(), mBallPixmap.size().height());
    mBallWindow.resize(mBallPixmap.size().width(), mBallPixmap.size().height());
    mBallWindow.setAttribute(Qt::WA_TranslucentBackground);
    mBallWindow.setWindowFlags(Qt::FramelessWindowHint);
    mBallWindow.setWindowFlags(Qt::X11BypassWindowManagerHint);

    mBallWindow.show();

    // BALL BODY
    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    body_def.position.Set(100.0f, 100.0f);
    mBallBody = mWorld->CreateBody(&body_def);
    b2CircleShape dynamic_circle;
    //dynamic_circle.m_p.Set(2.0f, 3.0f);
    dynamic_circle.m_radius = 10.0f;
    b2FixtureDef fixture_def;
    fixture_def.shape = &dynamic_circle;
    fixture_def.density = 1.0f;
    fixture_def.friction = 0.3f;
    mBallBody->CreateFixture(&fixture_def);

    /*
    // WINDOW STUFF
    WnckScreen *screen;
    WnckWindow *active_window;
    WnckWorkspace *active_workspace;
    GList *window_l;

    gdk_init (&argc, &argv);

    screen = wnck_screen_get_default ();

    wnck_screen_force_update (screen);

    active_window = wnck_screen_get_active_window (screen);
    active_workspace = wnck_screen_get_active_workspace (screen);

    for(window_l = wnck_screen_get_windows (screen); window_l != NULL; window_l = window_l->next) {
        WnckWindow *window = WNCK_WINDOW (window_l->data);
        int x;
        int y;
        int width;
        int height;
        wnck_window_get_geometry(window, &x, &y, &width, &height);
        if(wnck_window_is_on_workspace(window, active_workspace) &&
                wnck_window_get_window_type(window) == WNCK_WINDOW_NORMAL) {
            b2BodyDef window_body_def;
            window_body_def.position.Set((float)(x+(width/2)), (float)(y+(height/2)));
            b2Body* window_body = mWorld->CreateBody(&window_body_def);
            b2PolygonShape window_box;
            window_box.SetAsBox((float)(width/2), (float)(height/2));
            window_body->CreateFixture(&window_box, 0.0f);
            
            g_print ("%s%s - %ux%u - %ix%i\n", wnck_window_get_name (window),
                    window == active_window ? " (active)" : "",
                    width, height, x, y);
        }
    }*/

}

void Application::tick() {
        // SETUP
        float32 timeStep = 1.0/60.f;
        int32 velocityIterations = 6;
        int32 positionIterations = 2;

        mWorld->Step(timeStep, velocityIterations, positionIterations);
        mBallWindow.move((int)mBallBody->GetPosition().x, (int)mBallBody->GetPosition().y);
        qDebug() << mBallBody->GetPosition().x << " " << mBallBody->GetPosition().y;
}