#pragma once

namespace BITFramework
{
    constexpr float FLOAT_DELTA = 0.0001f; // this might fail for sufficiently large numbers for our use case it's fine
    
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
        vec3 operator-(const vec3& vec) const;
        vec3 operator*(float scalar) const;
        void operator+=(const vec3& vec);
        void operator*=(float scalar);
        bool operator==(const vec3& vec) const;

        void normalize();
        float length();
        float lengthSquared();
        float distanceTo(const vec3& vec) const;
        float distanceToSquared(const vec3& vec) const;

    private:
        float m_x, m_y, m_z;
    };
}

