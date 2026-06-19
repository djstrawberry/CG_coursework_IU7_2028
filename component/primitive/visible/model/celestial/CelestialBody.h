#pragma once

#include "../BaseModel.h"
#include "../impl/SphereImpl.h"
#include "../../../../../point/Point.h"
#include <string>

class CelestialBody final: public BaseModel {
public:
    CelestialBody() = delete;
    explicit CelestialBody(std::shared_ptr<SphereImpl> impl);
    ~CelestialBody() override = default;

    void accept(std::shared_ptr<BaseVisitor> visitor) override;
    std::shared_ptr<BaseObject> clone() const override;
    Point getCenter() const noexcept override;
};