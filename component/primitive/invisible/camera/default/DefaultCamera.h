#pragma once

#include "../impl/CameraImpl.h"
#include "../../../../../point/Point.h"

class DefaultCameraImpl final : public CameraImpl
{
private:
    Point m_position;
    Point m_target;
    Point m_up;
    double m_fov;
    double m_near;
    double m_far;

public:
    DefaultCameraImpl();
    ~DefaultCameraImpl() override = default;

    std::shared_ptr<CameraImpl> clone() const override;
    
    Point getPosition() const override;
    void setPosition(const Point& pos) override;
    
    Point getTarget() const override;
    void setTarget(const Point& target) override;
    
    double getFov() const override;
    void setFov(double fov) override;
    
    void rotateAroundTarget(double angleX, double angleY) override;
    void zoom(double amount) override;
};