#ifndef BASE_CAMERA_H
#define BASE_CAMERA_H

#include "../../../BaseObject.h"
#include "../../../../vector/Vec3.h"

class BaseCamera : public BaseObject {
public:
    BaseCamera() = default;
    ~BaseCamera() override = default;

    bool isVisible() const override { return false; }

    virtual Vec3<double> getPosition() const = 0;
    virtual void setPosition(const Vec3<double>& pos) = 0;

    virtual Vec3<double> getTarget() const = 0;
    virtual void setTarget(const Vec3<double>& target) = 0;

    virtual double getFov() const = 0;
    virtual void setFov(double fov) = 0;
};

#endif // BASE_CAMERA_H
