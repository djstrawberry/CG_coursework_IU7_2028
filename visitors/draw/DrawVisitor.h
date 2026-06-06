#ifndef DRAW_VISITOR_H
#define DRAW_VISITOR_H

#include "../BaseVisitor.h"
#include <memory>
#include <QPainter>

class BaseCamera;

class DrawVisitor : public BaseVisitor {
public:
    DrawVisitor(QPainter* painter, std::shared_ptr<BaseCamera> activeCamera, int width, int height, const float lightColor[4]);
    ~DrawVisitor() override = default;

    void visitCelestialBody(CelestialBody& body) override;
    void visitComposite(Composite& comp) override;
    void visitCamera(BaseCamera& camera) override;

private:
    QPainter* m_painter;
    std::shared_ptr<BaseCamera> m_camera;
    int m_viewportWidth;
    int m_viewportHeight;
    float m_lightColor[4];
};

#endif // DRAW_VISITOR_H
