#include "DefaultProjectionStrategy.h"
#include <cmath>

static bool projectPoint(const Point& point,
                         const Point& camPos,
                         const Point& forward,
                         const Point& right,
                         const Point& up,
                         double scale,
                         Point& out)
{
    Point relative = point - camPos;
    double camZ = relative.dot(forward);
    if (camZ <= 0.01)
        return false;

    double camX = relative.dot(right);
    double camY = relative.dot(up);
    out = Point((camX / camZ) * scale, (camY / camZ) * scale, camZ);
    return true;
}

void DefaultProjectionStrategy::project(const SphereImpl& sphere,
                         const CameraImpl& camera, std::vector<Point>& projected)
{
    projected.clear();

    Point camPos = camera.getPosition();
    Point camTarget = camera.getTarget();
    double fov = camera.getFov();

    Point forward = (camTarget - camPos).normalized();
    Point worldUp = Point::up();
    Point right = forward.cross(worldUp).normalized();
    if (right.length() < 1e-6)
        right = Point::right();
    Point up = right.cross(forward).normalized();

    double scale = 1.0 / (2.0 * std::tan(fov * M_PI / 360.0));

    const auto& vertices = sphere.getVertices();  
    if (!vertices.empty()) {
        projected.reserve(vertices.size());
        for (const auto& vertex : vertices) {
            Point point(vertex.getX(), vertex.getY(), vertex.getZ());
            if (projectPoint(point, camPos, forward, right, up, scale, point))
                projected.push_back(point);
            else
                projected.push_back(Point(0.0, 0.0, -1.0));
        }
        return;
    }

    Point center(sphere.getCenter().getX(), sphere.getCenter().getY(), sphere.getCenter().getZ());
    Point point;
    if (projectPoint(center, camPos, forward, right, up, scale, point))
        projected.push_back(point);
}