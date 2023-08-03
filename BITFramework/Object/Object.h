#pragma once

namespace BITFramework
{
    class Entity;
    
    class Object
    {
    public:
        Object(Entity& owningEntity);
        virtual ~Object() = 0;

    protected:
        std::reference_wrapper<Entity> m_Entity;
    };
}



