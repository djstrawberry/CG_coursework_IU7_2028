#include "DefaultCamera.h"
#include <cmath>

DefaultCameraImpl::DefaultCameraImpl()
    : m_position(0, 10, 20)
    , m_target(0, 0, 0)
    , m_up(0, 1, 0)
    , m_fov(60.0)
    , m_near(0.1)
    , m_far(1000.0)
{ }

std::shared_ptr<CameraImpl> DefaultCameraImpl::clone() const
{
    auto cloned = std::make_shared<DefaultCameraImpl>();
    cloned->m_position = m_position;
    cloned->m_target = m_target;
    cloned->m_up = m_up;
    cloned->m_fov = m_fov;
    cloned->m_near = m_near;
    cloned->m_far = m_far;
    return cloned;
}

Point DefaultCameraImpl::getPosition() const { return m_position; }

void DefaultCameraImpl::setPosition(const Point& pos) { m_position = pos; }

Point DefaultCameraImpl::getTarget() const { return m_target; }

void DefaultCameraImpl::setTarget(const Point& target) { m_target = target; }

double DefaultCameraImpl::getFov() const { return m_fov; }

void DefaultCameraImpl::setFov(double fov) { m_fov = fov; }

void DefaultCameraImpl::rotateAroundTarget(double angleX, double angleY)
{
    Point direction = m_position - m_target;
    double distance = direction.length();
    
    double radX = angleX * M_PI / 180.0;
    Point right = m_up.cross(direction.normalized()).normalized();
    
    double cosX = std::cos(radX);
    double sinX = std::sin(radX);
    direction = direction * cosX + right * (sinX * distance);
    
    double radY = angleY * M_PI / 180.0;
    double cosY = std::cos(radY);
    double sinY = std::sin(radY);
    direction = direction * cosY + m_up * (sinY * distance);
    
    m_position = m_target + direction.normalized() * distance;
}

void DefaultCameraImpl::zoom(double amount)
{
    Point direction = (m_target - m_position).normalized();
    double distance = (m_position - m_target).length();
    double newDistance = distance - amount;
    
    if (newDistance < 1.0) newDistance = 1.0;
    
    m_position = m_target - direction * newDistance;
}