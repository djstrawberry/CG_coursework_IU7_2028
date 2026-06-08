#include "DrawVisitor.h"

DrawVisitor::DrawVisitor(std::shared_ptr<BaseProjectionStrategy> projStrategy,
                         std::shared_ptr<BaseCoordinateConvertStrategy> convertStrategy,
                         std::shared_ptr<BasePainter> painter,
                         std::shared_ptr<CameraImpl> camera)
    : m_painter(std::move(painter))
    , m_camera(std::move(camera))
    , m_projStrategy(std::move(projStrategy))
    , m_convertStrategy(std::move(convertStrategy))
{ }

void DrawVisitor::visit(std::shared_ptr<CameraImpl> camera) const
{
    (void)camera;
}

void DrawVisitor::visit(std::shared_ptr<SphereImpl> sphere) const
{
    if (!m_painter || !m_camera || !sphere || !m_projStrategy || !m_convertStrategy)
        return;
    
    size_t width = m_painter->getWidth();
    size_t height = m_painter->getHeight();
    
    std::vector<Vec3<double>> projected;
    m_projStrategy->project(sphere, m_camera, projected);
    m_convertStrategy->convertPoint(projected, width, height);
    
    if (!projected.empty())
    {
        Vec3<double> screenCenter = projected[0];
        double radius = sphere->getRadius();
        Material mat = sphere->getMaterial();
        
        m_painter->drawFilledCircle(
            screenCenter.getX(), screenCenter.getY(), radius,
            static_cast<int>(mat.r * 255),
            static_cast<int>(mat.g * 255),
            static_cast<int>(mat.b * 255),
            static_cast<int>(mat.a * 255)
        );
        
        m_painter->drawCircleOutline(
            screenCenter.getX(), screenCenter.getY(), radius,
            255, 255, 255
        );
    }
}