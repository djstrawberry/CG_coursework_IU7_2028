#pragma once

#include "../../../../../vector/Vec3.h"
#include <vector>
#include <memory>

class BaseVisitor;

class LightImpl {
public:
    LightImpl(const Vec3<double>& position, const std::vector<float>& color);
    virtual ~LightImpl() = default;

    void accept(std::shared_ptr<BaseVisitor> visitor);

    Vec3<double> getPosition() const;
    void setPosition(const Vec3<double>& pos);

    std::vector<float> getColor() const;
    void setColor(const std::vector<float>& color);

private:
    Vec3<double> m_position;
    std::vector<float> m_color; 
};