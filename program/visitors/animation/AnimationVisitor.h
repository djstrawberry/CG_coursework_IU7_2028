#pragma once
#include "../BaseVisitor.h"
#include "../../component/primitive/visible/model/impl/parametric/ParametricSphereImpl.h"
#include "../../component/primitive/visible/model/impl/tessellated/TessellatedSphereImpl.h"
#include "../../point/Point.h"

class AnimationVisitor : public BaseVisitor {
    double m_deltaSeconds;
    Point m_starCenter;
public:
    explicit AnimationVisitor(double deltaSeconds, const Point& starCenter);
    void visit(ParametricSphereImpl& impl) const override;
    void visit(TessellatedSphereImpl& impl) const override;
    void visit(CameraImpl& camera) const override {}
    void visit(SphereImpl& sphere) const override {}
    void visit(LightImpl& light) const override {}
};