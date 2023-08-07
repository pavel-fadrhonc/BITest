#pragma once
#include "Object/Object.h"
#include "Entity/Core/Entity.h"

namespace BITFramework
{
    class EntityAction : public Object
    {
    public:
        explicit EntityAction(Entity& owningEntity);

        friend std::ostream& operator<<(std::ostream& os, const EntityAction& e);
        
        virtual bool CanBeVisible() const {return m_IsVisible;}
        void SetVisible(bool visible) {m_IsVisible = visible;}

        virtual void Update(float dt) = 0;

        template
        <typename T, typename ...Targs>
        static void Create(Entity& e, Targs... args) { new T(e, args...); }

    private:
        bool m_IsVisible{true};
    };
}


