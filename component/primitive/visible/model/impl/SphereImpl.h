#pragma once

#include "../../../../../point/Point.h"
#include "../../../../../materials/Material.h"
#include "../../../../../visitors/BaseVisitor.h"
#include "../vertex/Vertex.h"
#include "../edge/Edge.h"
#include <memory>
#include <vector>

class SphereImpl {
protected:
    Material m_material;
    double m_radius;
    Point m_center;
    double m_orbitRadius = 0.0;
    double m_orbitSpeed = 0.0;
    double m_orbitAngle = 0.0;
    Point m_baseCenter;
public:
    SphereImpl() = default;
    virtual ~SphereImpl() = default;

    virtual std::shared_ptr<SphereImpl> clone() const = 0;
    
    virtual double getRadius() const = 0;
    virtual void setRadius(double r) = 0;
    
    virtual Point getCenter() const = 0;
    virtual void setCenter(const Point& center) = 0;

    virtual void setMaterial(const Material& material) = 0;
    virtual Material getMaterial() const = 0;

    virtual double getOrbitRadius() const = 0;
    virtual void setOrbitRadius(double r) = 0;

    virtual double getOrbitSpeed() const = 0;
    virtual void setOrbitSpeed(double s) = 0;

    virtual double getOrbitAngle() const = 0;
    virtual void setOrbitAngle(double a) = 0;

    virtual Point getBaseCenter() const = 0;
    virtual void setBaseCenter(const Point& c) = 0;

    virtual size_t getSlices() const = 0;
    virtual size_t getStacks() const = 0;
    virtual void setResolution(int slices, int stacks) = 0;

    virtual const std::vector<Vertex>& getVertices() = 0;
    virtual const std::vector<Vertex>& getVertices() const = 0;
    virtual const std::vector<Edge>& getEdges() = 0;
    virtual const std::vector<Edge>& getEdges() const = 0;

    virtual void generateMesh() = 0;

    virtual void updatePosition() = 0;

    virtual void accept(std::shared_ptr<BaseVisitor> visitor)
    {
        if (visitor)
            visitor->visit(*this);
    }
};