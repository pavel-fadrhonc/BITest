#include "bitpch.h"

#include "vec3.h"

namespace BITFramework
{
    vec3 vec3::operator+(const vec3& vec) const
    {
        return {m_x + vec.m_x, m_y + vec.m_y, m_z + vec.m_z};
    }

    vec3 vec3::operator-(const vec3& vec) const
    {
        return {m_x - vec.m_x, m_y - vec.m_y, m_z - vec.m_z};
    }

    vec3 vec3::operator*(float scalar) const
    {
        return {m_x * scalar, m_y * scalar, m_z * scalar};
    }

    void vec3::operator+=(const vec3& vec)
    {
        m_x += vec.m_x;
        m_y += vec.m_y;
        m_z += vec.m_z;
    }

    void vec3::operator*=(float scalar)
    {
        m_x *= scalar;
        m_y *= scalar;
        m_z *= scalar;
    }

    bool vec3::operator==(const vec3& vec) const
    {
        using std::abs;
        return  abs(m_x - vec.m_x) < FLOAT_DELTA &&
                abs(m_y - vec.m_y) < FLOAT_DELTA &&
                abs(m_z - vec.m_z) < FLOAT_DELTA;
    }

    void vec3::normalize()
    {
        float length = this->length();
        if (length < FLOAT_DELTA)
            return;
            
        m_x /= length;
        m_y /= length;
        m_z /= length;
    }

    float vec3::length()
    {
        return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
    }

    float vec3::lengthSquared()
    {
        return m_x * m_x + m_y * m_y + m_z * m_z;
    }

    float vec3::distanceTo(const vec3& vec) const
    {
        return std::sqrt(
            vec.m_x - m_x * vec.m_x - m_x +
            vec.m_y - m_y * vec.m_y - m_y +
            vec.m_z - m_z * vec.m_z - m_z);
    }

    float vec3::distanceToSquared(const vec3& vec) const
    {
        return
            (vec.m_x - m_x) * (vec.m_x - m_x) +
            (vec.m_y - m_y) * (vec.m_y - m_y) +
            (vec.m_z - m_z) * (vec.m_z - m_z);
    }
}

