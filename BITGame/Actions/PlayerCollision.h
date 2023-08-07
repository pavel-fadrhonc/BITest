#pragma once

#include "../BITGameCommon.h"

namespace BITGame 
{
    class PlayerCollision : public bf::EntityAction, public BITFramework::ICollisionHandler
    {
    public:
        PlayerCollision(bf::Entity& entity)
            : EntityAction(entity)
        { }
        
        void Update(float dt) override {}
        void OnCollision(bf::Entity& entity) const override;

        ~PlayerCollision() override = default;

    protected:
        std::ostream& print(std::ostream& os) const override;
    };

}

