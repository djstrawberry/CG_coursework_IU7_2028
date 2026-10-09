#include "TessellatedSphereImpl.h"
#include <cmath>
#include <map>
#include <array>

TessellatedSphereImpl::TessellatedSphereImpl(double radius, const Point& center, size_t subdivisions)
    : m_subdivisions(subdivisions)
{
    m_radius = radius;
    m_center = center;
    createBaseIcosahedron();
    for (size_t i = 0; i < m_subdivisions; ++i) {
        subdivideOnce();
    }
    normalizeToSphere();
}

std::shared_ptr<SphereImpl> TessellatedSphereImpl::clone() const {
    auto cloned = std::make_shared<TessellatedSphereImpl>(m_radius, m_center, m_subdivisions);
    cloned->m_material = m_material;
    cloned->m_vertices = m_vertices;
    cloned->m_edges = m_edges;
    cloned->m_orbitRadius = m_orbitRadius;
    cloned->m_orbitSpeed  = m_orbitSpeed;
    cloned->m_orbitAngle  = m_orbitAngle;
    cloned->m_baseCenter  = m_baseCenter;
    return cloned;
}

void TessellatedSphereImpl::createBaseIcosahedron() {
    const double t = (1.0 + std::sqrt(5.0)) / 2.0;

    std::array<Point, 12> baseVerts = {{
        {-1,  t,  0}, {1,  t,  0}, {-1, -t,  0}, {1, -t,  0},
        {0, -1,  t}, {0,  1,  t}, {0, -1, -t}, {0,  1, -t},
        {t,  0, -1}, {t,  0,  1}, {-t,  0, -1}, {-t,  0,  1}
    }};

    for (const auto& v : baseVerts) {
        Point normalized = v.normalized();
        Point result = normalized * m_radius + m_center;
        m_vertices.emplace_back(result.getX(), result.getY(), result.getZ());
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
            if (e.getStart() == a && e.getEnd() == b) return;
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
    std::vector<Vertex> newVertices = m_vertices;
    std::vector<Edge> newEdges;
    std::map<std::pair<size_t, size_t>, size_t> midpointCache;

    auto getMidpoint = [&](size_t a, size_t b) -> size_t {
        if (a > b) std::swap(a, b);
        auto key = std::make_pair(a, b);
        auto it = midpointCache.find(key);
        if (it != midpointCache.end()) {
            return it->second;
        }

        Vertex mid = (m_vertices[a] + m_vertices[b]) * 0.5;
        size_t newIdx = newVertices.size();
        newVertices.push_back(mid);
        midpointCache[key] = newIdx;
        return newIdx;
    };

    for (const auto& edge : m_edges) {
        size_t a = edge.getStart();
        size_t b = edge.getEnd();
        size_t mid = getMidpoint(a, b);

        newEdges.emplace_back(a, mid);
        newEdges.emplace_back(mid, b);
    }

    m_vertices = std::move(newVertices);
    m_edges = std::move(newEdges);
}

void TessellatedSphereImpl::normalizeToSphere() {
    for (auto& vertex : m_vertices) {
        Point dir(vertex.getX() - m_center.getX(),
                  vertex.getY() - m_center.getY(),
                  vertex.getZ() - m_center.getZ());
        dir = dir.normalized();
        vertex = Vertex(m_center.getX() + dir.getX() * m_radius,
                        m_center.getY() + dir.getY() * m_radius,
                        m_center.getZ() + dir.getZ() * m_radius);
    }
}

double TessellatedSphereImpl::getRadius() const { return m_radius; }
void TessellatedSphereImpl::setRadius(double r) { m_radius = r; generateMesh(); }

Point TessellatedSphereImpl::getCenter() const { return m_center; }

void TessellatedSphereImpl::setCenter(const Point& c) {
    Point offset = c - m_center;
    m_center = c;
    for (auto& v : m_vertices) {
        v.setX(v.getX() + offset.getX());
        v.setY(v.getY() + offset.getY());
        v.setZ(v.getZ() + offset.getZ());
    }
}

void TessellatedSphereImpl::setMaterial(const Material& material) { m_material = material; }
Material TessellatedSphereImpl::getMaterial() const { return m_material; }

double TessellatedSphereImpl::getOrbitRadius() const { return m_orbitRadius; }
void TessellatedSphereImpl::setOrbitRadius(double radius) { m_orbitRadius = radius; updatePosition(); }

double TessellatedSphereImpl::getOrbitSpeed() const { return m_orbitSpeed; }
void TessellatedSphereImpl::setOrbitSpeed(double speed) { m_orbitSpeed = speed; }

double TessellatedSphereImpl::getOrbitAngle() const { return m_orbitAngle; }
void TessellatedSphereImpl::setOrbitAngle(double angle) { m_orbitAngle = angle; updatePosition(); }

size_t TessellatedSphereImpl::getSlices() const { return static_cast<size_t>(1 << (m_subdivisions + 1)); }
size_t TessellatedSphereImpl::getStacks() const { return static_cast<size_t>(1 << m_subdivisions); }
void TessellatedSphereImpl::setResolution(int slices, int stacks) {
    m_subdivisions = std::max(0, (slices + stacks) / 32);
    generateMesh();
}

Point TessellatedSphereImpl::getBaseCenter() const { return m_baseCenter; }
void TessellatedSphereImpl::setBaseCenter(const Point& c) { m_baseCenter = c; updatePosition(); }

void TessellatedSphereImpl::updatePosition() {
    if (m_orbitRadius <= 0.0) return;
    double rad = m_orbitAngle * M_PI / 180.0;
    double newX = m_baseCenter.getX() + m_orbitRadius * std::cos(rad);
    double newZ = m_baseCenter.getZ() + m_orbitRadius * std::sin(rad);
    setCenter(Point(newX, m_baseCenter.getY(), newZ));
    generateMesh();
}

const std::vector<Vertex>& TessellatedSphereImpl::getVertices() { return m_vertices; }
const std::vector<Vertex>& TessellatedSphereImpl::getVertices() const { return m_vertices; }
const std::vector<Edge>& TessellatedSphereImpl::getEdges() { return m_edges; }
const std::vector<Edge>& TessellatedSphereImpl::getEdges() const { return m_edges; }

void TessellatedSphereImpl::generateMesh() {
    m_vertices.clear();
    m_edges.clear();
    createBaseIcosahedron();
    for (size_t i = 0; i < m_subdivisions; ++i) {
        subdivideOnce();
    }
    normalizeToSphere();
}

void TessellatedSphereImpl::accept(std::shared_ptr<BaseVisitor> visitor)
{
    if (visitor) visitor->visit(*this);
}