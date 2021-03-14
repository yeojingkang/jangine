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
    T LengthSq(const Vec<T, N>& vec)
    {
        auto ret = vec.data[0] * vec.data[0];
        for (auto i = 1; i < N; ++i)
            ret += vec.data[i] * vec.data[i];
        return ret;
    }

    template <typename T, size_t N>
    T Length(const Vec<T, N>& vec)
    {
        return std::sqrt(LengthSq(vec));
    }

    template <typename T>
    struct Vec<T, 2>
    {
        union
        {
            T data[2];
            struct { T x, y; };
            struct { T u, v; };
        };

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
