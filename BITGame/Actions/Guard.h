#pragma once

#include "../BITGameCommon.h"
#include "BITGame/Components/PatrolComponent.h"

namespace BITGame
{
    class Guard : public BITFramework::EntityAction, public BITFramework::ICollisionHandler
    {
    public:
        explicit Guard(
            BITFramework::Entity& owningEntity,
            const BITFramework::vec3& position,
            const std::vector<bf::vec3>& waypoints);

        void Update(float dt) override;
        void OnCollision(BITFramework::Entity& entity) const override;

    protected:
        std::ostream& print(std::ostream& os) const override;
        
    private:
        std::weak_ptr<bf::MoveInDirection> m_MoveAction;
        std::shared_ptr<BITFramework::Position> m_Position;
        std::shared_ptr<PatrolComponent> m_PatrolComponent;

        std::vector<bf::vec3>::const_iterator m_CurrentWaypoint;
    };
}
