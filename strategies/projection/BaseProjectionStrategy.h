#pragma once

#include "../../component/primitive/invisible/camera/impl/CameraImpl.h"
#include "../../component/primitive/visible/model/impl/SphereImpl.h"
#include "../../point/Point.h"
#include "../../vector/Vec3.h"

#include <memory>
#include <vector>

class BaseProjectionStrategy
{
public:
    BaseProjectionStrategy() = default;
    virtual ~BaseProjectionStrategy() = default;

    virtual void project(const SphereImpl& sphere,
                         const CameraImpl& camera, std::vector<Point> &projected) = 0;
};
