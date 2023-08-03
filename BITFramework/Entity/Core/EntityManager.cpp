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

    void EntityManager::DeleteEntity(const std::weak_ptr<Entity>& entity)
    {
        if (entity.expired())
            return;

        auto it = std::find(m_Entities.begin(), m_Entities.end(), entity.lock());
        if (it != m_Entities.end())
        {
            m_Components.erase(entity.lock()->getId());
            m_Entities.erase(it);
        }
    }
}

