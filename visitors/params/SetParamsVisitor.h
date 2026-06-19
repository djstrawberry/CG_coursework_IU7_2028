#pragma once
#include "../BaseVisitor.h"
#include "../../component/primitive/visible/model/impl/parametric/ParametricSphereImpl.h"
#include "../../component/primitive/visible/model/impl/tessellated/TessellatedSphereImpl.h"
#include "../../materials/Material.h"
#include "../../point/Point.h"
#include <optional>

class SetParamsVisitor : public BaseVisitor {
private:
    std::optional<double> m_newOrbitRadius;
    std::optional<double> m_newOrbitSpeed;
    std::optional<double> m_newOrbitAngle;
    std::optional<Point> m_newBaseCenter;
    std::optional<Material> m_newMaterial;
public:
    explicit SetParamsVisitor(const Point& center);
    explicit SetParamsVisitor(const Material& mat);
    SetParamsVisitor(double orbitRadius, double orbitSpeed);
    SetParamsVisitor(double radius, const Point& center, const Material& mat);
    SetParamsVisitor(double orbitRadius, double orbitSpeed, double orbitAngle,
                     const Point& baseCenter, const Material& mat);
    SetParamsVisitor(const Material& mat, const Point& baseCenter);

    void visit(ParametricSphereImpl& impl) const override;
    void visit(TessellatedSphereImpl& impl) const override;
    void visit(CameraImpl& camera) const override {};
    void visit(SphereImpl& sphere) const override {};
    void visit(LightImpl& light) const override {};
};