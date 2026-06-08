#pragma once

#include "../../products/BasePainter.h"
#include "../../../../vector/Vec3.h"
#include <QGraphicsScene>
#include <memory>

class QtPainter final : public BasePainter
{
private:
    std::shared_ptr<QGraphicsScene> m_scene;

public:
    QtPainter() = delete;
    QtPainter(std::shared_ptr<QGraphicsScene> scene);

    virtual ~QtPainter() override = default;

    void drawLine(const Vec3<double> &p1, const Vec3<double> &p2) override;
    void drawLine(const double x1, const double y1, const double x2, const double y2) override;

    void clear() override;

    size_t getWidth() const noexcept override;
    size_t getHeight() const noexcept override;
    void setWidth(size_t w);
    void setHeight(size_t h);
    void drawFilledCircle(double x, double y, double radius,
                      int r, int g, int b, int a = 255) override;
    void drawCircleOutline(double x, double y, double radius,
                       int r, int g, int b, int a = 255) override;
};