#pragma once

#include "../../../../../point/Point.h"
#include "../../../../../visitors/BaseVisitor.h"
#include <memory>

class CameraImpl
{
public:
    CameraImpl() = default;
    virtual ~CameraImpl() = default;

    virtual std::shared_ptr<CameraImpl> clone() const = 0;
    
    virtual Point getPosition() const = 0;
    virtual void setPosition(const Point& pos) = 0;
    
    virtual Point getTarget() const = 0;
    virtual void setTarget(const Point& target) = 0;
    
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