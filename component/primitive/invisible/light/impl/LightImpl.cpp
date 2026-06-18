#include "LightImpl.h"
#include "../../../../../visitors/BaseVisitor.h" 

LightImpl::LightImpl(const Vec3<double>& position, const std::vector<float>& color)
    : m_position(position), m_color(color) {}

void LightImpl::accept(std::shared_ptr<BaseVisitor> visitor) {
    if (visitor) {
        visitor->visit(*const_cast<LightImpl*>(this));
    }
}

Vec3<double> LightImpl::getPosition() const 
{
    return m_position; 
}
void LightImpl::setPosition(const Vec3<double>& pos) { 
    m_position = pos; 
}

std::vector<float> LightImpl::getColor() const { 
    return m_color; 
}
void LightImpl::setColor(const std::vector<float>& color) { 
    m_color = color; 
}