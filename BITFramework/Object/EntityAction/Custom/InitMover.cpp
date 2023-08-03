#include "bitpch.h"

#include "InitMover.h"
#include "MoveInDirection.h"
#include "Component/Custom/Position.h"
#include "Core/vec3.h"
#include "Entity/Core/EntityManager.h"
#include "Object/EntityAction/Core/EntityAction.h"

namespace BITFramework
{
    InitMover::InitMover(Entity& owningEntity, const vec3& position, const vec3& direction)
        : BITFramework::EntityAction(owningEntity)
    {
        m_Position = std::make_shared<Position>(m_Entity, position);
        EntityManager::Instance().AddComponent(m_Entity, m_Position);
        m_MoveAction = &Create<MoveInDirection>(m_Entity, direction);
    }

    void InitMover::Update(float dt)
    {
        m_MoveAction->Update(dt);

        //std::cout << *m_Position << '\n';
    }
}

