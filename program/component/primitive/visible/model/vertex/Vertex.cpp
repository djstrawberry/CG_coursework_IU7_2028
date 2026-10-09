#include "Vertex.h"

Vertex::Vertex(const Point& position) noexcept : m_position(position) {}
Vertex::Vertex(double x, double y, double z) noexcept : m_position(x, y, z) {}

const Point& Vertex::getPosition() const noexcept { return m_position; }
void Vertex::setPosition(const Point& position) noexcept { m_position = position; }

double Vertex::getX() const noexcept { return m_position.getX(); }
double Vertex::getY() const noexcept { return m_position.getY(); }
double Vertex::getZ() const noexcept { return m_position.getZ(); }

void Vertex::setX(double x) noexcept { m_position.setX(x); }
void Vertex::setY(double y) noexcept { m_position.setY(y); }
void Vertex::setZ(double z) noexcept { m_position.setZ(z); }

Vertex Vertex::operator+(const Vertex& other) const
{
    return Vertex(m_position + other.m_position);
}

Vertex Vertex::operator*(double scalar) const
{
    return Vertex(m_position * scalar);
}