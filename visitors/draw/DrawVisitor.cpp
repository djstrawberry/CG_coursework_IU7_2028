#include "DrawVisitor.h"
#include "../../materials/Material.h"
#include "../../component/primitive/visible/model/celestial/CelestialBody.h"
#include "../../component/primitive/invisible/camera/CameraAdapter.h"
#include "../../component/composite/Composite.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <vector>

DrawVisitor::DrawVisitor(std::shared_ptr<BaseProjectionStrategy> projStrategy,
                std::shared_ptr<BaseCoordinateConvertStrategy> convertStrategy,
                std::shared_ptr<BaseRenderStrategy> renderStrategy,
                std::shared_ptr<BasePainter> painter,
                std::shared_ptr<CameraImpl> camera,
                std::vector<float> lightColor,
                const Vec3<double>& lightSourcePos)
    : m_painter(std::move(painter))
    , m_camera(std::move(camera))
    , m_projStrategy(std::move(projStrategy))
    , m_convertStrategy(std::move(convertStrategy))
    , m_renderStrategy(std::move(renderStrategy))
    , m_lightColor(lightColor)
    , m_lightSourcePos(lightSourcePos)
{ }

void DrawVisitor::visit(SphereImpl& sphere) const
{
    if (!m_painter || !m_camera || !m_renderStrategy) return;

    const size_t width = m_painter->getWidth();
    const size_t height = m_painter->getHeight();

    if (width == 0 || height == 0) return;
    
    std::vector<Vec3<double>> projected;
    m_projStrategy->project(sphere, *m_camera, projected);
    m_convertStrategy->convertPoint(projected, width, height);

    const float *light = m_lightColor.empty() ? nullptr : m_lightColor.data();
    
    m_renderStrategy->renderSphere(sphere, projected, m_camera, light, m_lightSourcePos, width, height);
}

void DrawVisitor::visit(CameraImpl& camera) const
{
    (void)camera;
}