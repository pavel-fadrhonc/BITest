#include "bitpch.h"

#include "Entity.h"
#include "Object/EntityAction/Core/EntityAction.h"

namespace BITFramework
{
    Entity::Entity(int id)
        :m_Id(id),
        m_ActionManager(*this)
    { }

    std::ostream& operator<<(std::ostream& os, const Entity& e)
    {
        os << "Entity(ID:" << e.m_Id << ')';
        auto actions{ e.m_ActionManager.GetVisibleActions() };
        for (auto action : actions)
        {
            os << "\n    " << *action.lock();
        }
        return os;
    }
}
