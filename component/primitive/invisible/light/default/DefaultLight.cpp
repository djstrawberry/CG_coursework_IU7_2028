#include "DefaultLight.h"

DefaultLight::DefaultLight(std::shared_ptr<LightImpl> impl)
    : BaseLight(std::move(impl)) {}

Vec3<double> DefaultLight::getPosition() const {
    return m_impl ? m_impl->getPosition() : Vec3<double>{0.0, 0.0, 0.0};
}

void DefaultLight::setPosition(const Vec3<double>& pos) {
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

void DefaultLight::accept(std::shared_ptr<BaseVisitor> visitor) {
    if (m_impl) {
        m_impl->accept(visitor);
    }
}