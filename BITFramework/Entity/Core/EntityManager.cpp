#include "bitpch.h"

#include "EntityManager.h"
#include "Component/Core/Component.h"

namespace BITFramework
{
    // cannot do std::make_unique because constructor is private
    std::unique_ptr<EntityManager> EntityManager::s_Instance = std::unique_ptr<EntityManager>(new EntityManager);
    
    std::weak_ptr<Entity> EntityManager::CreateEntity()
    {
        m_Entities.push_back(std::make_shared<Entity>(m_NextEntityId));
        m_Components.insert({m_NextEntityId, std::vector<std::shared_ptr<Component>>{}});
        ++m_NextEntityId;

        return m_Entities.back();
    }

    void EntityManager::DeleteEntity(Entity* entity)
    {
        assert(entity != nullptr);

        entity->m_MarkedForDeletion = true;
    }

    void EntityManager::Update()
    {
        decltype(m_Entities.begin()) it; 
        while((it = std::find_if(m_Entities.begin(), m_Entities.end(),
            [&](auto ptr)
            {
                return ptr->m_MarkedForDeletion; 
            }))
            != m_Entities.end())
        {
            DeleteEntityImpl(it->get());
        }
    }

    void EntityManager::DeleteEntityImpl(Entity* entity)
    {
        assert(entity != nullptr);

        auto it = std::find_if(m_Entities.begin(), m_Entities.end(),
            [&](auto ptr){ return ptr.get() == entity; });
        if (it != m_Entities.end())
        {
            m_Components.erase(entity->getId());
            m_Entities.erase(it);
        }
    }
}

