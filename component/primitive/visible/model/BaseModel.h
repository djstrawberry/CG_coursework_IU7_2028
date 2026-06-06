#pragma once

#include "../VisibleObject.h"
#include "impl/SphereImpl.h"

class BaseModel : public VisibleObject {
public:
    BaseModel() = default;
    ~BaseModel() override = default;

    virtual std::shared_ptr<SphereImpl> getImpl() const = 0;
};
