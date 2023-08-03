#pragma once
#include "Entity/Core/Entity.h"

namespace BITFramework
{
    class ICollisionHandler
    {
    public:
        virtual void OnCollision(const Entity& entity) const = 0;
        
        virtual ~ICollisionHandler() = default;
    };
}
