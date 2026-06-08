#pragma once

#include "../../../vector/Vec3.h"
#include <cstddef>

class BasePainter
{
protected:
    size_t m_width;
    size_t m_height;

public:
    BasePainter() = default;
    virtual ~BasePainter() = default;

    virtual void drawLine(const Vec3<double> &p1, const Vec3<double> &p2) = 0;
    virtual void drawLine(const double x1, const double y1, const double x2, const double y2) = 0;
    
    virtual void drawFilledCircle(double x, double y, double radius, 
                                  int r, int g, int b, int a = 255) = 0;
    virtual void drawCircleOutline(double x, double y, double radius,
                                   int r, int g, int b, int a = 255) = 0;

    virtual void clear() = 0;

    virtual size_t getWidth() const noexcept = 0;
    virtual size_t getHeight() const noexcept = 0;
};