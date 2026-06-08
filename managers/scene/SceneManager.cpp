#include "SceneManager.h"

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
