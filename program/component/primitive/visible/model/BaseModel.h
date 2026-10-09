#pragma once

#include "../VisibleObject.h"
#include "impl/SphereImpl.h"

class BaseModel : public VisibleObject {
public:
    BaseModel() = default;
    ~BaseModel() override = default;
protected:
    std::shared_ptr<SphereImpl> m_impl;
};
