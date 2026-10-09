#pragma once

#include "../BaseVisitor.h"
#include "../../../factories/draw/products/BasePainter.h"
#include "../../../strategies/projection/BaseProjectionStrategy.h"
#include "../../../strategies/conversion/BaseCoordinateConvertStrategy.h"
#include "../../../strategies/render/BaseRenderStrategy.h"
#include "../../../component/primitive/invisible/camera/impl/CameraImpl.h"
#include "../../../component/primitive/invisible/light/impl/LightImpl.h"
#include "../../../materials/Material.h"
#include "../../../vector/Vec3.h"
#include <memory>
#include <vector>

class DrawVisitor : public BaseVisitor
{
private:
    std::shared_ptr<BasePainter> m_painter;
    std::shared_ptr<CameraImpl> m_camera;
    std::shared_ptr<BaseProjectionStrategy> m_projStrategy;
    std::shared_ptr<BaseCoordinateConvertStrategy> m_convertStrategy;
    std::shared_ptr<BaseRenderStrategy> m_renderStrategy;
  
public:
    DrawVisitor() = delete;
    DrawVisitor(std::shared_ptr<BaseProjectionStrategy> projStrategy,
                std::shared_ptr<BaseCoordinateConvertStrategy> convertStrategy,
                std::shared_ptr<BaseRenderStrategy> renderStrategy,
                std::shared_ptr<BasePainter> painter,
                std::shared_ptr<CameraImpl> camera);
    ~DrawVisitor() override = default;

    void visit(CameraImpl& camera) const override;
    void visit(SphereImpl& sphere) const override;
    void visit(LightImpl& light) const override;
    void visit(ParametricSphereImpl& parametricSphere) const override;
    void visit(TessellatedSphereImpl& tessellatedSphere) const override;
};

