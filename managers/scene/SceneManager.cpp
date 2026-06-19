#include "SceneManager.h"
#include "../../visitors/params/SetParamsVisitor.h"
#include "../../visitors/animation/AnimationVisitor.h"
#include "../../component/primitive/invisible/light/default/DefaultLight.h"
#include "../../component/primitive/invisible/light/BaseLight.h"
#include "../../component/primitive/visible/model/celestial/CelestialBody.h"

SceneManager::SceneManager() : m_scene(Scene::getInstance()) {}

void SceneManager::setSphereFactory(std::shared_ptr<SphereFactory> factory) {
    m_sphereFactory = std::move(factory);
}

size_t SceneManager::addObject(const std::shared_ptr<BaseObject>& obj) {
    return m_scene.addObject(obj);
}

void SceneManager::removeObject(size_t id) {
    m_scene.removeObject(id);
}

std::shared_ptr<BaseObject> SceneManager::getObject(size_t id) {
    auto it = m_scene.getObject(id);
    if (it != m_scene.end()) {
        return it->second; 
    }
    return nullptr;
}

void SceneManager::setObjectName(size_t id, const std::string& name) {
    m_names[id] = name;
}

std::string SceneManager::getObjectName(size_t id) const {
    auto it = m_names.find(id);
    return it != m_names.end() ? it->second : "Unnamed";
}

void SceneManager::setOrbitCenter(size_t id, const Point &orbitCenter)
{
    auto obj = getObject(id);
    if (!obj) return;
    auto visitor = std::make_shared<SetParamsVisitor>(orbitCenter);
    obj->accept(visitor);
}

size_t SceneManager::addCelestialBody(const std::string &name, double radius, const Point &center, const Material &material)
{
    auto sphereImpl = m_sphereFactory->createSphere(radius, center);
    auto body = std::make_shared<CelestialBody>(sphereImpl); 
    auto initVisitor = std::make_shared<SetParamsVisitor>(material, center);
    body->accept(initVisitor);
    size_t id = addObject(body);
    setObjectName(id, name);
    return id;
}

size_t SceneManager::addPlanet(const std::string &name, double radius, const Point &orbitCenter,
                                double orbitRadius, double orbitAngle, double orbitSpeed, const Material &material)
{
    size_t id = addCelestialBody(name, radius, Point{0.0, 0.0, 0.0}, Material{});
    auto obj = getObject(id);
    if (!obj) return id;
    auto orbitVisitor = std::make_shared<SetParamsVisitor>(orbitRadius, orbitSpeed, orbitAngle, orbitCenter, material);
    obj->accept(orbitVisitor);
    return id;
}

void SceneManager::updateCelestialBody(size_t id, double radius, const Point& center, const Material& material)
{
    auto obj = getObject(id);
    if (!obj) return;
    auto visitor = std::make_shared<SetParamsVisitor>(radius, center, material);
    obj->accept(visitor);
}

void SceneManager::advanceOrbits(double deltaSeconds)
{
    if (deltaSeconds <= 0.0) return;
    auto light = getLightSource();
    Point starCenter = light ? light->getPosition() : Point{0.0, 0.0, 0.0};
    auto visitor = std::make_shared<AnimationVisitor>(deltaSeconds, starCenter);
    for (auto& [id, obj] : m_scene.getObjects()) {
        if (obj && obj->isVisible())
            obj->accept(visitor);
    }
}

void SceneManager::setCelestialMaterial(size_t id, const Material &mat)
{
    auto obj = getObject(id);
    if (!obj) return;
    auto visitor = std::make_shared<SetParamsVisitor>(mat);
    obj->accept(visitor);
}

void SceneManager::transformCelestial(size_t id, double orbitRadius, double orbitSpeed)
{
    auto obj = getObject(id);
    if (!obj) return;
    auto visitor = std::make_shared<SetParamsVisitor>(orbitRadius, orbitSpeed);
    obj->accept(visitor);
}

void SceneManager::addLightSource(std::shared_ptr<BaseLight> light)
{
    for (auto& [id, obj] : m_scene.getObjects()) {
        if (std::dynamic_pointer_cast<BaseLight>(obj)) {
            m_scene.removeObject(id);
            break;
        }
    }
    m_scene.addObject(light);
}

std::shared_ptr<BaseLight> SceneManager::getLightSource() const
{
    for (const auto& [id, obj] : m_scene.getObjects()) {
        auto light = std::dynamic_pointer_cast<BaseLight>(obj);
        if (light) return light;
    }
    return nullptr;
}

void SceneManager::addLight(const Point& pos, const std::vector<float>& color)
{
    auto impl = std::make_shared<LightImpl>(pos, color);
    auto light = std::make_shared<DefaultLight>(impl);
    addLightSource(light);
}

void SceneManager::updateLight(const Point& pos, const std::vector<float>& color)
{
    auto light = getLightSource();
    if (light) {
        light->setPosition(pos);
        light->setColor(color);
    }
}

void SceneManager::accept(std::shared_ptr<BaseVisitor> visitor) {
    for (auto& [id, obj] : m_scene.getObjects()) {
        if (obj) {
            obj->accept(visitor);
        }
    }
}

const std::map<size_t, std::shared_ptr<BaseObject>>& SceneManager::getObjects() const {
    return m_scene.getObjects();
}