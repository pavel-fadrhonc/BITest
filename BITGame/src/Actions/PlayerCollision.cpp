#include "BITGameCommon.h"

#include "PlayerCollision.h"

#include "Components/DiamondComponent.h"
#include "Components/ExitTagComponent.h"
#include "Components/PlayerComponent.h"
#include "Events/PlayerWonEvent.h"

namespace BITGame
{
    void PlayerCollision::OnCollision(bf::Entity& entity) const
    {
        auto diamond = bf::EntityManager::Instance().GetComponent<DiamondComponent>(entity);
        if (diamond.has_value())
        {
            auto playerComp = bf::EntityManager::Instance().GetComponent<PlayerComponent>(m_Entity);
            if (playerComp.has_value())
                playerComp->lock()->SetHasDiamond(true);
            
            bf::EntityManager::Instance().DeleteEntity(&entity);

            bf::println("You got the diamond!");
        }
        else 
        {
            auto exitComp = bf::EntityManager::Instance().GetComponent<ExitTagComponent>(entity);
            if (exitComp.has_value())
            {
                auto playerComp = bf::EntityManager::Instance().GetComponent<PlayerComponent>(m_Entity);
                if (playerComp.has_value() && playerComp->lock()->HasDiamond())
                    bf::EventDispatcher::Instance().DispatchEvent(PlayerWonEvent{});
            }
        }
    }

    std::ostream& PlayerCollision::print(std::ostream& os) const
    {
        os << "PlayerCollision()";
        
        return os;
    }
}

