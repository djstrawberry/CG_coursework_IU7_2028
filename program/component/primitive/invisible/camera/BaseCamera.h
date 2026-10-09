#pragma once

#include "../InvisibleObject.h"
#include "../../../../point/Point.h"
#include <memory>

class CameraImpl;

class BaseCamera : public InvisibleObject
{
protected:
    std::shared_ptr<CameraImpl> m_impl;
public:
    explicit BaseCamera(std::shared_ptr<CameraImpl> impl) : m_impl(std::move(impl)) {};
    ~BaseCamera() override = default;
    
    virtual Point getPosition() const = 0;
    virtual void setPosition(const Point& pos) = 0;
    
    virtual Point getTarget() const = 0;
    virtual void setTarget(const Point& target) = 0;

    virtual double getFov() const = 0;
    virtual void setFov(double fov) = 0;
    
    virtual void rotateAroundTarget(double angleX, double angleY) = 0;
    virtual void zoom(double amount) = 0;
};