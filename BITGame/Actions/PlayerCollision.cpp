#include "../BITGameCommon.h"

#include "PlayerCollision.h"

#include "../Components/DiamondComponent.h"
#include "BITGame/Components/ExitTagComponent.h"
#include "BITGame/Components/PlayerComponent.h"
#include "BITGame/Events/PlayerWonEvent.h"

namespace BITGame
{
    void PlayerCollision::OnCollision(bf::Entity& entity) const
    {
        if (auto diamond = bf::EntityManager::Instance().GetComponent<DiamondComponent>(entity))
        {
            auto playerComp = bf::EntityManager::Instance().GetComponent<PlayerComponent>(m_Entity);
            playerComp->SetHasDiamond(true);
            
            bf::EntityManager::Instance().DeleteEntity(&entity);

            bf::println("You got the diamond!");
        }
        else if (auto exitComp = bf::EntityManager::Instance().GetComponent<ExitTagComponent>(entity))
        {
            auto playerComp = bf::EntityManager::Instance().GetComponent<PlayerComponent>(m_Entity);
            if (playerComp->HasDiamond())
                bf::EventDispatcher::Instance().DispatchEvent(PlayerWonEvent{});
        }
    }
    
}

