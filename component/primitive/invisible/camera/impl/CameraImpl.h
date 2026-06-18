#pragma once

#include "../../../../../vector/Vec3.h"
#include "../../../../../visitors/BaseVisitor.h"
#include <memory>

class CameraImpl
{
public:
    CameraImpl() = default;
    virtual ~CameraImpl() = default;

    virtual std::shared_ptr<CameraImpl> clone() const = 0;
    
    virtual Vec3<double> getPosition() const = 0;
    virtual void setPosition(const Vec3<double>& pos) = 0;
    
    virtual Vec3<double> getTarget() const = 0;
    virtual void setTarget(const Vec3<double>& target) = 0;
    
    virtual double getFov() const = 0;
    virtual void setFov(double fov) = 0;
    
    virtual void rotateAroundTarget(double angleX, double angleY) = 0;
    virtual void zoom(double amount) = 0;

    virtual void accept(std::shared_ptr<BaseVisitor> visitor)
    {
        if (visitor)
            visitor->visit(*this);
    }
};