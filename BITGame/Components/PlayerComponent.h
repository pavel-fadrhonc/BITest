#pragma once

#include "../BITGameCommon.h"

namespace BITGame 
{
    class PlayerComponent : public BITFramework::Component
    {
    public:
        PlayerComponent(const BITFramework::Entity& entity, const std::string& playerName)
            : Component(entity, std::string{"Player, playerName:"} + playerName)
        { }

        ~PlayerComponent() override = default;

        void SetHasDiamond(bool hasDiamond) { m_HasDiamond = hasDiamond; }

    private:
        bool m_HasDiamond{false};
    };
}

