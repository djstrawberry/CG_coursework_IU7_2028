#include "CameraCommand.h"
#include "../../managers/ManagerProvider.h"
#include "../../managers/camera/CameraManager.h"

MoveActiveCameraCommand::MoveActiveCameraCommand(const Point &displacement) :
    m_action(&CameraManager::moveActiveCamera), m_disp(displacement), m_camManager(ManagerProvider::getCameraManager())
{ }

void MoveActiveCameraCommand::execute()
{
    ((*m_camManager).*m_action)(m_disp);
}

SetActiveCameraDetailsCommand::SetActiveCameraDetailsCommand(const Point &pos, const Point &target, double fov) :
    m_action(&CameraManager::setActiveCameraDetails), m_pos(pos), m_target(target), m_fov(fov), m_camManager(ManagerProvider::getCameraManager())
{ }

void SetActiveCameraDetailsCommand::execute()
{
    ((*m_camManager).*m_action)(m_pos, m_target, m_fov);
}