#include "CameraManager.h"

size_t CameraManager::addCamera(const std::shared_ptr<BaseCamera>& camera) {
    size_t id = m_cameraCounter++;
    m_cameras[id] = camera;
    if (m_cameras.size() == 1) {
        m_activeCameraId = id;
    }
    return id;
}

void CameraManager::setActiveCamera(size_t id) {
    if (m_cameras.find(id) != m_cameras.end()) {
        m_activeCameraId = id;
    }
}

std::shared_ptr<BaseCamera> CameraManager::getActiveCamera() const {
    auto it = m_cameras.find(m_activeCameraId);
    if (it != m_cameras.end()) {
        return it->second;
    }
    return nullptr;
}
