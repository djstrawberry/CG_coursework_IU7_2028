#pragma once

#include "../VisibleObject.h"
#include "impl/SphereImpl.h"

class BaseModel : public VisibleObject {
public:
    BaseModel(std::shared_ptr<SphereImpl> impl) : m_impl(std::move(impl)) {}
    ~BaseModel() override = default;

    virtual std::shared_ptr<SphereImpl> getImpl() const { return m_impl; };
protected:
    std::shared_ptr<SphereImpl> m_impl;
};
