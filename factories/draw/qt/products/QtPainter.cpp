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

namespace {

std::vector<double> buildGaussianKernel(int radius, double sigma)
{
    std::vector<double> kernel(static_cast<size_t>(2 * radius + 1));
    double sum = 0.0;
    for (int i = -radius; i <= radius; ++i) {
        const double value = std::exp(-(static_cast<double>(i * i)) / (2.0 * sigma * sigma));
        kernel[static_cast<size_t>(i + radius)] = value;
        sum += value;
    }
    for (double& value : kernel)
        value /= sum;
    return kernel;
}

int clampByte(double value)
{
    return static_cast<int>(std::clamp(value, 0.0, 255.0));
}

QImage gaussianBlur(const QImage& source, double sigma)
{
    const int width = source.width();
    const int height = source.height();
    const int radius = std::max(1, static_cast<int>(std::ceil(sigma * 3.0)));
    const auto kernel = buildGaussianKernel(radius, sigma);

    QImage temp(width, height, QImage::Format_ARGB32_Premultiplied);
    QImage result(width, height, QImage::Format_ARGB32_Premultiplied);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double red = 0.0;
            double green = 0.0;
            double blue = 0.0;
            double alpha = 0.0;
            for (int i = -radius; i <= radius; ++i) {
                const int sampleX = std::clamp(x + i, 0, width - 1);
                const QColor color = source.pixelColor(sampleX, y);
                const double weight = kernel[static_cast<size_t>(i + radius)];
                red += color.red() * weight;
                green += color.green() * weight;
                blue += color.blue() * weight;
                alpha += color.alpha() * weight;
            }
            temp.setPixelColor(x, y, QColor(clampByte(red), clampByte(green), clampByte(blue), clampByte(alpha)));
        }
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double red = 0.0;
            double green = 0.0;
            double blue = 0.0;
            double alpha = 0.0;
            for (int i = -radius; i <= radius; ++i) {
                const int sampleY = std::clamp(y + i, 0, height - 1);
                const QColor color = temp.pixelColor(x, sampleY);
                const double weight = kernel[static_cast<size_t>(i + radius)];
                red += color.red() * weight;
                green += color.green() * weight;
                blue += color.blue() * weight;
                alpha += color.alpha() * weight;
            }
            result.setPixelColor(x, y, QColor(clampByte(red), clampByte(green), clampByte(blue), clampByte(alpha)));
        }
    }

    return result;
}

QImage buildEmissiveField(int size, double coreRadius, int r, int g, int b, float intensity)
{
    QImage image(size, size, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);

    const double center = size / 2.0;
    const double coronaScale = coreRadius * 2.4;

    for (int py = 0; py < size; ++py) {
        for (int px = 0; px < size; ++px) {
            const double dx = px - center;
            const double dy = py - center;
            const double dist = std::sqrt(dx * dx + dy * dy);

            double radiance = 0.0;
            if (dist <= coreRadius) {
                const double normalized = dist / std::max(coreRadius, 1e-6);
                radiance = intensity * (1.2 - 0.2 * normalized * normalized);
            } else {
                const double delta = (dist - coreRadius) / std::max(coronaScale, 1e-6);
                radiance = intensity * std::exp(-2.8 * delta * delta);
            }

            const int alpha = clampByte(radiance * 255.0);
            if (alpha <= 0)
                continue;

            image.setPixelColor(px, py, QColor(r, g, b, alpha));
        }
    }

    return image;
}

void compositeBloom(QImage& base, const QImage& bloom)
{
    for (int y = 0; y < base.height(); ++y) {
        for (int x = 0; x < base.width(); ++x) {
            const QColor source = base.pixelColor(x, y);
            const QColor blurred = bloom.pixelColor(x, y);
            const int red = clampByte(source.red() + blurred.red() * 0.75);
            const int green = clampByte(source.green() + blurred.green() * 0.75);
            const int blue = clampByte(source.blue() + blurred.blue() * 0.75);
            const int alpha = clampByte(source.alpha() + blurred.alpha() * 0.75);
            base.setPixelColor(x, y, QColor(red, green, blue, alpha));
        }
    }
}

} // namespace

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

    // ВСЕ цвета строятся из переданных (r, g, b):
    gradient.setColorAt(0.0,  QColor(255, 255, 255, baseAlpha));               // белая сердцевина
    gradient.setColorAt(0.15, QColor(r, g, b, baseAlpha));                     // твой цвет
    gradient.setColorAt(0.40, QColor(r, g, b, midAlpha));                      // он же, прозрачнее
    gradient.setColorAt(0.70, QColor(r * 0.5, g * 0.5, b * 0.5, lowAlpha));   // потемневший
    gradient.setColorAt(1.0,  QColor(0, 0, 0, 0));                             // прозрачный край

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