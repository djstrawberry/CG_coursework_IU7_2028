#include "../BaseProjectionStrategy.h"

#include <vector>

class DefaultProjectionStrategy : public BaseProjectionStrategy
{
public:
    DefaultProjectionStrategy() = default;
    virtual ~DefaultProjectionStrategy() override = default;

    void project(const SphereImpl& sphere,
                         const CameraImpl& camera, std::vector<Vec3<double>> &projected) override;
};
