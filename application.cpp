#include "application.hpp"

#include <QtGui/QApplication>

Application::Application() {}

Application::~Application() {}

void Application::init(int argc, char** argv) {
    b2Vec2 gravity(0.0f, 10.0f);
    mWorld = QSharedPointer<b2World>(new b2World(gravity));
    mWorld->SetAllowSleeping(false);

    // Get windowing system
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
        if(wnck_window_is_on_workspace(window, active_workspace) &&
           !wnck_window_is_minimized(window) &&
           wnck_window_get_window_type(window) == WNCK_WINDOW_NORMAL) {
            mPhysicalWindows.append(QSharedPointer<PhysicalWindow>(new PhysicalWindow(window, mWorld)));
        }
    }

    mPhysicalWindows.append(QSharedPointer<PhysicalWindow>(new PhysicalWindow(100, 100, 100, 100, mWorld)));
}

void Application::update() {
        float32 timeStep = 1.0/60.f;
        int32 velocityIterations = 6;
        int32 positionIterations = 2;

        mWorld->Step(timeStep, velocityIterations, positionIterations);
        foreach(QSharedPointer<PhysicalWindow> physwin, mPhysicalWindows) {
            physwin->update();
        }
}

void Application::spawnStuff() {
}
