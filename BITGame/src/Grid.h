#pragma once

#include "BITGameCommon.h"

class Grid
{
using vec3 = BITFramework::vec3;
    
public:
    Grid(float step, const std::pair<vec3, vec3>& boundaries)
        : m_Step(step), m_Boundaries(boundaries)
    {
        RefreshGridSize();
    }
    
    void AddEntity(std::weak_ptr<bf::Entity> entity, char sign);
    void Display();
    
    float GetStep() const { return m_Step; }
    const std::pair<vec3, vec3>& GetBoundaries() const { return m_Boundaries; }

    void SetStep(float step) { m_Step = step; RefreshGridSize(); }
    void SetBoundaries(const std::pair<vec3, vec3>& boundaries) { m_Boundaries = boundaries; RefreshGridSize(); }

    void Update(float dt);
    /**
     * \brief Has to be done after EntityManager::Update() so that we remove entities that were destroyed
     */
    void Cleanup();
    
private:
    bool IsInBounds(const vec3& pos) const;
    int GetIndex(const vec3& pos) const;
    void RefreshGridSize();
    
    std::pair<int, int> m_GridSize;
    
    float m_Step{1.0};
    std::pair<vec3, vec3> m_Boundaries;
    std::vector<
        std::pair<
            std::weak_ptr<
                BITFramework::Entity>,
            char>>
    m_Entities{};
};
