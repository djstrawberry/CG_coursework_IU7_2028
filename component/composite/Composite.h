#pragma once

#include "../BaseObject.h"
#include "../../vector/Vec3.h"
#include <map>

class Composite : public BaseObject {
private:
    mapObjects m_objects;
    size_t m_count = 0;

public:
    Composite() = default;
    ~Composite() override = default;

    iterator begin() noexcept override;
    iterator end() noexcept override;
    const_iterator begin() const noexcept override;
    const_iterator end() const noexcept override;

    void accept(std::shared_ptr<BaseVisitor> visitor) override;
    std::shared_ptr<BaseObject> clone() const override;

    bool isComposite() const noexcept override;
    bool isVisible() const noexcept override;

    bool add(const std::shared_ptr<BaseObject>& obj) override;
    bool remove(const size_t id) noexcept override;
    std::shared_ptr<BaseObject> getObject(const size_t id) const override;
    Vec3<double> getCenter() const noexcept override;
};
