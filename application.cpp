#include "application.hpp"

Application::Application() {}

Application::~Application() {}

void Application::init(int argc, char** argv) {
    b2Vec2 gravity(0.0f, 10.0f);
    mWorld = QSharedPointer<b2World>(new b2World(gravity));
    mWorld->SetAllowSleeping(false);

    mPhysicalWindows.append(QSharedPointer<PhysicalWindow>(new PhysicalWindow(100, 100, 100, 100, mWorld)));

    // DEBUG WINDOWS
    //mDebugWindows.append(QSharedPointer<QMainWindow>(new QMainWindow));
    //mDebugPixmaps.append(QSharedPointer<QPixmap>(new QPixmap(100, 100)));
    //mDebugPixmaps.back()->fill(QColor(0, 0, 0, 0));
    //QPainter painter_debug(mDebugPixmaps.back().data());
    //QPainterPath path_debug;
    //painter_debug.setRenderHint(QPainter::Antialiasing, true);
    //painter_debug.setBrush(QBrush(Qt::green));
    //path_debug.addRect(0, 0, 100, 100);
    //painter_debug.drawPath(path_debug);
    //mDebugLabels.append(QSharedPointer<QLabel>(new QLabel(mDebugWindows.back().data())));
    //mDebugLabels.back()->setPixmap(*mDebugPixmaps.back().data());
    //mDebugLabels.back()->resize(100, 100);
    //mDebugWindows.back()->resize(100, 100);
    //mDebugWindows.back()->setAttribute(Qt::WA_TranslucentBackground);
    //mDebugWindows.back()->setWindowFlags(Qt::FramelessWindowHint);
    //mDebugWindows.back()->setWindowFlags(Qt::X11BypassWindowManagerHint);
    //mDebugWindows.back()->show();

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

void Application::update() {
        // SETUP
        float32 timeStep = 1.0/60.f;
        int32 velocityIterations = 6;
        int32 positionIterations = 2;

        mWorld->Step(timeStep, velocityIterations, positionIterations);
        foreach(QSharedPointer<PhysicalWindow> physwin, mPhysicalWindows) {
            physwin->update();
        }
}
