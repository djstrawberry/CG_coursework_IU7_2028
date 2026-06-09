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

Scene::iterator Scene::getObject(size_t id) {
    return m_objects.find(id);
}

Scene::iterator Scene::end() {
    return m_objects.end();
}

std::map<size_t, std::shared_ptr<BaseObject>>& Scene::getObjects() { 
    return m_objects; 
}

const std::map<size_t, std::shared_ptr<BaseObject>>& Scene::getObjects() const { 
    return m_objects; 
}

void Scene::clear() { 
    m_objects.clear(); 
}