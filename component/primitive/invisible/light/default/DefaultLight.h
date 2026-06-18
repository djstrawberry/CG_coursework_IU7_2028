#pragma once

#include "../BaseLight.h" 
#include "../impl/LightImpl.h"

class DefaultLight : public BaseLight {
public:
    explicit DefaultLight(std::shared_ptr<LightImpl> impl);
    ~DefaultLight() override = default;

    Vec3<double> getPosition() const override;
    void setPosition(const Vec3<double>& pos) override;

    std::vector<float> getColor() const override;
    void setColor(const std::vector<float>& color) override;

    void accept(std::shared_ptr<BaseVisitor> visitor) override;
};