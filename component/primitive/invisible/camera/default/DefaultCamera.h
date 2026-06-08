#pragma once

#include "../impl/CameraImpl.h"
#include "../../../../../vector/Vec3.h"


class DefaultCameraImpl final : public CameraImpl
{
private:
    Vec3<double> m_position;
    Vec3<double> m_target;
    Vec3<double> m_up;
    double m_fov;
    double m_near;
    double m_far;

public:
    DefaultCameraImpl();
    ~DefaultCameraImpl() override = default;

    std::shared_ptr<CameraImpl> clone() const override;
    
    Vec3<double> getPosition() const override;
    void setPosition(const Vec3<double>& pos) override;
    
    Vec3<double> getTarget() const override;
    void setTarget(const Vec3<double>& target) override;
    
    double getFov() const override;
    void setFov(double fov) override;
    
    void rotateAroundTarget(double angleX, double angleY) override;
    void zoom(double amount) override;
};