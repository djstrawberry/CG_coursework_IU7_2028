#pragma once

#include "BaseCamera.h"

class CameraAdapter final: public BaseCamera {
public:
    CameraAdapter() = delete;
    explicit CameraAdapter(std::shared_ptr<CameraImpl> impl);
    ~CameraAdapter() override = default;

    Point getPosition() const override;
    void setPosition(const Point& pos) override;

    Point getTarget() const override;
    void setTarget(const Point& target) override;

    double getFov() const override;
    void setFov(double fov) override;

    void rotateAroundTarget(double angleX, double angleY) override;
    void zoom(double amount) override;

    void accept(std::shared_ptr<BaseVisitor> visitor) override;
    Point getCenter() const noexcept override;
    std::shared_ptr<BaseObject> clone() const override;
};