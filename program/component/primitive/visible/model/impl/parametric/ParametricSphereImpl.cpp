#include "ParametricSphereImpl.h"
#include <cmath>

ParametricSphereImpl::ParametricSphereImpl(double radius, const Point& center,
                                           size_t slices, size_t stacks)
    : m_slices(slices), m_stacks(stacks)
{
    m_radius = radius;
    m_center = center;
    generateMesh();
}

std::shared_ptr<SphereImpl> ParametricSphereImpl::clone() const {
    auto cloned = std::make_shared<ParametricSphereImpl>(m_radius, m_center, m_slices, m_stacks);
    cloned->m_material = m_material;
    cloned->m_orbitRadius = m_orbitRadius; 
    cloned->m_orbitSpeed  = m_orbitSpeed;    
    cloned->m_orbitAngle  = m_orbitAngle;  
    cloned->m_baseCenter  = m_baseCenter;   
    cloned->m_vertices = m_vertices;
    cloned->m_edges = m_edges;
    return cloned;
}

double ParametricSphereImpl::getRadius() const { return m_radius; }
void ParametricSphereImpl::setRadius(double r) { m_radius = r; generateMesh(); }

Point ParametricSphereImpl::getCenter() const { return m_center; }
void ParametricSphereImpl::setCenter(const Point& c) {
    m_center = c;
    generateMesh();
}

void ParametricSphereImpl::setMaterial(const Material& m) { m_material = m; }
Material ParametricSphereImpl::getMaterial() const { return m_material; }

double ParametricSphereImpl::getOrbitRadius() const {
    return m_orbitRadius;
}

void ParametricSphereImpl::setOrbitRadius(double radius) {
    m_orbitRadius = radius;
    updatePosition();  
}

double ParametricSphereImpl::getOrbitSpeed() const {
    return m_orbitSpeed;
}

void ParametricSphereImpl::setOrbitSpeed(double speed) {
    m_orbitSpeed = speed;
}

double ParametricSphereImpl::getOrbitAngle() const {
    return m_orbitAngle;
}

void ParametricSphereImpl::setOrbitAngle(double angle) {
    m_orbitAngle = angle;
    updatePosition();  
}

Point ParametricSphereImpl::getBaseCenter() const {
    return m_baseCenter;
}

void ParametricSphereImpl::setBaseCenter(const Point& c) {
    m_baseCenter = c;
    updatePosition();
}

size_t ParametricSphereImpl::getSlices() const { return m_slices; }
size_t ParametricSphereImpl::getStacks() const { return m_stacks; }
void ParametricSphereImpl::setResolution(int s, int t) { m_slices = s; m_stacks = t; generateMesh(); }

const std::vector<Vertex>& ParametricSphereImpl::getVertices() { return m_vertices; }
const std::vector<Vertex>& ParametricSphereImpl::getVertices() const { return m_vertices; }

const std::vector<Edge>& ParametricSphereImpl::getEdges() { return m_edges; }
const std::vector<Edge>& ParametricSphereImpl::getEdges() const { return m_edges; }

void ParametricSphereImpl::generateMesh() {
    m_vertices.clear();
    m_edges.clear();

    for (size_t t = 0; t <= m_stacks; ++t) {
        double phi = M_PI * double(t) / double(m_stacks);
        double sinPhi = std::sin(phi);
        double cosPhi = std::cos(phi);

        for (size_t s = 0; s <= m_slices; ++s) {
            double theta = 2.0 * M_PI * double(s) / double(m_slices);
            double sinTheta = std::sin(theta);
            double cosTheta = std::cos(theta);

            double x = m_radius * sinTheta * sinPhi;
            double y = m_radius * cosPhi;
            double z = m_radius * cosTheta * sinPhi;

            m_vertices.emplace_back(m_center.getX() + x, m_center.getY() + y, m_center.getZ() + z);
        }
    }

    for (size_t t = 0; t < m_stacks; ++t) {
        for (size_t s = 0; s < m_slices; ++s) {
            size_t p0 = t * (m_slices + 1) + s;
            size_t p1 = p0 + 1;
            size_t p2 = p0 + (m_slices + 1);
            size_t p3 = p2 + 1;

            m_edges.emplace_back(p0, p2);
            m_edges.emplace_back(p0, p1);
        }
    }
}

void ParametricSphereImpl::updatePosition() {
    if (m_orbitRadius <= 0.0) return;
    double rad = m_orbitAngle * M_PI / 180.0;
    double newX = m_baseCenter.getX() + m_orbitRadius * std::cos(rad);
    double newZ = m_baseCenter.getZ() + m_orbitRadius * std::sin(rad);
    setCenter(Point(newX, m_baseCenter.getY(), newZ));
    generateMesh();
}

void ParametricSphereImpl::accept(std::shared_ptr<BaseVisitor> visitor) {
    if (visitor) visitor->visit(*this);
}