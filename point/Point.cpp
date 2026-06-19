#include "Point.h"
#include <cmath>
#include <ostream>

Point::Point() noexcept : m_x(0), m_y(0), m_z(0) {}

Point::Point(double x, double y, double z) noexcept
    : m_x(x), m_y(y), m_z(z) {}

double Point::getX() const noexcept { return m_x; }
double Point::getY() const noexcept { return m_y; }
double Point::getZ() const noexcept { return m_z; }

void Point::setX(double x) noexcept { m_x = x; }
void Point::setY(double y) noexcept { m_y = y; }
void Point::setZ(double z) noexcept { m_z = z; }

double Point::calcDistance(const Point &other) const noexcept
{
    double dx = m_x - other.m_x;
    double dy = m_y - other.m_y;
    double dz = m_z - other.m_z;
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

double Point::dot(const Point &other) const noexcept
{
    return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
}

Point Point::cross(const Point &other) const noexcept
{
    return Point(
        m_y * other.m_z - m_z * other.m_y,
        m_z * other.m_x - m_x * other.m_z,
        m_x * other.m_y - m_y * other.m_x
    );
}

double Point::length() const noexcept
{
    return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

Point Point::normalized() const noexcept
{
    double len = length();
    if (len < 1e-12)
        return Point(0, 0, 0);
    return Point(m_x / len, m_y / len, m_z / len);
}

Point Point::up() noexcept
{
    return Point(0, 1, 0);
}

Point Point::right() noexcept
{
    return Point(1, 0, 0);
}

bool Point::operator==(const Point &other) const noexcept
{
    const double eps = 1e-9;
    return std::abs(m_x - other.m_x) <= eps &&
           std::abs(m_y - other.m_y) <= eps &&
           std::abs(m_z - other.m_z) <= eps;
}

bool Point::equal(const Point &other) const noexcept { return *this == other; }
bool Point::operator!=(const Point &other) const noexcept { return !(*this == other); }
bool Point::notEqual(const Point &other) const noexcept { return *this != other; }

Point &Point::add(const Point &other) noexcept
{
    m_x += other.m_x;
    m_y += other.m_y;
    m_z += other.m_z;
    return *this;
}

Point &Point::operator+=(const Point &other) noexcept { return add(other); }

Point Point::make_sum(const Point &other) const
{
    return Point(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
}

Point Point::operator+(const Point &other) const { return make_sum(other); }

Point &Point::subtract(const Point &other) noexcept
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    m_z -= other.m_z;
    return *this;
}

Point &Point::operator-=(const Point &other) noexcept { return subtract(other); }

Point Point::make_diff(const Point &other) const
{
    return Point(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
}

Point Point::operator-(const Point &other) const { return make_diff(other); }

Point Point::operator*(double s) const {
    return Point(m_x * s, m_y * s, m_z * s);
}

Point Point::operator/(double s) const
{
    return Point(m_x / s, m_y / s, m_z / s);
}

std::ostream &operator<<(std::ostream &os, const Point &Point)
{
    os << "(" << Point.getX() << ", " << Point.getY() << ", " << Point.getZ() << ")";
    return os;
}