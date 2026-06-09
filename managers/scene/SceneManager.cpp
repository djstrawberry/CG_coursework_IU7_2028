#include "SceneManager.h"
#include "../../component/primitive/visible/model/celestial/CelestialBody.h"
#include "../../component/primitive/visible/model/impl/parametric/ParametricSphereImpl.h"

SceneManager::SceneManager() {
    m_scene = Scene::getInstance();
}

size_t SceneManager::addObject(const std::shared_ptr<BaseObject>& obj) {
    return m_scene->addObject(obj);
}

void SceneManager::removeObject(size_t id) {
    m_scene->removeObject(id);
}

std::shared_ptr<BaseObject> SceneManager::getObject(size_t id) {
    auto it = m_scene->getObject(id);
    if (it != m_scene->end()) {
        return it->second; 
    }
    return nullptr;
}

void SceneManager::setOrbitCenter(size_t id, const Vec3<double> &orbitCenter)
{
    auto obj = getObject(id);
    auto body = std::dynamic_pointer_cast<CelestialBody>(obj);
    if (body) {
        body->setBaseCenter(orbitCenter);
    }
}

size_t SceneManager::addCelestialBody(const std::string &name, double radius, const Vec3<double> &center, const Material &material)
{
    auto sphereImpl = std::make_shared<ParametricSphereImpl>(radius, center, 32, 32);
    auto body = std::make_shared<CelestialBody>(name, sphereImpl);
    Material mat = material;
    mat.luminous = true;
    body->setMaterial(mat);
    body->setBaseCenter(center);
    return addObject(body);
}

size_t SceneManager::addPlanet(const std::string &name, double radius, const Vec3<double> &orbitCenter,
                                double orbitRadius, double orbitAngle, double orbitSpeed, const Material &material)
{
    const double rad = orbitAngle * M_PI / 180.0;
    const Vec3<double> initialPos(
        orbitCenter.getX() + orbitRadius * std::cos(rad),
        orbitCenter.getY(),
        orbitCenter.getZ() + orbitRadius * std::sin(rad)
    );

    auto sphereImpl = std::make_shared<ParametricSphereImpl>(radius, initialPos, 24, 24);
    auto body = std::make_shared<CelestialBody>(name, sphereImpl);
    Material mat = material;
    mat.luminous = false;
    body->setMaterial(mat);
    body->setBaseCenter(orbitCenter);
    body->setOrbitRadius(orbitRadius);
    body->setOrbitAngle(orbitAngle);
    body->setOrbitSpeed(orbitSpeed);

    return addObject(body);
}

void SceneManager::updateCelestialBody(size_t id, double radius, const Vec3<double> &center, const Material &material)
{
    auto obj = getObject(id);
    auto body = std::dynamic_pointer_cast<CelestialBody>(obj);
    if (!body) return;
    auto impl = body->getImpl();
    if (!impl) return;
    impl->setRadius(radius);
    impl->setCenter(center);
    body->setMaterial(material);
    body->setBaseCenter(center);
}

void SceneManager::advanceOrbits(double deltaSeconds)
{
    if (deltaSeconds <= 0.0) return;
    const Vec3<double> starCenter = getPrimaryLightPosition();
    for (const auto &[id, obj] : getObjects()) {
        (void)id;
        auto body = std::dynamic_pointer_cast<CelestialBody>(obj);
        if (!body || body->getMaterial().luminous || body->getOrbitRadius() <= 0.0) continue;
        double speed = body->getOrbitSpeed();
        if (speed <= 0.0) continue;
        body->setBaseCenter(starCenter);
        double angle = std::fmod(body->getOrbitAngle() + speed * deltaSeconds, 360.0);
        if (angle < 0.0) angle += 360.0;
        body->setOrbitAngle(angle);
    }
}

void SceneManager::setCelestialMaterial(size_t id, const Material &mat)
{
    auto obj = getObject(id);
    auto body = std::dynamic_pointer_cast<CelestialBody>(obj);
    if (body) body->setMaterial(mat);
}

void SceneManager::transformCelestial(size_t id, double orbitRadius, double orbitSpeed)
{
    auto obj = getObject(id);
    auto body = std::dynamic_pointer_cast<CelestialBody>(obj);
    if (body) {
        body->setOrbitRadius(orbitRadius);
        body->setOrbitSpeed(orbitSpeed);
        body->updatePosition();
    }
}

void SceneManager::accept(std::shared_ptr<BaseVisitor> visitor) {
    for (auto& [id, obj] : m_scene->getObjects()) {
        if (obj) {
            obj->accept(visitor);
        }
    }
}

const std::map<size_t, std::shared_ptr<BaseObject>>& SceneManager::getObjects() const {
    return m_scene->getObjects();
}

Vec3<double> SceneManager::getPrimaryLightPosition() const {
    for (const auto& [id, obj] : m_scene->getObjects()) {
        auto body = std::dynamic_pointer_cast<CelestialBody>(obj);
        if (body && body->getMaterial().luminous) {
            return body->getCenter();
        }
    }
    return Vec3<double>{};
}
