#ifndef J_VEC_H
#define J_VEC_H

#include <cassert> // assert
#include <cmath> // std::sqrt

namespace jg
{
    template <typename T, size_t N>
    struct Vec
    {
        T data[N];

        explicit constexpr Vec(const T& val = T{})
        {
            for (auto i = 0; i < N; ++i)
                data[i] = val;
        }

        T& operator[](size_t index)
        {
            assert(index < N);
            return data[index];
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
        auto ret = lhs;
        for (auto i = 0; i < N; ++i)
            ret.data[i] -= rhs.data[i];
        return ret;
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
        auto ret = lhs.data[0] * rhs.data[0];
        for (auto i = 0; i < N; ++i)
            ret += lhs.data[i] * rhs.data[i];
        return ret;
    }

    template <typename T, size_t N>
    T LengthSq(const Vec<T, N>& vec) { return Dot(vec, vec); }

    template <typename T, size_t N>
    T Length(const Vec<T, N>& vec) { return std::sqrt(LengthSq(vec)); }

    template <typename T>
    struct Vec<T, 2>
    {
        union
        {
            T data[2];
            struct { T x, y; };
            struct { T u, v; };
        };

        explicit constexpr Vec(const T& val = T{}) : x{ val }, y{ val } {}

        T& operator[](size_t index)
        {
            assert(index < 2);
            return data[index];
        }
    };

    template <typename T>
    struct Vec<T, 3>
    {
        union
        {
            T data[3];
            struct { T x, y, z; };
            struct { T u, v, w; };
            struct { T r, g, b; };
            Vec<T, 2> xy;
            Vec<T, 2> uv;
        };

        explicit constexpr Vec(const T& val = T{}) : x{ val }, y{ val }, z{ val } {}

        T& operator[](size_t index)
        {
            assert(index < 3);
            return data[index];
        }
    };

    template <typename T>
    struct Vec<T, 4>
    {
        union
        {
            T data[4];
            struct { T x, y, z, w; };
            struct { T r, g, b, a; };
            Vec<T, 2> xy;
            Vec<T, 3> xyz;
            Vec<T, 3> rgb;
        };

        explicit constexpr Vec(const T& val = T{}) : x{ val }, y{ val }, z{ val }, w{ val } {}

        T& operator[](size_t index)
        {
            assert(index < 2);
            return data[index];
        }
    };

    // Aliases
    using Vec2f = Vec<float, 2>;
}

#endif // J_VEC_H
