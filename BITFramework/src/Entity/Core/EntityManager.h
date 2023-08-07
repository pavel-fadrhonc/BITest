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
        ~EntityManager() = default;
        
        static EntityManager& Instance() {return *s_Instance;}
        
        std::weak_ptr<Entity> CreateEntity();
        void DeleteEntity(Entity* entity);

        void Update();

        EntityCollection::const_iterator cbegin() const { return m_Entities.cbegin(); }
        EntityCollection::const_iterator cend() const { return m_Entities.cend(); }

        template<typename T>
        std::optional<std::weak_ptr<T>> GetComponent(const Entity& entity)
        {
            if (m_Components.count(entity.getId()) == 0)
                return {};

            for (auto& component : m_Components[entity.getId()])
            {
                if (T* t = dynamic_cast<T*>(component.get()))
                {
                    return {std::weak_ptr<T>(std::dynamic_pointer_cast<T>(component))};
                }
            }

            return {};
        }

        void AddComponent(const Entity& entity, std::shared_ptr<Component> component);
        void RemoveComponent(const Entity& entity, std::shared_ptr<Component> component);

    private:
        EntityManager() = default;

        void DeleteEntityImpl(Entity* entity);
        
        int m_NextEntityId {};
        EntityCollection m_Entities{};
        std::map<int, std::vector<std::shared_ptr<Component>>> m_Components{};

        static std::unique_ptr<EntityManager> s_Instance;
    };
}

