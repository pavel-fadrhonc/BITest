#include "bitpch.h"

#include "Object.h"
#include "Entity/Core/Entity.h"

namespace BITFramework
{
    Object::~Object() = default;

    Object::Object(Entity& owningEntity)
        : m_Entity(owningEntity)
    {}

    std::ostream& operator<<(std::ostream& os, const Object& e)
    {
        e.print(os);
        return os;
    }
}
