#include "bitpch.h"

#include "Core/GenericCollection.h"
#include "EntityAction.h"
#include "EntityActionManager.h"

namespace BITFramework
{
    
    
    // EntityActionManager::EntityActionManager(const EntityActionManager& other)
    //     : ObjectManager<EntityAction>(other)
    // {}

    const std::vector<std::shared_ptr<EntityAction>>& EntityActionManager::GetVisibleActions()
    {
        m_VisibleActions.clear();
        // for (const auto& action: m_Objects)
        // {
        //     if (action->CanBeVisible())
        //         m_VisibleActions.push_back(action);
        // }

        std::copy_if(m_Objects.begin(), m_Objects.end(), m_VisibleActions.begin(),
            [](const auto& action){ return action->CanBeVisible(); });

        return m_VisibleActions;
    }
}

