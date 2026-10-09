#pragma once

#include <iostream>   

class Point
{
private:
    double m_x, m_y, m_z;

public:
    Point() noexcept;
    Point(double x, double y, double z) noexcept;

    Point(const Point &other) = default;
    Point(Point &&other) = default;
    Point &operator=(const Point &other) = default;
    Point &operator=(Point &&other) = default;
    ~Point() = default;

    double getX() const noexcept;
    double getY() const noexcept;
    double getZ() const noexcept;

    void setX(double x) noexcept;
    void setY(double y) noexcept;
    void setZ(double z) noexcept;

    double calcDistance(const Point &other) const noexcept;

    double dot(const Point &other) const noexcept;
    Point cross(const Point &other) const noexcept;
    double length() const noexcept;
    Point normalized() const noexcept;

    static Point up() noexcept;
    static Point right() noexcept;

    bool operator==(const Point &other) const noexcept;
    bool equal(const Point &other) const noexcept;
    bool operator!=(const Point &other) const noexcept;
    bool notEqual(const Point &other) const noexcept;

    Point &add(const Point &other) noexcept;
    Point &operator+=(const Point &other) noexcept;
    Point make_sum(const Point &other) const;
    Point operator+(const Point &other) const;

    Point &subtract(const Point &other) noexcept;
    Point &operator-=(const Point &other) noexcept;
    Point make_diff(const Point &other) const;
    Point operator-(const Point &other) const;
    Point operator*(double s) const;
    Point operator/(double s) const;
};

std::ostream &operator<<(std::ostream &os, const Point &point);