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
            Vec<T, M> col[N];
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
}


#endif // J_MATRIX_H
