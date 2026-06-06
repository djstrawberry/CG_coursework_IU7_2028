#include "Composite.h"
#include "../../visitors/BaseVisitor.h"

void Composite::accept(std::shared_ptr<BaseVisitor> visitor) {
    visitor->visitComposite(*this);
    for (auto& [id, obj] : m_objects) {
        if (obj) {
            obj->accept(visitor);
        }
    }
}

std::shared_ptr<BaseObject> Composite::clone() {
    auto copy = std::make_shared<Composite>();
    for (const auto& [id, obj] : m_objects) {
        copy->add(obj->clone());
    }
    return copy;
}

void Composite::add(const std::shared_ptr<BaseObject>& obj) {
    m_objects[m_count++] = obj;
}

void Composite::remove(size_t id) {
    m_objects.erase(id);
}

std::shared_ptr<BaseObject> Composite::getObject(size_t id) {
    auto it = m_objects.find(id);
    if (it != m_objects.end()) {
        return it->second;
    }
    return nullptr;
}
