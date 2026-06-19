#pragma once

#include "../SphereImpl.h"
#include "../../vertex/Vertex.h"
#include "../../edge/Edge.h"
#include "../../../../../../point/Point.h"
#include <vector>

class ParametricSphereImpl : public SphereImpl {
public:
    ParametricSphereImpl(double radius, const Point& center, size_t slices = 16, size_t stacks = 16);
    ~ParametricSphereImpl() override = default;

    std::shared_ptr<SphereImpl> clone() const override;

    double getRadius() const override;
    void setRadius(double radius) override;

    Point getCenter() const override;
    void setCenter(const Point& center) override;

    void setMaterial(const Material& material) override;
    Material getMaterial() const override;

    double getOrbitRadius() const override;
    void setOrbitRadius(double r) override;

    double getOrbitSpeed() const override;
    void setOrbitSpeed(double s) override;

    double getOrbitAngle() const override;
    void setOrbitAngle(double a) override;

    Point getBaseCenter() const override;
    void setBaseCenter(const Point& c) override;

    size_t getSlices() const override;
    size_t getStacks() const override;
    void setResolution(int slices, int stacks) override;

    const std::vector<Vertex>& getVertices() override;
    const std::vector<Vertex>& getVertices() const override;
    const std::vector<Edge>& getEdges() override;
    const std::vector<Edge>& getEdges() const override;

    void generateMesh() override;

    void updatePosition() override;

    void accept(std::shared_ptr<BaseVisitor> visitor) override;

private:
    size_t m_slices;
    size_t m_stacks;

    std::vector<Vertex> m_vertices;
    std::vector<Edge> m_edges;
};