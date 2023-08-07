#pragma once

namespace BITFramework
{
    class Entity;
    
    class Object
    {
    public:
        Object(Entity& owningEntity);
        virtual ~Object() = 0;

        friend std::ostream& operator<<(std::ostream& os, const Object& e);

    protected:
        virtual std::ostream& print(std::ostream& os) const = 0;
        
        std::reference_wrapper<Entity> m_Entity;
    };
}



