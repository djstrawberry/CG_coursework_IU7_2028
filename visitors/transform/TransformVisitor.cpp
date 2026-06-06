#include "TransformVisitor.h"
#include "../../component/primitive/visible/model/celestial/CelestialBody.h"
#include "../../component/primitive/invisible/camera/BaseCamera.h"
#include <cmath>

TransformVisitor::TransformVisitor(const Vec3<double>& delta, const Vec3<double>& scale, const Vec3<double>& rotation)
    : m_delta(delta), m_scale(scale), m_rotation(rotation) {}

void TransformVisitor::visitCelestialBody(CelestialBody& body) {
    auto impl = body.getImpl();
    if (!impl) return;

    // Shift Center
    Vec3<double> oldCenter = impl->getCenter();
    Vec3<double> newCenter = oldCenter + m_delta;

    // Direct radius scale
    double oldRad = impl->getRadius();
    impl->setRadius(oldRad * m_scale.x);
    
    impl->setCenter(newCenter);
}

void TransformVisitor::visitComposite(Composite& comp) {
    (void)comp;
}

void TransformVisitor::visitCamera(BaseCamera& camera) {
    // Apply translations on spatial camera coordinate systems
    Vec3<double> pos = camera.getPosition();
    camera.setPosition(pos + m_delta);
}
