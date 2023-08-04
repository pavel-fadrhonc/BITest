#include "../BITGameCommon.h"

#include "Guard.h"
#include "../Events/PlayerLostEvent.h"
#include "../Components/PlayerComponent.h"
#include "../Game.h"

namespace BITGame
{
    namespace bf = BITFramework;
    
    Guard::Guard(
        bf::Entity& owningEntity,
        const bf::vec3& position,
        const std::vector<bf::vec3>& waypoints)
        : EntityAction(owningEntity)
    {
        m_Position = std::make_shared<bf::Position>(m_Entity, position);
        bf::EntityManager::Instance().AddComponent(m_Entity, m_Position);

        m_PatrolComponent = std::make_shared<PatrolComponent>(m_Entity, waypoints);
        m_CurrentWaypoint = m_PatrolComponent->GetWaypoints().cbegin();

        auto direction = *m_CurrentWaypoint - m_Position->GetPosVec3();
        
        m_MoveAction = &Create<bf::MoveInDirection>(m_Entity, direction);
        Create<bf::Collide>(m_Entity, Game::COLLIDE_DISTANCE);
    }

    void Guard::Update(float dt)
    {
        if (m_Position->GetPosVec3().distanceToSquared(*m_CurrentWaypoint) < Game::COLLIDE_DISTANCE_SQ)
        {
            ++m_CurrentWaypoint;
            if (m_CurrentWaypoint == m_PatrolComponent->GetWaypoints().cend())
            {
                m_CurrentWaypoint = m_PatrolComponent->GetWaypoints().cbegin();
            }

            m_MoveAction->SetDirection(*m_CurrentWaypoint - m_Position->GetPosVec3());
        }
    }

    void Guard::OnCollision(BITFramework::Entity& entity) const
    {
        auto playerTag = BITFramework::EntityManager::Instance().GetComponent<PlayerComponent>(entity);
        if (playerTag)
        {
            BITFramework::EventDispatcher::Instance().DispatchEvent(PlayerLostEvent{});
        }
    }
}
