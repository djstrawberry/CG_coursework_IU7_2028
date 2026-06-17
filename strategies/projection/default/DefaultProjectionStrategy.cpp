#include "DefaultProjectionStrategy.h"
#include <cmath>

bool projectPoint(const Vec3<double>& point,
                  const Vec3<double>& camPos,
                  const Vec3<double>& forward,
                  const Vec3<double>& right,
                  const Vec3<double>& up,
                  double scale,
                  Vec3<double>& out)
{
    Vec3<double> relative = point - camPos;
    double camZ = relative.dot(forward);
    if (camZ <= 0.01)
        return false;

    double camX = relative.dot(right);
    double camY = relative.dot(up);
    out.setX((camX / camZ) * scale);
    out.setY((camY / camZ) * scale);
    out.setZ(camZ);
    return true;
}

void DefaultProjectionStrategy::project(const SphereImpl& sphere,
                         const CameraImpl& camera, std::vector<Vec3<double>> &projected)
{
    projected.clear();

    Vec3<double> camPos = camera.getPosition();
    Vec3<double> camTarget = camera.getTarget();
    double fov = camera.getFov();

    Vec3<double> forward = (camTarget - camPos).normalized();
    Vec3<double> worldUp = Vec3<double>::up();
    Vec3<double> right = forward.cross(worldUp).normalized();
    if (right.length() < 1e-6)
        right = Vec3<double>::right();
    Vec3<double> up = right.cross(forward).normalized();

    double scale = 1.0 / (2.0 * std::tan(fov * M_PI / 360.0));

    const auto& vertices = sphere.getVertices();
    if (!vertices.empty()) {
        projected.reserve(vertices.size());
        for (const auto& vertex : vertices) {
            Vec3<double> point;
            if (projectPoint(vertex, camPos, forward, right, up, scale, point))
                projected.push_back(point);
            else
                projected.push_back({0.0, 0.0, -1.0});
        }
        return;
    }

    Vec3<double> center = sphere.getCenter();
    Vec3<double> point;
    if (projectPoint(center, camPos, forward, right, up, scale, point))
        projected.push_back(point);
}