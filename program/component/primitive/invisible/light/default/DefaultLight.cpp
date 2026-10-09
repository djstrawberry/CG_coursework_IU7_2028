#include "DefaultLight.h"

DefaultLight::DefaultLight(std::shared_ptr<LightImpl> impl)
    : BaseLight(std::move(impl)) {}

Point DefaultLight::getPosition() const {
    return m_impl ? m_impl->getPosition() : Point{0.0, 0.0, 0.0};
}

void DefaultLight::setPosition(const Point& pos) {
    if (m_impl) {
        m_impl->setPosition(pos);
    }
}

std::vector<float> DefaultLight::getColor() const {
    return m_impl ? m_impl->getColor() : std::vector<float>{1.0f, 1.0f, 1.0f, 1.0f};
}

void DefaultLight::setColor(const std::vector<float>& color) {
    if (m_impl) {
        m_impl->setColor(color);
    }
}

std::shared_ptr<BaseObject> DefaultLight::clone() const {
    auto implClone = std::make_shared<LightImpl>(getPosition(), getColor());
    return std::make_shared<DefaultLight>(implClone);
}

Point DefaultLight::getCenter() const noexcept
{ 
    return getPosition(); 
}

void DefaultLight::accept(std::shared_ptr<BaseVisitor> visitor) {
    if (m_impl) {
        m_impl->accept(visitor);
    }
}