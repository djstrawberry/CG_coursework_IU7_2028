#include "Scene.h"

std::shared_ptr<Scene> Scene::getInstance() {
    static auto instance = std::shared_ptr<Scene>(new Scene());
    return instance;
}

size_t Scene::addObject(const std::shared_ptr<BaseObject>& obj) {
    size_t id = m_idCounter++;
    m_objects[id] = obj;
    return id;
}

void Scene::removeObject(size_t id) {
    m_objects.erase(id);
}

std::shared_ptr<BaseObject> Scene::getObject(size_t id) {
    auto it = m_objects.find(id);
    if (it != m_objects.end()) {
        return it->second;
    }
    return nullptr;
}
