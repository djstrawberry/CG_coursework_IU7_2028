#include "SetParamsVisitor.h"

SetParamsVisitor::SetParamsVisitor(const Point& baseCenter)
        : m_newBaseCenter(baseCenter) {}

SetParamsVisitor::SetParamsVisitor(const Material& material)
        : m_newMaterial(material) {}

SetParamsVisitor::SetParamsVisitor(double orbitRadius, double orbitSpeed)
        : m_newOrbitRadius(orbitRadius), m_newOrbitSpeed(orbitSpeed) {}

SetParamsVisitor::SetParamsVisitor(double orbitRadius, const Point& baseCenter, const Material& material)
        : m_newOrbitRadius(orbitRadius), m_newBaseCenter(baseCenter), m_newMaterial(material) {}

SetParamsVisitor::SetParamsVisitor(double orbitRadius, double orbitSpeed, double orbitAngle,
                     const Point& baseCenter, const Material& material)
        : m_newOrbitRadius(orbitRadius), m_newOrbitSpeed(orbitSpeed), 
        m_newOrbitAngle(orbitAngle), m_newBaseCenter(baseCenter), m_newMaterial(material) {}
    
SetParamsVisitor::SetParamsVisitor(const Material& material, const Point& baseCenter)
        : m_newMaterial(material), m_newBaseCenter(baseCenter) {}

void SetParamsVisitor::visit(ParametricSphereImpl& impl) const {
    if (m_newOrbitRadius) impl.setOrbitRadius(*m_newOrbitRadius);
    if (m_newOrbitSpeed)  impl.setOrbitSpeed(*m_newOrbitSpeed);
    if (m_newOrbitAngle)  impl.setOrbitAngle(*m_newOrbitAngle);
    if (m_newBaseCenter)  impl.setBaseCenter(*m_newBaseCenter);
    if (m_newMaterial)    impl.setMaterial(*m_newMaterial);
    impl.updatePosition();
}

void SetParamsVisitor::visit(TessellatedSphereImpl& impl) const {
    if (m_newOrbitRadius) impl.setOrbitRadius(*m_newOrbitRadius);
    if (m_newOrbitSpeed)  impl.setOrbitSpeed(*m_newOrbitSpeed);
    if (m_newOrbitAngle)  impl.setOrbitAngle(*m_newOrbitAngle);
    if (m_newBaseCenter)  impl.setBaseCenter(*m_newBaseCenter);
    if (m_newMaterial)    impl.setMaterial(*m_newMaterial);
    impl.updatePosition();
}