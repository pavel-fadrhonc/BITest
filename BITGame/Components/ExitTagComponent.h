#pragma once

#include "../BITGameCommon.h"

namespace BITGame
{
    class ExitTagComponent : public bf::Component
    {
    public:
        ExitTagComponent(const bf::Entity& entity)
            : Component(entity, "ExitTagComponent")
        { }
        
        ~ExitTagComponent() override = default;
    };
}