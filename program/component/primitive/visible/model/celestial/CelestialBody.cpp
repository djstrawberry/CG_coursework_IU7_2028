#include "CelestialBody.h"
#include <stdexcept>
#include <cmath>

CelestialBody::CelestialBody(std::shared_ptr<SphereImpl> impl) 
{
    if (!impl) {
        throw std::invalid_argument("Celestial body implementation cannot be null!");
    }
    m_impl = std::move(impl); 
}

Point CelestialBody::getCenter() const noexcept {
    return m_impl ? m_impl->getCenter() : Point{0,0,0};
}

void CelestialBody::accept(std::shared_ptr<BaseVisitor> visitor) {
    if (m_impl) {
        m_impl->accept(visitor);  
    }
}

std::shared_ptr<BaseObject> CelestialBody::clone() const {
    auto clonedImpl = m_impl ? m_impl->clone() : nullptr;
    return std::make_shared<CelestialBody>(clonedImpl);
}