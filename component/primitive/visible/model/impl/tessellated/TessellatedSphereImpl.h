#pragma once

#include "../SphereImpl.h"
#include <vector>
#include <map>

class TessellatedSphereImpl : public SphereImpl {
public:
    TessellatedSphereImpl(double radius, const Vec3<double>& center, size_t subdivisions = 2);
    ~TessellatedSphereImpl() override = default;

    std::shared_ptr<SphereImpl> clone() const override;

    double getRadius() const override;
    void setRadius(double r) override;

    Vec3<double> getCenter() const override;
    void setCenter(const Vec3<double>& c) override;

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
    void subdivideIcosahedron();
    void createBaseIcosahedron();
    void subdivideOnce();
    void normalizeToSphere();
    Vec3<double> normalizeVertex(const Vec3<double>& v);

    double m_radius;
    Vec3<double> m_center;
    size_t m_subdivisions;
    Material m_material;

    std::vector<Vec3<double>> m_vertices;
    std::vector<std::pair<size_t, size_t>> m_edges;
    
    std::map<std::pair<size_t, size_t>, size_t> m_midpointCache;
};