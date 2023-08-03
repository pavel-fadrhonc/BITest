#include "bitpch.h"

#include "vec3.h"

namespace BITFramework
{
    vec3 vec3::operator+(const vec3& vec) const
    {
        return {m_x + vec.m_x, m_y + vec.m_y, m_z + vec.m_z};
    }
}

