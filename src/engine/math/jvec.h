#ifndef J_VEC_H
#define J_VEC_H

#include <cassert> // assert
#include <cmath> // std::sqrt
#include <array> // std::array

#include "jtypes.h"

namespace jg
{
    template <typename T, size_t N>
    struct Vec
    {
        std::array<T, N> data;

        explicit constexpr Vec(const T& val)
        {
            for (auto i = 0; i < N; ++i)
                data[i] = val;
        }

        constexpr T& operator[](size_t index)
        {
            assert(index < N);
            return data[index];
        }
        constexpr const T& operator[](size_t index) const
        {
            assert(index < N);
            return data[index];
        }

        constexpr Vec operator-() const
        {
            auto out = *this;
            for (auto i = 0; i < N; ++i)
                out.data[i] = -out.data[i];
            return out;
        }
    };

    template <typename T, size_t N>
    Vec<T, N> operator+(const Vec<T, N>& lhs, const Vec<T, N>& rhs)
    {
        auto ret = lhs;
        for (auto i = 0; i < N; ++i)
            ret.data[i] += rhs.data[i];
        return ret;
    }

    template <typename T, size_t N>
    Vec<T, N> operator-(const Vec<T, N>& lhs, const Vec<T, N>& rhs)
    {
        return lhs + -rhs;
    }

    template <typename T, size_t N>
    Vec<T, N> operator*(const Vec<T, N>& lhs, const T& rhs)
    {
        auto ret = lhs;
        for (auto i = 0; i < N; ++i)
            ret.data[i] *= rhs;
        return ret;
    }

    template <typename T, size_t N>
    Vec<T, N> operator*(const T& lhs, const Vec<T, N>& rhs)
    {
        return rhs * lhs;
    }

    template <typename T, size_t N>
    Vec<T, N> operator/(const Vec<T, N>& lhs, const T& rhs)
    {
        auto ret = lhs;
        for (auto i = 0; i < N; ++i)
            ret.data[i] /= rhs;
        return ret;
    }

    template <typename T, size_t N>
    T Dot(const Vec<T, N>& lhs, const Vec<T, N>& rhs)
    {
        auto ret = T{};
        for (auto i = 0; i < N; ++i)
            ret += lhs.data[i] * rhs.data[i];
        return ret;
    }

    template <typename T, size_t N>
    T LengthSq(const Vec<T, N>& vec) { return Dot(vec, vec); }

    template <typename T, size_t N>
    T Length(const Vec<T, N>& vec) { return std::sqrt(LengthSq(vec)); }

    template <typename T, size_t N>
    Vec<T, N> Normalize(const Vec<T, N>& vec) { return vec / Length(vec); }



    template <typename T>
    struct Vec<T, 2>
    {
        union
        {
            std::array<T, 2> data;
            struct { T x, y; };
            struct { T u, v; };
        };

        explicit constexpr Vec(const T& val = T{}) : x{ val }, y{ val } {}
        explicit constexpr Vec(const T& nx, const T& ny) : x{ nx }, y{ ny } {}

        constexpr T& operator[](size_t index)
        {
            assert(index < 2);
            return data[index];
        }
        constexpr const T& operator[](size_t index) const
        {
            assert(index < 2);
            return data[index];
        }

        constexpr Vec operator-() const { return Vec{ -x, -y }; }
    };



    template <typename T>
    struct Vec<T, 3>
    {
        union
        {
            std::array<T, 3> data;
            struct { T x, y, z; };
            struct { T u, v, w; };
            struct { T r, g, b; };
            Vec<T, 2> xy;
            Vec<T, 2> uv;
        };

        explicit constexpr Vec(const T& val = T{}) : x{ val }, y{ val }, z{ val } {}
        explicit constexpr Vec(const T& nx, const T& ny, const T& nz) : x{ nx }, y{ ny }, z{ nz } {}

        constexpr T& operator[](size_t index)
        {
            assert(index < 3);
            return data[index];
        }
        constexpr const T& operator[](size_t index) const
        {
            assert(index < 3);
            return data[index];
        }

        constexpr Vec operator-() const { return Vec{ -x, -y, -z }; }
    };

    template <typename T>
    Vec<T, 3> Cross(const Vec<T, 3>& lhs, const Vec<T, 3>& rhs)
    {
        return Vec<T, 3>{
            lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.x * rhs.y - lhs.y * rhs.x
        };
    }



    template <typename T>
    struct Vec<T, 4>
    {
        union
        {
            std::array<T, 4> data;
            struct { T x, y, z, w; };
            struct { T r, g, b, a; };
            Vec<T, 2> xy;
            Vec<T, 3> xyz;
            Vec<T, 3> rgb;
        };

        explicit constexpr Vec(const T& val = T{}) : x{ val }, y{ val }, z{ val }, w{ val } {}
        explicit constexpr Vec(const T& nx, const T& ny, const T& nz, const T& nw) : x{ nx }, y{ ny }, z{ nz }, w{ nw } {}

        constexpr T& operator[](size_t index)
        {
            assert(index < 4);
            return data[index];
        }
        constexpr const T& operator[](size_t index) const
        {
            assert(index < 4);
            return data[index];
        }

        constexpr Vec operator-() const { return Vec{ -x, -y, -z, -w }; }
    };



    // Aliases
    using Vec2f = Vec<f32, 2>;
    using Vec3f = Vec<f32, 3>;
    using Vec4f = Vec<f32, 4>;
}

#endif // J_VEC_H
