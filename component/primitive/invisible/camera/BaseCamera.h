#pragma once

#include "../InvisibleObject.h"
#include "../../../../vector/Vec3.h"
#include <memory>

class CameraImpl;

class BaseCamera : public InvisibleObject
{
public:
    BaseCamera() = default;
    ~BaseCamera() override = default;

    virtual std::shared_ptr<CameraImpl> getImpl() const = 0;
    
    virtual Vec3<double> getPosition() const = 0;
    virtual void setPosition(const Vec3<double>& pos) = 0;
    
    virtual Vec3<double> getTarget() const = 0;
    virtual void setTarget(const Vec3<double>& target) = 0;

    virtual double getFov() const = 0;
    virtual void setFov(double fov) = 0;
    
    virtual void rotateAroundTarget(double angleX, double angleY) = 0;
    virtual void zoom(double amount) = 0;
};