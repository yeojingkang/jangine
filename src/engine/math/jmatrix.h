#ifndef J_MATRIX_H
#define J_MATRIX_H

#include <cassert> // assert
#include <cmath> // std::sin, std::cos
#include <array> // std::array
#include <initializer_list> // std::initializer_list

#include "jtypes.h"
#include "jvec.h"
#include "jmath_consts.h"

// Disable warning for nameless struct/union
#pragma warning(disable:4201)

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

        constexpr Vec<T, M>& operator[](size_t index)
        {
            assert(index < N);
            return col[index];
        }
        constexpr const Vec<T, M>& operator[](size_t index) const
        {
            assert(index < N);
            return col[index];
        }

        constexpr Mat operator-() const
        {
            auto ret = *this;
            for (auto i = 0; i < M * N; ++i)
                ret.data[i] = -ret.data[i];
            return ret;
        }
    };

    template <typename T, size_t M, size_t N>
    Mat<T, M, N> operator+(const Mat<T, M, N>& lhs, const Mat<T, M, N>& rhs)
    {
        auto ret = lhs;
        for (auto i = 0u; i < M * N; ++i)
            ret.data[i] += rhs.data[i];
        return ret;
    }

    template <typename T, size_t M, size_t N>
    Mat<T, M, N> operator-(const Mat<T, M, N>& lhs, const Mat<T, M, N>& rhs) { return lhs + -rhs; }

    template <typename T, size_t M, size_t N, size_t K>
    Mat<T, M, K> operator*(const Mat<T, M, N>& lhs, const Mat<T, N, K>& rhs)
    {
        Mat<T, M, K> ret;
        for (auto i = 0u; i < K; ++i)
            for (auto j = 0u; j < M; ++j)
                for (auto k = 0u; k < N; ++k)
                    ret[i][j] += lhs[k][j] * rhs[i][k];
        return ret;
    }

    template <typename T, size_t M, size_t N>
    Vec<T, M> operator*(const Mat<T, M, N>& lhs, const Vec<T, N>& rhs)
    {
        Vec<T, M> ret;
        for (auto i = 0u; i < M; ++i)
            for (auto j = 0u; j < N; ++j)
                ret[i] += lhs[j][i] * rhs[j];
        return ret;
    }

    template <typename T, size_t M, size_t N>
    Mat<T, M, N> operator*(const Mat<T, M, N>& lhs, const T& rhs)
    {
        auto ret = lhs;
        for (auto i = 0u; i < N; ++i)
            for (auto j = 0; j < M; ++j)
                ret[i][j] *= rhs;
        return ret;
    }

    template <typename T, size_t M, size_t N>
    Mat<T, M, N> operator*(const T& lhs, const Mat<T, M, N>& rhs) { return rhs * lhs; }

    template <typename T, size_t M>
    Mat<T, M, M> Transpose(const Mat<T, M, M>& mat)
    {
        auto transposed = mat;
        for (auto i = 0u; i < M; ++i)
            for (auto j = i + 1; j < M; ++j)
                std::swap(transposed[i][j], transposed[j][i]);
        return transposed;
    }



    template <typename T>
    struct Mat<T, 3, 3>
    {
        union
        {
            struct
            {
                T m00, m10, m20,
                  m01, m11, m21,
                  m02, m12, m22;
            };
            std::array<T, 9> data;
            std::array<Vec<T, 3>, 3> col;
        };

        static constexpr Mat Identity()
        {
            return Mat{
                static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
                static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
                static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
            };
        }
        static constexpr Mat Translation2D(const T& x, const T& y)
        {
            return Mat{
                static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
                static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
                                x,                 y, static_cast<T>(1)
            };
        }
        static constexpr Mat Scale2D(const T& x, const T& y)
        {
            return Mat{
                                x, static_cast<T>(0), static_cast<T>(0),
                static_cast<T>(0),                 y, static_cast<T>(0),
                static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
            };
        }
        static Mat Rotation2D(const T& rad)
        {
            const auto sinRad = std::sin(rad);
            const auto cosRad = std::cos(rad);
            return Mat{
                           cosRad,            sinRad, static_cast<T>(0),
                          -sinRad,            cosRad, static_cast<T>(0),
                static_cast<T>(0), static_cast<T>(0), static_cast<T>(1),
            };
        }

        explicit constexpr Mat() : data{} {}
        explicit constexpr Mat(const T& x0, const T& y0, const T& z0,
                               const T& x1, const T& y1, const T& z1,
                               const T& x2, const T& y2, const T& z2) :
            m00{x0}, m10{y0}, m20{z0},
            m01{x1}, m11{y1}, m21{z1},
            m02{x2}, m12{y2}, m22{z2} {}

        constexpr Vec<T, 3>& operator[](size_t index)
        {
            assert(index < 3);
            return col[index];
        }
        constexpr const Vec<T, 3>& operator[](size_t index) const
        {
            assert(index < 3);
            return col[index];
        }

        constexpr Mat operator-() const
        {
            return Mat{ -m00, -m10, -m20,
                        -m01, -m11, -m21,
                        -m02, -m12, -m22 };
        }
    };

    template <typename T>
    constexpr Mat<T, 3, 3> Transpose(const Mat<T, 3, 3>& mat)
    {
        return Mat<T, 3, 3>{
            mat.m00, mat.m01, mat.m02,
            mat.m10, mat.m11, mat.m12,
            mat.m20, mat.m21, mat.m22
        };
    }

    template <typename T>
    constexpr T Determinant(const Mat<T, 3, 3>& mat)
    {
        return mat.m00 * (mat.m11 * mat.m22 - mat.m12 * mat.m21)
             - mat.m01 * (mat.m10 * mat.m22 - mat.m12 * mat.m20)
             + mat.m02 * (mat.m10 * mat.m21 - mat.m11 * mat.m20);
    }

    template <typename T>
    constexpr Mat<T, 3, 3> Inverse(const Mat<T, 3, 3>& mat)
    {
        const auto det = Determinant(mat);
        assert(std::abs(det) > static_cast<T>(EPSILON_F32));

        /*
         * Each element is the determinant of each minor 2x2 matrix of the transposed matrix
         *
         * | 00 10 20 | Transposed: | 00 01 02 |
         * | 01 11 21 |             | 10 11 12 |
         * | 02 12 22 |             | 20 21 22 |
         *
         * Adjugate matrix:
         * | det|11 12| -det|10 12| det|10 11|  |
         * |    |21 22|     |20 22|    |20 21|  |
         * |                                    |
         * | -det|01 02| det|00 02| -det|00 01| |
         * |     |21 22|    |20 22|     |20 21| |
         * |                                    |
         * | det|01 02| -det|00 02| det|00 01|  |
         * |    |11 12|     |10 12|    |10 11|  |
         */
        Mat<T, 3, 3> ret{
            mat.m11 * mat.m22 - mat.m12 * mat.m21,
            mat.m12 * mat.m20 - mat.m10 * mat.m22,
            mat.m10 * mat.m21 - mat.m11 * mat.m20,

            mat.m02 * mat.m21 - mat.m01 * mat.m22,
            mat.m00 * mat.m22 - mat.m02 * mat.m20,
            mat.m01 * mat.m20 - mat.m00 * mat.m21,

            mat.m01 * mat.m12 - mat.m02 * mat.m11,
            mat.m02 * mat.m10 - mat.m00 * mat.m12,
            mat.m00 * mat.m11 - mat.m01 * mat.m10
        };

        return (static_cast<T>(1) / det) * ret;
    }



    using Mat3f = Mat<f32, 3, 3>;
}


#endif // J_MATRIX_H
