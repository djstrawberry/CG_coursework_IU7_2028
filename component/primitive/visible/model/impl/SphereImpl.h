#pragma once

#include "../../../../../vector/Vec3.h"
#include "../../materials/Material.h"
#include <memory>
#include <vector>

class SphereImpl {
public:
    SphereImpl() = default;
    virtual ~SphereImpl() = default;

    virtual std::shared_ptr<SphereImpl> clone() const = 0;
    
    virtual double getRadius() const = 0;
    virtual void setRadius(double r) = 0;
    
    virtual Vec3 getCenter() const = 0;
    virtual void setCenter(const Vec3& center) = 0;

    virtual void setMaterial(const Material& material) = 0;
    virtual Material getMaterial() const = 0;

    virtual int getSlices() const = 0;
    virtual int getStacks() const = 0;
    virtual void setResolution(int slices, int stacks) = 0;

    virtual const std::vector<Vec3>& getVertices() = 0;
    virtual const std::vector<Vec3>& getVertices() const = 0;
    virtual const std::vector<std::pair<size_t, size_t>>& getEdges() = 0;
    virtual const std::vector<std::pair<size_t, size_t>>& getEdges() const = 0;

    virtual void generateMesh() = 0;
};