#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "../BaseObject.h"
#include <map>

class Composite : public BaseObject {
public:
    Composite() = default;
    ~Composite() override = default;

    void accept(std::shared_ptr<BaseVisitor> visitor) override;
    std::shared_ptr<BaseObject> clone() override;

    bool isComposite() const override { return true; }

    void add(const std::shared_ptr<BaseObject>& obj) override;
    void remove(size_t id) override;
    std::shared_ptr<BaseObject> getObject(size_t id) override;

    auto begin() { return m_objects.begin(); }
    auto end() { return m_objects.end(); }

private:
    std::map<size_t, std::shared_ptr<BaseObject>> m_objects;
    size_t m_count = 0;
};

#endif // COMPOSITE_H
