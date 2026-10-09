// Vertex.h
#pragma once
#include "../../../../../point/Point.h"

class Vertex 
{
private:
    Point m_position; 
public:
    Vertex() noexcept = default;
    
    explicit Vertex(const Point& position) noexcept;
    Vertex(double x, double y, double z) noexcept;

    const Point& getPosition() const noexcept;
    void setPosition(const Point& position) noexcept;

    double getX() const noexcept;
    double getY() const noexcept;
    double getZ() const noexcept;

    void setX(double x) noexcept;
    void setY(double y) noexcept;
    void setZ(double z) noexcept;

    Vertex operator+(const Vertex& other) const;
    Vertex operator*(double scalar) const;
};