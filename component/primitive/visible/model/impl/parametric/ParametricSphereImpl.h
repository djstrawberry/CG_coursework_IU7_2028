#pragma once

#include "../SphereImpl.h"
#include <vector>

class ParametricSphereImpl : public SphereImpl {
public:
    ParametricSphereImpl(double radius, const Vec3& center, int slices = 16, int stacks = 16);
    ~ParametricSphereImpl() override = default;

    std::shared_ptr<SphereImpl> clone() const override;

    double getRadius() const override;
    void setRadius(double radius) override;

    Vec3 getCenter() const override;
    void setCenter(const Vec3& center) override;

    void setMaterial(const Material& material) override;
    Material getMaterial() const override;

    int getSlices() const override;
    int getStacks() const override;
    void setResolution(int slices, int stacks) override;

    const std::vector<Vec3>& getVertices() override;
    const std::vector<Vec3>& getVertices() const override;
    const std::vector<std::pair<size_t, size_t>>& getEdges() override;
    const std::vector<std::pair<size_t, size_t>>& getEdges() const override;

    void generateMesh() override;

private:
    double m_radius;
    Vec3 m_center;
    int m_slices;
    int m_stacks;
    Material m_material;

    std::vector<Vec3> m_vertices;
    std::vector<std::pair<size_t, size_t>> m_edges;
};