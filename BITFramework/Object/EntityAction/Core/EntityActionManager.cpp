#include "bitpch.h"

#include "Core/GenericCollection.h"
#include "EntityAction.h"
#include "EntityActionManager.h"

namespace BITFramework
{
    std::vector<std::weak_ptr<EntityAction>> EntityActionManager::GetVisibleActions() const
    {
        auto visibleActions = std::vector<std::weak_ptr<EntityAction>>{};

        std::copy_if(m_Objects.cbegin(), m_Objects.cend(), std::back_inserter(visibleActions),
            [](const auto& action){ return action->CanBeVisible(); });

        return visibleActions;
    }
}

