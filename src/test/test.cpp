#include <iostream>

#include "math/jvec.h"

int main()
{
    jg::Vec<int, 5> v3{1};

    std::cout << v3.data[0] << ", " << v3.data[1] << ", " << v3.data[2] << std::endl;

    jg::Vec2f vec;
    std::cout << "Hello world" << std::endl;
    std::cout << vec.x << ", " << vec.y << std::endl;
    vec.x = 10.0f;
    vec.y = -2.0f;
    std::cout << vec.x << ", " << vec.y << std::endl;
    std::cout << jg::LengthSq(vec) << std::endl;
    std::cout << jg::Length(vec) << std::endl;

    jg::Vec2f vec2;
    vec2.x = 5.0f;
    vec2.y = 3.0f;

    std::cout << vec2.x << ", " << vec2.y << std::endl;
    vec2 = vec + vec2;
    std::cout << vec2.x << ", " << vec2.y << std::endl;

    constexpr jg::Vec2f vec3{ 2.0f };
    std::cout << vec3.x << ", " << vec3.y << std::endl;
}
