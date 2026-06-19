#include "DefaultRenderStrategy.h"
#include "../../../component/primitive/visible/model/impl/SphereImpl.h"
#include "../../../component/primitive/invisible/camera/impl/CameraImpl.h"
#include <algorithm>
#include <cmath>

int DefaultRenderStrategy::clampChannel(double value) const
{
    return static_cast<int>(std::clamp(value, 0.0, 255.0));
}

bool DefaultRenderStrategy::isFrontFacing(const Vertex& v0, const Vertex& v1,
                                           const Vertex& v2, const Point& camPos,
                                           const Point& sphereCenter)
{
    Point p0(v0.getX(), v0.getY(), v0.getZ());
    Point p1(v1.getX(), v1.getY(), v1.getZ());
    Point p2(v2.getX(), v2.getY(), v2.getZ());

    Point triCenter = (p0 + p1 + p2) / 3.0;
    Point normal = (triCenter - sphereCenter).normalized();
    return normal.dot(camPos - triCenter) > 0.0;
}

void DefaultRenderStrategy::renderSphere(const SphereImpl& sphere,
                      std::vector<Point> projected,          
                      const std::shared_ptr<CameraImpl>& camera,
                      size_t screenWidth,
                      size_t screenHeight)
{
    if (projected.empty()) return;

    correctAspectRatio(projected, screenWidth, screenHeight);

    const Material mat = sphere.getMaterial();
    Point center(sphere.getCenter().getX(), sphere.getCenter().getY(), sphere.getCenter().getZ());
    Point camPos = camera->getPosition();   

    const auto& vertices = sphere.getVertices();   
    if (vertices.empty() || projected.size() != vertices.size()) return;

    const double fov = camera->getFov();
    const float* lightColor = m_lightColor.data();

    auto [screenCenter, screenRadius] = computeScreenCenterAndRadius(projected, sphere.getRadius(), fov, screenHeight);
    if (screenRadius == 0) return;

    if (mat.isStar()) {
        addGlowPass(screenCenter, screenRadius * 1.5, mat, lightColor, 1.0);
    }
    processAllTriangles(projected, vertices, center, camPos, mat,
                        sphere.getSlices(), sphere.getStacks(), lightColor, m_lightPos);
}

void DefaultRenderStrategy::setLight(const Point& pos, const std::vector<float>& color)
{
    m_lightPos = pos;
    if (!color.empty()) m_lightColor = color;
}

void DefaultRenderStrategy::beginScene()
{
    m_glowPasses.clear();
    m_trianglePasses.clear();
}

void DefaultRenderStrategy::flushScene(std::shared_ptr<BasePainter> painter)
{
    if (!painter) return;
    renderGlowPasses(painter);
    renderTrianglePasses(painter);
}

void DefaultRenderStrategy::renderGlowPasses(std::shared_ptr<BasePainter> painter) const
{
    for (const auto& g : m_glowPasses)
        painter->drawGlow(g.x, g.y, g.radius, g.r, g.g, g.b, g.intensity);
}

void DefaultRenderStrategy::renderTrianglePasses(std::shared_ptr<BasePainter> painter) const
{
    auto sorted = m_trianglePasses;
    std::sort(sorted.begin(), sorted.end(),
              [](const auto& a, const auto& b) { return a.depth > b.depth; });
    for (const auto& t : sorted)
        painter->drawGouraudTriangle(t.x0, t.y0, t.x1, t.y1, t.x2, t.y2,
                                     t.r0, t.g0, t.b0,
                                     t.r1, t.g1, t.b1,
                                     t.r2, t.g2, t.b2,
                                     t.a);
}

void DefaultRenderStrategy::computeLitColor(const Material& mat, const Point& normal,
                                            const Point& viewDir, const Point& lightDir,
                                            int& r, int& g, int& b, const float* light) const
{
    if (mat.isStar()) {
        double nDotV = std::max(0.0, normal.dot(viewDir));

        double coreR = 255.0;
        double coreG = 255.0;
        double coreB = 210.0;

        double edgeR = mat.r() * 255.0;
        double edgeG = mat.g() * 255.0 * 0.4;
        double edgeB = 0.0;

        double factor = std::pow(nDotV, 1.2);

        r = clampChannel(edgeR + (coreR - edgeR) * factor);
        g = clampChannel(edgeG + (coreG - edgeG) * factor);
        b = clampChannel(edgeB + (coreB - edgeB) * factor);
        return;
    }

    double lr = light[0], lg = light[1], lb = light[2], intensity = light[3];
    double nDotL = std::max(0.0, normal.dot(lightDir));
    Point reflect = normal * (2.0 * nDotL) - lightDir;      
    double rDotV = std::max(0.0, reflect.normalized().dot(viewDir));
    double spec = mat.specular() * std::pow(rDotV, mat.shininess() / 10.0);
    double shading = mat.ambient() + mat.diffuse() * nDotL + spec;
    r = clampChannel(mat.r() * lr * shading * 255.0);
    g = clampChannel(mat.g() * lg * shading * 255.0);
    b = clampChannel(mat.b() * lb * shading * 255.0);
}

void DefaultRenderStrategy::correctAspectRatio(std::vector<Point>& projected,
                                                size_t w, size_t h) const
{
    double ar = static_cast<double>(w) / static_cast<double>(h);
    if (ar > 1.0) {
        double ox = w * (1.0 - 1.0 / ar) / 2.0;
        for (auto& p : projected)
            p = Point(p.getX() / ar + ox, p.getY(), p.getZ());
    } else {
        double oy = h * (1.0 - ar) / 2.0;
        for (auto& p : projected)
            p = Point(p.getX(), p.getY() * ar + oy, p.getZ());
    }
}

std::pair<Point, double> DefaultRenderStrategy::computeScreenCenterAndRadius(
    const std::vector<Point>& projected, double sphereRadius, double fov, size_t height) const
{
    double sx = 0, sy = 0;
    size_t n = 0;
    for (const auto& p : projected) {
        if (p.getZ() <= 0) continue;
        sx += p.getX(); sy += p.getY(); ++n;
    }
    if (n == 0) return {Point{0,0,0}, 0};
    Point c(sx / n, sy / n, 0);
    double r = 0;
    for (const auto& p : projected) {
        if (p.getZ() <= 0) continue;
        r = std::max(r, std::hypot(p.getX() - c.getX(), p.getY() - c.getY()));
    }
    if (r < 1e-3 && !projected.empty()) {
        double d = projected[0].getZ();
        double scale = 1.0 / (2.0 * std::tan(fov * M_PI / 360.0));
        r = (sphereRadius / d) * scale * (height / 2.0);
    }
    return {c, r};
}

void DefaultRenderStrategy::addGlowPass(const Point& c, double r,
                 const Material& mat, const float* light,
                 double intensityFactor)
{
    GlowPass g;
    g.x = c.getX(); g.y = c.getY(); g.radius = r;
    g.r = clampChannel(mat.r() * light[0] * 255);
    g.g = clampChannel(mat.g() * light[1] * 255);
    g.b = clampChannel(mat.b() * light[2] * 255);
    g.intensity = light[3] * (0.65 + mat.ambient() * 0.25 + mat.diffuse() * 0.2) * intensityFactor;
    m_glowPasses.push_back(g);
}

void DefaultRenderStrategy::processTriangle(const std::vector<Point>& projected,
                                            const std::vector<Vertex>& vertices,
                                            const Point& center, const Point& camPos,
                                            const Material& mat, size_t i0, size_t i1, size_t i2,
                                            const float* light, const Point& lightSourcePos)
{
    if (i0 >= projected.size() || i1 >= projected.size() || i2 >= projected.size()) return;
    if (projected[i0].getZ() <= 0 || projected[i1].getZ() <= 0 || projected[i2].getZ() <= 0) return;

    Point p0(vertices[i0].getX(), vertices[i0].getY(), vertices[i0].getZ());
    Point p1(vertices[i1].getX(), vertices[i1].getY(), vertices[i1].getZ());
    Point p2(vertices[i2].getX(), vertices[i2].getY(), vertices[i2].getZ());

    if (!isFrontFacing(vertices[i0], vertices[i1], vertices[i2], camPos, center)) return;

    Point n0 = (p0 - center).normalized();
    Point n1 = (p1 - center).normalized();
    Point n2 = (p2 - center).normalized();
    Point v0 = (camPos - p0).normalized();
    Point v1 = (camPos - p1).normalized();
    Point v2 = (camPos - p2).normalized();

    Point l0 = (lightSourcePos - p0).normalized();
    Point l1 = (lightSourcePos - p1).normalized();
    Point l2 = (lightSourcePos - p2).normalized();

    int r0, g0, b0, r1, g1, b1, r2, g2, b2;
    computeLitColor(mat, n0, v0, l0, r0, g0, b0, light);
    computeLitColor(mat, n1, v1, l1, r1, g1, b1, light);
    computeLitColor(mat, n2, v2, l2, r2, g2, b2, light);

    TrianglePass t;
    t.x0 = projected[i0].getX(); t.y0 = projected[i0].getY();
    t.x1 = projected[i1].getX(); t.y1 = projected[i1].getY();
    t.x2 = projected[i2].getX(); t.y2 = projected[i2].getY();
    t.depth = (projected[i0].getZ() + projected[i1].getZ() + projected[i2].getZ()) / 3.0;
    t.r0 = r0; t.g0 = g0; t.b0 = b0;
    t.r1 = r1; t.g1 = g1; t.b1 = b1;
    t.r2 = r2; t.g2 = g2; t.b2 = b2;
    t.a = 255;
    m_trianglePasses.push_back(t);
}

void DefaultRenderStrategy::processAllTriangles(const std::vector<Point>& projected,
                                                const std::vector<Vertex>& vertices,
                                                const Point& center, const Point& camPos,
                                                const Material& mat, size_t slices, size_t stacks,
                                                const float* light, const Point& lightSourcePos)
{
    for (size_t t = 0; t < stacks; ++t)
        for (size_t s = 0; s < slices; ++s) {
            size_t p0 = t * (slices + 1) + s, p1 = p0 + 1, p2 = p0 + slices + 1, p3 = p2 + 1;
            processTriangle(projected, vertices, center, camPos, mat, p0, p1, p2, light, lightSourcePos);
            processTriangle(projected, vertices, center, camPos, mat, p1, p3, p2, light, lightSourcePos);
        }
}