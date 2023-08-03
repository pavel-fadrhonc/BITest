#pragma once
#include "Core/vec3.h"
#include "Object/EntityAction/Core/EntityAction.h"

namespace BITFramework
{
    class MoveInDirection : public EntityAction
    {
    public:
        MoveInDirection(Entity& owningEntity, const vec3& direction);

        void Update(float dt) override;

        void SetDirection(const vec3& direction) { m_Direction = direction; }

    private:
        vec3 m_Direction;
    };
}

