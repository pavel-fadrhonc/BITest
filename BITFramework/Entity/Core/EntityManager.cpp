#include "bitpch.h"

#include "EntityManager.h"
#include "Component/Core/Component.h"

namespace BITFramework
{
    // cannot do std::make_unique because constructor is private
    std::unique_ptr<EntityManager> EntityManager::s_Instance = std::unique_ptr<EntityManager>(new EntityManager);
    
    Entity& EntityManager::CreateEntity()
    {
        m_Entities.push_back(std::make_unique<Entity>(m_NextEntityId));
        m_Components.insert({m_NextEntityId, std::vector<std::shared_ptr<Component>>{}});
        ++m_NextEntityId;

        return *m_Entities.back();
    }
}

