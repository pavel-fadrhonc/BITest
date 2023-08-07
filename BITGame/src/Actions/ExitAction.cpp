#include "ExitAction.h"

#include "../Game.h"
#include "Components/ExitTagComponent.h"

namespace BITGame
{
    ExitAction::ExitAction(bf::Entity& entity, const BITFramework::vec3& position): EntityAction(entity)
    {
        auto pos = std::make_shared<bf::Position>(m_Entity, position);
        bf::EntityManager::Instance().AddComponent(m_Entity, pos);
        auto exitComp = std::make_shared<ExitTagComponent>(m_Entity);
        bf::EntityManager::Instance().AddComponent(m_Entity, exitComp);
    }

    std::ostream& ExitAction::print(std::ostream& os) const
    {
        os << "ExitAction()";

        return os;
    }
}

