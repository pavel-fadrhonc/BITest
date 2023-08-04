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
        const bf::vec3& direction)
        : EntityAction(owningEntity)
    {
        m_Position = std::make_shared<bf::Position>(m_Entity, position);
        bf::EntityManager::Instance().AddComponent(m_Entity, m_Position);
        m_MoveAction = &Create<bf::MoveInDirection>(m_Entity, direction);
        Create<bf::Collide>(m_Entity, Game::COLLIDE_DISTANCE);
    }

    void Guard::Update(float dt)
    {
        m_MoveAction->Update(dt);

        std::cout << *m_Position << '\n';
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
