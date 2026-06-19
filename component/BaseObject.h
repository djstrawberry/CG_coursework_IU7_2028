#pragma once

#include "../visitors/BaseVisitor.h"
#include "../point/Point.h"
#include <memory>
#include <map>

class BaseObject;
using mapObjects = std::map<size_t, std::shared_ptr<BaseObject>>;

class BaseObject {
public:
    using iterator = mapObjects::iterator;
    using const_iterator = mapObjects::const_iterator;

    BaseObject() = default;
    virtual ~BaseObject() = default;

    BaseObject(const BaseObject&) = delete;
    BaseObject& operator=(const BaseObject&) = delete;
    BaseObject(BaseObject&&) = delete;
    BaseObject& operator=(BaseObject&&) = delete;

    virtual iterator begin() noexcept;
    virtual iterator end() noexcept;
    virtual const_iterator begin() const noexcept;
    virtual const_iterator end() const noexcept;

    virtual void accept(std::shared_ptr<BaseVisitor> visitor) = 0;
    virtual std::shared_ptr<BaseObject> clone() const = 0;

    virtual bool isComposite() const noexcept = 0;
    virtual bool isVisible() const noexcept = 0;

    virtual bool add(const std::shared_ptr<BaseObject>& object);
    virtual bool remove(const size_t id) noexcept;

    virtual std::shared_ptr<BaseObject> getObject(const size_t id) const;
    virtual Point getCenter() const noexcept;
};