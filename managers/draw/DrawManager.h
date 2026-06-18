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
    std::shared_ptr<CameraImpl> m_cameraImpl;

public:
    DrawManager() = default;
    ~DrawManager() = default;

    void setCameraImpl(std::shared_ptr<CameraImpl> impl);
    void setPainter(std::shared_ptr<BasePainter> painter);
    void draw();
};