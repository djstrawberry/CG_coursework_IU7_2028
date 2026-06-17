#include "ManagerProvider.h"
#include "scene/SceneManager.h"
#include "camera/CameraManager.h"
#include "draw/DrawManager.h"
#include "../factories/sphere/SphereFactory.h"

std::shared_ptr<SceneManager> ManagerProvider::getSceneManager()
{
    static auto instance = std::make_shared<SceneManager>();
    static bool initialized = false;
    if (!initialized) {
        instance->setSphereFactory(
            std::make_shared<ParametricSphereFactory>(44, 44)
        );
        initialized = true;
    }
    return instance;
}

std::shared_ptr<CameraManager> ManagerProvider::getCameraManager()
{
    static auto instance = std::make_shared<CameraManager>();
    return instance;
}

std::shared_ptr<DrawManager> ManagerProvider::getDrawManager()
{
    static auto instance = std::make_shared<DrawManager>();
    return instance;
}