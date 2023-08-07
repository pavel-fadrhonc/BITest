#include "bitpch.h"

#include "EntityAction.h"

namespace BITFramework
{
    EntityAction::EntityAction(Entity& owningEntity)
        : Object(owningEntity)
    {
        m_Entity.get().getActionManager().RegisterObject(std::shared_ptr<EntityAction>(this));
    }

    std::ostream& operator<<(std::ostream& os, const EntityAction& e)
    {
        return e.print(os);
    }
}

