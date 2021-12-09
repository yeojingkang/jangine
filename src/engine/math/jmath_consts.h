#ifndef J_MATH_CONSTS_H
#define J_MATH_CONSTS_H

#include <limits>

namespace jg
{
    constexpr auto PI = 3.1415926535f;
    constexpr auto HALF_PI = PI * 0.5f;
    constexpr auto EPSILON = std::numeric_limits<float>::epsilon();
}

#endif // J_MATH_CONSTS_H
