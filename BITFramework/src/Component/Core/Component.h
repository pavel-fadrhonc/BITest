#pragma once
#include "Entity/Core/Entity.h"

namespace BITFramework
{
    class Component
    {
    public:
        Component(const Entity& entity, std::string_view name)
            : m_Entity(entity), m_Name(name)
        { }

        std::string getName() { return m_Name; }
        
        friend std::ostream& operator<<(std::ostream& os, const Component& e);

        virtual ~Component() = 0;

    protected:
        virtual std::ostream& print(std::ostream& os) const;
        
        const Entity& m_Entity;
        std::string m_Name;
    };
}
