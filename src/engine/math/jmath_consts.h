#ifndef J_MATH_CONSTS_H
#define J_MATH_CONSTS_H

#include <limits>

#include "jtypes.h"

namespace jg
{
    constexpr auto PI = 3.1415926535f;
    constexpr auto HALF_PI = PI * 0.5f;

    template <typename T>
    constexpr T EPSILON = std::numeric_limits<T>::epsilon();
    constexpr auto EPSILON_F32 = EPSILON<f32>;
    constexpr auto EPSILON_F64 = EPSILON<f64>;
}

#endif // J_MATH_CONSTS_H
