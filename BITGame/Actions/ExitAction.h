#pragma once

#include "../BITGameCommon.h"

namespace BITGame 
{
    class ExitAction : public bf::EntityAction
    {
    public:
        ExitAction(bf::Entity& entity, const BITFramework::vec3& position);

        void Update(float dt) override {}

    protected:
        std::ostream& print(std::ostream& os) const override;
    };
}

