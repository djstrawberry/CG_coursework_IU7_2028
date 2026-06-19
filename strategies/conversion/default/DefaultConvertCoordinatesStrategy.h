#pragma once

#include "../BaseCoordinateConvertStrategy.h"
#include "../../../point/Point.h"
#include "../../../vector/Vec3.h"

class DefaultConvertCoordinatesStrategy : public BaseCoordinateConvertStrategy
{
public:
    DefaultConvertCoordinatesStrategy() = default;
    virtual ~DefaultConvertCoordinatesStrategy() override = default;

    void convertPoint(std::vector<Point> &points, const size_t width, const size_t height) override;
};