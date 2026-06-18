#pragma once

#include <memory>
#include <vector>
#include "../../../vector/Vec3.h"

class SphereImpl;
class CameraImpl;
class BasePainter;

class BaseRenderStrategy
{
public:
    virtual ~BaseRenderStrategy() = default;

    virtual void setLight(const Vec3<double>& pos, const std::vector<float>& color) = 0;
    virtual void beginScene() = 0;

    virtual void renderSphere(const SphereImpl& sphere,
                              std::vector<Vec3<double>> projectedVertices,
                              const std::shared_ptr<CameraImpl>& camera,
                              size_t screenWidth,
                              size_t screenHeight) = 0;

    virtual void flushScene(std::shared_ptr<BasePainter> painter) = 0;
};