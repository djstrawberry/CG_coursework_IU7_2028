#pragma once

#include "../../component/primitive/invisible/camera/BaseCamera.h"
#include <map>
#include <memory>

class CameraManager {
public:
    CameraManager() = default;
    ~CameraManager() = default;

    size_t addCamera(const std::shared_ptr<BaseCamera>& camera);
    void setActiveCamera(size_t id);
    std::shared_ptr<BaseCamera> getActiveCamera() const;
    void moveActiveCamera(const Vec3<double> &displacement);
    void setActiveCameraDetails(const Vec3<double> &pos, const Vec3<double> &target, double fov);

private:
    std::map<size_t, std::shared_ptr<BaseCamera>> m_cameras;
    size_t m_activeCameraId = 0;
    size_t m_cameraCounter = 0;
};
