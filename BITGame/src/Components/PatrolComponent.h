#pragma once

#include "../BITGameCommon.h"

namespace BITGame
{
    class PatrolComponent : public bf::Component
    {
    public:
        using WaypointCollection = std::vector<bf::vec3>;
        
        PatrolComponent(const bf::Entity& entity, std::vector<bf::vec3> waypoints)
            : Component(entity, "PatrolComponent"), m_Waypoints(std::move(waypoints))
        { }

        const WaypointCollection& GetWaypoints() const { return m_Waypoints; }

    private:
        std::vector<bf::vec3> m_Waypoints;
    };
}

