#pragma once

#include "Entity.h"
#include "Component/Core/Component.h"

namespace BITFramework
{
    class EntityManager
    {
    public:
        using EntityCollection = std::vector<std::shared_ptr<Entity>>;
        
        EntityManager(const EntityManager& other) = delete;
        EntityManager& operator=(const EntityManager& other) = delete;
        EntityManager(EntityManager&& other) = delete;
        EntityManager& operator=(EntityManager&& other) = delete;
        
        static EntityManager& Instance() {return *s_Instance;}
        
        std::weak_ptr<Entity> CreateEntity();
        void DeleteEntity(const std::weak_ptr<Entity>& Entity);

        EntityCollection::const_iterator cbegin() const { return m_Entities.cbegin(); }
        EntityCollection::const_iterator cend() const { return m_Entities.cend(); }

        template<typename T>
        T* GetComponent(const Entity& entity)
        {
            if (m_Components.count(entity.getId()) == 0)
                return nullptr;

            for (auto& component : m_Components[entity.getId()])
            {
                if (T* t = dynamic_cast<T*>(component.get()))
                    return t;
            }

            return nullptr;
        }

        void AddComponent(const Entity& entity, std::shared_ptr<Component> component)
        {
            m_Components[entity.getId()].push_back(component);
        }

    private:
        EntityManager()
        {}
        
        int m_NextEntityId {};
        EntityCollection m_Entities{};
        std::map<int, std::vector<std::shared_ptr<Component>>> m_Components{};

        static std::unique_ptr<EntityManager> s_Instance;
    };
}

