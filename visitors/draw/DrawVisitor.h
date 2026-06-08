#pragma once

#include "../BaseVisitor.h"
#include "../../../factories/draw/products/BasePainter.h"
#include "../../../strategies/projection/BaseProjectionStrategy.h"
#include "../../../strategies/conversion/BaseCoordinateConvertStrategy.h"
#include "../../../component/primitive/invisible/camera/impl/CameraImpl.h"
#include <memory>

class DrawVisitor : public BaseVisitor
{
private:
    std::shared_ptr<BasePainter> m_painter;
    std::shared_ptr<CameraImpl> m_camera;
    std::shared_ptr<BaseProjectionStrategy> m_projStrategy;
    std::shared_ptr<BaseCoordinateConvertStrategy> m_convertStrategy;

public:
    DrawVisitor() = delete;
    DrawVisitor(std::shared_ptr<BaseProjectionStrategy> projStrategy,
                std::shared_ptr<BaseCoordinateConvertStrategy> convertStrategy,
                std::shared_ptr<BasePainter> painter,
                std::shared_ptr<CameraImpl> camera);
    ~DrawVisitor() override = default;

    void visit(std::shared_ptr<CameraImpl> camera) const override;
    void visit(std::shared_ptr<SphereImpl> sphere) const override;
};