#include "../BaseProjectionStrategy.h"

#include <vector>

class DefaultProjectionStrategy : public BaseProjectionStrategy
{
public:
    DefaultProjectionStrategy() = default;
    virtual ~DefaultProjectionStrategy() override = default;

    void project(std::shared_ptr<const SphereImpl> figure, std::shared_ptr<const CameraImpl> camera,
                 std::vector<Vec3<double>> &projected) override;
};
