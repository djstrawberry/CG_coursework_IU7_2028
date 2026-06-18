#pragma once

#include "../../../../../vector/Vec3.h"
#include "../../../../../materials/Material.h"
#include "../../../../../visitors/BaseVisitor.h"
#include <memory>
#include <vector>

class SphereImpl {
public:
    SphereImpl() = default;
    virtual ~SphereImpl() = default;

    virtual std::shared_ptr<SphereImpl> clone() const = 0;
    
    virtual double getRadius() const = 0;
    virtual void setRadius(double r) = 0;
    
    virtual Vec3<double> getCenter() const = 0;
    virtual void setCenter(const Vec3<double>& center) = 0;

    virtual void setMaterial(const Material& material) = 0;
    virtual Material getMaterial() const = 0;

    virtual size_t getSlices() const = 0;
    virtual size_t getStacks() const = 0;
    virtual void setResolution(int slices, int stacks) = 0;

    virtual const std::vector<Vec3<double>>& getVertices() = 0;
    virtual const std::vector<Vec3<double>>& getVertices() const = 0;
    virtual const std::vector<std::pair<size_t, size_t>>& getEdges() = 0;
    virtual const std::vector<std::pair<size_t, size_t>>& getEdges() const = 0;

    virtual void generateMesh() = 0;

    virtual void accept(std::shared_ptr<BaseVisitor> visitor)
    {
        if (visitor)
            visitor->visit(*this);
    }
};