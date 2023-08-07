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
        auto posOpt = EntityManager::Instance().GetComponent<Position>(m_Entity);
        if (posOpt.has_value())
            m_Position = posOpt.value();
    }

    void Collide::Update(float dt)
    {
        const auto& entityManager{EntityManager::Instance()};
        for(auto entityIt = entityManager.cbegin(); entityIt != entityManager.cend(); ++entityIt)
        {
            if (&**entityIt == &m_Entity.get()) // Skip self
                continue;

            auto pos = EntityManager::Instance().GetComponent<Position>(**entityIt);
            if (!pos.has_value())
                continue;
            
            if (m_Position.lock()->GetPosVec3().distanceToSquared(pos.value().lock()->GetPosVec3()) < m_CollideDistanceSquared)
            {
                m_Entity.get().getActionManager().InvokeAll(&ICollisionHandler::OnCollision, std::reference_wrapper(**entityIt));
            }
        }
    }

    std::ostream& Collide::print(std::ostream& os) const
    {
        os << "Collide(CollideDistance:" << m_CollideDistance << ")";

        return os;
    }
}

