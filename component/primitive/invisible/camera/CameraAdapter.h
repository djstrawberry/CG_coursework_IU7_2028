#ifndef CAMERA_ADAPTER_H
#define CAMERA_ADAPTER_H

#include "BaseCamera.h"

// Demonstrates the Adapter / Bridge Pattern for the Camera module in cleaner OO
class CameraAdapter : public BaseCamera {
public:
    CameraAdapter(const Vec3<double>& pos, const Vec3<double>& target, double fov = 60.0);
    ~CameraAdapter() override = default;

    void accept(std::shared_ptr<BaseVisitor> visitor) override;
    std::shared_ptr<BaseObject> clone() override;

    Vec3<double> getPosition() const override { return m_pos; }
    void setPosition(const Vec3<double>& pos) override { m_pos = pos; }

    Vec3<double> getTarget() const override { return m_target; }
    void setTarget(const Vec3<double>& target) override { m_target = target; }

    double getFov() const override { return m_fov; }
    void setFov(double fov) override { m_fov = fov; }

private:
    Vec3<double> m_pos;
    Vec3<double> m_target;
    double m_fov;
};

#endif // CAMERA_ADAPTER_H
