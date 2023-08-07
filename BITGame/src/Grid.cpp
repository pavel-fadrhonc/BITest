﻿#include "BITGameCommon.h"

#include "Grid.h"

#include "Component/Custom/Position.h"
#include "Entity/Core/EntityManager.h"

void Grid::AddEntity(std::weak_ptr<bf::Entity> entity, char sign)
{   
    m_Entities.emplace_back(entity, sign);
}

void Grid::Display()
{
    std::map<int, char> entitySigns{};

    // add records for entities
    for (auto [entity, sign] : m_Entities)
    {
        if (auto pos = BITFramework::EntityManager::Instance().GetComponent<BITFramework::Position>(*entity.lock()))
        {
            if (!IsInBounds(pos->GetPosVec3()))
                continue;

            int index = GetIndex(pos->GetPosVec3());
            entitySigns[index] = sign;
        }
    }

    // print out the whole grid
    for (int y = m_GridSize.second - 1; y >= 0; --y)
    {
        for (int x = 0; x < m_GridSize.first; ++x)
        {
            int index = y * m_GridSize.first + x;
            if (entitySigns.count(index) == 0)
                std::cout << "[ ]";
            else
                std::cout << '[' << entitySigns[index] << ']';
        }
        std::cout << std::endl;
    }
}

int Grid::GetIndex(const vec3& pos)
{
    // converts pos to position in grid and then to index
    auto [gridPosX, gridPosY] = std::make_pair(std::floor(pos.getX() - m_Boundaries.first.getX() / m_Step),
                                  std::floor(pos.getY() - m_Boundaries.first.getY() / m_Step));

    return gridPosY * static_cast<int>(std::floor(m_GridSize.first)) + gridPosX;
}

void Grid::RefreshGridSize()
{
    auto [min, max] = m_Boundaries;
    m_GridSize = { (max.getX() - min.getX()) / m_Step, (max.getY() - min.getY()) / m_Step };
}

void Grid::Update(float dt)
{
    for(auto entity : m_Entities)
    {
        entity.first.lock()->getActionManager().InvokeAll(&bf::EntityAction::Update, dt);
    }
}

void Grid::Cleanup()
{
    for (auto it = m_Entities.begin(); it != m_Entities.end();)
    {
        if (it->first.expired())
            it = m_Entities.erase(it);
        else
            ++it;
    }
}

bool Grid::IsInBounds(const vec3& pos)
{
    return pos.getX() > m_Boundaries.first.getX() && pos.getX() < m_Boundaries.second.getX() &&
           pos.getY() > m_Boundaries.first.getY() && pos.getY() < m_Boundaries.second.getY() &&
           pos.getZ() > m_Boundaries.first.getZ() && pos.getZ() < m_Boundaries.second.getZ();
}