#ifndef J_VEC2_H
#define J_VEC2_H

#include <cassert> // assert
#include <cmath> // std::sqrt

namespace Jangine
{
    template <typename T>
    class Vec2
    {
    public:
        T x, y;

        Vec2() = default;
        Vec2(T nx, T ny) : x{ nx }, y{ ny } {}

        Vec2& operator+=(const Vec2& rhs) noexcept
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        Vec2& operator-=(const Vec2& rhs) noexcept
        {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        Vec2& operator*=(T rhs) noexcept
        {
            x *= rhs;
            y *= rhs;
            return *this;
        }

        Vec2& operator/=(T rhs) noexcept
        {
            x /= rhs;
            y /= rhs;
            return *this;
        }

        Vec2 operator-() const noexcept { return Vec2{ -x, -y }; }

        T& operator[](const size_t index)
        {
            assert(index < 2);
            return index == 0 ? x : y;
        }

        T LengthSq() const noexcept { return x * x + y * y; }
        T Length() const { return std::sqrt(LengthSq()); }
    };

    template <typename T>
    Vec2<T> operator+(const Vec2<T>& lhs, const Vector2& rhs)
    {
        auto ret = lhs;
        ret += rhs;
        return ret;
    }

    template <typename T>
    Vec2<T> operator-(const Vec2<T>& lhs, const Vector2& rhs) { return lhs + -rhs; }

    template <typename T>
    Vec2<T> operator*(const Vec2<T>& lhs, T rhs)
    {
        auto ret = lhs;
        ret *= rhs;
        return ret;
    }

    template <typename T>
    Vec2<T> operator*(T lhs, const Vec2<T>& rhs) { return rhs * lhs; }

    template <typename T>
    Vec2<T> operator/(const Vec2<T>& lhs, T rhs)
    {
        auto ret = lhs;
        lhs /= rhs;
        return ret;
    }
}

#endif // J_VEC2_H
