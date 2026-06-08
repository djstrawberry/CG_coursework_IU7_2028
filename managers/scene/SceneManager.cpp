#include "SceneManager.h"
#include "../../component/primitive/visible/model/celestial/CelestialBody.h"

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
    return m_scene->getObject(id);
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
