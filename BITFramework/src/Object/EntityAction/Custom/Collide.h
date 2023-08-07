#pragma once
#include "Component/Custom/Position.h"
#include "Object/EntityAction/Core/EntityAction.h"

namespace BITFramework
{
    using CollisionHandler = std::function<void(Entity& first, Entity& second)>;
    
    class Collide : public EntityAction
    {
    public:
        Collide(Entity& owningEntity, float collideDistance);

        void Update(float dt) override;

        void SetHandler(CollisionHandler* handler) { m_Handler = handler; }

    protected:
        std::ostream& print(std::ostream& os) const override;
        
    private:
        float m_CollideDistance;
        float m_CollideDistanceSquared;
        Position* m_Position;
        CollisionHandler* m_Handler;
    };
}

