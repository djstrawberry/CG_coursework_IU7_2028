#include "CelestialBody.h"
#include <stdexcept>
#include <cmath>

CelestialBody::CelestialBody(const std::string& name, std::shared_ptr<SphereImpl> impl) 
    :  BaseModel(std::move(impl)), m_name(std::move(name))
{
    if (!m_impl) {
        throw std::invalid_argument("Celestial body implementation cannot be null!");
    }
    m_baseCenter = m_impl->getCenter();
}

std::string CelestialBody::getName() const {
    return m_name;
}

void CelestialBody::setName(const std::string& name) {
    m_name = name;
}

Material CelestialBody::getMaterial() const {
    return m_material;
}

void CelestialBody::setMaterial(const Material& mat) {
    m_material = mat;
    if (m_impl) {
        m_impl->setMaterial(mat);  
    }
}

double CelestialBody::getOrbitRadius() const {
    return m_orbitRadius;
}

void CelestialBody::setOrbitRadius(double radius) {
    m_orbitRadius = radius;
    updatePosition();  
}

double CelestialBody::getOrbitSpeed() const {
    return m_orbitSpeed;
}

void CelestialBody::setOrbitSpeed(double speed) {
    m_orbitSpeed = speed;
}

double CelestialBody::getOrbitAngle() const {
    return m_orbitAngle;
}

void CelestialBody::setOrbitAngle(double angle) {
    m_orbitAngle = angle;
    updatePosition();  
}

Vec3<double> CelestialBody::getBaseCenter() const {
    return m_baseCenter;
}

void CelestialBody::setBaseCenter(const Vec3<double>& center) {
    m_baseCenter = center;
    updatePosition();
}

Vec3<double> CelestialBody::getCenter() const noexcept {
    return m_impl ? m_impl->getCenter() : Vec3<double>{};
}

std::shared_ptr<SphereImpl> CelestialBody::getImpl() const {
    return m_impl;
}

void CelestialBody::accept(std::shared_ptr<BaseVisitor> visitor) {
    if (visitor) {
        visitor->visit(m_impl);  
    }
}

std::shared_ptr<BaseObject> CelestialBody::clone() const {
    auto cloned = std::make_shared<CelestialBody>(m_name, m_impl->clone());
    cloned->m_material = m_material;
    cloned->m_orbitRadius = m_orbitRadius;
    cloned->m_orbitSpeed = m_orbitSpeed;
    cloned->m_orbitAngle = m_orbitAngle;
    cloned->m_baseCenter = m_baseCenter;
    return cloned;
}

void CelestialBody::updatePosition() {
    if (!m_impl || m_orbitRadius <= 0.0) return;

    double rad = m_orbitAngle * M_PI / 180.0;
    double newX = m_baseCenter.getX() + m_orbitRadius * std::cos(rad);
    double newZ = m_baseCenter.getZ() + m_orbitRadius * std::sin(rad);

    m_impl->setCenter(Vec3<double>(newX, m_baseCenter.getY(), newZ));
}