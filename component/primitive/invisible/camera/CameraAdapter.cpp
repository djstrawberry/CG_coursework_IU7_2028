#include "CameraAdapter.h"
#include "impl/CameraImpl.h"

CameraAdapter::CameraAdapter(std::shared_ptr<CameraImpl> impl)
    : BaseCamera(std::move(impl)) {
    if (!m_impl)
        throw std::invalid_argument("Camera implementation cannot be null!");
}

std::shared_ptr<CameraImpl> CameraAdapter::getImpl() const noexcept {
    return m_impl;
}

Vec3<double> CameraAdapter::getPosition() const {
    return m_impl->getPosition();
}

void CameraAdapter::setPosition(const Vec3<double>& pos) {
    m_impl->setPosition(pos);
}

Vec3<double> CameraAdapter::getTarget() const {
    return m_impl->getTarget();
}

void CameraAdapter::setTarget(const Vec3<double>& target) {
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

Vec3<double> CameraAdapter::getCenter() const noexcept {
    return m_impl ? m_impl->getPosition() : Vec3<double>();
}

void CameraAdapter::accept(std::shared_ptr<BaseVisitor> visitor) {
    if (visitor)
        visitor->visit(m_impl);
}

std::shared_ptr<BaseObject> CameraAdapter::clone() const {
    auto implCopy = m_impl->clone();
    return std::make_shared<CameraAdapter>(std::move(implCopy));
}
