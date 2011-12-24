#include "physicalwindow.hpp"

PhysicalWindow::PhysicalWindow(int x, int y, int width, int height, 
                               QSharedPointer<b2World> physics_world) {
    mType = "dynamic";

    // Graphics stuff
    QPixmap pixmap(width, height);
    mPixmap = pixmap;
    mPixmap.fill(QColor(0, 0, 0, 0));
    QPainter painter(&mPixmap);
    QPainterPath path;
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(Qt::green));
    path.addEllipse(0, 0, width, height);
    painter.drawPath(path);
    mLabel.setParent(&mWindow);
    mLabel.setPixmap(mPixmap);
    mLabel.resize(width, height);
    mWindow.resize(width, height);
    mWindow.setAttribute(Qt::WA_TranslucentBackground);
    mWindow.setWindowFlags(Qt::FramelessWindowHint);
    mWindow.setWindowFlags(Qt::X11BypassWindowManagerHint);
    mWindow.move(x, y);
    mWindow.show();

    // Physics stuff
    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    body_def.position.Set(x, y);
    mPhysicsBody = physics_world->CreateBody(&body_def);
    b2CircleShape dynamic_circle;
    //dynamic_circle.m_p.Set(2.0f, 3.0f);
    dynamic_circle.m_radius = width/2;
    b2FixtureDef fixture_def;
    fixture_def.shape = &dynamic_circle;
    fixture_def.density = 1.0f;
    fixture_def.friction = 0.3f;
    mPhysicsBody->CreateFixture(&fixture_def);
}

PhysicalWindow::PhysicalWindow(WnckWindow* window,
                               QSharedPointer<b2World> physics_world) {
    mType = "window";

    // Get window geometry
    int x;
    int y;
    int width;
    int height;
    wnck_window_get_geometry(window, &x, &y, &width, &height);

    // Graphics stuff
    //QPixmap pixmap(width, height);
    //mPixmap = pixmap;
    //mPixmap.fill(QColor(0, 0, 0, 0));
    //QPainter painter(&mPixmap);
    //QPainterPath path;
    //painter.setRenderHint(QPainter::Antialiasing, true);
    //painter.setBrush(QBrush(Qt::green));
    //path.addRect(0, 0, width, height);
    //painter.drawPath(path);
    //mLabel.setParent(&mWindow);
    //mLabel.setPixmap(mPixmap);
    //mLabel.resize(width, height);
    //mWindow.resize(width, height);
    //mWindow.setAttribute(Qt::WA_TranslucentBackground);
    //mWindow.setWindowFlags(Qt::FramelessWindowHint);
    //mWindow.setWindowFlags(Qt::X11BypassWindowManagerHint);
    //mWindow.move(x, y);
    //mWindow.show();

    // Physics stuff
    b2BodyDef window_body_def;
    window_body_def.position.Set((float)(x+(width/2)), (float)(y+(height/2)));
    mPhysicsBody = physics_world->CreateBody(&window_body_def);
    b2PolygonShape window_box;
    window_box.SetAsBox(width/2, height/2);
    mPhysicsBody->CreateFixture(&window_box, 0.0f);
    g_print ("%s%s - dim: %ux%u - pos: %ix%i\n", wnck_window_get_name (window),
            window == window ? " (active)" : "",
            width, height, x, y);
}

PhysicalWindow::~PhysicalWindow() {}

void PhysicalWindow::update() {
    // If we are dynamic, update position using physics calculation
    // elsewise, we are a window and therefore update position using signals.
    if(mType == "dynamic") {
        mWindow.move((int)mPhysicsBody->GetPosition().x-mWindow.rect().width()/2,
                     (int)mPhysicsBody->GetPosition().y-mWindow.rect().height()/2);
        //qDebug() << mPhysicsBody->GetPosition().x << " " << mPhysicsBody->GetPosition().y;
    } else if (mType == "window") {
        // TODO
    }
}
