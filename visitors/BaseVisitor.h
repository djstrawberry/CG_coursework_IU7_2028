#pragma once

#include <memory>

class CelestialBody;
class CameraAdapter;
class Composite;

class BaseVisitor
{
public:
    BaseVisitor() = default;
    virtual ~BaseVisitor() = default;

    virtual void visit(const CelestialBody& body) const = 0;
    virtual void visit(const CameraAdapter& camera) const = 0; 
    virtual void visit(const Composite& composite) const = 0;

    virtual void beginScene() const {}
    virtual void flushScene() const {}
};