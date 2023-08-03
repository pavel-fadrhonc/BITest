#include "bitpch.h"

#include "Object.h"

namespace BITFramework
{
    Object::~Object() = default;
    
    Object::Object(Entity& owningEntity)
        : m_Entity(owningEntity)
    {}

}
