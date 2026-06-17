#pragma once

#include <array>
#include <memory>
#include <QPainter>

class BasePainter;
class BaseVisitor;
class CameraImpl;

class DrawManager
{
private:
    std::shared_ptr<BasePainter> m_painter;
    std::vector<float> m_lightColor = {1.0f, 0.9f, 0.4f, 1.0f};
    std::shared_ptr<CameraImpl> m_cameraImpl;

public:
    DrawManager() = default;
    ~DrawManager() = default;

    void setCameraImpl(std::shared_ptr<CameraImpl> impl);
    void setPainter(std::shared_ptr<BasePainter> painter);
    void setLightColor(float r, float g, float b, float intensity);
    std::vector<float> getLightColor() const noexcept;
    void draw();
};