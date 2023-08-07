#include "BITGameCommon.h"

#include "Guard.h"
#include "Events/PlayerLostEvent.h"
#include "Components/PlayerComponent.h"
#include "Game.h"

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
        
        Create<bf::MoveInDirection>(m_Entity, direction);
        m_MoveAction = *m_Entity.get().getActionManager().GetObject<bf::MoveInDirection>();
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

            if (!m_MoveAction.expired())
                m_MoveAction.lock()->SetDirection(*m_CurrentWaypoint - m_Position->GetPosVec3());
        }
    }

    void Guard::OnCollision(BITFramework::Entity& entity) const
    {
        auto playerComp = BITFramework::EntityManager::Instance().GetComponent<PlayerComponent>(entity);
        if (playerComp.has_value())
        {
            BITFramework::EventDispatcher::Instance().DispatchEvent(PlayerLostEvent{});
        }
    }

    std::ostream& Guard::print(std::ostream& os) const
    {
        os << "Guard(Position:" << m_Position->GetPosVec3() << ")";

        return os;
    }
}
