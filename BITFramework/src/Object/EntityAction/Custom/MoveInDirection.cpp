#include "bitpch.h"

#include "MoveInDirection.h"
#include "Component/Custom/Position.h"
#include "Core/vec3.h"
#include "Entity/Core/EntityManager.h"
#include "Object/EntityAction/Core/EntityAction.h"

namespace BITFramework
{
    MoveInDirection::MoveInDirection(Entity& owningEntity, const vec3& direction)
        : BITFramework::EntityAction(owningEntity), m_Direction(direction)
    {
        m_Direction.normalize();
    }

    void MoveInDirection::Update(float dt)
    {
        auto pos = EntityManager::Instance().GetComponent<Position>(m_Entity);
        if (pos.has_value())
            pos->lock()->GetPosVec3() += m_Direction * dt;
    }

    std::ostream& MoveInDirection::print(std::ostream& os) const
    {
        os << "MoveInDirection(Direction:" << m_Direction << ")";

        return os;
    }
}

