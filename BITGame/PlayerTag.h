#pragma once

#include "BITGameCommon.h"

namespace BITGame 
{
    class PlayerTag : public BITFramework::Component
    {
    public:
        PlayerTag(const BITFramework::Entity& entity, const std::string& playerName)
            : Component(entity, std::string{"PlayerTag, playerName:"} + playerName)
        { }

        ~PlayerTag() override = default;
    };
}

