#include "AnimationVisitor.h"
#include <cmath>

AnimationVisitor::AnimationVisitor(double deltaSeconds, const Point& starCenter)
    : m_deltaSeconds(deltaSeconds), m_starCenter(starCenter) {}

void AnimationVisitor::visit(ParametricSphereImpl& impl) const {
    if (impl.getOrbitRadius() <= 0.0 || impl.getOrbitSpeed() <= 0.0) return;
    impl.setBaseCenter(m_starCenter);
    double newAngle = std::fmod(impl.getOrbitAngle() + impl.getOrbitSpeed() * m_deltaSeconds, 360.0);
    if (newAngle < 0.0) newAngle += 360.0;
    impl.setOrbitAngle(newAngle);
    impl.updatePosition();
}

void AnimationVisitor::visit(TessellatedSphereImpl& impl) const {
    if (impl.getOrbitRadius() <= 0.0 || impl.getOrbitSpeed() <= 0.0) return;
    impl.setBaseCenter(m_starCenter);
    double newAngle = std::fmod(impl.getOrbitAngle() + impl.getOrbitSpeed() * m_deltaSeconds, 360.0);
    if (newAngle < 0.0) newAngle += 360.0;
    impl.setOrbitAngle(newAngle);
    impl.updatePosition();
}