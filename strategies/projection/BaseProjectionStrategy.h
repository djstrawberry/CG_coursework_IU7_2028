#pragma once

#include "../../component/primitive/invisible/camera/impl/CameraImpl.h"
#include "../../component/primitive/visible/model/impl/SphereImpl.h"
#include "../../vector/Vec3.h"

#include <memory>
#include <vector>

class BaseProjectionStrategy
{
public:
    BaseProjectionStrategy() = default;
    virtual ~BaseProjectionStrategy() = default;

    virtual void project(const SphereImpl& sphere,
                         const CameraImpl& camera, std::vector<Vec3<double>> &projected) = 0;
};
