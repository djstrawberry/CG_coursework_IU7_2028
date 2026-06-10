#pragma once

#include <array>
#include <memory>
#include <QPainter>

class BasePainter;
class BaseVisitor;

class DrawManager
{
private:
    std::shared_ptr<BasePainter> m_painter;
    std::vector<float> m_lightColor = {1.0f, 0.9f, 0.4f, 1.0f};

public:
    DrawManager() = default;
    ~DrawManager() = default;

    void setPainter(std::shared_ptr<BasePainter> painter);
    void setLightColor(float r, float g, float b, float intensity);
    std::vector<float> getLightColor() const noexcept;
    void draw();
};