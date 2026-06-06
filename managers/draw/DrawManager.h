#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include <memory>
#include <QPainter>

class DrawManager {
public:
    DrawManager();
    ~DrawManager() = default;

    void setLightColor(float r, float g, float b, float intensity);
    void draw(QPainter* painter, int width, int height);

private:
    float m_lightColor[4]; // R, G, B, Intensity
};

#endif // DRAW_MANAGER_H
