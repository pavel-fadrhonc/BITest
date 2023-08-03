#include "BITGameCommon.h"

#include "Guard.h"
#include "PlayerLostEvent.h"
#include "PlayerTag.h"

namespace BITGame
{
    namespace bf = BITFramework;
    
    Guard::Guard(
        bf::Entity& owningEntity,
        const bf::vec3& position,
        const bf::vec3& direction)
        : EntityAction(owningEntity)
    {
        m_Position = std::make_shared<bf::Position>(m_Entity, position);
        bf::EntityManager::Instance().AddComponent(m_Entity, m_Position);
        m_MoveAction = &Create<bf::MoveInDirection>(m_Entity, direction);
        Create<bf::Collide>(m_Entity, COLLIDE_DISTANCE);
    }

    void Guard::Update(float dt)
    {
        m_MoveAction->Update(dt);

        std::cout << *m_Position << '\n';
    }

    void Guard::OnCollision(const BITFramework::Entity& entity) const
    {
        auto playerTag = BITFramework::EntityManager::Instance().GetComponent<PlayerTag>(entity);
        if (playerTag)
        {
            BITFramework::EventDispatcher::Instance().DispatchEvent(PlayerLostEvent{});
        }
    }
}
