#include "QtPainter.h"
#include <QPen>
#include <QBrush>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>
#include <QPolygonF>
#include <QRadialGradient>
#include <algorithm>
#include <cmath>
#include <vector>

int clampByte(double value)
{
    return static_cast<int>(std::clamp(value, 0.0, 255.0));
}

QtPainter::QtPainter(std::shared_ptr<QGraphicsScene> scene) :
    m_scene(std::move(scene))
{ 
    m_width = static_cast<size_t>(m_scene->width());
    m_height = static_cast<size_t>(m_scene->height());
}

void QtPainter::drawLine(const Vec3<double> &p1, const Vec3<double> &p2)
{
    m_scene->addLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), QPen(Qt::white));
}

void QtPainter::drawLine(const double x1, const double y1, const double x2, const double y2)
{
    m_scene->addLine(x1, y1, x2, y2, QPen(Qt::white));
}

void QtPainter::drawLine(const double x1, const double y1, const double x2, const double y2,
                         int r, int g, int b, int a)
{
    QPen pen(QColor(r, g, b, a));
    pen.setWidthF(1.0);
    m_scene->addLine(x1, y1, x2, y2, pen);
}

void QtPainter::clear()
{
    m_scene->clear();
}

size_t QtPainter::getWidth() const noexcept
{
    return m_width;
}

size_t QtPainter::getHeight() const noexcept
{
    return m_height;
}

void QtPainter::setWidth(size_t w)
{
    m_width = w;
}

void QtPainter::setHeight(size_t h)
{
    m_height = h;
}

void QtPainter::drawFilledCircle(double x, double y, double radius,
                                  int r, int g, int b, int a)
{
    m_scene->addEllipse(x - radius, y - radius, radius * 2, radius * 2,
                        QPen(Qt::NoPen), QBrush(QColor(r, g, b, a)));
}

void QtPainter::drawCircleOutline(double x, double y, double radius,
                                   int r, int g, int b, int a)
{
    m_scene->addEllipse(x - radius, y - radius, radius * 2, radius * 2,
                        QPen(QColor(r, g, b, a)), QBrush(Qt::NoBrush));
}

void QtPainter::drawShadedDisc(double x, double y, double radius,
                               int r, int g, int b,
                               double highlightDx, double highlightDy)
{
    QRadialGradient gradient(QPointF(radius + highlightDx, radius + highlightDy), radius * 1.15);
    gradient.setColorAt(0.0, QColor(std::min(255, r + 110), std::min(255, g + 90), std::min(255, b + 60)));
    gradient.setColorAt(0.35, QColor(r, g, b));
    gradient.setColorAt(1.0, QColor(std::max(0, r / 3), std::max(0, g / 4), std::max(0, b / 6)));
    m_scene->addEllipse(x - radius, y - radius, radius * 2, radius * 2,
                        QPen(Qt::NoPen), QBrush(gradient));
}

void QtPainter::drawGlow(double x, double y, double radius,
                         int r, int g, int b, float intensity)
{
    double glowRadius = radius * 4.5;

    QRadialGradient gradient(QPointF(x, y), glowRadius);

    int baseAlpha = std::clamp(static_cast<int>(intensity * 255.0f), 0, 255);
    int midAlpha  = std::clamp(static_cast<int>(intensity * 140.0f), 0, 255);
    int lowAlpha  = std::clamp(static_cast<int>(intensity * 50.0f), 0, 255);

    gradient.setColorAt(0.0,  QColor(255, 255, 255, baseAlpha));               
    gradient.setColorAt(0.15, QColor(r, g, b, baseAlpha));                     
    gradient.setColorAt(0.40, QColor(r, g, b, midAlpha));                     
    gradient.setColorAt(0.70, QColor(r * 0.5, g * 0.5, b * 0.5, lowAlpha));   
    gradient.setColorAt(1.0,  QColor(0, 0, 0, 0));                           

    m_scene->addEllipse(x - glowRadius, y - glowRadius, glowRadius * 2, glowRadius * 2,
                        Qt::NoPen, QBrush(gradient));
}

void QtPainter::drawFilledTriangle(double x0, double y0,
                                   double x1, double y1,
                                   double x2, double y2,
                                   int r, int g, int b, int a)
{
    QPolygonF polygon;
    polygon << QPointF(x0, y0) << QPointF(x1, y1) << QPointF(x2, y2);
    m_scene->addPolygon(polygon, QPen(Qt::NoPen), QBrush(QColor(r, g, b, a)));
}