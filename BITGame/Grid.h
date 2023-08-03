#pragma once

#include "BITGameCommon.h"

class Grid
{
using vec3 = BITFramework::vec3;
    
public:
    Grid(float step, std::pair<vec3, vec3> boundaries)
        : m_Step(step), m_Boundaries(boundaries)
    {
        RefreshGridSize();
    }
    
    void AddEntity(std::weak_ptr<bf::Entity> entity, char sign);
    void Display();
    
    const float& GetStep() { return m_Step; }
    const std::pair<vec3, vec3>& GetBoundaries() { return m_Boundaries; };

    void SetStep(float step) { m_Step = step; RefreshGridSize(); }
    void SetBoundaries(std::pair<vec3, vec3> boundaries) { m_Boundaries = boundaries; RefreshGridSize(); }
    
private:
    bool IsInBounds(const vec3& pos);
    int GetIndex(const vec3& pos);
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
