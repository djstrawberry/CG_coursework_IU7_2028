#ifndef VEC3_H
#define VEC3_H

#include <cmath>

template <typename T>
class Vec3 {
public:
    T x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& other) const { return Vec3(x + other.x, y + other.y, z + other.z); }
    Vec3 operator-(const Vec3& other) const { return Vec3(x - other.x, y - other.y, z - other.z); }
    Vec3 operator*(T scalar) const { return Vec3(x * scalar, y * scalar, z * scalar); }
    Vec3 operator/(T scalar) const { return Vec3(x / scalar, y / scalar, z / scalar); }

    T dot(const Vec3& other) const { return x * other.x + y * other.y + z * other.z; }
    
    Vec3 cross(const Vec3& other) const {
        return Vec3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    T length() const { return std::sqrt(x * x + y * y + z * z); }
    
    Vec3 normalized() const {
        T len = length();
        if (len == 0) return Vec3();
        return *this / len;
    }
};

#endif // VEC3_H
