#pragma once

#include "../SphereImpl.h"
#include <vector>

class ParametricSphereImpl : public SphereImpl {
public:
    ParametricSphereImpl(double radius, const Vec3<double>& center, size_t slices = 16, size_t stacks = 16);
    ~ParametricSphereImpl() override = default;

    std::shared_ptr<SphereImpl> clone() const override;

    double getRadius() const override;
    void setRadius(double radius) override;

    Vec3<double> getCenter() const override;
    void setCenter(const Vec3<double>& center) override;

    void setMaterial(const Material& material) override;
    Material getMaterial() const override;

    size_t getSlices() const override;
    size_t getStacks() const override;
    void setResolution(int slices, int stacks) override;

    const std::vector<Vec3<double>>& getVertices() override;
    const std::vector<Vec3<double>>& getVertices() const override;
    const std::vector<std::pair<size_t, size_t>>& getEdges() override;
    const std::vector<std::pair<size_t, size_t>>& getEdges() const override;

    void generateMesh() override;

private:
    double m_radius;
    Vec3<double> m_center;
    size_t m_slices;
    size_t m_stacks;
    Material m_material;

    std::vector<Vec3<double>> m_vertices;
    std::vector<std::pair<size_t, size_t>> m_edges;
};