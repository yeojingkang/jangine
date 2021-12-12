#ifndef J_MATH_H
#define J_MATH_H

#include <type_traits>
#include <cmath>

#include "jvec.h"
#include "jmatrix.h"

namespace jg
{
    template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
    inline constexpr bool FP_EQ(T a, T b) { return std::abs(a - b) < EPSILON<T>; }

    template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
    inline constexpr bool FP_IS_ZERO(T a) { return -EPSILON<T> < a && a < EPSILON<T>; }
}

#endif // J_MATH_H
