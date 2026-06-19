#pragma once

#include "../BaseLight.h" 
#include "../impl/LightImpl.h"
#include "../../../../../point/Point.h"

class DefaultLight : public BaseLight {
public:
    DefaultLight(std::shared_ptr<LightImpl> impl);
    ~DefaultLight() override = default;

    Point getPosition() const override;
    void setPosition(const Point& pos) override;

    std::vector<float> getColor() const override;
    void setColor(const std::vector<float>& color) override;

    std::shared_ptr<BaseObject> clone() const override;
    Point getCenter() const noexcept override;

    void accept(std::shared_ptr<BaseVisitor> visitor) override;
};