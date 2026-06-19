#pragma once

#include "../InvisibleObject.h"
#include "../../../../point/Point.h"
#include <memory>
#include <vector>

class LightImpl;

class BaseLight : public InvisibleObject
{
protected:
    std::shared_ptr<LightImpl> m_impl;

public:
    explicit BaseLight(std::shared_ptr<LightImpl> impl) : m_impl(std::move(impl)) {}
    ~BaseLight() override = default;
    
    virtual Point getPosition() const = 0;
    virtual void setPosition(const Point& pos) = 0;
    
    virtual std::vector<float> getColor() const = 0;
    virtual void setColor(const std::vector<float>& color) = 0;
};