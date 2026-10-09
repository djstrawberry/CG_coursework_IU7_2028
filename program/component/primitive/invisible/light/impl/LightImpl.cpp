#include "LightImpl.h"
#include "../../../../../visitors/BaseVisitor.h"

LightImpl::LightImpl(const Point& position, const std::vector<float>& color)
    : m_position(position), m_color(color) {}

void LightImpl::accept(std::shared_ptr<BaseVisitor> visitor) {
    if (visitor) {
        visitor->visit(*this);
    }
}

Point LightImpl::getPosition() const {
    return m_position;
}

void LightImpl::setPosition(const Point& pos) {
    m_position = pos;
}

std::vector<float> LightImpl::getColor() const {
    return m_color;
}

void LightImpl::setColor(const std::vector<float>& color) {
    m_color = color;
}