#pragma once

// Adapter (интерфейс)	BaseCamera
// ConAdapter (конкретный адаптер)	CameraAdapter
// BaseAdaptee (интерфейс адаптируемого)	CameraImpl
// ConAdaptee (конкретная реализация)	PerspectiveCameraImpl
// adaptee->specificRequest()	m_impl->rotate() / m_impl->zoom()

#include "BaseCamera.h"

class CameraAdapter final: public BaseCamera {
private:
    std::shared_ptr<CameraImpl> m_impl;
public:
    CameraAdapter() = delete;
    explicit CameraAdapter(std::shared_ptr<CameraImpl> impl);
    ~CameraAdapter() override = default;

    std::shared_ptr<CameraImpl> getImpl() const noexcept override;

    Vec3<double> getPosition() const override;
    void setPosition(const Vec3<double>& pos) override;

    Vec3<double> getTarget() const override;
    void setTarget(const Vec3<double>& target) override;

    double getFov() const override;
    void setFov(double fov) override;

    void rotateAroundTarget(double angleX, double angleY) override;
    void zoom(double amount) override;

    void accept(std::shared_ptr<BaseVisitor> visitor) override;
    Vec3<double> getCenter() const noexcept override;
    std::shared_ptr<BaseObject> clone() const override;
};