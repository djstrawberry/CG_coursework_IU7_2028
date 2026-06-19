#pragma once

#include "../../../../../point/Point.h"
#include <vector>
#include <memory>

class BaseVisitor;

class LightImpl {
public:
    LightImpl(const Point& position, const std::vector<float>& color);
    virtual ~LightImpl() = default;

    void accept(std::shared_ptr<BaseVisitor> visitor);

    Point getPosition() const;
    void setPosition(const Point& pos);

    std::vector<float> getColor() const;
    void setColor(const std::vector<float>& color);

private:
    Point m_position;
    std::vector<float> m_color;
};