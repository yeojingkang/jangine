#ifndef J_MATRIX_H
#define J_MATRIX_H

#include <cassert> // assert
#include <array> // std::array
#include <initializer_list> // std::initializer_list
#include "jvec.h"

namespace jg
{
    template <typename T, size_t M, size_t N>
    struct Mat
    {
        union
        {
            std::array<T, M * N> data;
            std::array<Vec<T, M>, N> col;
        };

        constexpr Mat() : data{} {}
        constexpr Mat(std::initializer_list<T> l)
        {
            assert(l.size() <= M * N);
            std::copy_n(std::begin(l), l.size(), data.data());
            std::fill_n(data.data() + l.size(), M * N - l.size(), T{});
        }

        Vec<T, M>& operator[](size_t index)
        {
            assert(index < N);
            return col[index];
        }
        const Vec<T, M>& operator[](size_t index) const
        {
            assert(index < N);
            return col[index];
        }

        Mat operator-() const
        {
            auto out = *this;
            for (auto i = 0; i < M * N; ++i)
                out.data[i] = -out.data[i];
            return out;
        }
    };

    template <typename T, size_t M, size_t N>
    Mat<T, M, N> operator+(const Mat<T, M, N>& lhs, const Mat<T, M, N>& rhs)
    {
        auto out = lhs;
        for (auto i = 0; i < M * N; ++i)
            out.data[i] += rhs.data[i];
        return out;
    }

    template <typename T, size_t M, size_t N>
    Mat<T, M, N> operator-(const Mat<T, M, N>& lhs, const Mat<T, M, N>& rhs) { return lhs + -rhs; }

    template <typename T, size_t M, size_t N, size_t K>
    Mat<T, M, K> operator*(const Mat<T, M, N>& lhs, const Mat<T, N, K>& rhs)
    {
        Mat<T, M, K> out;
        for (auto i = 0; i < K; ++i)
            for (auto j = 0; j < M; ++j)
                for (auto k = 0; k < N; ++k)
                    out[i][j] += lhs[k][j] * rhs[i][k];
        return out;
    }

    template <typename T, size_t M, size_t N>
    Vec<T, M> operator*(const Mat<T, M, N>& lhs, const Vec<T, N>& rhs)
    {
        Vec<T, M> out;
        for (auto i = 0; i < M; ++i)
            for (auto j = 0; j < N; ++j)
                out[i] += lhs[j][i] * rhs[j];
        return out;
    }

    template <typename T, size_t M>
    Mat<T, M, M> Transpose(const Mat<T, M, M>& mat)
    {
        auto transposed = mat;
        for (auto i = 0; i < M; ++i)
            for (auto j = i + 1; j < M; ++j)
                std::swap(transposed[i][j], transposed[j][i]);
        return transposed;
    }

    template <typename T>
    struct Mat<T, 3, 3>
    {
        union
        {
            std::array<T, 9> data;
            std::array<Vec<T, 3>, 3> col;
        };

        static constexpr Mat<T, 3, 3> Identity()
        {
            return Mat<T, 3, 3>{
                static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
                static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
                static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
            };
        }
        static constexpr Mat<T, 3, 3> Translation(const T& x, const T& y)
        {
            return Mat<T, 3, 3>{
                static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
                static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
                                x,                 y, static_cast<T>(1)
            };
        }
        static constexpr Mat<T, 3, 3> Scale(const T& x, const T& y)
        {
            return Mat<T, 3, 3>{
                                x, static_cast<T>(0), static_cast<T>(0),
                static_cast<T>(0),                 y, static_cast<T>(0),
                static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
            };
        }

        explicit constexpr Mat() : data{} {}
        explicit constexpr Mat(const T& x0, const T& y0, const T& z0,
                               const T& x1, const T& y1, const T& z1,
                               const T& x2, const T& y2, const T& z2) :
            data{ x0, y0, z0,
                  x1, y1, z1,
                  x2, y2, z2 } {}

        Vec<T, 3>& operator[](size_t index)
        {
            assert(index < 3);
            return col[index];
        }
        const Vec<T, 3>& operator[](size_t index) const
        {
            assert(index < 3);
            return col[index];
        }

        Mat<T, 3, 3> operator-() const
        {
            return Mat<T, 3, 3>{ -data[0], -data[1], -data[2],
                                 -data[3], -data[4], -data[5],
                                 -data[6], -data[7], -data[8] };
        }
    };

    template <typename T>
    constexpr Mat<T, 3, 3> Transpose(const Mat<T, 3, 3>& mat)
    {
        return Mat<T, 3, 3>{
            mat.data[0], mat.data[3], mat.data[6],
            mat.data[1], mat.data[4], mat.data[7],
            mat.data[2], mat.data[5], mat.data[8]
        };
    }

    using Mat3f = Mat<float, 3, 3>;
}


#endif // J_MATRIX_H
