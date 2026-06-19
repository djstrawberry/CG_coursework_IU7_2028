#pragma once

#include "../BaseRenderStrategy.h"
#include "../../../point/Point.h"  
#include "../../../component/primitive/visible/model/vertex/Vertex.h"        
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
        int r0 = 0, g0 = 0, b0 = 0;
        int r1 = 0, g1 = 0, b1 = 0;
        int r2 = 0, g2 = 0, b2 = 0;
        int a = 255;
    };

    mutable std::vector<GlowPass> m_glowPasses;
    mutable std::vector<TrianglePass> m_trianglePasses;

    Point m_lightPos{0, 0, 0};                     
    std::vector<float> m_lightColor{1.0f, 0.9f, 0.4f, 1.0f};

    int clampChannel(double value) const;

    bool isFrontFacing(const Vertex& v0, const Vertex& v1,
                              const Vertex& v2, const Point& camPos,
                              const Point& sphereCenter);

    void computeLitColor(const Material& mat, const Point& normal,
                         const Point& viewDir, const Point& lightDir,
                         int& r, int& g, int& b, const float* light) const;

    void correctAspectRatio(std::vector<Point>& projected, size_t w, size_t h) const;

    std::pair<Point, double> computeScreenCenterAndRadius(
        const std::vector<Point>& projected, double sphereRadius,
        double fov, size_t height) const;

    void addGlowPass(const Point& c, double r,
                 const Material& mat, const float* light,
                 double intensityFactor = 1.0);

    void processTriangle(const std::vector<Point>& projected,
                         const std::vector<Vertex>& vertices,
                         const Point& center, const Point& camPos,
                         const Material& mat, size_t i0, size_t i1, size_t i2,
                         const float* light, const Point& lightSourcePos);

    void processAllTriangles(const std::vector<Point>& projected,
                             const std::vector<Vertex>& vertices,
                             const Point& center, const Point& camPos,
                             const Material& mat, size_t slices, size_t stacks,
                             const float* light, const Point& lightSourcePos);

    void renderGlowPasses(std::shared_ptr<BasePainter> painter) const;
    void renderTrianglePasses(std::shared_ptr<BasePainter> painter) const;

public:
    DefaultRenderStrategy() = default;
    ~DefaultRenderStrategy() override = default;

    void setLight(const Point& pos, const std::vector<float>& color) override;
    void beginScene() override;
    void renderSphere(const SphereImpl& sphere,
                      std::vector<Point> projected,
                      const std::shared_ptr<CameraImpl>& camera,
                      size_t screenWidth,
                      size_t screenHeight) override;
    void flushScene(std::shared_ptr<BasePainter> painter) override;
};