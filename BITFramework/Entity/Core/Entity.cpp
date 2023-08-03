#include "bitpch.h"

#include "Entity.h"

namespace BITFramework
{
    Entity::Entity(int id)
        :m_Id(id),
        m_ActionManager(*this)
    { }

    std::ostream& operator<<(std::ostream& os, const Entity& e)
    {
        os << "Entity(ID:" << e.m_Id << ')';
        return os;
    }
}
