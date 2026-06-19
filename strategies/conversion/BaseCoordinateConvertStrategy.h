#pragma once

#include "../../vector/Vec3.h"
#include "../../point/Point.h"

#include <vector>

class BaseCoordinateConvertStrategy
{
public:
    BaseCoordinateConvertStrategy() = default;
    virtual ~BaseCoordinateConvertStrategy() = default;

    virtual void convertPoint(std::vector<Point> &points, const size_t width, const size_t height) = 0;
};
