#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "../../scene/Scene.h"
#include "../../visitors/BaseVisitor.h"
#include <memory>

class SceneManager {
public:
    SceneManager();
    ~SceneManager() = default;

    size_t addObject(const std::shared_ptr<BaseObject>& obj);
    void removeObject(size_t id);
    std::shared_ptr<BaseObject> getObject(size_t id);

    void acceptVisitor(std::shared_ptr<BaseVisitor> visitor);

private:
    std::shared_ptr<Scene> m_scene;
};

#endif // SCENE_MANAGER_H
