#pragma once

#include <optional>

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
            auto objPos = std::find_if(m_Objects.begin(), m_Objects.end(),
                [&obj](auto ptr){ return ptr.get() == obj.get(); });
            if (objPos != m_Objects.end())
            {
                m_Objects.RemoveFirst(*objPos);
            }
        }

        template
        <typename Tderived>
        std::optional<std::weak_ptr<Tderived>> GetObject()
        {
            auto objIt = std::find_if(m_Objects.begin(), m_Objects.end(),
                [](auto ptr){ return dynamic_cast<Tderived*>(ptr.get()) != nullptr; });
            if (objIt != m_Objects.end())
            {
                auto obj = *objIt;
                return {std::weak_ptr<Tderived>{std::dynamic_pointer_cast<Tderived>(obj)}};
            }

            return {};
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

