#include "physicalwindow.hpp"

PhysicalWindow::PhysicalWindow(int x, int y, int width, int height, 
                               QSharedPointer<b2World> physics_world) {
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
    mWindow.show();

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
}

PhysicalWindow::~PhysicalWindow() {}

void PhysicalWindow::update() {
    mWindow.move((int)mPhysicsBody->GetPosition().x, (int)mPhysicsBody->GetPosition().y);
    qDebug() << mPhysicsBody->GetPosition().x << " " << mPhysicsBody->GetPosition().y;
}
