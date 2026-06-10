#pragma once

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
