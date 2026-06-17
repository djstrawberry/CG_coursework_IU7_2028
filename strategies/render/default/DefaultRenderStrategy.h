#pragma once

#include "../BaseRenderStrategy.h"
#include "../../../vector/Vec3.h"
#include "../../../materials/Material.h"
#include "../../../factories/draw/products/BasePainter.h"
#include <memory>
#include <vector>

class DefaultRenderStrategy : public BaseRenderStrategy
{
private:
    struct GlowPass {
        double x = 0.0, y = 0.0, radius = 0.0;
        int r = 0, g = 0, b = 0;
        float intensity = 0.0f;
    };

    struct TrianglePass {
        double x0 = 0.0, y0 = 0.0, x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
        double depth = 0.0;
        int r = 0, g = 0, b = 0, a = 255; 
    };

    mutable std::vector<GlowPass> m_glowPasses;
    mutable std::vector<TrianglePass> m_trianglePasses;

    int clampChannel(double value) const;
    bool isFrontFacing(const Vec3<double>& v0, const Vec3<double>& v1,
                              const Vec3<double>& v2, const Vec3<double>& camPos,
                              const Vec3<double>& sphereCenter);

    void computeLitColor(const Material& mat, const Vec3<double>& normal,
                         const Vec3<double>& viewDir, const Vec3<double>& lightDir,
                         int& r, int& g, int& b, const float* light) const;

    void correctAspectRatio(std::vector<Vec3<double>>& projected, size_t w, size_t h) const;

    std::pair<Vec3<double>, double> computeScreenCenterAndRadius(
        const std::vector<Vec3<double>>& projected, double sphereRadius,
        double fov, size_t height) const;

    void addGlowPass(const Vec3<double>& center, double radius,
                     const Material& mat, const float* light);

    void processTriangle(const std::vector<Vec3<double>>& projected,
                         const std::vector<Vec3<double>>& vertices,
                         const Vec3<double>& center, const Vec3<double>& camPos,
                         const Material& mat, size_t i0, size_t i1, size_t i2,
                         const float* light, const Vec3<double>& lightSourcePos);

    void processAllTriangles(const std::vector<Vec3<double>>& projected,
                             const std::vector<Vec3<double>>& vertices,
                             const Vec3<double>& center, const Vec3<double>& camPos,
                             const Material& mat, size_t slices, size_t stacks,
                             const float* light, const Vec3<double>& lightSourcePos);

    void renderGlowPasses(std::shared_ptr<BasePainter> painter) const;
    void renderTrianglePasses(std::shared_ptr<BasePainter> painter) const;

public:
    DefaultRenderStrategy() = default;
    ~DefaultRenderStrategy() override = default;

    void beginScene() override;
    void renderSphere(const SphereImpl& sphere,
                      std::vector<Vec3<double>> projected,
                      const std::shared_ptr<CameraImpl>& camera,
                      const float* lightColor,
                      const Vec3<double>& lightSourcePos,
                      size_t screenWidth,
                      size_t screenHeight) override;
    void flushScene(std::shared_ptr<BasePainter> painter) override;
};