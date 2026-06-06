#include "BaseObject.h"

typename BaseObject::iterator BaseObject::begin()
{
    return iterator();
}

typename BaseObject::iterator BaseObject::end()
{
    return iterator();
}

typename BaseObject::const_iterator BaseObject::begin() const
{
    return const_iterator();
}

typename BaseObject::const_iterator BaseObject::end() const
{
    return const_iterator();
}

bool BaseObject::add(std::shared_ptr<BaseObject>) 
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

Vec3 BaseObject::getCenter() const noexcept
{
    return { 0, 0, 0 }; 
}
