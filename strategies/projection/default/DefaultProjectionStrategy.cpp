#include "DefaultProjectionStrategy.h"
#include <cmath>

void DefaultProjectionStrategy::project(std::shared_ptr<const SphereImpl> sphere,
                                        std::shared_ptr<const CameraImpl> camera,
                                        std::vector<Vec3<double>>& projected)
{
    projected.clear();
    
    if (!sphere || !camera) return;
    
    Vec3<double> center = sphere->getCenter();
    double radius = sphere->getRadius();
    
    Vec3<double> camPos = camera->getPosition();
    Vec3<double> camTarget = camera->getTarget();
    double fov = camera->getFov();
    
    Vec3<double> relative = center - camPos;
    double distance = relative.length();
    
    Vec3<double> camForward = (camTarget - camPos).normalized();
    
    if (relative.dot(camForward) <= 0) return;
    
    double scale = 1.0 / (2.0 * std::tan(fov * M_PI / 360.0));
    
    double projX = (relative.getX() / distance) * scale / (relative.getZ() / distance);
    double projY = (relative.getY() / distance) * scale / (relative.getZ() / distance);
    double projZ = distance;
    
    projected.push_back({projX, projY, projZ});
}