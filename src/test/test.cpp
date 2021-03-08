#include <iostream>

#include "math/jvec2.h"

int main()
{
    Jangine::Vec2<float> vec;
    std::cout << "Hello world" << std::endl;
    std::cout << vec.x << ", " << vec.y << std::endl;
    vec.x = 10.0f;
    vec.y = -2.0f;
    std::cout << vec.x << ", " << vec.y << std::endl;
}
