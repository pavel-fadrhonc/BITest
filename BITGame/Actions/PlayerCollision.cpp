#include "../BITGameCommon.h"

#include "PlayerCollision.h"
#include "../Components/DiamondComponent.h"
#include "BITGame/Components/PlayerComponent.h"

namespace BITGame
{
    void PlayerCollision::OnCollision(bf::Entity& entity) const
    {
        if (auto diamond = bf::EntityManager::Instance().GetComponent<DiamondComponent>(entity))
        {
            auto playerComp = bf::EntityManager::Instance().GetComponent<PlayerComponent>(m_Entity);
            playerComp->SetHasDiamond(true);
            
            bf::EntityManager::Instance().DeleteEntity(&entity);
        }
    }
    
}

