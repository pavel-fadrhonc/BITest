#pragma once
#include "MoveInDirection.h"
#include "Component/Custom/Position.h"
#include "Core/vec3.h"
#include "Object/EntityAction/Core/EntityAction.h"

namespace BITFramework
{
    class InitMover : public EntityAction
    {
    public:
        InitMover(Entity& owningEntity, const vec3& position, const vec3& direction);

        void Update(float dt) override;

    protected:
        std::ostream& print(std::ostream& os) const override;
        
    private:
        std::weak_ptr<MoveInDirection> m_MoveAction;
        std::shared_ptr<Position> m_Position;
    };
}

