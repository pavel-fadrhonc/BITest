#pragma once
#include "Object/ObjectManager.h"

namespace BITFramework
{
    class EntityAction;
    
    class EntityActionManager : public ObjectManager<EntityAction>
    {
    public:
        EntityActionManager(Entity& owningEntity)
            : ObjectManager(owningEntity)
        {}
        
        EntityActionManager(const EntityActionManager& other) = delete;

        const std::vector<std::shared_ptr<EntityAction>>& GetVisibleActions();

        template
        <typename TFunc, typename TDerived, typename TBase, typename ...TArgs>
        void Invoke(TFunc TDerived::* pm, TBase& base, TArgs... args)
        {
            if (TDerived* der = dynamic_cast<TDerived*>(&base))
            {
                std::mem_fn(pm)(der, args...);
            }
        }

        template
        <typename TFunc, typename TDerived, typename ...TArgs>
        void InvokeAll(TFunc TDerived::* pm, TArgs... args)
        {
            for(auto obj : m_Objects)
            {
                if (TDerived* der = dynamic_cast<TDerived*>(obj.get()))
                {
                    auto fun = std::mem_fn(pm);
                    fun(der, args...);
                }
            }
        }

    private:
        std::vector<std::shared_ptr<EntityAction>> m_VisibleActions;
    };
}

