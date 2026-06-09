#include "Composite.h"
#include <stdexcept>
#include <memory>

Composite::iterator Composite::begin() noexcept {
    return m_objects.begin();
}

Composite::iterator Composite::end() noexcept {
    return m_objects.end();
}

Composite::const_iterator Composite::begin() const noexcept {
    return m_objects.begin();
}

Composite::const_iterator Composite::end() const noexcept {
    return m_objects.end();
}


bool Composite::isComposite() const noexcept {
    return true;
}

bool Composite::isVisible() const noexcept {
    return true;
}


bool Composite::add(const std::shared_ptr<BaseObject>& obj) {
    if (!obj) return false;
    
    auto result = m_objects.insert({m_count, obj});
    if (result.second) {
        ++m_count;
        return true;
    }
    return false;
}

bool Composite::remove(const size_t id) noexcept {
    return m_objects.erase(id) > 0;
}

std::shared_ptr<BaseObject> Composite::getObject(const size_t id) const {
    auto it = m_objects.find(id);
    if (it != m_objects.end()) {
        return it->second;
    }
    
    for (const auto& [childId, child] : m_objects) {
        if (child->isComposite()) {
            auto found =child->getObject(id);
            if (found) return found;
        }
    }
    
    return nullptr;
}

Vec3<double> Composite::getCenter() const noexcept {
    if (m_objects.empty()) {
        return Vec3<double>{0, 0, 0};
    }
    
    Vec3<double> sum{0, 0, 0};
    size_t count = 0;
    
    for (const auto& [id, child] : m_objects) {
        if (child->isVisible()) {
            sum = sum + child->getCenter();
            ++count;
        }
    }
    
    if (count == 0) {
        return Vec3<double>{0, 0, 0};
    }
    
    return Vec3<double>(sum.getX() / count, sum.getY() / count, sum.getZ() / count);
}


void Composite::accept(std::shared_ptr<BaseVisitor> visitor) {
    if (!visitor)
        return;
    visitor->visit(*this);
    for (auto& [id, child] : m_objects) {
        child->accept(visitor);
    }
}

std::shared_ptr<BaseObject> Composite::clone() const {
    auto cloned = std::make_shared<Composite>();
    for (const auto& [id, child] : m_objects) {
        cloned->add(child->clone());
    }
    return cloned;
}