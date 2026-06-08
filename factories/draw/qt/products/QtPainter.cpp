#include "QtPainter.h"
#include <QPen>
#include <QBrush>

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