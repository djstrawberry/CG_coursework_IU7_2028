#include "ManagerProvider.h"
#include "camera/CameraManager.h"
#include "scene/SceneManager.h"
#include "draw/DrawManager.h"

std::shared_ptr<CameraManager> ManagerProvider::getCameraManager() {
    static auto cameraManager = std::make_shared<CameraManager>();
    return cameraManager;
}

std::shared_ptr<SceneManager> ManagerProvider::getSceneManager() {
    static auto sceneManager = std::make_shared<SceneManager>();
    return sceneManager;
}

std::shared_ptr<DrawManager> ManagerProvider::getDrawManager() {
    static auto drawManager = std::make_shared<DrawManager>();
    return drawManager;
}
