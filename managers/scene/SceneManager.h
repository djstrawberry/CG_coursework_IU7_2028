#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "../../scene/Scene.h"
#include "../../visitors/BaseVisitor.h"
#include "../../vector/Vec3.h"
#include <map>
#include <memory>

class SceneManager {
public:
    SceneManager();
    ~SceneManager() = default;

    size_t addObject(const std::shared_ptr<BaseObject>& obj);
    void removeObject(size_t id);
    std::shared_ptr<BaseObject> getObject(size_t id);

    void accept(std::shared_ptr<BaseVisitor> visitor);
    const std::map<size_t, std::shared_ptr<BaseObject>>& getObjects() const;
    Vec3<double> getPrimaryLightPosition() const;

private:
    std::shared_ptr<Scene> m_scene;
};

#endif // SCENE_MANAGER_H
