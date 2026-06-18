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

public:
    DrawManager() = default;
    ~DrawManager() = default;

    void setPainter(std::shared_ptr<BasePainter> painter);
    void draw();
};