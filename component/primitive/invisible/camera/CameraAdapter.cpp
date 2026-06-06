#include "CameraAdapter.h"
#include "../../../../visitors/BaseVisitor.h"

CameraAdapter::CameraAdapter(const Vec3<double>& pos, const Vec3<double>& target, double fov)
    : m_pos(pos), m_target(target), m_fov(fov) {}

void CameraAdapter::accept(std::shared_ptr<BaseVisitor> visitor) {
    visitor->visitCamera(*this);
}

std::shared_ptr<BaseObject> CameraAdapter::clone() {
    return std::make_shared<CameraAdapter>(m_pos, m_target, m_fov);
}
