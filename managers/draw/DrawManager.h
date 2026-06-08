#pragma once

#include <memory>
#include <QPainter>

class BasePainter;
class BaseVisitor;

class DrawManager
{
private:
    std::shared_ptr<BasePainter> m_painter;
    float m_lightColor[4] = {1.0f, 0.9f, 0.4f, 1.0f};

public:
    DrawManager() = default;
    ~DrawManager() = default;

    void setPainter(std::shared_ptr<BasePainter> painter);
    void setLightColor(float r, float g, float b, float intensity);
    const float* getLightColor() const noexcept { return m_lightColor; }
    void draw();
};