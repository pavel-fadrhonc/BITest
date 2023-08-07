#pragma once
#include "Component/Custom/Position.h"
#include "Object/EntityAction/Core/EntityAction.h"

namespace BITFramework
{
    class Collide : public EntityAction
    {
    public:
        Collide(Entity& owningEntity, float collideDistance);

        void Update(float dt) override;

    protected:
        std::ostream& print(std::ostream& os) const override;
        
    private:
        float m_CollideDistance;
        float m_CollideDistanceSquared;
        Position* m_Position;
    };
}

