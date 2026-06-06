#ifndef TRANSFORM_VISITOR_H
#define TRANSFORM_VISITOR_H

#include "../BaseVisitor.h"
#include "../../vector/Vec3.h"

class TransformVisitor : public BaseVisitor {
public:
    TransformVisitor(const Vec3<double>& delta, const Vec3<double>& scale, const Vec3<double>& rotation);
    ~TransformVisitor() override = default;

    void visitCelestialBody(CelestialBody& body) override;
    void visitComposite(Composite& comp) override;
    void visitCamera(BaseCamera& camera) override;

private:
    void applyTransform(Vec3<double>& point);

    Vec3<double> m_delta;
    Vec3<double> m_scale;
    Vec3<double> m_rotation; // Angles in degrees
};

#endif // TRANSFORM_VISITOR_H
