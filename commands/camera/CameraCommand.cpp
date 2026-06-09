#include "CameraCommand.h"
#include "../../managers/ManagerProvider.h"
#include "../../managers/camera/CameraManager.h"

MoveActiveCameraCommand::MoveActiveCameraCommand(const Vec3<double> &displacement) :
    m_action(&CameraManager::moveActiveCamera), m_disp(displacement), m_camManager(ManagerProvider::getCameraManager())
{ }

void MoveActiveCameraCommand::execute()
{
    ((*m_camManager).*m_action)(m_disp);
}

SetActiveCameraDetailsCommand::SetActiveCameraDetailsCommand(const Vec3<double> &pos, const Vec3<double> &target, double fov) :
    m_action(&CameraManager::setActiveCameraDetails), m_pos(pos), m_target(target), m_fov(fov), m_camManager(ManagerProvider::getCameraManager())
{ }

void SetActiveCameraDetailsCommand::execute()
{
    ((*m_camManager).*m_action)(m_pos, m_target, m_fov);
}