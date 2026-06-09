#include "DrawVisitor.h"
#include "../../materials/Material.h"
#include "../../component/primitive/visible/model/celestial/CelestialBody.h"
#include "../../component/primitive/invisible/camera/CameraAdapter.h"
#include "../../component/composite/Composite.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <vector>

constexpr float kDefaultLight[4] = {1.0f, 0.9f, 0.4f, 1.0f};

int clampChannel(double value)
{
    return static_cast<int>(std::clamp(value, 0.0, 255.0));
}

bool isFrontFacing(const Vec3<double>& v0,
                   const Vec3<double>& v1,
                   const Vec3<double>& v2,
                   const Vec3<double>& camPos,
                   const Vec3<double>& sphereCenter)
{
    const Vec3<double> triCenter = (v0 + v1 + v2) / 3.0;
    const Vec3<double> normal = (triCenter - sphereCenter).normalized();
    return normal.dot(camPos - triCenter) > 0.0;
}

DrawVisitor::DrawVisitor(std::shared_ptr<BaseProjectionStrategy> projStrategy,
                         std::shared_ptr<BaseCoordinateConvertStrategy> convertStrategy,
                         std::shared_ptr<BasePainter> painter,
                         std::shared_ptr<CameraImpl> camera,
                         std::vector<float> lightColor,
                         const Vec3<double>& lightSourcePos)
    : m_painter(std::move(painter))
    , m_camera(std::move(camera))
    , m_projStrategy(std::move(projStrategy))
    , m_convertStrategy(std::move(convertStrategy))
    , m_lightColor(lightColor)
    , m_lightSourcePos(lightSourcePos)
{ }

void DrawVisitor::beginScene() const
{
    m_glowPasses.clear();
    m_trianglePasses.clear();
}

void DrawVisitor::flushScene() const
{
    if (!m_painter) return;

    renderGlowPasses();
    renderTrianglePasses();
}

void DrawVisitor::renderGlowPasses() const
{
    for (const auto& glow : m_glowPasses) {
        m_painter->drawGlow(glow.x, glow.y, glow.radius, glow.r, glow.g, glow.b, glow.intensity);
    }
}

void DrawVisitor::renderTrianglePasses() const
{
    std::vector<TrianglePass> sorted = m_trianglePasses;
    std::sort(sorted.begin(), sorted.end(),
              [](const TrianglePass& a, const TrianglePass& b) { return a.depth > b.depth; });

    for (const auto& t : sorted) {
        m_painter->drawFilledTriangle(t.x0, t.y0, t.x1, t.y1, t.x2, t.y2, t.r, t.g, t.b, t.a);
    }
}

void DrawVisitor::computeLitColor(const Material& mat,
                                  const Vec3<double>& normal,
                                  const Vec3<double>& viewDir,
                                  const Vec3<double>& lightDir,
                                  int& r, int& g, int& b) const
{
    const float* light = m_lightColor.data();
    const double lr = light[0], lg = light[1], lb = light[2], intensity = light[3];

    const double nDotL = std::max(0.0, normal.dot(lightDir));
    const Vec3<double> reflect = normal * (2.0 * nDotL) - lightDir;
    const double rDotV = std::max(0.0, reflect.normalized().dot(viewDir));
    const double spec = mat.specular * std::pow(rDotV, mat.shininess / 10.0);

    const double emissiveTerm = mat.luminous
        ? (0.12 + mat.ambient * 0.45 + mat.diffuse * 0.35) * intensity
        : 0.0;
    const double shading = mat.ambient + mat.diffuse * nDotL + spec;

    r = clampChannel((mat.r * lr * shading + mat.r * lr * emissiveTerm) * 255.0);
    g = clampChannel((mat.g * lg * shading + mat.g * lg * emissiveTerm) * 255.0);
    b = clampChannel((mat.b * lb * shading + mat.b * lb * emissiveTerm) * 255.0);
}

void DrawVisitor::correctAspectRatio(std::vector<Vec3<double>>& projected,
                                     size_t width, size_t height) const
{
    double aspectRatio = static_cast<double>(width) / static_cast<double>(height);

    if (aspectRatio > 1.0) {
        double offsetX = width * (1.0 - 1.0 / aspectRatio) / 2.0;
        for (auto& p : projected) {
            p = Vec3<double>(p.getX() / aspectRatio + offsetX, p.getY(), p.getZ());
        }
    } else {
        double offsetY = height * (1.0 - aspectRatio) / 2.0;
        for (auto& p : projected) {
            p = Vec3<double>(p.getX(), p.getY() * aspectRatio + offsetY, p.getZ());
        }
    }
}

std::pair<Vec3<double>, double> DrawVisitor::computeScreenCenterAndRadius(
    const std::vector<Vec3<double>>& projected, double sphereRadius) const
{
    double sumX = 0.0, sumY = 0.0;
    size_t visibleCount = 0;

    for (const auto& p : projected) {
        if (p.getZ() <= 0.0) continue;
        sumX += p.getX();
        sumY += p.getY();
        ++visibleCount;
    }

    if (visibleCount == 0) return {{0, 0, 0}, 0.0};

    const Vec3<double> center(sumX / visibleCount, sumY / visibleCount, 0.0);

    double radius = 0.0;
    for (const auto& p : projected) {
        if (p.getZ() <= 0.0) continue;
        double dx = p.getX() - center.getX();
        double dy = p.getY() - center.getY();
        radius = std::max(radius, std::sqrt(dx * dx + dy * dy));
    }

    if (radius < 1e-3 && !projected.empty()) {
        double distance = projected[0].getZ();
        double fov = m_camera->getFov();
        double scale = 1.0 / (2.0 * std::tan(fov * M_PI / 360.0));
        radius = (sphereRadius / distance) * scale * (m_painter->getHeight() / 2.0);
    }

    return {center, radius};
}

void DrawVisitor::addGlowPass(const Vec3<double>& screenCenter, double screenRadius,
                              const Material& mat, const float* light) const
{
    if (!mat.luminous) return;

    const double glowStrength = 0.65 + mat.ambient * 0.25 + mat.diffuse * 0.2;
    GlowPass glow;
    glow.x = screenCenter.getX();
    glow.y = screenCenter.getY();
    glow.radius = screenRadius;
    glow.r = clampChannel(mat.r * light[0] * 255.0);
    glow.g = clampChannel(mat.g * light[1] * 255.0);
    glow.b = clampChannel(mat.b * light[2] * 255.0);
    glow.intensity = static_cast<float>(light[3] * glowStrength);
    m_glowPasses.push_back(glow);
}

void DrawVisitor::processTriangle(const std::vector<Vec3<double>>& projected,
                                  const std::vector<Vec3<double>>& vertices,
                                  const Vec3<double>& center, const Vec3<double>& camPos,
                                  const Material& mat,
                                  size_t i0, size_t i1, size_t i2) const
{
    if (i0 >= projected.size() || i1 >= projected.size() || i2 >= projected.size()) return;
    if (projected[i0].getZ() <= 0.0 || projected[i1].getZ() <= 0.0 || projected[i2].getZ() <= 0.0) return;
    if (!isFrontFacing(vertices[i0], vertices[i1], vertices[i2], camPos, center)) return;

    Vec3<double> n0 = (vertices[i0] - center).normalized();
    Vec3<double> n1 = (vertices[i1] - center).normalized();
    Vec3<double> n2 = (vertices[i2] - center).normalized();

    Vec3<double> v0 = (camPos - vertices[i0]).normalized();
    Vec3<double> v1 = (camPos - vertices[i1]).normalized();
    Vec3<double> v2 = (camPos - vertices[i2]).normalized();

    Vec3<double> l0, l1, l2;
    if (mat.luminous) {
        Vec3<double> camDir = (camPos - center).normalized();
        l0 = l1 = l2 = camDir;
    } else {
        l0 = (m_lightSourcePos - vertices[i0]).normalized();
        l1 = (m_lightSourcePos - vertices[i1]).normalized();
        l2 = (m_lightSourcePos - vertices[i2]).normalized();
    }

    int r0, g0, b0, r1, g1, b1, r2, g2, b2;
    computeLitColor(mat, n0, v0, l0, r0, g0, b0);
    computeLitColor(mat, n1, v1, l1, r1, g1, b1);
    computeLitColor(mat, n2, v2, l2, r2, g2, b2);

    TrianglePass pass;
    pass.x0 = projected[i0].getX(); pass.y0 = projected[i0].getY();
    pass.x1 = projected[i1].getX(); pass.y1 = projected[i1].getY();
    pass.x2 = projected[i2].getX(); pass.y2 = projected[i2].getY();
    pass.depth = (projected[i0].getZ() + projected[i1].getZ() + projected[i2].getZ()) / 3.0;
    pass.r = (r0 + r1 + r2) / 3;
    pass.g = (g0 + g1 + g2) / 3;
    pass.b = (b0 + b1 + b2) / 3;
    pass.a = 255;
    m_trianglePasses.push_back(pass);
}

void DrawVisitor::processAllTriangles(const std::vector<Vec3<double>>& projected,
                                      const std::vector<Vec3<double>>& vertices,
                                      const Vec3<double>& center, const Vec3<double>& camPos,
                                      const Material& mat, size_t slices, size_t stacks) const
{
    for (size_t t = 0; t < stacks; ++t) {
        for (size_t s = 0; s < slices; ++s) {
            size_t p0 = t * (slices + 1) + s;
            size_t p1 = p0 + 1;
            size_t p2 = p0 + (slices + 1);
            size_t p3 = p2 + 1;
            processTriangle(projected, vertices, center, camPos, mat, p0, p1, p2);
            processTriangle(projected, vertices, center, camPos, mat, p1, p3, p2);
        }
    }
}

void DrawVisitor::collectSphere(const std::shared_ptr<SphereImpl>& sphere) const
{
    const size_t width = m_painter->getWidth();
    const size_t height = m_painter->getHeight();

    const Material mat = sphere->getMaterial();
    const Vec3<double> center = sphere->getCenter();
    const Vec3<double> camPos = m_camera->getPosition();
    const float* light = m_lightColor.data();

    std::vector<Vec3<double>> projected;
    m_projStrategy->project(sphere, m_camera, projected);
    if (projected.empty()) return;

    m_convertStrategy->convertPoint(projected, width, height);
    correctAspectRatio(projected, width, height);

    const auto& vertices = sphere->getVertices();
    if (vertices.empty() || projected.size() != vertices.size()) return;

    auto [screenCenter, screenRadius] = computeScreenCenterAndRadius(projected, sphere->getRadius());
    if (screenRadius == 0.0) return;

    addGlowPass(screenCenter, screenRadius, mat, light);
    processAllTriangles(projected, vertices, center, camPos, mat, sphere->getSlices(), sphere->getStacks());
}

void DrawVisitor::visit(const CelestialBody& body) const
{
    auto sphere = body.getImpl();
    if (!sphere || !m_painter || !m_camera || !m_projStrategy || !m_convertStrategy) return;
    if (m_painter->getWidth() == 0 || m_painter->getHeight() == 0) return;

    collectSphere(sphere);
}

void DrawVisitor::visit(const CameraAdapter& camera) const
{
    (void)camera;
}

void DrawVisitor::visit(const Composite& composite) const
{
    (void)composite;
}