#pragma once
#include "../BITGameCommon.h"

namespace BITGame
{
    class Guard : public BITFramework::EntityAction, public BITFramework::ICollisionHandler
    {
    public:
        constexpr static float COLLIDE_DISTANCE = 1.0f;
        
        explicit Guard(
            BITFramework::Entity& owningEntity,
            const BITFramework::vec3& position,
            const BITFramework::vec3& direction);

        void Update(float dt) override;
        void OnCollision(BITFramework::Entity& entity) const override;

    private:
        BITFramework::MoveInDirection* m_MoveAction;
        std::shared_ptr<BITFramework::Position> m_Position;

    };
}
