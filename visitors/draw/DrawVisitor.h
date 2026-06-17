#pragma once

#include "../BaseVisitor.h"
#include "../../../factories/draw/products/BasePainter.h"
#include "../../../strategies/projection/BaseProjectionStrategy.h"
#include "../../../strategies/conversion/BaseCoordinateConvertStrategy.h"
#include "../../../strategies/render/BaseRenderStrategy.h"
#include "../../../component/primitive/invisible/camera/impl/CameraImpl.h"
#include "../../../materials/Material.h"
#include "../../../vector/Vec3.h"
#include <memory>
#include <vector>

class DrawVisitor : public BaseVisitor
{
private:
    struct GlowPass {
        double x = 0.0;
        double y = 0.0;
        double radius = 0.0;
        int r = 0;
        int g = 0;
        int b = 0;
        float intensity = 0.0f;
    };

    struct TrianglePass {
        double x0 = 0.0;
        double y0 = 0.0;
        double x1 = 0.0;
        double y1 = 0.0;
        double x2 = 0.0;
        double y2 = 0.0;
        double depth = 0.0;
        int r = 0;
        int g = 0;
        int b = 0;
        int a = 255;
    };

    std::shared_ptr<BasePainter> m_painter;
    std::shared_ptr<CameraImpl> m_camera;
    std::shared_ptr<BaseProjectionStrategy> m_projStrategy;
    std::shared_ptr<BaseCoordinateConvertStrategy> m_convertStrategy;
    std::shared_ptr<BaseRenderStrategy> m_renderStrategy;
    std::vector<float> m_lightColor;
    Vec3<double> m_lightSourcePos;

    mutable std::vector<GlowPass> m_glowPasses;
    mutable std::vector<TrianglePass> m_trianglePasses;

    void computeLitColor(const Material& mat,
                         const Vec3<double>& normal,
                         const Vec3<double>& viewDir,
                         const Vec3<double>& lightDir,
                         int& r, int& g, int& b) const;

    void collectSphere(const SphereImpl& sphere) const;
    void renderGlowPasses() const;
    void renderTrianglePasses() const;
    void correctAspectRatio(std::vector<Vec3<double>>& projected, size_t width, size_t height) const;
    std::pair<Vec3<double>, double> computeScreenCenterAndRadius(
        const std::vector<Vec3<double>>& projected, double sphereRadius) const;
    void addGlowPass(const Vec3<double>& screenCenter, double screenRadius,
                     const Material& mat, const float* light) const;
    void processTriangle(const std::vector<Vec3<double>>& projected,
                         const std::vector<Vec3<double>>& vertices,
                         const Vec3<double>& center, const Vec3<double>& camPos,
                         const Material& mat, size_t i0, size_t i1, size_t i2) const;
    void processAllTriangles(const std::vector<Vec3<double>>& projected,
                             const std::vector<Vec3<double>>& vertices,
                             const Vec3<double>& center, const Vec3<double>& camPos,
                             const Material& mat, size_t slices, size_t stacks) const;

public:
    DrawVisitor() = delete;
    DrawVisitor(std::shared_ptr<BaseProjectionStrategy> projStrategy,
                std::shared_ptr<BaseCoordinateConvertStrategy> convertStrategy,
                std::shared_ptr<BaseRenderStrategy> renderStrategy,
                std::shared_ptr<BasePainter> painter,
                std::shared_ptr<CameraImpl> camera,
                std::vector<float> lightColor,
                const Vec3<double>& lightSourcePos);
    ~DrawVisitor() override = default;

    void beginScene() const;
    void flushScene() const;

    void visit(CameraImpl& camera) const override;
    void visit(SphereImpl& sphere) const override;
};
