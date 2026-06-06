#include "DrawManager.h"
#include "../ManagerProvider.h"
#include "../camera/CameraManager.h"
#include "../scene/SceneManager.h"
#include "../../visitors/draw/DrawVisitor.h"

DrawManager::DrawManager() {
    // Soft off-yellow central star light color preset
    m_lightColor[0] = 1.0f;
    m_lightColor[1] = 0.9f;
    m_lightColor[2] = 0.4f;
    m_lightColor[3] = 1.0f; // Intensity scale factor
}

void DrawManager::setLightColor(float r, float g, float b, float intensity) {
    m_lightColor[0] = r;
    m_lightColor[1] = g;
    m_lightColor[2] = b;
    m_lightColor[3] = intensity;
}

void DrawManager::draw(QPainter* painter, int width, int height) {
    auto cameraManager = ManagerProvider::getCameraManager();
    auto sceneManager = ManagerProvider::getSceneManager();

    auto activeCamera = cameraManager->getActiveCamera();
    if (!activeCamera) return;

    auto drawVisitor = std::make_shared<DrawVisitor>(painter, activeCamera, width, height, m_lightColor);
    sceneManager->acceptVisitor(drawVisitor);
}
