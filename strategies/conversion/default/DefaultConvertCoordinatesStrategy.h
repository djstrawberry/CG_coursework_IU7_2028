#pragma once

#include "../BaseCoordinateConvertStrategy.h"
#include "../../../vector/Vec3.h"

class DefaultConvertCoordinatesStrategy : public BaseCoordinateConvertStrategy
{
public:
    DefaultConvertCoordinatesStrategy() = default;
    virtual ~DefaultConvertCoordinatesStrategy() override = default;

    void convertPoint(std::vector<Vec3<double>> &vertices, const size_t width, const size_t height) override;
};