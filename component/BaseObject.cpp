#include "BaseObject.h"

typename BaseObject::iterator BaseObject::begin() noexcept
{
    return iterator();
}

typename BaseObject::iterator BaseObject::end() noexcept
{
    return iterator();
}

typename BaseObject::const_iterator BaseObject::begin() const noexcept
{
    return const_iterator();
}

typename BaseObject::const_iterator BaseObject::end() const noexcept
{
    return const_iterator();
}

bool BaseObject::add(const std::shared_ptr<BaseObject>&) 
{ 
    return false;
}

bool BaseObject::remove(size_t id) noexcept
{
    (void)id;
    return false;
}

std::shared_ptr<BaseObject> BaseObject::getObject(size_t id) const
{
    (void)id;
    return nullptr;
}

Point BaseObject::getCenter() const noexcept
{
    return Point{0, 0, 0};
}