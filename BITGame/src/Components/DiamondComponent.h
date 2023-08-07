#pragma once

#include "../BITGameCommon.h"

namespace BITGame 
{
    class DiamondComponent : public bf::Component
    {
    public:
        DiamondComponent(const bf::Entity& owningEntity)
            : Component(owningEntity, "Diamond Component")
        { }

        ~DiamondComponent() override = default;
    };
}
