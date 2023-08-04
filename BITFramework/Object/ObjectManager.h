#pragma once

#include "Core/GenericCollection.h"

namespace BITFramework
{
    template<typename T>
    class ObjectManager
    {
    public:
        friend class Entity;
        
        void RegisterObject(const std::shared_ptr<T>& obj)
        {
            m_Objects.Append(obj);
        }

        void UnregisterObject(const std::shared_ptr<T>& obj)
        {
            auto objPos = std::find(m_Objects.begin(), m_Objects.end(),
                [&obj](auto ptr){ return *ptr == *obj; });
            if (objPos != m_Objects.end())
            {
                m_Objects.RemoveFirst(objPos);
            }
        }
        
        ObjectManager(Entity& owningEntity)
            : m_OwningEntity(owningEntity)
        {}
        
        ObjectManager(const ObjectManager& other) = delete;
        ObjectManager& operator=(const ObjectManager& om) = delete;

    protected:
        GenericCollection<std::shared_ptr<T>> m_Objects;
        Entity& m_OwningEntity;
    };
}

