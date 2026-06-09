#include "DrawVisitor.h"
#include "../../materials/Material.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <vector>

namespace {

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
    // Истинная нормаль сферы направлена от центра планеты наружу
    const Vec3<double> normal = (triCenter - sphereCenter).normalized();
    // Проверяем, смотрит ли полигон на камеру
    return normal.dot(camPos - triCenter) > 0.0;
}

} // namespace

DrawVisitor::DrawVisitor(std::shared_ptr<BaseProjectionStrategy> projStrategy,
                         std::shared_ptr<BaseCoordinateConvertStrategy> convertStrategy,
                         std::shared_ptr<BasePainter> painter,
                         std::shared_ptr<CameraImpl> camera,
                         const float* lightColor,
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
    if (!m_painter)
        return;

    for (const auto& glow : m_glowPasses) {
        m_painter->drawGlow(glow.x, glow.y, glow.radius, glow.r, glow.g, glow.b, glow.intensity);
    }

    std::vector<TrianglePass> sortedTriangles = m_trianglePasses;
    std::sort(sortedTriangles.begin(), sortedTriangles.end(),
              [](const TrianglePass& a, const TrianglePass& b) { return a.depth > b.depth; });

    for (const auto& triangle : sortedTriangles) {
        m_painter->drawFilledTriangle(
            triangle.x0, triangle.y0,
            triangle.x1, triangle.y1,
            triangle.x2, triangle.y2,
            triangle.r, triangle.g, triangle.b, triangle.a
        );
    }
}

void DrawVisitor::computeLitColor(const Material& mat,
                                  const Vec3<double>& normal,
                                  const Vec3<double>& viewDir,
                                  const Vec3<double>& lightDir,
                                  int& r, int& g, int& b) const
{
    const float* light = m_lightColor ? m_lightColor : kDefaultLight;
    const double lr = light[0];
    const double lg = light[1];
    const double lb = light[2];
    const double intensity = light[3];

    const double nDotL = std::max(0.0, normal.dot(lightDir));
    Vec3<double> reflect = normal * (2.0 * nDotL) - lightDir;
    const double rDotV = std::max(0.0, reflect.normalized().dot(viewDir));
    const double spec = mat.specular * std::pow(rDotV, mat.shininess / 10.0);

    const double ambientTerm = mat.ambient;
    const double diffuseTerm = mat.diffuse * nDotL;
    const double emissiveTerm = mat.luminous
        ? (0.12 + mat.ambient * 0.45 + mat.diffuse * 0.35) * intensity
        : 0.0;

    const double shading = ambientTerm + diffuseTerm + spec;
    r = clampChannel((mat.r * lr * shading + mat.r * lr * emissiveTerm) * 255.0);
    g = clampChannel((mat.g * lg * shading + mat.g * lg * emissiveTerm) * 255.0);
    b = clampChannel((mat.b * lb * shading + mat.b * lb * emissiveTerm) * 255.0);
}

void DrawVisitor::visit(std::shared_ptr<CameraImpl> camera) const
{
    (void)camera;
}

void DrawVisitor::collectSphere(const std::shared_ptr<SphereImpl>& sphere) const
{
    const size_t width = m_painter->getWidth();
    const size_t height = m_painter->getHeight();

    const Material mat = sphere->getMaterial();
    const Vec3<double> center = sphere->getCenter();
    const Vec3<double> camPos = m_camera->getPosition();
    const float* light = m_lightColor ? m_lightColor : kDefaultLight;

    std::vector<Vec3<double>> projected;
    m_projStrategy->project(sphere, m_camera, projected);
    if (projected.empty())
        return;

    m_convertStrategy->convertPoint(projected, width, height);

    double aspectRatio = static_cast<double>(width) / static_cast<double>(height);

    if (aspectRatio > 1.0) {
        // Окно шире — сжимаем по X и центрируем:
        double offsetX = width * (1.0 - 1.0 / aspectRatio) / 2.0;
        for (auto& p : projected) {
            p = Vec3<double>(p.getX() / aspectRatio + offsetX, p.getY(), p.getZ());
        }
    } else {
        // Окно выше — сжимаем по Y и центрируем:
        double offsetY = height * (1.0 - aspectRatio) / 2.0;
        for (auto& p : projected) {
            p = Vec3<double>(p.getX(), p.getY() * aspectRatio + offsetY, p.getZ());
        }
    }

    const auto& vertices = sphere->getVertices();
    if (vertices.empty() || projected.size() != vertices.size())
        return;

    double sumX = 0.0;
    double sumY = 0.0;
    size_t visibleCount = 0;
    for (size_t i = 0; i < projected.size(); ++i) {
        if (projected[i].getZ() <= 0.0)
            continue;
        sumX += projected[i].getX();
        sumY += projected[i].getY();
        ++visibleCount;
    }
    if (visibleCount == 0)
        return;
    
    const Vec3<double> screenCenter(sumX / static_cast<double>(visibleCount),
                                    sumY / static_cast<double>(visibleCount), 0.0);
    double screenRadius = 0.0;
    for (size_t i = 0; i < projected.size(); ++i) {
        if (projected[i].getZ() <= 0.0)
            continue;
        const double dx = projected[i].getX() - screenCenter.getX();
        const double dy = projected[i].getY() - screenCenter.getY();
        screenRadius = std::max(screenRadius, std::sqrt(dx * dx + dy * dy));
    }
    if (screenRadius < 1e-3) {
        const double distance = projected[0].getZ();
        const double fov = m_camera->getFov();
        const double scale = 1.0 / (2.0 * std::tan(fov * M_PI / 360.0));
        screenRadius = (sphere->getRadius() / distance) * scale * (height / 2.0);
    }

    if (mat.luminous) {
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

    const size_t slices = sphere->getSlices();
    const size_t stacks = sphere->getStacks();
    auto tryAddTriangle = [&](size_t i0, size_t i1, size_t i2) {
        if (i0 >= projected.size() || i1 >= projected.size() || i2 >= projected.size())
            return;
        if (projected[i0].getZ() <= 0.0 || projected[i1].getZ() <= 0.0 || projected[i2].getZ() <= 0.0)
            return;
        
        // 1. Передаём глобальные координаты камеры и центр планеты
        if (!isFrontFacing(vertices[i0], vertices[i1], vertices[i2], camPos, center))
            return;

        // 2. Идеальные нормали от центра к вершине
        Vec3<double> n0 = (vertices[i0] - center).normalized();
        Vec3<double> n1 = (vertices[i1] - center).normalized();
        Vec3<double> n2 = (vertices[i2] - center).normalized();

        // 3. Векторы взгляда в мировых координатах
        Vec3<double> v0 = (camPos - vertices[i0]).normalized();
        Vec3<double> v1 = (camPos - vertices[i1]).normalized();
        Vec3<double> v2 = (camPos - vertices[i2]).normalized();

        // 4. Векторы освещения в мировых координатах
        Vec3<double> l0, l1, l2;
        if (mat.luminous) {
            Vec3<double> camDir = (camPos - center).normalized();
            l0 = l1 = l2 = camDir;
        } else {
            l0 = (m_lightSourcePos - vertices[i0]).normalized();
            l1 = (m_lightSourcePos - vertices[i1]).normalized();
            l2 = (m_lightSourcePos - vertices[i2]).normalized();
        }
        int r0 = 0, g0 = 0, b0 = 0;
        int r1 = 0, g1 = 0, b1 = 0;
        int r2 = 0, g2 = 0, b2 = 0;
        computeLitColor(mat, n0, v0, l0, r0, g0, b0);
        computeLitColor(mat, n1, v1, l1, r1, g1, b1);
        computeLitColor(mat, n2, v2, l2, r2, g2, b2);

        TrianglePass pass;
        pass.x0 = projected[i0].getX();
        pass.y0 = projected[i0].getY();
        pass.x1 = projected[i1].getX();
        pass.y1 = projected[i1].getY();
        pass.x2 = projected[i2].getX();
        pass.y2 = projected[i2].getY();
        pass.depth = (projected[i0].getZ() + projected[i1].getZ() + projected[i2].getZ()) / 3.0;
        pass.r = (r0 + r1 + r2) / 3;
        pass.g = (g0 + g1 + g2) / 3;
        pass.b = (b0 + b1 + b2) / 3;
        pass.a = 255;
        m_trianglePasses.push_back(pass);
    };

    for (size_t t = 0; t < stacks; ++t) {
        for (size_t s = 0; s < slices; ++s) {
            const size_t p0 = t * (slices + 1) + s;
            const size_t p1 = p0 + 1;
            const size_t p2 = p0 + (slices + 1);
            const size_t p3 = p2 + 1;
            tryAddTriangle(p0, p1, p2);
            tryAddTriangle(p1, p3, p2);
        }
    }
}

void DrawVisitor::visit(std::shared_ptr<SphereImpl> sphere) const
{
    if (!m_painter || !m_camera || !sphere || !m_projStrategy || !m_convertStrategy)
        return;

    if (m_painter->getWidth() == 0 || m_painter->getHeight() == 0)
        return;

    collectSphere(sphere);
}
