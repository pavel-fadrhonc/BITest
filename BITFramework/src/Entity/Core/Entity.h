#pragma once

#include "Object/EntityAction/Core/EntityActionManager.h"

namespace BITFramework
{
    class Entity final
    {
    public:
        friend class EntityManager;
        
        Entity(int id);

        int getId() const {return m_Id;}

        friend std::ostream& operator<<(std::ostream& os, const Entity& e);

        EntityActionManager& getActionManager() { return m_ActionManager; }
    
    private:
        int m_Id;
        EntityActionManager m_ActionManager;

        bool m_MarkedForDeletion{false};
    };    
}

