#pragma once

#include "../../component/primitive/visible/model/impl/SphereImpl.h"
#include "../../component/primitive/visible/model/impl/parametric/ParametricSphereImpl.h"
#include "../../component/primitive/visible/model/impl/tessellated/TessellatedSphereImpl.h"
#include "../../vector/Vec3.h"
#include <memory>

class SphereFactory {
public:
    virtual ~SphereFactory() = default;
    virtual std::shared_ptr<SphereImpl> createSphere(double radius, const Vec3<double>& center) = 0;
};

class ParametricSphereFactory : public SphereFactory {
    size_t m_slices, m_stacks;
public:
    ParametricSphereFactory(size_t slices = 64, size_t stacks = 64)
        : m_slices(slices), m_stacks(stacks) {}
    std::shared_ptr<SphereImpl> createSphere(double radius, const Vec3<double>& center) override {
        return std::make_shared<ParametricSphereImpl>(radius, center, m_slices, m_stacks);
    }
};

class TessellatedSphereFactory : public SphereFactory {
    size_t m_subdivisions;
public:
    TessellatedSphereFactory(size_t subdiv = 3) : m_subdivisions(subdiv) {}
    std::shared_ptr<SphereImpl> createSphere(double radius, const Vec3<double>& center) override {
        return std::make_shared<TessellatedSphereImpl>(radius, center, m_subdivisions);
    }
};