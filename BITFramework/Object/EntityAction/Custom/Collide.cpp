#include "bitpch.h"
#include "Collide.h"

#include "ICollisionHandler.h"
#include "Component/Custom/Position.h"
#include "Entity/Core/EntityManager.h"

namespace BITFramework
{
    Collide::Collide(Entity& owningEntity, float collideDistance)
        : EntityAction(owningEntity),
        m_CollideDistance(collideDistance),
        m_CollideDistanceSquared(collideDistance * collideDistance)
    {
        m_Position = EntityManager::Instance().GetComponent<Position>(m_Entity);
    }

    void Collide::Update(float dt)
    {
        const auto& entityManager{EntityManager::Instance()};
        for(auto entityIt = entityManager.cbegin(); entityIt != entityManager.cend(); ++entityIt)
        {
            if (&**entityIt == &m_Entity.get()) // Skip self
                continue;
            
            if (auto pos = EntityManager::Instance().GetComponent<Position>(**entityIt))
            {
                if (m_Position->GetPosVec3().distanceToSquared(pos->GetPosVec3()) < m_CollideDistanceSquared)
                {
                    m_Entity.get().getActionManager().InvokeAll(&ICollisionHandler::OnCollision, std::reference_wrapper(**entityIt));
                }
            }
        }
    }
}

