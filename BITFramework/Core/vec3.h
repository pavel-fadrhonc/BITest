#pragma once

namespace BITFramework
{
    class vec3
    {
    public:
        static vec3 zero() { return {0, 0, 0}; }
        static vec3 one() { return {1, 1, 1}; }
        static vec3 up() { return {0, 1, 0}; }
        static vec3 down() { return {0, -1, 0}; }
        static vec3 left() { return {-1, 0, 0}; }
        static vec3 right() { return {1, 0, 0}; }
    
    public:
        constexpr vec3(float x, float y, float z)
            : m_x(x), m_y(y), m_z(z)
        { }

        float getX() const { return m_x; }
        float getY() const { return m_y; }
        float getZ() const { return m_z; }

        void setX(float x) { m_x = x; }
        void setY(float y) { m_y = y; }
        void setZ(float z) { m_z = z; }

        friend std::ostream& operator<<(std::ostream& os, const vec3& vec)
        {
            os << "vec3(" << vec.m_x << ", " << vec.m_y << ", " << vec.m_z << ")";
            return os;
        }

        vec3 operator+(const vec3& vec) const;

        vec3 operator-(const vec3& vec) const
        {
            return {m_x - vec.m_x, m_y - vec.m_y, m_z - vec.m_z};
        }

        vec3 operator*(float scalar) const
        {
            return {m_x * scalar, m_y * scalar, m_z * scalar};
        }

        void operator+=(const vec3& vec)
        {
            m_x += vec.m_x;
            m_y += vec.m_y;
            m_z += vec.m_z;
        }

        void operator*=(float scalar)
        {
            m_x *= scalar;
            m_y *= scalar;
            m_z *= scalar;
        }

        void normalize()
        {
            float length = this->length();
            m_x /= length;
            m_y /= length;
            m_z /= length;
        }

        float length()
        {
            return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
        }

        float lengthSquared()
        {
            return m_x * m_x + m_y * m_y + m_z * m_z;
        }

        float distanceTo(const vec3& vec) const
        {
            return std::sqrt(
                vec.m_x - m_x * vec.m_x - m_x +
                vec.m_y - m_y * vec.m_y - m_y +
                vec.m_z - m_z * vec.m_z - m_z);
        }

        float distanceToSquared(const vec3& vec) const
        {
            return
                vec.m_x - m_x * vec.m_x - m_x +
                vec.m_y - m_y * vec.m_y - m_y +
                vec.m_z - m_z * vec.m_z - m_z;
        }

    private:
        float m_x, m_y, m_z;
    };
}

