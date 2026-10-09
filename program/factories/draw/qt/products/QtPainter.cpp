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

void QtPainter::drawGouraudTriangle(double x0, double y0, double x1, double y1, double x2, double y2,
                                     int r0, int g0, int b0,
                                     int r1, int g1, int b1,
                                     int r2, int g2, int b2,
                                     int a)
{
    Q_UNUSED(a);
    int minX = static_cast<int>(std::max(0.0, std::min({x0, x1, x2})));
    int maxX = static_cast<int>(std::min(static_cast<double>(m_width - 1), std::max({x0, x1, x2})));
    int minY = static_cast<int>(std::max(0.0, std::min({y0, y1, y2})));
    int maxY = static_cast<int>(std::min(static_cast<double>(m_height - 1), std::max({y0, y1, y2})));

    if (minX > maxX || minY > maxY) return;

    QImage img(maxX - minX + 1, maxY - minY + 1, QImage::Format_ARGB32);
    img.fill(Qt::transparent);

    auto edge = [](double x0, double y0, double x1, double y1, double px, double py) {
        return (x1 - x0) * (py - y0) - (y1 - y0) * (px - x0);
    };

    double area = edge(x0, y0, x1, y1, x2, y2);
    if (std::abs(area) < 1e-6) return;

    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            double px = x + 0.5, py = y + 0.5;
            double w0 = edge(x1, y1, x2, y2, px, py);
            double w1 = edge(x2, y2, x0, y0, px, py);
            double w2 = edge(x0, y0, x1, y1, px, py);
            if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0)) {
                w0 /= area; w1 /= area; w2 /= area;
                int r = std::clamp(static_cast<int>(r0 * w0 + r1 * w1 + r2 * w2), 0, 255);
                int g = std::clamp(static_cast<int>(g0 * w0 + g1 * w1 + g2 * w2), 0, 255);
                int b = std::clamp(static_cast<int>(b0 * w0 + b1 * w1 + b2 * w2), 0, 255);
                img.setPixelColor(x - minX, y - minY, QColor(r, g, b));
            }
        }
    }

    m_scene->addPixmap(QPixmap::fromImage(img))->setPos(minX, minY);
}