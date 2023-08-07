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
        EntityActionManager& operator=(const EntityActionManager& om) = delete;
        EntityActionManager(EntityActionManager&& other) = delete;
        EntityActionManager& operator=(EntityActionManager&& om) = delete;

        std::vector<std::weak_ptr<EntityAction>> GetVisibleActions() const;

        template
        <typename TFunc, typename TDerived, typename TBase, typename ...TArgs>
        void Invoke(TFunc TDerived::* pm, TBase& base, TArgs... args)
        {
            if (TDerived* der = dynamic_cast<TDerived*>(&base))
            {
                std::mem_fn(pm)(der, args...);
            }
        }

        /**
         * \brief Invokes a member function on all objects of type TDerived
         * \param pm pointer to a EntityAction derived class member function 
         * \param args arguments for the member function
         */
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
    };
}

