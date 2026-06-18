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
    void drawLine(const double x1, const double y1, const double x2, const double y2,
                  int r, int g, int b, int a = 255) override;

    void clear() override;

    size_t getWidth() const noexcept override;
    size_t getHeight() const noexcept override;
    void setWidth(size_t w);
    void setHeight(size_t h);
    void drawFilledCircle(double x, double y, double radius,
                      int r, int g, int b, int a = 255) override;
    void drawCircleOutline(double x, double y, double radius,
                       int r, int g, int b, int a = 255) override;
    void drawShadedDisc(double x, double y, double radius,
                        int r, int g, int b,
                        double highlightDx, double highlightDy) override;
    void drawGlow(double x, double y, double radius,
                  int r, int g, int b, float intensity) override;
    void drawFilledTriangle(double x0, double y0,
                            double x1, double y1,
                            double x2, double y2,
                            int r, int g, int b, int a = 255) override;
    void drawGouraudTriangle(double x0, double y0, double x1, double y1, double x2, double y2,
                                 int r0, int g0, int b0,
                                 int r1, int g1, int b1,
                                 int r2, int g2, int b2,
                                 int a) override;
};