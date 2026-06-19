#pragma once

#include <memory>

class CameraImpl;
class SphereImpl;
class ParametricSphereImpl;
class TessellatedSphereImpl;
class LightImpl;

class BaseVisitor
{
public:
    BaseVisitor() = default;
    virtual ~BaseVisitor() = default;

    virtual void visit(CameraImpl& camera) const = 0;
    virtual void visit(SphereImpl& sphere) const = 0;
    virtual void visit(LightImpl& light) const = 0;
    virtual void visit(ParametricSphereImpl& parametricSphere) const = 0;
    virtual void visit(TessellatedSphereImpl& tesselatedSphere) const = 0;
};