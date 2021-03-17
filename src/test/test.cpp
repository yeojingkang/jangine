#include "gtest/gtest.h"

#include "jangine.h"

TEST(Math, Vector)
{
    jg::Vec2f v1;
    EXPECT_FLOAT_EQ(v1.x, 0.0f);
    EXPECT_FLOAT_EQ(v1.y, 0.0f);

    jg::Vec2f v2{ 2.0f };
    EXPECT_FLOAT_EQ(v2.x, 2.0f);
    EXPECT_FLOAT_EQ(v2.y, 2.0f);

    jg::Vec2f v3{ 5.0f, -1.0f };
    EXPECT_FLOAT_EQ(v3.x, 5.0f);
    EXPECT_FLOAT_EQ(v3.y, -1.0f);
}
