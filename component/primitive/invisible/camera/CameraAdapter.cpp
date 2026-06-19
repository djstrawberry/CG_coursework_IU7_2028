#include "CameraAdapter.h"
#include "impl/CameraImpl.h"
#include <stdexcept>

CameraAdapter::CameraAdapter(std::shared_ptr<CameraImpl> impl)
    : BaseCamera(std::move(impl)) {
    if (!m_impl)
        throw std::invalid_argument("Camera implementation cannot be null!");
}

Point CameraAdapter::getPosition() const {
    return m_impl->getPosition();
}

void CameraAdapter::setPosition(const Point& pos) {
    m_impl->setPosition(pos);
}

Point CameraAdapter::getTarget() const {
    return m_impl->getTarget();
}

void CameraAdapter::setTarget(const Point& target) {
    m_impl->setTarget(target);
}

double CameraAdapter::getFov() const {
    return m_impl->getFov();
}

void CameraAdapter::setFov(double fov) {
    m_impl->setFov(fov);
}

void CameraAdapter::rotateAroundTarget(double angleX, double angleY) {
    m_impl->rotateAroundTarget(angleX, angleY);
}

void CameraAdapter::zoom(double amount) {
    m_impl->zoom(amount);
}

Point CameraAdapter::getCenter() const noexcept {
    return m_impl ? m_impl->getPosition() : Point{0,0,0};
}

void CameraAdapter::accept(std::shared_ptr<BaseVisitor> visitor) {
    if (m_impl) {
        m_impl->accept(visitor);  
    }
}

std::shared_ptr<BaseObject> CameraAdapter::clone() const {
    auto implCopy = m_impl->clone();
    return std::make_shared<CameraAdapter>(std::move(implCopy));
}