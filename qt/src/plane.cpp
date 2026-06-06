#include "../inc/plane.h"
#include "../../managers/ManagerProvider.h"
#include "../../managers/draw/DrawManager.h"
#include "../../managers/camera/CameraManager.h"
#include <QPainter>
#include <QMouseEvent>
#include <cmath>

Plane::Plane(QWidget *parent) : QWidget(parent) {
    setMinimumSize(400, 400);
    // Dark Space theme background styling
    setAttribute(Qt::WA_OpaquePaintEvent);
}

void Plane::paintEvent(QPaintEvent *event) {
    (void)event;
    QPainter painter(this);
    
    // Draw Space canvas background
    painter.fillRect(rect(), QColor(10, 10, 15));

    // Delegate painting pipeline orchestration to DrawManager
    ManagerProvider::getDrawManager()->draw(&painter, width(), height());
}

void Plane::mousePressEvent(QMouseEvent *event) {
    m_lastMousePos = event->pos();
}

void Plane::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        int dx = event->position().x() - m_lastMousePos.x();
        int dy = event->position().y() - m_lastMousePos.y();

        auto camera = ManagerProvider::getCameraManager()->getActiveCamera();
        if (camera) {
            Vec3<double> pos = camera->getPosition();
            
            // Standard spherical rotate coordinates mapping on active viewports
            double radius = pos.length();
            double theta = std::atan2(pos.z, pos.x);
            double phi = std::acos(pos.y / radius);

            theta -= dx * 0.01;
            phi += dy * 0.01;

            // Restrict vertical look to prevent camera flipping
            phi = std::clamp(phi, 0.1, M_PI - 0.1);

            double newX = radius * std::sin(phi) * std::cos(theta);
            double newY = radius * std::cos(phi);
            double newZ = radius * std::sin(phi) * std::sin(theta);

            camera->setPosition(Vec3<double>(newX, newY, newZ));
            update(); // Retrigger rendering
        }

        m_lastMousePos = event->pos();
    }
}
