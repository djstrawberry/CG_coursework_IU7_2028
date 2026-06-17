#include "DrawManager.h"
#include "../../strategies/projection/creators/ProjectionStrategyCreator.h"
#include "../../strategies/conversion/creator/ConvertCoordsStrategyCreator.h"
#include "../../strategies/render/creators/RenderStrategyCreator.h"
#include "../../component/primitive/invisible/camera/impl/CameraImpl.h"
#include "../../visitors/creators/VisitorCreator.h"
#include "../ManagerProvider.h"
#include "../camera/CameraManager.h"     
#include "../scene/SceneManager.h"       

void DrawManager::setPainter(std::shared_ptr<BasePainter> painter)
{
    m_painter = std::move(painter);
}

void DrawManager::setCameraImpl(std::shared_ptr<CameraImpl> impl)
{
    m_cameraImpl = impl;
}

void DrawManager::setLightColor(float r, float g, float b, float intensity)
{
    m_lightColor[0] = r;
    m_lightColor[1] = g;
    m_lightColor[2] = b;
    m_lightColor[3] = intensity;
}

std::vector<float>  DrawManager::getLightColor() const noexcept { 
    return m_lightColor; 
}

void DrawManager::draw()
{
    if (!m_painter)
        return;

    m_painter->clear();

    auto cameraManager = ManagerProvider::getCameraManager();
    auto activeCam = cameraManager->getActiveCamera();
    if (!activeCam)
        return;

    auto projStrategy = DefaultProjectionStrategyCreator::create();
    auto convertStrategy = DefaultConvertCoordinatesStrategyCreator::create();
    auto renderStrategy = DefaultRenderStrategyCreator::create();

    auto sceneManager = ManagerProvider::getSceneManager();
    const Vec3<double> lightSourcePos = sceneManager->getPrimaryLightPosition();

    renderStrategy->beginScene();

    auto drawVisitor = DrawVisitorCreator::create(
        std::move(projStrategy),
        std::move(convertStrategy),
        renderStrategy,
        m_painter,
        m_cameraImpl,
        m_lightColor,
        lightSourcePos
    );

    sceneManager->accept(drawVisitor);
    renderStrategy->flushScene(m_painter);
}