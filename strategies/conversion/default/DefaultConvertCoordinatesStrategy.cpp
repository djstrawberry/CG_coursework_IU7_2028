#include "DefaultConvertCoordinatesStrategy.h"

void DefaultConvertCoordinatesStrategy::convertPoint(std::vector<Point> &points, const size_t width,
                                                    const size_t height)
{
    size_t centerX = static_cast<size_t>(width / 2.0);
    size_t centerY = static_cast<size_t>(height / 2.0);

    for (auto &point : points)
    {
        point.setX(point.getX() * centerX + centerX);
        point.setY(-point.getY() * centerY + centerY);
    }
}
