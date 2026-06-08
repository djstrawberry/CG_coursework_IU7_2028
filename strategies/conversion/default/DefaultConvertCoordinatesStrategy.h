#pragma once

#include "../BaseCoordinateConvertStrategy.h"
#include "../../../vector/Vec3.h"

class DefaultConvertCoordinateStrategy : public BaseCoordinateConvertStrategy
{
public:
    DefaultConvertCoordinateStrategy() = default;
    virtual ~DefaultConvertCoordinateStrategy() override = default;

    void convertPoint(std::vector<Vec3<double>> &vertices, const size_t width, const size_t height) override;
};