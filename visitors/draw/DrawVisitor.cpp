#include "DrawVisitor.h"
#include "../../component/primitive/visible/model/celestial/CelestialBody.h"
#include "../../component/primitive/invisible/camera/BaseCamera.h"
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QPolygonF>
#include <QRadialGradient>
#include <algorithm>
#include <cmath>

DrawVisitor::DrawVisitor(QPainter* painter, std::shared_ptr<BaseCamera> activeCamera, int width, int height, const float lightColor[4])
    : m_painter(painter), m_camera(activeCamera), m_viewportWidth(width), m_viewportHeight(height) {
    m_lightColor[0] = lightColor[0];
    m_lightColor[1] = lightColor[1];
    m_lightColor[2] = lightColor[2];
    m_lightColor[3] = lightColor[3];
}

void DrawVisitor::visitCelestialBody(CelestialBody& body) {
    auto impl = body.getImpl();
    if (!impl || !m_camera) return;

    const auto& vertices = impl->getVertices();
    const auto& edges = impl->getEdges();

    Vec3<double> camPos = m_camera->getPosition();
    Vec3<double> camTarget = m_camera->getTarget();
    Vec3<double> lookDir = (camTarget - camPos).normalized();

    // Simplified camera projection matrix coordinate calculation
    // Translate point relative to camera space
    auto projectPoint = [&](const Vec3<double>& p) -> std::pair<double, double> {
        Vec3<double> rel = p - camPos;
        
        // Orthogonal components relative to look direction
        Vec3<double> up(0, 1, 0); 
        Vec3<double> right = lookDir.cross(up).normalized();
        Vec3<double> trueUp = right.cross(lookDir).normalized();

        double depth = rel.dot(lookDir);
        if (depth < 0.1) depth = 0.1; // Guard divide by zero

        double xProj = rel.dot(right) / depth;
        double yProj = rel.dot(trueUp) / depth;

        // Map to screen pixel dimensions
        double scale = 400.0 * std::tan((m_camera->getFov() * M_PI / 180.0) / 2);
        double screenX = m_viewportWidth / 2.0 + xProj * scale;
        double screenY = m_viewportHeight / 2.0 - yProj * scale; // Flip Y for Qt graphics coordinate space
        
        return {screenX, screenY};
    };

    m_painter->save();
    m_painter->setRenderHint(QPainter::Antialiasing, true);

    auto centerPt = projectPoint(impl->getCenter());
    double radius = impl->getRadius();
    auto edgePt = projectPoint(impl->getCenter() + Vec3<double>(radius, 0, 0));
    double pxRadius = std::abs(edgePt.first - centerPt.first);

    // Draw solar corona/glow behind the sphere
    for (int rStep = 3; rStep >= 1; --rStep) {
        double rGlow = pxRadius * (1.0 + rStep * 0.8);
        QRadialGradient alphaGlow(centerPt.first, centerPt.second, rGlow);
        alphaGlow.setColorAt(0.0, QColor(255, 160, 20, 120 * m_lightColor[3] / rStep));
        alphaGlow.setColorAt(0.4, QColor(255, 70, 0, 50 * m_lightColor[3] / rStep));
        alphaGlow.setColorAt(1.0, QColor(0, 0, 0, 0));
        m_painter->setBrush(QBrush(alphaGlow));
        m_painter->setPen(Qt::NoPen);
        m_painter->drawEllipse(QPointF(centerPt.first, centerPt.second), rGlow, rGlow);
    }

    int slices = impl->getSlices();
    int stacks = impl->getStacks();

    struct Face {
        size_t indices[4];
        double depth;
    };

    std::vector<Face> faces;
    if (slices > 0 && stacks > 0 && vertices.size() >= (size_t)((slices + 1) * (stacks + 1))) {
        for (int t = 0; t < stacks; ++t) {
            for (int s = 0; s < slices; ++s) {
                size_t p0 = t * (slices + 1) + s;
                size_t p1 = t * (slices + 1) + s + 1;
                size_t p2 = (t + 1) * (slices + 1) + s;
                size_t p3 = (t + 1) * (slices + 1) + s + 1;

                if (p0 < vertices.size() && p1 < vertices.size() && p2 < vertices.size() && p3 < vertices.size()) {
                    Vec3<double> v0 = vertices[p0];
                    Vec3<double> v1 = vertices[p1];
                    Vec3<double> v2 = vertices[p2];
                    Vec3<double> v3 = vertices[p3];

                    double cx = (v0.x + v1.x + v2.x + v3.x) / 4.0;
                    double cy = (v0.y + v1.y + v2.y + v3.y) / 4.0;
                    double cz = (v0.z + v1.z + v2.z + v3.z) / 4.0;
                    Vec3<double> centroid(cx, cy, cz);

                    double depth = (centroid - camPos).dot(lookDir);
                    faces.push_back({{p0, p1, p3, p2}, depth});
                }
            }
        }

        // Sort faces (Painter's Algorithm)
        std::sort(faces.begin(), faces.end(), [](const Face& a, const Face& b) {
            return a.depth > b.depth;
        });

        // Lighting settings
        Material mat = body.getMaterial();
        Vec3<double> starCenter = impl->getCenter();
        Vec3<double> lightDirVec = Vec3<double>(-1.0, 1.5, 1.0).normalized();

        for (const auto& face : faces) {
            Vec3<double> v0 = vertices[face.indices[0]];
            Vec3<double> v1 = vertices[face.indices[1]];
            Vec3<double> v2 = vertices[face.indices[2]];
            Vec3<double> v3 = vertices[face.indices[3]];

            auto pt0 = projectPoint(v0);
            auto pt1 = projectPoint(v1);
            auto pt2 = projectPoint(v2);
            auto pt3 = projectPoint(v3);

            // Centroid for normal vector extraction
            double cx = (v0.x + v1.x + v2.x + v3.x) / 4.0;
            double cy = (v0.y + v1.y + v2.y + v3.y) / 4.0;
            double cz = (v0.z + v1.z + v2.z + v3.z) / 4.0;
            Vec3<double> centroid(cx, cy, cz);

            Vec3<double> normal = (centroid - starCenter).normalized();
            Vec3<double> viewDirVec = (camPos - centroid).normalized();

            // Diffuse Lighting using customized Lambert/Half-Lambert
            double dotNL = normal.dot(lightDirVec);
            double halfLambert = std::max(0.0, dotNL) * 0.5 + 0.5;
            double diffuseTerm = halfLambert * mat.diffuse * m_lightColor[3];

            // Specular highlighting (Blinn-Phong)
            Vec3<double> halfVec = (lightDirVec + viewDirVec).normalized();
            double specFactor = std::pow(std::max(0.0, normal.dot(halfVec)), mat.shininess);
            double specularTerm = specFactor * mat.specular * m_lightColor[3];

            // Limb darkening factor based on viewer sightline
            double dotNV = normal.dot(viewDirVec);
            double edgeFactor = std::max(0.0, std::min(1.0, dotNV));

            // Ambient + Diffuse overall scaling
            float intensityAmbient = mat.ambient * m_lightColor[3];
            double temp = intensityAmbient + diffuseTerm;

            // Thermodynamic color ramp to match React version beautifully
            double baseR = 255.0;
            double baseG = 80.0 + 135.0 * edgeFactor;
            double baseB = 15.0 * (edgeFactor * edgeFactor) + 195.0 * std::pow(edgeFactor, 10);

            int finalR = std::min(255.0, baseR * temp * m_lightColor[0] + specularTerm * 255.0);
            int finalG = std::min(255.0, baseG * temp * m_lightColor[1] + specularTerm * 255.0);
            int finalB = std::min(255.0, baseB * temp * m_lightColor[2] + specularTerm * 255.0);

            // Draw face
            QPolygonF poly;
            poly << QPointF(pt0.first, pt0.second)
                 << QPointF(pt1.first, pt1.second)
                 << QPointF(pt2.first, pt2.second)
                 << QPointF(pt3.first, pt3.second);

            QColor faceColor(finalR, finalG, finalB);
            
            // Draw face fill
            m_painter->setBrush(QBrush(faceColor));
            
            // Subtle edge pen for grid structure
            QColor penColor(m_lightColor[0] * 255, m_lightColor[1] * 255, m_lightColor[2] * 255, 38);
            m_painter->setPen(QPen(penColor, 0.5));
            m_painter->drawPolygon(poly);
        }
    } else {
        // Fallback to wireframe drawing if not parametric
        Material mat = body.getMaterial();
        QColor baseColor(mat.r * 255, mat.g * 255, mat.b * 255);

        float intensityAmbient = mat.ambient * m_lightColor[3];
        int redCh = std::min(255.0f, baseColor.red() * (intensityAmbient + m_lightColor[0] * mat.diffuse));
        int greenCh = std::min(255.0f, baseColor.green() * (intensityAmbient + m_lightColor[1] * mat.diffuse));
        int blueCh = std::min(255.0f, baseColor.blue() * (intensityAmbient + m_lightColor[2] * mat.diffuse));

        QColor shadeColor(redCh, greenCh, blueCh);
        m_painter->setPen(QPen(shadeColor, 1));
        m_painter->setBrush(Qt::NoBrush);

        for (const auto& edge : edges) {
            if (edge.first < vertices.size() && edge.second < vertices.size()) {
                auto pt1 = projectPoint(vertices[edge.first]);
                auto pt2 = projectPoint(vertices[edge.second]);
                m_painter->drawLine(pt1.first, pt1.second, pt2.first, pt2.second);
            }
        }
    }

    // Centered primary white glow core
    m_painter->setBrush(QBrush(Qt::white));
    m_painter->setPen(Qt::NoPen);
    m_painter->drawEllipse(QPointF(centerPt.first, centerPt.second), 3, 3);

    m_painter->restore();
}

void DrawVisitor::visitComposite(Composite& comp) {
    // Composite traversal managed automatically by recursion
    (void)comp;
}

void DrawVisitor::visitCamera(BaseCamera& camera) {
    // Camera does not draw itself on target canvas
    (void)camera;
}
