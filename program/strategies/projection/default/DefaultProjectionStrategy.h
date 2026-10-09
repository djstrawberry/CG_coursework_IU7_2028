#include "../BaseProjectionStrategy.h"
#include "../../../point/Point.h"

#include <vector>

class DefaultProjectionStrategy : public BaseProjectionStrategy
{
public:
    DefaultProjectionStrategy() = default;
    virtual ~DefaultProjectionStrategy() override = default;

    void project(const SphereImpl& sphere,
                         const CameraImpl& camera, std::vector<Point> &projected) override;
};
