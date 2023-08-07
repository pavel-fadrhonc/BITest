#pragma once
#include "Component/Core/Component.h"
#include "Core/vec3.h"
#include "Entity/Core/Entity.h"

namespace BITFramework
{
    class Position : public Component
    {
    public:
        Position(const Entity& entity, vec3 pos)
            : Component(entity, "Position"), m_Pos(pos)
        {}

        vec3& GetPosVec3() { return m_Pos; }

    protected:
        std::ostream& print(std::ostream& os) const override;

    private:
        vec3 m_Pos;
    };
}

