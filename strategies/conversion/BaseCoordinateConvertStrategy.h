#pragma once

#include "../../vector/Vec3.h"

#include <vector>

class BaseCoordinateConvertStrategy
{
public:
    BaseCoordinateConvertStrategy() = default;
    virtual ~BaseCoordinateConvertStrategy() = default;

    virtual void convertPoint(std::vector<Vec3<double>> &vertices, const size_t width, const size_t height) = 0;
};
