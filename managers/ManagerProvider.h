#ifndef MANAGER_PROVIDER_H
#define MANAGER_PROVIDER_H

#include <memory>

class CameraManager;
class SceneManager;
class DrawManager;

class ManagerProvider {
public:
    static std::shared_ptr<CameraManager> getCameraManager();
    static std::shared_ptr<SceneManager> getSceneManager();
    static std::shared_ptr<DrawManager> getDrawManager();
};

#endif // MANAGER_PROVIDER_H
