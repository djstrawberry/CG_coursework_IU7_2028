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

    renderStrategy->beginScene();

    auto drawVisitor = DrawVisitorCreator::create(
        std::move(projStrategy),
        std::move(convertStrategy),
        renderStrategy,
        m_painter,
        m_cameraImpl
    );

    sceneManager->accept(drawVisitor);
    renderStrategy->flushScene(m_painter);
}