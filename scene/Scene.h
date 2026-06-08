#ifndef SCENE_H
#define SCENE_H

#include "../component/BaseObject.h"
#include <map>
#include <memory>

class Scene {
public:
    static std::shared_ptr<Scene> getInstance();

    size_t addObject(const std::shared_ptr<BaseObject>& obj);
    void removeObject(size_t id);
    std::shared_ptr<BaseObject> getObject(size_t id);

    auto& getObjects() { return m_objects; }
    const std::map<size_t, std::shared_ptr<BaseObject>>& getObjects() const { return m_objects; }
    void clear() { m_objects.clear(); }

private:
    Scene() = default;
    
    std::map<size_t, std::shared_ptr<BaseObject>> m_objects;
    size_t m_idCounter = 0;
};

#endif // SCENE_H
