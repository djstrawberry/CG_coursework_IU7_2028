#pragma once

#include "../component/BaseObject.h"
#include <map>
#include <memory>

class Scene {
public:
    using iterator = std::map<size_t, std::shared_ptr<BaseObject>>::iterator;
    using objectMap = std::map<size_t, std::shared_ptr<BaseObject>>;

    static std::shared_ptr<Scene> getInstance();

    size_t addObject(const std::shared_ptr<BaseObject>& obj);
    void removeObject(size_t id);
    iterator getObject(size_t id);
    iterator end(); 

    objectMap& getObjects();
    const objectMap& getObjects() const;
    void clear();

private:
    Scene() = default;
    
    std::map<size_t, std::shared_ptr<BaseObject>> m_objects;
    size_t m_idCounter = 0;
};
