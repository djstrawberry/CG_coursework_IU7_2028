#pragma once

#include <memory>

class CameraImpl;
class SphereImpl;

class BaseVisitor
{
public:
    BaseVisitor() = default;
    virtual ~BaseVisitor() = default;

    virtual void visit(std::shared_ptr<CameraImpl> camera) const = 0;
    virtual void visit(std::shared_ptr<SphereImpl> sphere) const = 0;
};