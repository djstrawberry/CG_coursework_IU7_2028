#include "CameraCommand.h"
#include "../../managers/ManagerProvider.h"
#include "../../managers/camera/CameraManager.h"

MoveActiveCameraCommand::MoveActiveCameraCommand(const Vec3<double>& displacement)
    : m_disp(displacement) {}

void MoveActiveCameraCommand::execute() {
    auto activeCamera = ManagerProvider::getCameraManager()->getActiveCamera();
    if (activeCamera) {
        Vec3<double> oldPos = activeCamera->getPosition();
        activeCamera->setPosition(oldPos + m_disp);
    }
}

SetActiveCameraDetailsCommand::SetActiveCameraDetailsCommand(const Vec3<double>& pos, const Vec3<double>& target, double fov)
    : m_pos(pos), m_target(target), m_fov(fov) {}

void SetActiveCameraDetailsCommand::execute() {
    auto activeCamera = ManagerProvider::getCameraManager()->getActiveCamera();
    if (activeCamera) {
        activeCamera->setPosition(m_pos);
        activeCamera->setTarget(m_target);
        activeCamera->setFov(m_fov);
    }
}
