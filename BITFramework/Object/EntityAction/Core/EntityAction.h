#pragma once
#include "Object/Object.h"
#include "Entity/Core/Entity.h"

namespace BITFramework
{
    class EntityAction : public Object
    {
    public:
        explicit EntityAction(Entity& owningEntity);

        virtual bool CanBeVisible() const {return m_IsVisible;}

        virtual void Update(float dt) = 0;

        template
        <typename T, typename ...Targs>
        static T& Create(Entity& e, Targs... args) { return *(new T(e, args...)); }

    private:
        bool m_IsVisible{true};
    };
}


