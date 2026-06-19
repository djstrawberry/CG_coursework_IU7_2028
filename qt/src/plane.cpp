#include "../inc/plane.h"
#include "../../managers/ManagerProvider.h"
#include "../../managers/draw/DrawManager.h"
#include "../../managers/camera/CameraManager.h"
#include "../../factories/draw/qt/QtDrawFactory.h"
#include "../../factories/draw/products/BasePainter.h"
#include "../../factories/draw/qt/products/QtPainter.h"
#include <QPainter>
#include <QMouseEvent>
#include <QResizeEvent>
#include <cmath>

Plane::Plane(QWidget *parent) : QWidget(parent) {
    setMinimumSize(400, 400);
    setAttribute(Qt::WA_OpaquePaintEvent);

    m_scene = std::make_shared<QGraphicsScene>();
    m_scene->setSceneRect(0, 0, width(), height());

    auto factory = std::make_shared<QtDrawFactory>(m_scene);
    auto painter = factory->createPainter();
    m_painter = std::unique_ptr<BasePainter>(std::move(painter));
    ManagerProvider::getDrawManager()->setPainter(m_painter);
    updatePainterSize();
}

void Plane::updatePainterSize() {
    if (!m_painter || !m_scene)
        return;

    m_scene->setSceneRect(0, 0, width(), height());

    if (auto* qtPainter = dynamic_cast<QtPainter*>(m_painter.get())) {
        qtPainter->setWidth(static_cast<size_t>(width()));
        qtPainter->setHeight(static_cast<size_t>(height()));
    }
}

void Plane::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    updatePainterSize();
}

void Plane::paintEvent(QPaintEvent *event) {
    (void)event;
    QPainter painter(this);

    painter.fillRect(rect(), QColor(10, 10, 15));

    updatePainterSize();
    ManagerProvider::getDrawManager()->draw();
    m_scene->render(&painter);
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
            Point pos = camera->getPosition();
            
            double radius = pos.length();
            double theta = std::atan2(pos.getZ(), pos.getX());
            double phi = std::acos(pos.getY() / radius);

            theta -= dx * 0.01;
            phi += dy * 0.01;

            phi = std::clamp(phi, 0.1, M_PI - 0.1);

            double newX = radius * std::sin(phi) * std::cos(theta);
            double newY = radius * std::cos(phi);
            double newZ = radius * std::sin(phi) * std::sin(theta);

            camera->setPosition(Point(newX, newY, newZ));
            update(); 
        }

        m_lastMousePos = event->pos();
    }
}

void Plane::wheelEvent(QWheelEvent* event)
{
    double delta = event->angleDelta().y() / 120.0;
    auto cameraManager = ManagerProvider::getCameraManager();
    auto camera = cameraManager->getActiveCamera();
    if (camera) {
        camera->zoom(delta * 2.0);  
        update(); 
    }
}
