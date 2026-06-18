#pragma once

#include <memory>

class CameraImpl;
class SphereImpl;
class LightImpl;

class BaseVisitor
{
public:
    BaseVisitor() = default;
    virtual ~BaseVisitor() = default;

    virtual void visit(CameraImpl& camera) const = 0;
    virtual void visit(SphereImpl& sphere) const = 0;
    virtual void visit(LightImpl& light) const = 0;
};