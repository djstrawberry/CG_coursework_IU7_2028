#include "TessellatedSphereImpl.h"
#include <cmath>
#include <map>
#include <array>

TessellatedSphereImpl::TessellatedSphereImpl(double radius, const Vec3& center, int subdivisions)
    : m_radius(radius), m_center(center), m_subdivisions(subdivisions) {
    createBaseIcosahedron();
    for (int i = 0; i < m_subdivisions; ++i) {
        subdivideOnce();
    }
    normalizeToSphere();
}

std::shared_ptr<SphereImpl> TessellatedSphereImpl::clone() {
    auto cloned = std::make_shared<TessellatedSphereImpl>(m_radius, m_center, m_subdivisions);
    cloned->m_material = m_material;
    cloned->m_vertices = m_vertices;
    cloned->m_edges = m_edges;
    return cloned;
}

void TessellatedSphereImpl::createBaseIcosahedron() {
    const double t = (1.0 + std::sqrt(5.0)) / 2.0;  // Tak nado
    
    std::array<Vec3, 12> baseVerts = {{
        {-1,  t,  0}, {1,  t,  0}, {-1, -t,  0}, {1, -t,  0},
        {0, -1,  t}, {0,  1,  t}, {0, -1, -t}, {0,  1, -t},
        {t,  0, -1}, {t,  0,  1}, {-t,  0, -1}, {-t,  0,  1}
    }};
    
    for (const auto& v : baseVerts) {
        Vec3 normalized = v.normalized();
        m_vertices.push_back(normalized * m_radius + m_center);
    }
    
    std::array<std::array<size_t, 3>, 20> faces = {{
        {0, 11, 5}, {0, 5, 1}, {0, 1, 7}, {0, 7, 10}, {0, 10, 11},
        {1, 5, 9}, {5, 11, 4}, {11, 10, 2}, {10, 7, 6}, {7, 1, 8},
        {3, 9, 4}, {3, 4, 2}, {3, 2, 6}, {3, 6, 8}, {3, 8, 9},
        {4, 9, 5}, {2, 4, 11}, {6, 2, 10}, {8, 6, 7}, {9, 8, 1}
    }};
    
    auto addEdge = [this](size_t a, size_t b) {
        if (a > b) std::swap(a, b);
        for (const auto& e : m_edges) {
            if (e.first == a && e.second == b) return;
        }
        m_edges.emplace_back(a, b);
    };
    
    for (const auto& face : faces) {
        addEdge(face[0], face[1]);
        addEdge(face[1], face[2]);
        addEdge(face[2], face[0]);
    }
}

void TessellatedSphereImpl::subdivideOnce() {
    std::vector<Vec3> newVertices = m_vertices;
    std::vector<std::pair<size_t, size_t>> newEdges;
    std::map<std::pair<size_t, size_t>, size_t> midpointCache;
    
    auto getMidpoint = [&](size_t a, size_t b) -> size_t {
        if (a > b) std::swap(a, b);
        auto key = std::make_pair(a, b);
        auto it = midpointCache.find(key);
        if (it != midpointCache.end()) {
            return it->second;
        }
        
        Vec3 mid = (m_vertices[a] + m_vertices[b]) * 0.5;
        size_t newIdx = newVertices.size();
        newVertices.push_back(mid);
        midpointCache[key] = newIdx;
        return newIdx;
    };
    
    for (const auto& edge : m_edges) {
        size_t a = edge.first;
        size_t b = edge.second;
        size_t mid = getMidpoint(a, b);
        
        newEdges.emplace_back(a, mid);
        newEdges.emplace_back(mid, b);
    }
    
    m_vertices = std::move(newVertices);
    m_edges = std::move(newEdges);
}

void TessellatedSphereImpl::normalizeToSphere() {
    for (auto& vertex : m_vertices) {
        Vec3 direction = vertex - m_center;
        direction.normalize();
        vertex = m_center + direction * m_radius;
    }
}

double TessellatedSphereImpl::getRadius() const {
    return m_radius;
}

void TessellatedSphereImpl::setRadius(double r) {
    m_radius = r;
    generateMesh(); 
}

Vec3 TessellatedSphereImpl::getCenter() const {
    return m_center;
}

void TessellatedSphereImpl::setCenter(const Vec3& c) {
    m_center = c;
    Vec3 offset = c - m_center;
    for (auto& v : m_vertices) {
        v = v + offset;
    }
    m_center = c;
}

void TessellatedSphereImpl::setMaterial(const Material& material) {
    m_material = material;
}

Material TessellatedSphereImpl::getMaterial() const {
    return m_material;
}

size_t TessellatedSphereImpl::getSlices() const {
    return 0;  
}

size_t TessellatedSphereImpl::getStacks() const {
    return 0;
}

void TessellatedSphereImpl::setResolution(int slices, int stacks) {
    m_subdivisions = std::max(0, (slices + stacks) / 32);
    generateMesh();
}

const std::vector<Vec3>& TessellatedSphereImpl::getVertices() {
    return m_vertices;
}

const std::vector<Vec3>& TessellatedSphereImpl::getVertices() const {
    return m_vertices;
}

const std::vector<std::pair<size_t, size_t>>& TessellatedSphereImpl::getEdges() {
    return m_edges;
}

const std::vector<std::pair<size_t, size_t>>& TessellatedSphereImpl::getEdges() const {
    return m_edges;
}

void TessellatedSphereImpl::generateMesh() {
    createBaseIcosahedron();
    for (size_t i = 0; i < m_subdivisions; ++i) {
        subdivideOnce();
    }
    normalizeToSphere();
}